#!/usr/bin/env python3
import glob, os, io, subprocess, zipfile

def patch_single_elf(filename, data):
    tmp_path = "tmp_native.so"
    with open(tmp_path, "wb") as f:
        f.write(data)

    try:
        # Заменяем glibc на системный Bionic
        subprocess.run(["patchelf", "--replace-needed", "libpthread.so.0", "libc.so", tmp_path], check=False)
        subprocess.run(["patchelf", "--replace-needed", "libc.so.6", "libc.so", tmp_path], check=False)
        subprocess.run(["patchelf", "--replace-needed", "libm.so.6", "libm.so", tmp_path], check=False)
        subprocess.run(["patchelf", "--remove-needed", "ld-linux-aarch64.so.1", tmp_path], check=False)

        # НЕ ТРОГАЕМ libgcc_s.so.1 и libstdc++.so.6! Они предзагружены в Vulkan.java

        # Снимаем glibc-версионирование символов
        subprocess.run(["patchelf", "--clear-symbol-version", tmp_path], check=False)

        with open(tmp_path, "rb") as f:
            data = f.read()
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
