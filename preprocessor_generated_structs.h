/**
 * You can generate struct via pattern matching with the C pre processor aswell as
 * functions to use on these custom structs with the X macro technique
 */

/* This whole section under curly brackets should be inside a "generate_struct.h" file to be included later */
{
    // first define help macros 

    // wrapper over primitive_cat to ensure evaluation
    #define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)                                   
    // cat two args
    #define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__
    // to ensure stringify
    #define STRINGFY(x) #x

    // only use the macros if we have defined a nem for the struct and the members. Later we'll see how to invoke
    // the struct, how to use this thing
    #if defined(STRUCT_MEMBERS) && defined(STRUCT_NAME)

    #ifdef __cplusplus 
    extern "C" {
    #endif

    // the struct definition using X macros (https://www.geeksforgeeks.org/x-macros-in-c/)
    typedef struct{
        #define X(type, member) type member;
        STRUCT_MEMBERS
        #undef X
    }STRUCT_NAME;

    // store the offsets for the members to the struct instance base address in a size_t array
    // with name STRUCT_NAME_offsets 
    size_t CAT(STRUCT_NAME, _offsets)[] = (size_t[]){
        #define X(type, member) offsetof(struct_ex_t, member),
        STRUCT_MEMBERS
        #undef X
    };

    // store the members name as string in a char* array
    // with name STRUCT_NAME_names 
    char *CAT(STRUCT_NAME, _names)[] = (char*[]){
        #define X(type, member) #member,
        STRUCT_MEMBERS
        #undef X
    };

    // variable "size_t STRUCT_NAME_members" that stores the quantity of members 
    size_t CAT(STRUCT_NAME, _members) = (
        #define X(type, member) 1 +
        STRUCT_MEMBERS
        #undef X
        0
    );

    // with X macros we can define function to operate on ouer struct, including this function
    // that translates the generated struct to another struct of type "doc" 
    doc *CAT(doc_struct_new_, STRUCT_NAME)(STRUCT_NAME struct_instance){
        doc *doc_struct = doc_new(STRINGFY(STRUCT_NAME), dt_obj, ";");
        #define X(type, member) doc_add(doc_struct, ".", #member, dt_##type, struct_instance.member); 
        STRUCT_MEMBERS
        #undef X

        return doc_struct;
    }

    // this sets the values of doc struct to the generated struct values 
    void CAT(doc_struct_set_, STRUCT_NAME)(STRUCT_NAME struct_instance, doc *doc_struct){
        #define X(type, member) doc_set(doc_struct, #member, type, struct_instance.member); 
        STRUCT_MEMBERS
        #undef X
    }

    // this does the opposite
    void CAT(doc_struct_get_, STRUCT_NAME)(STRUCT_NAME *struct_instance, doc *doc_struct){
        #define X(type, member) struct_instance->member = doc_get(doc_struct, #member, type); 
        STRUCT_MEMBERS
        #undef X
    }

    #ifdef __cplusplus 
    }
    #endif

    #endif
}

/**
 * To use the struct you must do this:
 */

// define name
#define STRUCT_NAME struct_ex_t
// define members with X macro
#define STRUCT_MEMBERS \
    X(int, value1)\
    X(int, value2)\
    X(double, value3)

// finally, include the header file explained above so it can use the macros to generate the code,
// thats how and why we need to separate the macros on a header file
#include "generate_struct.h"

