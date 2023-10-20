#include "main.h"
#include "window.h"
#include "debug.h"

int main(int argc, char *argv[])
{
	Uint32 ww = 800, wh = 640;
	SDL_Window *w = NULL;
	SDL_GLContext glContext;
	Uint32 err;
	err = initWindow(SDL_INIT_EVERYTHING, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL,
				"Hello world!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				ww, wh, &w, &glContext);
	if(err)
	{
		SDL_Log("Error during initialization: %s\n",whatHappened(err));
		return EXIT_FAILURE;
	}
	SDL_Delay(2000);
	return EXIT_SUCCESS;
}