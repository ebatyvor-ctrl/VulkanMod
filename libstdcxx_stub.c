// 100% Freestanding Bionic Shim - ZERO external dependencies
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

// GCC soft-fp helpers
void __floatunditf(void) {}
void __trunctfdf2(void) {}

// C++ Exceptions & Memory
void _ZSt20__throw_system_errori(int code) { while (1) {} }
void _ZSt16__throw_bad_castv(void) { while (1) {} }
void _ZSt17__throw_bad_allocv(void) { while (1) {} }
void _ZSt19__throw_logic_errorPKc(const char* s) { while (1) {} }
void _ZSt20__throw_length_errorPKc(const char* s) { while (1) {} }
void _ZSt20__throw_out_of_rangePKc(const char* s) { while (1) {} }
void _ZSt24__throw_out_of_range_fmtPKcz(const char* s, ...) { while (1) {} }
void _ZSt25__throw_bad_function_callv(void) { while (1) {} }

void _ZdlPvm(void* ptr, unsigned long sz) {}
void _ZdlPv(void* ptr) {}
void _ZdaPv(void* ptr) {}
void _ZdlPvRKSt9nothrow_t(void* ptr, void* tag) {}
void* _Znwm(unsigned long sz) { return (void*)0; }
void* _Znam(unsigned long sz) { return (void*)0; }
void* _ZnwmRKSt9nothrow_t(unsigned long sz, void* tag) { return (void*)0; }

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
void __cxa_atexit(void) {}
void __cxa_begin_catch(void) {}
void __cxa_end_catch(void) {}
void __cxa_finalize(void) {}
void __cxa_guard_acquire(void) {}
void __cxa_guard_release(void) {}
void __cxa_rethrow(void) {}
void __cxa_thread_atexit(void) {}

// Standard iostream and locale stubs
void* _ZSt4cerr[32] = {0};
void* _ZSt4cout[32] = {0};
void* _ZSt7nothrow[32] = {0};
void _ZNSt8ios_base4InitC1Ev(void) {}
void _ZNSt8ios_base4InitD1Ev(void) {}
void _ZNSt8ios_baseC2Ev(void) {}
void _ZNSt8ios_baseD2Ev(void) {}
