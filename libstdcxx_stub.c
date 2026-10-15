// ==============================================================================
// VulkanMod Android Bionic Master Freestanding Shim (libstdc++.so.6)
// Complete 133-symbol bridge for liblwjgl_vma.so, libshaderc.so & libspvc.so
// ZERO external dependencies (-nostdlib)
// ==============================================================================

// glibc FORTIFY_SOURCE Dummies (needed by libshaderc.so)
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

// Unwind & Personality routines (BOTH gcc and gxx)
void __gcc_personality_v0(void) {}
void __gxx_personality_v0(void) {}
void _Unwind_Resume(void) {}

// Pthread & TM clone helpers
int __pthread_key_create(void* key, void* destructor) { return 0; }
void __gmon_start__(void) {}
void _ITM_deregisterTMCloneTable(void) {}
void _ITM_registerTMCloneTable(void) {}
void __cxa_finalize(void* dso) {}

// C++ Exception handlers & memory allocators
void _ZSt20__throw_system_errori(int code) { while (1) {} }
void _ZSt16__throw_bad_castv(void) { while (1) {} }
void _ZSt17__throw_bad_allocv(void) { while (1) {} }
void _ZSt19__throw_logic_errorPKc(void) { while (1) {} }
void _ZSt20__throw_length_errorPKc(void) { while (1) {} }
void _ZSt20__throw_out_of_rangePKc(void) { while (1) {} }
void _ZSt24__throw_out_of_range_fmtPKcz(void) { while (1) {} }
void _ZSt25__throw_bad_function_callv(void) { while (1) {} }
void _ZdlPvm(void* ptr, unsigned long sz) {}
void _ZdlPv(void* ptr) {}
void _ZdaPv(void* ptr) {}
void _ZdlPvRKSt9nothrow_t(void) {}
void _Znam(void) {}
void _Znwm(void) {}
void _ZnwmRKSt9nothrow_t(void) {}

// ABI runtime
void __cxa_atexit(void) {}
void __cxa_begin_catch(void) {}
void __cxa_end_catch(void) {}
void __cxa_guard_acquire(void) {}
void __cxa_guard_release(void) {}
void __cxa_pure_virtual(void) {}
void __cxa_rethrow(void) {}
void __cxa_thread_atexit(void) {}

// C++ Locale & ctype
void _ZNKSt5ctypeIcE13_M_widen_initEv(void) {}
void _ZNSt6locale7classicEv(void) {}
void _ZNSt6localeC1Ev(void) {}
void _ZNSt6localeD1Ev(void) {}

// C++ basic_string methods
void _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE17find_first_not_ofEPKcmm(void) {}
void _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEPKcmm(void) {}
void _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEcm(void) {}
void _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE5rfindEcm(void) {}
void _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7compareEPKc(void) {}
void _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7compareERKS4_(void) {}
void _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7compareEmmPKc(void) {}
void _ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7compareEmmRKS4_(void) {}
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

// C++ iostream & stringbuf methods
void _ZNKSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEE3strEv(void) {}
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
void _ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEE7_M_syncEPcmm(void) {}
void _ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev(void) {}
void _ZNSt7__cxx1119basic_istringstreamIcSt11char_traitsIcESaIcEED1Ev(void) {}
void _ZNSt7__cxx1119basic_ostringstreamIcSt11char_traitsIcESaIcEEC1Ev(void) {}
void _ZNSt7__cxx1119basic_ostringstreamIcSt11char_traitsIcESaIcEED1Ev(void) {}
void _ZNSt8ios_base4InitC1Ev(void) {}
void _ZNSt8ios_base4InitD1Ev(void) {}
void _ZNSt8ios_baseC2Ev(void) {}
void _ZNSt8ios_baseD2Ev(void) {}
void _ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E(void) {}
void _ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate(void) {}
void _ZNSt9basic_iosIcSt11char_traitsIcEE5imbueERKSt6locale(void) {}
void _ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(void) {}
void _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc(void) {}
void _ZStrsIcSt11char_traitsIcESaIcEERSt13basic_istreamIT_T0_ES7_RNSt7__cxx1112basic_stringIS4_S5_T1_EE(void) {}

// C++ detail / hash / rb_tree helpers
void _ZNKSt8__detail20_Prime_rehash_policy11_M_next_bktEm(void) {}
void _ZNKSt8__detail20_Prime_rehash_policy14_M_need_rehashEmmm(void) {}
void _ZNSt8__detail15_List_node_base11_M_transferEPS0_S1_(void) {}
void _ZNSt8__detail15_List_node_base7_M_hookEPS0_(void) {}
void _ZNSt8__detail15_List_node_base9_M_unhookEv(void) {}
void _ZSt11_Hash_bytesPKvmm(void) {}
void _ZSt18_Rb_tree_decrementPSt18_Rb_tree_node_base(void) {}
void _ZSt18_Rb_tree_incrementPKSt18_Rb_tree_node_base(void) {}
void _ZSt18_Rb_tree_incrementPSt18_Rb_tree_node_base(void) {}
void _ZSt28_Rb_tree_rebalance_for_erasePSt18_Rb_tree_node_baseRS_(void) {}
void _ZSt29_Rb_tree_insert_and_rebalancebPSt18_Rb_tree_node_baseS0_RS_(void) {}

// Global streams
void* _ZSt4cerr[32] = {0};
void* _ZSt4cout[32] = {0};
void* _ZSt7nothrow[32] = {0};

// VTT Tables
void* _ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE[32] = {0};
void* _ZTTNSt7__cxx1119basic_istringstreamIcSt11char_traitsIcESaIcEEE[32] = {0};
void* _ZTTNSt7__cxx1119basic_ostringstreamIcSt11char_traitsIcESaIcEEE[32] = {0};
void* _ZTTSt14basic_ofstreamIcSt11char_traitsIcEE[32] = {0};

// RTTI Tables
void* _ZTVN10__cxxabiv117__class_type_infoE[32] = {0};
void* _ZTVN10__cxxabiv119__pointer_type_infoE[32] = {0};
void* _ZTVN10__cxxabiv120__function_type_infoE[32] = {0};
void* _ZTVN10__cxxabiv120__si_class_type_infoE[32] = {0};
void* _ZTVN10__cxxabiv121__vmi_class_type_infoE[32] = {0};

// Stream & stringbuf vtables (vklyuchaya _ZTVSt9basic_ios...)
void* _ZTVNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEEE[32] = {0};
void* _ZTVNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE[32] = {0};
void* _ZTVNSt7__cxx1119basic_istringstreamIcSt11char_traitsIcESaIcEEE[32] = {0};
void* _ZTVNSt7__cxx1119basic_ostringstreamIcSt11char_traitsIcESaIcEEE[32] = {0};
void* _ZTVSt13basic_filebufIcSt11char_traitsIcEE[32] = {0};
void* _ZTVSt14basic_ofstreamIcSt11char_traitsIcEE[32] = {0};
void* _ZTVSt15basic_streambufIcSt11char_traitsIcEE[32] = {0};
void* _ZTVSt9basic_iosIcSt11char_traitsIcEE[32] = {0};
