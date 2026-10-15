// glibc 2.32+ thread flag required by real Ubuntu libstdc++.so.6
char __libc_single_threaded = 0;

// Thread atexit implementation
int __cxa_thread_atexit_impl(void (*func)(void*), void* obj, void* dso_symbol) { return 0; }

// Soft-float quad functions needed by libstdc++.so.6
void __addtf3(void) {}
void __subtf3(void) {}
void __multf3(void) {}
void __divtf3(void) {}
void __eqtf2(void) {}
void __getf2(void) {}
void __letf2(void) {}
void __lttf2(void) {}
void __unordtf2(void) {}
void __fixunstfdi(void) {}
void __floatunditf(void) {}
void __trunctfdf2(void) {}
void __udivti3(void) {}
void __umodti3(void) {}

// glibc FORTIFY_SOURCE dummies for libshaderc.so
int __fprintf_chk(void* fp, int flag, const char* format, ...) { return 0; }
int __printf_chk(int flag, const char* format, ...) { return 0; }
int __snprintf_chk(char* s, unsigned long maxlen, int flag, unsigned long slen, const char* format, ...) {
    if (s && maxlen > 0) s[0] = '\0';
    return 0;
}
int __vsnprintf_chk(char* s, unsigned long maxlen, int flag, unsigned long slen, const char* format, void* ap) {
    if (s && maxlen > 0) s[0] = '\0';
    return 0;
}
int vsnprintf(char* s, unsigned long maxlen, const char* format, void* ap) {
    if (s && maxlen > 0) s[0] = '\0';
    return 0;
}

// Personality & Unwinder
void __gcc_personality_v0(void) {}
void __gxx_personality_v0(void) {}
void _Unwind_Resume(void) {}
void _Unwind_RaiseException(void) {}
void _Unwind_GetLanguageSpecificData(void) {}
void _Unwind_GetRegionStart(void) {}
void _Unwind_GetDataRelBase(void) {}
void _Unwind_GetTextRelBase(void) {}
void _Unwind_SetGR(void) {}
void _Unwind_SetIP(void) {}
void _Unwind_GetIP(void) {}
void _Unwind_GetIPInfo(void) {}
