#include "game.h"
#include "render.h"

float tileWidth = 1.0f;

void gameLoop(SDL_Window *w)
{
	bool shouldClose = false;
	while(!shouldClose)
	{
		(void)handleEvents(&shouldClose);
		if(shouldClose) return;

		glClear(GL_COLOR_BUFFER_BIT);
		//	Need to send camera position to renderAll eventually
		renderAll();
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