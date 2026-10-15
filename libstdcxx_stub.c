// Complete freestanding bridge for Android Bionic
char* gettext(const char* msgid) { return (char*)msgid; }
char* dgettext(const char* d, const char* m) { return (char*)m; }
char* dcgettext(const char* d, const char* m, int c) { return (char*)m; }
char* textdomain(const char* d) { return (char*)"messages"; }
char* bindtextdomain(const char* d, const char* dir) { return (char*)""; }

int __fprintf_chk(void* fp, int flag, const char* format, ...) { return 0; }
int __printf_chk(int flag, const char* format, ...) { return 0; }
int __snprintf_chk(char* s, unsigned long max, int f, unsigned long sl, const char* fmt, ...) {
    if (s && max > 0) s[0] = '\0';
    return 0;
}
int __vsnprintf_chk(char* s, unsigned long max, int f, unsigned long sl, const char* fmt, void* ap) {
    if (s && max > 0) s[0] = '\0';
    return 0;
}
int vsnprintf(char* s, unsigned long max, const char* fmt, void* ap) {
    if (s && max > 0) s[0] = '\0';
    return 0;
}

void __floatunditf(void) {}
void __trunctfdf2(void) {}
void __gcc_personality_v0(void) {}
void __gxx_personality_v0(void) {}
void _Unwind_Resume(void) {}
int __pthread_key_create(void* key, void* destructor) { return 0; }
void __gmon_start__(void) {}
void _ITM_deregisterTMCloneTable(void) {}
void _ITM_registerTMCloneTable(void) {}
void __cxa_finalize(void* dso) {}

void* _ZTVN10__cxxabiv117__class_type_infoE[32] = {0};
void* _ZTVN10__cxxabiv119__pointer_type_infoE[32] = {0};
void* _ZTVN10__cxxabiv120__function_type_infoE[32] = {0};
void* _ZTVN10__cxxabiv120__si_class_type_infoE[32] = {0};
void* _ZTVN10__cxxabiv121__vmi_class_type_infoE[32] = {0};
