
#ifndef PHP_MYSTEM_H
#define PHP_MYSTEM_H

extern zend_module_entry mystem_module_entry;
#define phpext_mystem_ptr &mystem_module_entry

#define PHP_MYSTEM_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#    define PHP_MYSTEM_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#    define PHP_MYSTEM_API __attribute__ ((visibility("default")))
#else
#    define PHP_MYSTEM_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#if defined(ZTS) && defined(COMPILE_DL_MYSTEM)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif    /* PHP_MYSTEM_H */

