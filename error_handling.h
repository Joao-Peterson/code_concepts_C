#include <stdlib.h>

/* ----------------------------------------- Private definitions ------------------------------ */

// macro for creating a structure with the value 'err' and name "err"
#define ERR_TO_STRUCT(err)  {err, #err} 

/* ----------------------------------------- Private Enum's ----------------------------------- */

// error codes
typedef enum{
    errno_doc_ok                                                                    =  0,
    errno_doc_not_a_type                                                            = -1,
    errno_doc_overflow_quantity_members_or_name_is_too_big                          = -2,
    errno_doc_value_not_same_type_as_array                                          = -3,
    errno_doc_duplicate_names                                                       = -4,
    errno_doc_null_passed_obj                                                       = -5,
    errno_doc_obj_not_found                                                         = -6,
    errno_doc_name_cointains_illegal_characters_or_missing_semi_colon_terminator    = -7
}errno_doc_code_t;

/* ----------------------------------------- Private Struct's --------------------------------- */

// error struct for ease error handling 
typedef struct{
    errno_doc_code_t code;
    char *msg;
}errno_doc_t;

/* ----------------------------------------- Private Globals -------------------------------- */

// array of structs with the value and names 
const errno_doc_t errno_doc_msg_code_array[] = {
    ERR_TO_STRUCT(errno_doc_ok),
    ERR_TO_STRUCT(errno_doc_not_a_type),
    ERR_TO_STRUCT(errno_doc_overflow_quantity_members_or_name_is_too_big),
    ERR_TO_STRUCT(errno_doc_value_not_same_type_as_array),
    ERR_TO_STRUCT(errno_doc_duplicate_names),
    ERR_TO_STRUCT(errno_doc_null_passed_obj),
    ERR_TO_STRUCT(errno_doc_obj_not_found),
    ERR_TO_STRUCT(errno_doc_name_cointains_illegal_characters_or_missing_semi_colon_terminator)
};

// internal global variable for errors
errno_doc_code_t errno_doc_code_internal = 0;

/* ----------------------------------------- Functions -------------------------------------- */

char *doc_get_error_msg(void){

    char *error_msg = NULL;

    // get errors array size
    size_t esp_doc_msg_code_array_size = sizeof(errno_doc_msg_code_array)/sizeof(errno_doc_msg_code_array[0]);

    // get error name message
    for(int i = 0; i < esp_doc_msg_code_array_size; i++){
        if(errno_doc_msg_code_array[i].code == errno_doc_code_internal)             // compare with internal global variable 'errno_doc_code_internal'
            error_msg = errno_doc_msg_code_array[i].msg;
    }

    // PRINT, any console print code can be inserted here
    // print code ... ex. snprintf()

    return error_msg;
}

// get error code function (internal) 
int __doc_get_error_code(void){
    return errno_doc_code_internal;
}

// macro so the function appears to be a read only variable
#define doc_error_code (__doc_get_error_code())