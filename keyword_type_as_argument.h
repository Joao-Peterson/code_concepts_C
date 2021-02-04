// multi line macro, using '\' to denote line break, '{}' to encapsulate the block  
#define doc_set_string(obj, name, new_string, new_len)      ({              \
    ((doc_string*)get_variable_ptr(obj,name))->string = new_string;         \
    ((doc_string*)get_variable_ptr(obj,name))->len = new_len;               \
})

// simple type macro, '##' concatenates the variable 'type' literal name with adjacent strings
#define doc_get_value(obj, type) (((doc_##type*)__check_obj(obj))->value)

// simple ternary operator to return diferent types
#define doc_get_string(obj) ( (__check_obj(obj)->type == dt_string) ? (char*)(((doc_string*)__check_obj(obj))->string) : (const char*)(((doc_string*)__check_obj(obj))->string) )