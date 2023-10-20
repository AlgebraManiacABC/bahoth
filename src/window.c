#include "window.h"
#include "debug.h"

//	What functions needed?
//
//	* Wrap:
//	 - SDL_Init
//	 - SDL_CreateWindow
//	 - SDL_GL_CreateContext
//	 - glewInit

int initWindow(Uint32 SDL_initFlags,
				Uint32 SDL_winFlags,
				const char * winTitle,
				Uint32 win_x, Uint32 win_y, Uint32 win_w, Uint32 win_h,
				SDL_Window ** w, SDL_GLContext * glContext)
{
	int err = EXIT_SUCCESS;
	if( (err = SDL_Init(SDL_initFlags)) )
	{
		variableError = SDL_GetError();
		return ERR_VARIA;
	}

	(*w) = SDL_CreateWindow(winTitle, win_x, win_y, win_w, win_h, SDL_winFlags);
	if(!(*w))
	{
		variableError = SDL_GetError();
		SDL_Quit();
		return ERR_VARIA;
	}

	(*glContext) = SDL_GL_CreateContext(*w);
	if(!(*glContext))
	{
		variableError = SDL_GetError();
		SDL_DestroyWindow((*w));
		SDL_Quit();
		return ERR_VARIA;
	}

	GLenum glewError = glewInit();
	if(glewError != GLEW_OK)
	{
		variableError = glewGetErrorString(glewError);
		SDL_GL_DeleteContext((*glContext));
		SDL_DestroyWindow((*w));
		SDL_Quit();
		return ERR_VARIA;
	}

	return EXIT_SUCCESS;
}