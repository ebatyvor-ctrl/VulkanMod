import glob, os, io, subprocess, zipfile

def patch_inner_jar(jar_bytes):
    with zipfile.ZipFile(io.BytesIO(jar_bytes), "r") as in_z:
        out_buf = io.BytesIO()
        with zipfile.ZipFile(out_buf, "w", compression=zipfile.ZIP_DEFLATED) as out_z:
            for item in in_z.infolist():
                data = in_z.read(item.filename)
                if item.filename.endswith(".so"):
                    with open("tmp.so", "wb") as f:
                        f.write(data)
                    subprocess.run(["patchelf", "--replace-needed", "libgcc_s.so.1", "libc.so", "tmp.so"], check=False)
                    subprocess.run(["patchelf", "--replace-needed", "libpthread.so.0", "libc.so", "tmp.so"], check=False)
                    subprocess.run(["patchelf", "--replace-needed", "libc.so.6", "libc.so", "tmp.so"], check=False)
                    subprocess.run(["patchelf", "--replace-needed", "libm.so.6", "libm.so", "tmp.so"], check=False)
                    subprocess.run(["patchelf", "--remove-needed", "ld-linux-aarch64.so.1", "tmp.so"], check=False)
                    with open("tmp.so", "rb") as f:
                        data = f.read()
                    if os.path.exists("tmp.so"):
                        os.remove("tmp.so")
                out_z.writestr(item, data)
        return out_buf.getvalue()

jars = [j for j in glob.glob("build/libs/*.jar") if not j.endswith("-sources.jar") and not j.endswith("-dev.jar")]
print("Found jars to patch:", jars)

for jar_path in jars:
    with zipfile.ZipFile(jar_path, "r") as in_main:
        out_main_buf = io.BytesIO()
        with zipfile.ZipFile(out_main_buf, "w", compression=zipfile.ZIP_DEFLATED) as out_main:
            for item in in_main.infolist():
                data = in_main.read(item.filename)
                if "natives-linux-arm64" in item.filename and item.filename.endswith(".jar"):
                    print("Patching inner jar:", item.filename)
                    data = patch_inner_jar(data)
                out_main.writestr(item, data)
    with open(jar_path, "wb") as f:
        f.write(out_main_buf.getvalue())
    print("Successfully patched and repacked:", jar_path)
