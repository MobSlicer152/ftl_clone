// Header that includes standard library headers and random definitions

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL2/SDL.h"
#undef main

#include "stb_ds.h"

// Byte
typedef uint8_t byte_t;

// Function name
#ifdef _MSC_VER
#define FTL_FUNCNAME __FUNCSIG__
#elif defined __clang__ || defined __GNUC__
#define FTL_FUNCNAME __PRETTY_FUNCTION__
#else
#define FTL_FUNCNAME __func__
#endif

// Print a message to the console
#define FTL_LOG(...) printf(__VA_ARGS__);

// Debug break
#ifdef _MSC_VER
#define FTL_DEBUGBREAK() __debugbreak()
#elif defined __clang__
#define FTL_DEBUGBREAK() __builtin_debugtrap()
#elif defined __GNUC__
#define FTL_DEBUGBREAK() __builtin_trap()
#else
#define FTL_DEBUGBREAK() \
	while (1)        \
		;
#endif

// Make an arbitrary thing a string literal
#define FTL_STRINGIZE(x) #x
#define FTL_STRINGIZE_EXPAND(x) FTL_STRINGIZE(x)

// Assertion
#define FTL_ASSERT(cond)                                                                                           \
	if (!(cond)) {                                                                                             \
		fprintf(stderr, "Assertion \"" #cond "\" at %s:%d:%s failed\n", __FILE__, __LINE__, FTL_FUNCNAME); \
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Assertion failed",                                 \
					 "Assertion \"" #cond "\" failed at " __FILE__                             \
					 ":" FTL_STRINGIZE_EXPAND(__LINE__),                                       \
					 NULL);                                                                    \
		FTL_DEBUGBREAK();                                                                                  \
	}
