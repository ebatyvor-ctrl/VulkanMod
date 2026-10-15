#include <stdlib.h>

void _ZSt20__throw_system_errori(int code) {
    abort();
}

void _ZdlPvm(void* ptr, unsigned long sz) {
    free(ptr);
}

void* _ZTVN10__cxxabiv117__class_type_infoE[8] = {0};
void* _ZTVN10__cxxabiv120__si_class_type_infoE[8] = {0};
