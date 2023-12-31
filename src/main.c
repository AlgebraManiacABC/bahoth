#include "main.h"
#include "window.h"
#include "debug.h"
#include "game.h"

int main(int argc, char *argv[])
{
	SDL_Window *w = NULL;
	SDL_GLContext glContext;
	Uint32 err;
	err = initWindow(SDL_INIT_EVERYTHING, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL,
				"STL Tester", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				INITIAL_WINDOW_W, INITIAL_WINDOW_H, &w, &glContext);
	if(err)
	{
		fprintf(stderr,"Error during intialization: %s\n",getError());
		return EXIT_FAILURE;
	}

	gameLoop(w);

	return EXIT_SUCCESS;
}