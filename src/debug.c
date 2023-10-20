#include "debug.h"

const char * errorMessages[] =
{
	"Unknown error!",
	"Should have checked variableError! Try again!"
};

const char * variableError;

const char * whatHappened(Uint32 errorCode)
{
	if(errorCode == ERR_VARIA)
	{
		return variableError;
	}
	return errorMessages[errorCode];
}