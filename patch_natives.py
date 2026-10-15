import glob, os, io, subprocess, zipfile, struct

def strip_all_versioning(elf_bytes):
    data = bytearray(elf_bytes)
    if len(data) < 64 or data[:4] != b'\x7fELF' or data[4] != 2:
        return elf_bytes
    e_phoff = struct.unpack('<Q', data[32:40])[0]
    e_phentsize = struct.unpack('<H', data[54:56])[0]
    e_phnum = struct.unpack('<H', data[56:58])[0]
    
    dynamic_offset = 0
    dynamic_size = 0
    for i in range(e_phnum):
        ph = data[e_phoff + i * e_phentsize : e_phoff + (i + 1) * e_phentsize]
        p_type = struct.unpack('<I', ph[0:4])[0]
        if p_type == 2: # PT_DYNAMIC
            dynamic_offset = struct.unpack('<Q', ph[8:16])[0]
            dynamic_size = struct.unpack('<Q', ph[32:40])[0]
            break
            
    if not dynamic_offset:
        return elf_bytes

    versym_offset = 0
    for j in range(0, dynamic_size, 16):
        tag, val = struct.unpack('<QQ', data[dynamic_offset + j : dynamic_offset + j + 16])
        if tag == 0x6ffffff0: # DT_VERSYM
            versym_offset = val
        # Нейтрализуем все теги версионирования glibc:
        # DT_VERSYM (0x6ffffff0), DT_VERDEF (0x6ffffffc), DT_VERDEFNUM (0x6ffffffd),
        # DT_VERNEED (0x6ffffffe), DT_VERNEEDNUM (0x6fffffff)
        if tag in (0x6ffffff0, 0x6ffffffc, 0x6ffffffd, 0x6ffffffe, 0x6fffffff):
            struct.pack_into('<QQ', data, dynamic_offset + j, 0x6ffffdf5, 0)

    # Превращаем все символы в неверсионированные (index = 1), как в Android NDK
    if versym_offset and versym_offset < len(data):
        for k in range(versym_offset, min(len(data) - 2, versym_offset + 8192), 2):
            val = struct.unpack('<H', data[k:k+2])[0]
            if val > 1:
                struct.pack_into('<H', data, k, 1)

    return bytes(data)

def patch_elf_binary(data):
    with open("tmp.so", "wb") as f:
        f.write(data)
    
    # Заменяем libc и libm на нативные Android
    subprocess.run(["patchelf", "--replace-needed", "libc.so.6", "libc.so", "tmp.so"], check=False)
    subprocess.run(["patchelf", "--replace-needed", "libm.so.6", "libm.so", "tmp.so"], check=False)

    with open("tmp.so", "rb") as f:
        patched = f.read()
    if os.path.exists("tmp.so"):
        os.remove("tmp.so")
    
    # Снимаем glibc-версионирование символов
    return strip_all_versioning(patched)

def patch_inner_jar(jar_bytes):
    with zipfile.ZipFile(io.BytesIO(jar_bytes), "r") as in_z:
        out_buf = io.BytesIO()
        with zipfile.ZipFile(out_buf, "w", compression=zipfile.ZIP_DEFLATED) as out_z:
            for item in in_z.infolist():
                data = in_z.read(item.filename)
                if item.filename.endswith(".so"):
                    print("  Patching ELF:", item.filename)
                    data = patch_elf_binary(data)
                out_z.writestr(item, data)
        return out_buf.getvalue()

jars = [j for j in glob.glob("build/libs/*.jar") if not j.endswith("-sources.jar") and not j.endswith("-javadoc.jar")]
print("Found jars to patch:", jars)

for jar_path in jars:
    print("Processing main JAR:", jar_path)
    with zipfile.ZipFile(jar_path, "r") as in_main:
        out_main_buf = io.BytesIO()
        with zipfile.ZipFile(out_main_buf, "w", compression=zipfile.ZIP_DEFLATED) as out_main:
            for item in in_main.infolist():
                data = in_main.read(item.filename)
                if ("natives-linux-arm64" in item.filename or "arm64" in item.filename) and item.filename.endswith(".jar"):
                    print("Patching nested jar:", item.filename)
                    data = patch_inner_jar(data)
                elif item.filename.endswith(".so"):
                    print("Patching direct so in jar:", item.filename)
                    data = patch_elf_binary(data)
                out_main.writestr(item, data)
    with open(jar_path, "wb") as f:
        f.write(out_main_buf.getvalue())
    print("Successfully patched and repacked:", jar_path)
