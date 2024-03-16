#ifdef BUILDING_LIBRARY
#define SYMBOL_EXPORT __attribute__((visibility("default")))
#else
#define SYMBOL_EXPORT
#endif

void SYMBOL_EXPORT shared_library_function();
