#include <stddef.h>

extern void* malloc(unsigned long) __attribute__((weak));
extern void free(void*) __attribute__((weak));

// Буфер памяти 8 МБ
static char s_heap[8 * 1024 * 1024] __attribute__((aligned(64)));
static unsigned long s_heap_pos = 1024; // отступ от нуля

static void* safe_alloc(unsigned long sz) {
    if (malloc) { void* p = malloc(sz); if (p) return p; }
    unsigned long a = (sz + 15) & ~15UL;
    if (s_heap_pos + a <= sizeof(s_heap)) {
        void* p = (void*)&s_heap[s_heap_pos];
        s_heap_pos += a;
        return p;
    }
    return (void*)&s_heap[1024];
}

void* _Znwm(unsigned long sz) { return safe_alloc(sz); }
void* _Znam(unsigned long sz) { return safe_alloc(sz); }
void* _ZnwmRKSt9nothrow_t(unsigned long sz, void* tag) { return safe_alloc(sz); }
void* _ZnamRKSt9nothrow_t(unsigned long sz, void* tag) { return safe_alloc(sz); }
void _ZdlPv(void* ptr) { if (ptr && free) free(ptr); }
void _ZdlPvm(void* ptr, unsigned long sz) { if (ptr && free) free(ptr); }
void _ZdaPv(void* ptr) { if (ptr && free) free(ptr); }
void _ZdaPvm(void* ptr, unsigned long sz) { if (ptr && free) free(ptr); }
void _ZdlPvRKSt9nothrow_t(void* ptr, void* tag) { if (ptr && free) free(ptr); }

// --- std::string ABI ---
static const char s_empty_str[32] = {0};

const char* _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4dataEv(const void* self) {
    if (!self) return s_empty_str;
    const char* ptr = *(const char* const*)self;
    return ptr ? ptr : s_empty_str;
}
const char* _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5c_strEv(const void* self) {
    return _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4dataEv(self);
}
size_t _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4sizeEv(const void* self) {
    if (!self) return 0;
    return *((const size_t*)self + 1);
}
size_t _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6lengthEv(const void* self) {
    return _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4sizeEv(self);
}
size_t _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE8capacityEv(const void* self) {
    if (!self) return 15;
    return *((const size_t*)self + 2);
}
int _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5emptyEv(const void* self) {
    return _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4sizeEv(self) == 0;
}

// --- Itanium C++ ABI VTables с защитой от смещения -24 (-0x18) ---
// Резервируем 8 слотов ДО точки входа (индекс [8]), чтобы [-3] (-24 байта) читало 0
static void* s_vtable_pool[512] __attribute__((aligned(64))) = {0};

#define DEF_SAFE_VTABLE(name) \
    void* name[64] __attribute__((aligned(64))) = {0}; \
    void* get_##name(void) { return (void*)&name[8]; }

DEF_SAFE_VTABLE(_ZTVSt9basic_iosIcSt11char_traitsIcEE)
DEF_SAFE_VTABLE(_ZTVN10__cxxabiv117__class_type_infoE)
DEF_SAFE_VTABLE(_ZTVN10__cxxabiv119__pointer_type_infoE)
DEF_SAFE_VTABLE(_ZTVN10__cxxabiv120__function_type_infoE)
DEF_SAFE_VTABLE(_ZTVN10__cxxabiv120__si_class_type_infoE)
DEF_SAFE_VTABLE(_ZTVN10__cxxabiv121__vmi_class_type_infoE)
DEF_SAFE_VTABLE(_ZTVNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEEE)
DEF_SAFE_VTABLE(_ZTVNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE)
DEF_SAFE_VTABLE(_ZTVNSt7__cxx1119basic_istringstreamIcSt11char_traitsIcESaIcEEE)
DEF_SAFE_VTABLE(_ZTVNSt7__cxx1119basic_ostringstreamIcSt11char_traitsIcESaIcEEE)
DEF_SAFE_VTABLE(_ZTVSt13basic_filebufIcSt11char_traitsIcEE)
DEF_SAFE_VTABLE(_ZTVSt14basic_ofstreamIcSt11char_traitsIcEE)
DEF_SAFE_VTABLE(_ZTVSt15basic_streambufIcSt11char_traitsIcEE)

void _ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E(void* self, void* sb) {
    if (!self) return;
    // Указываем на индекс [8], чтобы отступ -24 (-0x18) оставался внутри валидного нуля!
    *(void**)self = (void*)&_ZTVSt9basic_iosIcSt11char_traitsIcEE[8];
    void** ptrs = (void**)self;
    ptrs[1] = sb;
}

void _ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate(void* self, int state) {}
void _ZNSt9basic_iosIcSt11char_traitsIcEE5imbueERKSt6locale(void* self, const void* loc) {}

// GNU gettext
char* gettext(const char* m) { return (char*)m; }
char* dgettext(const char* d, const char* m) { return (char*)m; }
char* dcgettext(const char* d, const char* m, int c) { return (char*)m; }
char* textdomain(const char* d) { return (char*)"messages"; }
char* bindtextdomain(const char* d, const char* dir) { return (char*)""; }

// glibc FORTIFY & stdio
int __fprintf_chk(void* fp, int f, const char* fmt, ...) { return 0; }
int __printf_chk(int f, const char* fmt, ...) { return 0; }
int __snprintf_chk(char* s, unsigned long max, int f, unsigned long sl, const char* fmt, ...) { if (s && max > 0) s[0] = 0; return 0; }
int __vsnprintf_chk(char* s, unsigned long max, int f, unsigned long sl, const char* fmt, void* ap) { if (s && max > 0) s[0] = 0; return 0; }
int vsnprintf(char* s, unsigned long max, const char* fmt, void* ap) { if (s && max > 0) s[0] = 0; return 0; }
int snprintf(char* s, unsigned long max, const char* fmt, ...) { if (s && max > 0) s[0] = 0; return 0; }
int sprintf(char* s, const char* fmt, ...) { if (s) s[0] = 0; return 0; }
int printf(const char* fmt, ...) { return 0; }
int fprintf(void* s, const char* fmt, ...) { return 0; }

// GCC soft-fp & Unwind
void __floatunditf(void) {}
void __trunctfdf2(void) {}
void __gcc_personality_v0(void) {}
void __gxx_personality_v0(void) {}
void _Unwind_Resume(void) {}

// Pthread & TM clone
int __pthread_key_create(void* k, void* d) { return 0; }
void __gmon_start__(void) {}
void _ITM_deregisterTMCloneTable(void) {}
void _ITM_registerTMCloneTable(void) {}
void __cxa_finalize(void* dso) {}

// C++ ABI
void __cxa_atexit(void* f, void* a, void* d) {}
void __cxa_begin_catch(void) {}
void __cxa_end_catch(void) {}
void __cxa_guard_acquire(void) {}
void __cxa_guard_release(void) {}
void __cxa_pure_virtual(void) {}
void __cxa_rethrow(void) {}
void __cxa_thread_atexit(void) {}

// Shaderc / stream routines
void _ZNKSt5ctypeIcE13_M_widen_initEv(void) {}
void _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE17find_first_not_ofEPKcmm(void) {}
void _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEPKcmm(void) {}
void _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEcm(void) {}
void _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5rfindEcm(void) {}
void _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7compareEPKc(void) {}
void _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7compareERKS4_(void) {}
void _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7compareEmmPKc(void) {}
void _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7compareEmmRKS4_(void) {}
void _ZNKSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEE3strEv(void) {}
void _ZNKSt8__detail20_Prime_rehash_policy11_M_next_bktEm(void) {}
void _ZNKSt8__detail20_Prime_rehash_policy14_M_need_rehashEmmm(void) {}
void _ZNSi10_M_extractIdEERSiRT_(void) {}
void _ZNSi10_M_extractIfEERSiRT_(void) {}
void _ZNSi10_M_extractIjEERSiRT_(void) {}
void _ZNSi10_M_extractIlEERSiRT_(void) {}
void _ZNSi10_M_extractImEERSiRT_(void) {}
void _ZNSi3getEv(void) {}
void _ZNSi4peekEv(void) {}
void _ZNSi5ungetEv(void) {}
void _ZNSirsERi(void) {}
void _ZNSo3putEc(void) {}
void _ZNSo5flushEv(void) {}
void _ZNSo5writeEPKcl(void) {}
void _ZNSo9_M_insertIbEERSoT_(void) {}
void _ZNSo9_M_insertIdEERSoT_(void) {}
void _ZNSo9_M_insertIlEERSoT_(void) {}
void _ZNSo9_M_insertImEERSoT_(void) {}
void _ZNSolsEi(void) {}
void _ZNSolsEs(void) {}
void _ZNSt12__basic_fileIcED1Ev(void) {}
void _ZNSt13basic_filebufIcSt11char_traitsIcEE4openEPKcSt13_Ios_Openmode(void) {}
void _ZNSt13basic_filebufIcSt11char_traitsIcEE5closeEv(void) {}
void _ZNSt13basic_filebufIcSt11char_traitsIcEEC1Ev(void) {}
void _ZNSt6locale7classicEv(void) {}
void _ZNSt6localeC1Ev(void) {}
void _ZNSt6localeD1Ev(void) {}
void _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm(void) {}
void _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructEmc(void) {}
void _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE14_M_replace_auxEmmmc(void) {}
void _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6appendEPKc(void) {}
void _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6assignEPKc(void) {}
void _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7reserveEm(void) {}
void _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE8_M_eraseEmm(void) {}
void _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_appendEPKcm(void) {}
void _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_assignERKS4_(void) {}
void _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(void) {}
void _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm(void) {}
void _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9push_backEc(void) {}
void _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev(void) {}
void _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEaSEOS4_(void) {}
void _ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEE7_M_syncEPcmm(void) {}
void _ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev(void) {}
void _ZNSt7__cxx1119basic_istringstreamIcSt11char_traitsIcESaIcEED1Ev(void) {}
void _ZNSt7__cxx1119basic_ostringstreamIcSt11char_traitsIcESaIcEEC1Ev(void) {}
void _ZNSt7__cxx1119basic_ostringstreamIcSt11char_traitsIcESaIcEED1Ev(void) {}
void _ZNSt8__detail15_List_node_base11_M_transferEPS0_S1_(void) {}
void _ZNSt8__detail15_List_node_base7_M_hookEPS0_(void) {}
void _ZNSt8__detail15_List_node_base9_M_unhookEv(void) {}
void _ZNSt8ios_base4InitC1Ev(void) {}
void _ZNSt8ios_base4InitD1Ev(void) {}
void _ZNSt8ios_baseC2Ev(void) {}
void _ZNSt8ios_baseD2Ev(void) {}
void _ZSt11_Hash_bytesPKvmm(void) {}
void _ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(void) {}
void _ZSt16__throw_bad_castv(void) {}
void _ZSt17__throw_bad_allocv(void) {}
void _ZSt18_Rb_tree_decrementPSt18_Rb_tree_node_base(void) {}
void _ZSt18_Rb_tree_incrementPKSt18_Rb_tree_node_base(void) {}
void _ZSt18_Rb_tree_incrementPSt18_Rb_tree_node_base(void) {}
void _ZSt19__throw_logic_errorPKc(void) {}
void _ZSt20__throw_length_errorPKc(void) {}
void _ZSt20__throw_out_of_rangePKc(void) {}
void _ZSt20__throw_system_errori(void) {}
void _ZSt24__throw_out_of_range_fmtPKcz(void) {}
void _ZSt25__throw_bad_function_callv(void) {}
void _ZSt28_Rb_tree_rebalance_for_erasePSt18_Rb_tree_node_baseRS_(void) {}
void _ZSt29_Rb_tree_insert_and_rebalancebPSt18_Rb_tree_node_baseS0_RS_(void) {}

void* _ZSt4cerr[32] = {0};
void* _ZSt4cout[32] = {0};
void* _ZSt7nothrow[32] = {0};
void _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc(void) {}
void _ZStrsIcSt11char_traitsIcESaIcEERSt13basic_istreamIT_T0_ES7_RNSt7__cxx1112basic_stringIS4_S5_T1_EE(void) {}

void* _ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE[32] = {0};
void* _ZTTNSt7__cxx1119basic_istringstreamIcSt11char_traitsIcESaIcEEE[32] = {0};
void* _ZTTNSt7__cxx1119basic_ostringstreamIcSt11char_traitsIcESaIcEEE[32] = {0};
void* _ZTTSt14basic_ofstreamIcSt11char_traitsIcEE[32] = {0};

unsigned long _ZGVZN8spvutils8HexFloatINS_10FloatProxyIfEENS_14HexFloatTraitsIS2_EEE31getRoundedNormalizedSignificandINS0_INS1_INS_7Float16EEENS3_IS8_EEEEEENT_9uint_typeENS_15round_directionEPbE17first_rounded_bit = 1;

// Перехват функций shaderc: возвращаем валидный дескриптор без падения
static char s_dummy_compiler[1024] __attribute__((aligned(64)));

void* shaderc_compiler_initialize(void) {
    return (void*)s_dummy_compiler;
}

void shaderc_compiler_release(void* compiler) {}

void* shaderc_compile_options_initialize(void) {
    return (void*)s_dummy_compiler;
}

void shaderc_compile_options_release(void* options) {}
