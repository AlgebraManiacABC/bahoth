#include "game.h"

void gameLoop(SDL_Window *w)
{
	bool shouldClose = false;
	while(!shouldClose)
	{
		(void)handleEvents(&shouldClose);
		if(shouldClose) return;

		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(w);
		SDL_Delay(1000/FPS);
	}
}

int handleEvents(bool *shouldClose)
{
	SDL_Event event;
	Uint32 eventCount = 0;
	while(SDL_PollEvent(&event))
	{
		eventCount++;
		switch(event.type)
		{
			case SDL_QUIT:
				(*shouldClose) = true;
				return eventCount;
			default:
				break;
		}
	}
	return eventCount;
}