#!/usr/bin/env python3
import glob, os, io, subprocess, zipfile, struct

def strip_all_versioning(data):
    """
    Нейтрализует DT_VERNEED (0x6ffffffe), DT_VERNEEDNUM (0x6fffffff) и DT_VERSYM (0x6ffffff0)
    в заголовке PT_DYNAMIC. Полностью исключает ошибку verneed[0] в Android Bionic.
    """
    data = bytearray(data)
    if len(data) < 64 or data[:4] != b'\x7fELF':
        return bytes(data)

    e_phoff = struct.unpack('<Q', data[32:40])[0]
    e_phentsize = struct.unpack('<H', data[54:56])[0]
    e_phnum = struct.unpack('<H', data[56:58])[0]

    for i in range(e_phnum):
        p_offset = e_phoff + i * e_phentsize
        p_type = struct.unpack('<I', data[p_offset:p_offset+4])[0]
        if p_type == 2:  # PT_DYNAMIC
            p_fileoff = struct.unpack('<Q', data[p_offset+8:p_offset+16])[0]
            p_filesz = struct.unpack('<Q', data[p_offset+32:p_offset+40])[0]
            for j in range(0, p_filesz, 16):
                tag = struct.unpack('<q', data[p_fileoff+j:p_fileoff+j+8])[0]
                if tag in [0x6ffffffe, 0x6fffffff, 0x6ffffff0]:
                    struct.pack_into('<q', data, p_fileoff+j, 0)
    return bytes(data)

def patch_single_elf(filename, data):
    tmp_path = "tmp_native.so"
    with open(tmp_path, "wb") as f:
        f.write(data)

    try:
        # Заменяем только glibc pthread и libc
        subprocess.run(["patchelf", "--replace-needed", "libpthread.so.0", "libc.so", tmp_path], check=False)
        subprocess.run(["patchelf", "--replace-needed", "libc.so.6", "libc.so", tmp_path], check=False)
        subprocess.run(["patchelf", "--replace-needed", "libm.so.6", "libm.so", tmp_path], check=False)

        # НЕ удаляем ld-linux, libgcc_s и libstdc++ — они предзагружаются VulkanMod!
        with open(tmp_path, "rb") as f:
            data = f.read()

        # Полностью глушим DT_VERNEED и DT_VERSYM
        data = strip_all_versioning(data)
    finally:
        if os.path.exists(tmp_path):
            os.remove(tmp_path)

    return data

def patch_embedded(jar_bytes):
    with zipfile.ZipFile(io.BytesIO(jar_bytes), "r") as in_z:
        out_buf = io.BytesIO()
        with zipfile.ZipFile(out_buf, "w", compression=zipfile.ZIP_DEFLATED) as out_z:
            for item in in_z.infolist():
                data = in_z.read(item.filename)
                if item.filename.endswith(".jar"):
                    data = patch_embedded(data)
                elif item.filename.endswith(".so"):
                    data = patch_single_elf(item.filename, data)
                out_z.writestr(item, data)
        return out_buf.getvalue()

def main():
    jars = glob.glob("build/libs/*.jar")
    print(f"[patch_natives] Found {len(jars)} jars: {jars}")
    for jar in jars:
        print(f"[patch_natives] Patching {jar}...")
        with open(jar, "rb") as f:
            content = f.read()
        patched = patch_embedded(content)
        with open(jar, "wb") as f:
            f.write(patched)
        print(f"[patch_natives] Patched: {jar}")

if __name__ == "__main__":
    main()
