#ifndef _MACROS_H_
#define _MACROS_H_

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

#define IS_DEBUG_PANIC(statement, file, line) do {} while(1)

#define ASSERT(condition) \
    if (!(condition)) { \
        IS_DEBUG_PANIC("Assertion failed: " #condition, __FILE__, __LINE__); \
    }

#define NORETURN    __attribute__((noreturn))

#endif