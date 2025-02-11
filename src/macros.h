#ifndef MACROS_H_
#define MACROS_H_

#include <stdlib.h>

// General purpose macros

#define CAST(t, v) ((t)(v))

#define AS_BIT(i) (1ULL << (i))

#ifdef DEBUG_MODE
// Macros only used when debugging, won't be generated
// when running the engine in release mode to improve
// performance

#define ASSERT(cond, ...)                                                      \
  do {                                                                         \
    if (!(cond)) {                                                             \
      fprintf(stderr, __VA_ARGS__);                                            \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)

#define DEBUG(...)                                                             \
  do {                                                                         \
    fprintf(stdout, "[DEBUG]" __VA_ARGS__);                                    \
  } while (0)

#else

#define ASSERT(cond, ...)

#define DEBUG(...)

#endif // DEBUG_MODE

#endif // MACROS_H_
