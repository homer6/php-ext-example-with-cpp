#ifndef PHP_VEHICLES_H
#define PHP_VEHICLES_H

#define PHP_VEHICLES_EXTNAME  "vehicles"
#define PHP_VEHICLES_EXTVER   "0.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif 

extern "C" {
#include "php.h"
}

extern zend_module_entry vehicles_module_entry;
#define phpext_vehicles_ptr &vehicles_module_entry;

#endif /* PHP_VEHICLES_H */
