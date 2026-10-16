#include <stddef.h>

// GNU gettext
char* gettext(const char* m) { return (char*)m; }
char* dgettext(const char* d, const char* m) { return (char*)m; }
char* dcgettext(const char* d, const char* m, int c) { return (char*)m; }
char* textdomain(const char* d) { return (char*)"messages"; }
char* bindtextdomain(const char* d, const char* dir) { return (char*)""; }

// std::nothrow tag
const char _ZSt7nothrow[8] = {0};

extern void* malloc(unsigned long) __attribute__((weak));
extern void free(void*) __attribute__((weak));
static char s_heap[2 * 1024 * 1024];
static unsigned long s_pos = 0;
static void* safe_alloc(unsigned long sz) {
    if (malloc) { void* p = malloc(sz); if (p) return p; }
    unsigned long a = (sz + 15) & ~15UL;
    if (s_pos + a <= sizeof(s_heap)) { void* p = (void*)&s_heap[s_pos]; s_pos += a; return p; }
    return (void*)&s_heap[0];
}

void* _Znwm(unsigned long sz) { return safe_alloc(sz); }
void* _Znam(unsigned long sz) { return safe_alloc(sz); }
void* _ZnwmRKSt9nothrow_t(unsigned long sz, void* tag) { return safe_alloc(sz); }
void* _ZnamRKSt9nothrow_t(unsigned long sz, void* tag) { return safe_alloc(sz); }
void _ZdlPv(void* p) { if (p && free) free(p); }
void _ZdlPvm(void* p, unsigned long sz) { if (p && free) free(p); }
void _ZdaPv(void* p) { if (p && free) free(p); }
void _ZdaPvm(void* p, unsigned long sz) { if (p && free) free(p); }
void _ZdlPvRKSt9nothrow_t(void* p, void* tag) { if (p && free) free(p); }

void __cxa_pure_virtual(void) {}
void __cxa_atexit(void* f, void* a, void* d) {}
void __cxa_finalize(void* d) {}
void __gxx_personality_v0(void) {}
void __gcc_personality_v0(void) {}
void _Unwind_Resume(void) {}

// C++ RTTI
void* _ZTVN10__cxxabiv117__class_type_infoE[32] = {0};
void* _ZTVN10__cxxabiv120__si_class_type_infoE[32] = {0};
void* _ZTVN10__cxxabiv121__vmi_class_type_infoE[32] = {0};
void* _ZTVN10__cxxabiv119__pointer_type_infoE[32] = {0};
void* _ZTVN10__cxxabiv120__function_type_infoE[32] = {0};

// C++ Exceptions
void _ZSt20__throw_system_errori(int code) {}
void _ZSt19__throw_logic_errorPKc(const char* s) {}
void _ZSt20__throw_length_errorPKc(const char* s) {}
void _ZSt20__throw_out_of_rangePKc(const char* s) {}
void _ZSt24__throw_out_of_range_fmtPKcz(const char* s, ...) {}
void _ZSt17__throw_bad_allocv(void) {}
void _ZSt16__throw_bad_castv(void) {}
void _ZSt25__throw_bad_function_callv(void) {}

// VTables & Streams
void* _ZTVSt9basic_iosIcSt11char_traitsIcEE[32] = {0};
void* _ZTVSt15basic_streambufIcSt11char_traitsIcEE[32] = {0};
void* _ZTVSt13basic_filebufIcSt11char_traitsIcEE[32] = {0};
void* _ZTVSt14basic_ofstreamIcSt11char_traitsIcEE[32] = {0};
void* _ZTVNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEEE[32] = {0};
void* _ZTVNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE[32] = {0};
void* _ZTVNSt7__cxx1119basic_ostringstreamIcSt11char_traitsIcESaIcEEE[32] = {0};
void* _ZTVNSt7__cxx1119basic_istringstreamIcSt11char_traitsIcESaIcEEE[32] = {0};

void* _ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE[32] = {0};
void* _ZTTNSt7__cxx1119basic_istringstreamIcSt11char_traitsIcESaIcEEE[32] = {0};
void* _ZTTNSt7__cxx1119basic_ostringstreamIcSt11char_traitsIcESaIcEEE[32] = {0};
void* _ZTTSt14basic_ofstreamIcSt11char_traitsIcEE[32] = {0};

void* _ZSt4cerr[32] = {0};
void* _ZSt4cout[32] = {0};

void _ZNSt8ios_base4InitC1Ev(void* self) {}
void _ZNSt8ios_base4InitD1Ev(void* self) {}
void _ZNSt8ios_baseC2Ev(void* self) {}
void _ZNSt8ios_baseD2Ev(void* self) {}
void _ZNKSt5ctypeIcE13_M_widen_initEv(void* self) {}
void _ZNSt6locale7classicEv(void) {}
void _ZNSt6localeC1Ev(void* self) {}
void _ZNSt6localeD1Ev(void* self) {}

void* _ZNSo3putEc(void* self, char c) { return self; }
void* _ZNSo5flushEv(void* self) { return self; }
void* _ZNSo5writeEPKcl(void* self, const char* s, long n) { return self; }
void* _ZNSo9_M_insertIbEERSoT_(void* self, int b) { return self; }
void* _ZNSo9_M_insertIdEERSoT_(void* self, double d) { return self; }
void* _ZNSo9_M_insertIlEERSoT_(void* self, long l) { return self; }
void* _ZNSo9_M_insertImEERSoT_(void* self, unsigned long m) { return self; }
void* _ZNSolsEi(void* self, int i) { return self; }
void* _ZNSolsEs(void* self, short s) { return self; }
void* _ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(void* self, const char* s, long n) { return self; }
void* _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc(void* self, const char* s) { return self; }

void _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev(void* self) {}
void _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED2Ev(void* self) {}
void _ZNSt13basic_filebufIcSt11char_traitsIcEEC1Ev(void* self) {}
void _ZNSt13basic_filebufIcSt11char_traitsIcEE4openEPKcSt13_Ios_Openmode(void) {}
void _ZNSt13basic_filebufIcSt11char_traitsIcEE5closeEv(void) {}
