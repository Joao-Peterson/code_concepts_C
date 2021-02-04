#include <stdlib.h>

/* ----------------------------------------- Enum's ----------------------------------------- */

// parameters
typedef enum{
    dt_null,
    dt_obj,
    dt_array,
           
    dt_double,
    dt_float, 
            
    dt_uint,
    dt_uint64,
    dt_uint32,
    dt_uint16,
    dt_uint8,
             
    dt_int,
    dt_int64,
    dt_int32,
    dt_int16,
    dt_int8,   
                 
    dt_bool,  
               
    dt_string, 
    dt_const_string,
              
    dt_bindata,
    dt_const_bindata
}doc_type_t;

// assert macro to be used on asserts and so on
#define IS_DOC_TYPE(type) \
   (((type) == dt_null)             || \
    ((type) == dt_obj)              || \
    ((type) == dt_array)            || \
    ((type) == dt_double)           || \
    ((type) == dt_float)            || \
    ((type) == dt_uint)             || \
    ((type) == dt_uint64)           || \
    ((type) == dt_uint32)           || \
    ((type) == dt_uint16)           || \
    ((type) == dt_uint8)            || \
    ((type) == dt_int)              || \
    ((type) == dt_int64)            || \
    ((type) == dt_int32)            || \
    ((type) == dt_int16)            || \
    ((type) == dt_int8)             || \
    ((type) == dt_bool)             || \
    ((type) == dt_string)           || \
    ((type) == dt_const_string)     || \
    ((type) == dt_bindata)          || \
    ((type) == dt_const_bindata))