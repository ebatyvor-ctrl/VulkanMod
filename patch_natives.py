#!/usr/bin/env python3
import glob, os, io, subprocess, zipfile, struct

def fix_elf_for_android(data):
    data = bytearray(data)
    if len(data) < 64 or data[:4] != b'\x7fELF':
        return bytes(data)

    e_shoff, e_shentsize, e_shnum = struct.unpack('<QxxHH', data[40:50] + data[58:62])
    e_phoff, e_phentsize, e_phnum = struct.unpack('<QxxHH', data[32:42] + data[54:58])

    # 1. Зануляем DT_VERNEED, DT_VERNEEDNUM, DT_VERSYM в PT_DYNAMIC
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

    # 2. Конвертируем STB_GNU_UNIQUE (10) -> STB_GLOBAL (1)
    for i in range(e_shnum):
        offset = e_shoff + i * e_shentsize
        sh_type = struct.unpack('<I', data[offset+4:offset+8])[0]
        if sh_type in [11, 2]:
            sh_offset = struct.unpack('<Q', data[offset+24:offset+32])[0]
            sh_size = struct.unpack('<Q', data[offset+32:offset+40])[0]
            sh_entsize = struct.unpack('<Q', data[offset+56:offset+64])[0]
            if sh_entsize == 0:
                sh_entsize = 24
            for ent in range(0, sh_size, sh_entsize):
                st_info_pos = sh_offset + ent + 4
                if st_info_pos < len(data):
                    st_info = data[st_info_pos]
                    if (st_info >> 4) == 10:  # STB_GNU_UNIQUE
                        data[st_info_pos] = (1 << 4) | (st_info & 0xf)

    return bytes(data)

def patch_single_elf(filename, data):
    tmp_path = "tmp_native.so"
    with open(tmp_path, "wb") as f:
        f.write(data)

    try:
        subprocess.run(["patchelf", "--replace-needed", "libpthread.so.0", "libc.so", tmp_path], check=False)
        subprocess.run(["patchelf", "--replace-needed", "libc.so.6", "libc.so", tmp_path], check=False)
        subprocess.run(["patchelf", "--replace-needed", "libm.so.6", "libm.so", tmp_path], check=False)

        with open(tmp_path, "rb") as f:
            data = f.read()

        data = fix_elf_for_android(data)
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
        print(f"[patch_natives] Done: {jar}")

if __name__ == "__main__":
    main()
