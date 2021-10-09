/**
 * You can use variable arguments on macros with the ... syntax and access its values
 * by using the __VA_ARGS__ macro.
 * The below case use this so it can receive an exta argument for the variable "len".
 * It can also pass types.
 */

// define a "len" variable
#define def_len(type, ...) type len = __VA_ARGS__; 

/**
 * But if you dont pass nothing things will break
 */

// if we use this macro as PRINT("hello")
#define PRINT(format_string, ...) printf(format_string, __VAR_ARGS__);

// then it will evaluate to this:
printf("hello", );

/**
 * The above exmaple will fail, to fix things we can use a syntax for GCC where it
 * can eat traling commas.
 */

// now if we use this macro as PRINT("hello")
#define PRINT(format_string, ...) printf(format_string, ##__VAR_ARGS__);

// then it will evaluate to this:
printf("hello");

// and when using like this: "PRINT("hello %s", "kanye")" it will evaluate to:
printf("hello %s", "kanye");


/** 
 * Sometimes we may need to exclude code if nothing is passed. Taking our first 
 * example we have:
 */

#define def_len(type, ...) type len = __VA_ARGS__; 

// using like this: "def_len(int, 32)", we have:
int len = 32;

// but like this: "def_len(size_t)":
size_t len = ;

// we can fiz this by using __VAR_OPT__(), where eberything inside the paretheses
// will only be included if we pass at least one argument to the variadic

#define def_len(type, ...) type len __VA_OPT__(= __VA_ARGS__); 

// now using it like this: "def_len(size_t)", gives:
size_t len;

// and this: "def_len(float, 320.2)", gives:
float len = 320.2;

/**
 * Since some of this features are compile exlusive we should use them with care.
 * The __VA_OPT__ macro is specially dangerous and can be check at compiled time
 * with this macro:
 */

// if __VA_OPT__ is supported by the toolchain true will be the third argument on PP_THIRD_ARG()
// thus VA_OPT_SUPPORTED will be true 
#define PP_THIRD_ARG(a,b,c,...) c
#define VA_OPT_SUPPORTED_I(...) PP_THIRD_ARG(__VA_OPT__(,),true,false,)
#define VA_OPT_SUPPORTED VA_OPT_SUPPORTED_I(?)


// we can them use a if case to throw an error at compile time
#if !VA_OPT_SUPPORTED
    #error "__VA_OPT__" is not support on your toolchain, give up :( 
#endif
