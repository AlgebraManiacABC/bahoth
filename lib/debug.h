#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint32_t Uint32;

#define ERR_UNDEF (0)
#define ERR_VARIA (1)

extern const char * variableError;

/**
 * Run this function whenever an error appears! Note: Only works for wrapped functions (i.e. functions I have created)
 * This function should theoretically only run once: at the highest level.
 * @param errorCode The error code received/generated 
 * 
 * @returns a string (const char *) describing the error, for use in SDL_Log or fprintf(stderr,...) 
 */
const char * whatHappened(Uint32 errorCode);

#endif