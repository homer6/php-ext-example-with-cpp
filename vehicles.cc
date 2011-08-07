#include "php_vehicles.h"
#include "car.h"

#include <iostream>

using namespace std;

zend_object_handlers car_object_handlers;
zend_class_entry *car_ce;

struct car_object {
    zend_object std;
    Car *car;
};

void car_free_storage(void *object TSRMLS_DC)
{
    car_object *obj = (car_object *)object;

    delete obj->car;

    zend_hash_destroy(obj->std.properties);
    FREE_HASHTABLE(obj->std.properties);

    efree(obj);
}

zend_object_value car_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;

    car_object *obj = (car_object *)emalloc(sizeof(car_object));
    memset(obj, 0, sizeof(car_object));
    obj->std.ce = type;

    ALLOC_HASHTABLE(obj->std.properties);
    zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
    zend_hash_copy(obj->std.properties, &type->default_properties,
        (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, NULL,
        car_free_storage, NULL TSRMLS_CC);
    retval.handlers = &car_object_handlers;

    return retval;
}

PHP_METHOD(Car, __construct)
{
    long maxGear;
    Car *car = NULL;
    zval *object = getThis();

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &maxGear) == FAILURE) {
        RETURN_NULL();
    }

    car = new Car(maxGear);
    car_object *obj = (car_object *)zend_object_store_get_object(object TSRMLS_CC);
    obj->car = car;
}

PHP_METHOD(Car, shift)
{

}

PHP_METHOD(Car, accelerate)
{
    Car *car;
    car_object *obj = (car_object *)zend_object_store_get_object(
        getThis() TSRMLS_CC);
    car = obj->car;
    if (car != NULL) {
        car->accelerate();
    }
}

PHP_METHOD(Car, brake)
{

}

PHP_METHOD(Car, getCurrentSpeed)
{
    Car *car;
    car_object *obj = (car_object *)zend_object_store_get_object(
        getThis() TSRMLS_CC);
    car = obj->car;
    if (car != NULL) {
        RETURN_LONG(car->getCurrentSpeed());
    }
    RETURN_NULL();
}

PHP_METHOD(Car, getCurrentGear)
{

}

function_entry car_methods[] = {
    PHP_ME(Car,  __construct,     NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(Car,  shift,           NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Car,  accelerate,      NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Car,  brake,           NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Car,  getCurrentSpeed, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Car,  getCurrentGear,  NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};


PHP_MINIT_FUNCTION(vehicles)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Car", car_methods);
    car_ce = zend_register_internal_class(&ce TSRMLS_CC);
    car_ce->create_object = car_create_handler;
    memcpy(&car_object_handlers,
        zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    car_object_handlers.clone_obj = NULL;
    return SUCCESS;
}

zend_module_entry vehicles_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_VEHICLES_EXTNAME,
    NULL,        /* Functions */
    PHP_MINIT(vehicles),        /* MINIT */
    NULL,        /* MSHUTDOWN */
    NULL,        /* RINIT */
    NULL,        /* RSHUTDOWN */
    NULL,        /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    PHP_VEHICLES_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_VEHICLES
extern "C" {
ZEND_GET_MODULE(vehicles)
}
#endif
