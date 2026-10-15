static char dummy[512] = {0};
void* shaderc_compiler_initialize(void) { return (void*)dummy; }
void shaderc_compiler_release(void* c) {}
void* shaderc_compile_options_initialize(void) { return (void*)dummy; }
void shaderc_compile_options_release(void* o) {}
void shaderc_compile_options_set_source_language(void* o, int l) {}
void shaderc_compile_options_set_optimization_level(void* o, int l) {}
void* shaderc_compile_into_spv(void* c, const char* s, unsigned long sz, int k, const char* n, const char* e, void* o) { return (void*)dummy; }
int shaderc_result_get_compilation_status(void* r) { return 0; }
unsigned long shaderc_result_get_length(void* r) { return 0; }
const char* shaderc_result_get_bytes(void* r) { return ""; }
void shaderc_result_release(void* r) {}
