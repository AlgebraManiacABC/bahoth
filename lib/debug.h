#ifndef DEBUG_H
#define DEBUG_H

#include "windows_compat.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
typedef uint32_t Uint32;

//	New process to handle errors:
//
//	When an error occurs, no matter where (except for main or main loops), use `setError(errorCode)`.
//	The parent function has two options. If in a "printable" function (such as main or main loops), use getError() to retrieve a string explaining the error.
//	If the parent function is an intermediate function, it must pass the error further upward. This is easily done by just returning an erroroneous value.
//	In theory, the intermediate function will not have to use setError unless the child function does not.
//
//	How is this all done?
//
//	the setError "family" can receive either an errorCode (for common errors with repeatable strings) or a formatted string defining the error.
//	These functions shall be setErrorCode and setErrorMessage respectively. Alternatively, a variadic function could be used as follows:
//	setError(ERR_SETCODE,errorCode) || setError(ERR_SETMESG,errorMesg (formatted),...)
//	which would allow for a rudimentary form of "overloading."
//
//	getError() requires no parameters. It always returns a string. In case of setErrorCode, the underlying error string is set to a predetermined error
//	message which corresponds to the errorCode. This message is then returned from getError().
//	For setErrorMesg, the formatted string is filled depending on the contained format specifiers (printf-style), which will be returned by getError().

#define ERR_UNDEF (0)
#define ERR_NOFIL (1)
#define ERR_SHADE (2)
#define ERR_NULLP (3)
#define ERR_NOMEM (4)

typedef bool errType;
#define ERR_CODE (false)
#define ERR_MESG (true)

extern const char * errorMessages[];
extern const char * variableError;
extern char * editableError;
extern Uint32 lastErrorCode;

/**
 * Sets the error message to either a predefined error string (`ERR_CODE`) or a custom,
 * printf-style formatted string (`ERR_MESG`). The next argument is either the error code
 * or the formatted string (which would then be followed by any necessary matching variables)
 * 
 * @param type 
 * @param ... 
 */
void setError(errType type, ...);

/**
 * Gets the most current error string set by setError().
 * Please use as soon as an error is detected,
 * otherwise the error message may get stale.
 * 
 * @returns the error string as a const char *
 */
const char * getError(void);

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam );

#endif