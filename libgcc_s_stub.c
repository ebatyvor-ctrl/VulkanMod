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
void __floatunditf(void) {}
void __trunctfdf2(void) {}

void __gcc_personality_v0(void) {}
void __gxx_personality_v0(void) {}
void _Unwind_Resume(void) {}
