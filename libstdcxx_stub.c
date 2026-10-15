#include <stddef.h>
#include <stdarg.h>

extern int vprintf(const char *format, va_list ap);
extern int vfprintf(void *stream, const char *format, va_list ap);
extern int vsnprintf(char *str, size_t size, const char *format, va_list ap);

// glibc FORTIFY_SOURCE (необходимы для libshaderc.so)
int __fprintf_chk(void* fp, int flag, const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    int ret = vfprintf(fp, format, ap);
    va_end(ap);
    return ret;
}

int __printf_chk(int flag, const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    int ret = vprintf(format, ap);
    va_end(ap);
    return ret;
}

int __snprintf_chk(char* s, unsigned long maxlen, int flag, unsigned long slen, const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    int ret = vsnprintf(s, maxlen, format, ap);
    va_end(ap);
    return ret;
}

int __vsnprintf_chk(char* s, unsigned long maxlen, int flag, unsigned long slen, const char* format, va_list ap) {
    return vsnprintf(s, maxlen, format, ap);
}

// GCC soft-fp helpers
void __floatunditf(void) {}
void __trunctfdf2(void) {}

// C++ Exceptions & Memory
void _ZSt20__throw_system_errori(int code) { while (1) {} }
void _ZdlPvm(void* ptr, unsigned long sz) {}
void _ZdlPv(void* ptr) {}
void _ZdaPv(void* ptr) {}

// C++ RTTI vtables
void* _ZTVN10__cxxabiv117__class_type_infoE[32] = {0};
void* _ZTVN10__cxxabiv119__pointer_type_infoE[32] = {0};
void* _ZTVN10__cxxabiv120__function_type_infoE[32] = {0};
void* _ZTVN10__cxxabiv120__si_class_type_infoE[32] = {0};
void* _ZTVN10__cxxabiv121__vmi_class_type_infoE[32] = {0};

// C++ ABI hooks
void __cxa_pure_virtual(void) { while (1) {} }
void __gxx_personality_v0(void) {}
void __gmon_start__(void) {}
void _ITM_deregisterTMCloneTable(void) {}
void _ITM_registerTMCloneTable(void) {}
