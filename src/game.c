#include "game.h"
#include "render.h"
#include "shaders.h"
#include "camera.h"
#include "stl.h"

GLuint trLoc;
float tileWidth = 1.0f;
vec3 worldUp = {0.0f, 1.0f, 0.0f};

void gameLoop(SDL_Window *w)
{
	int ww, wh;
	SDL_GetWindowSize(w,&ww,&wh);
	float aspectRatio = ww/wh;
	STL teapot = loadSTLFromFile("../teapot.stl");
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CW);
	//glCullFace(GL_BACK);
	GLuint vs = createShader("../src/shaders/transform.vert",GL_VERTEX_SHADER);
	GLuint fs = createShader("../src/shaders/white.frag",GL_FRAGMENT_SHADER);
	GLuint sp = createProgram(2,vs,fs);
	glUseProgram(sp);
	//glClearColor(1.0f,1.0f,1.0f,1.0f);
	trLoc = glGetUniformLocation(sp,"transform");

	camera cam = initCamera(aspectRatio);

	Uint32 buttonsHeld = (0b0);
	bool shouldClose = false;
	while(!shouldClose)
	{
		(void)handleEvents(&shouldClose, &cam, &buttonsHeld);
		if(shouldClose) return;
		moveCamera(&cam,buttonsHeld);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//	Need to send camera position to renderAll eventually
		//renderAll(sp,cam);
		renderSTL(sp,cam,teapot);
		SDL_GL_SwapWindow(w);
		SDL_Delay(1000/FPS);
	}
}

int handleEvents(bool *shouldClose, camera * cam, Uint32 * buttonsHeld)
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
			case SDL_KEYDOWN:
				switch(event.key.keysym.scancode)
				{
					case SDL_SCANCODE_ESCAPE:
						(*shouldClose) = true;
						return eventCount;
					case SDL_SCANCODE_W:
						(*buttonsHeld) |= CAMERA_MOVE_FORWARD;
						break;
					case SDL_SCANCODE_A:
						(*buttonsHeld) |= CAMERA_MOVE_LEFT;
						break;
					case SDL_SCANCODE_S:
						(*buttonsHeld) |= CAMERA_MOVE_BACKWARD;
						break;
					case SDL_SCANCODE_D:
						(*buttonsHeld) |= CAMERA_MOVE_RIGHT;
						break;
					case SDL_SCANCODE_LSHIFT:
						(*buttonsHeld) |= CAMERA_MOVE_DOWN;
						break;
					case SDL_SCANCODE_SPACE:
						(*buttonsHeld) |= CAMERA_MOVE_UP;
						break;
					case SDL_SCANCODE_LEFT:
						(*buttonsHeld) |= CAMERA_YAW_LEFT;
						break;
					case SDL_SCANCODE_RIGHT:
						(*buttonsHeld) |= CAMERA_YAW_RIGHT;
						break;
					case SDL_SCANCODE_UP:
						(*buttonsHeld) |= CAMERA_PITCH_UP;
						break;
					case SDL_SCANCODE_DOWN:
						(*buttonsHeld) |= CAMERA_PITCH_DOWN;
						break;
					default:
						break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.scancode)
				{
					case SDL_SCANCODE_W:
						(*buttonsHeld) &= ~CAMERA_MOVE_FORWARD;
						break;
					case SDL_SCANCODE_A:
						(*buttonsHeld) &= ~CAMERA_MOVE_LEFT;
						break;
					case SDL_SCANCODE_S:
						(*buttonsHeld) &= ~CAMERA_MOVE_BACKWARD;
						break;
					case SDL_SCANCODE_D:
						(*buttonsHeld) &= ~CAMERA_MOVE_RIGHT;
						break;
					case SDL_SCANCODE_LSHIFT:
						(*buttonsHeld) &= ~CAMERA_MOVE_DOWN;
						break;
					case SDL_SCANCODE_SPACE:
						(*buttonsHeld) &= ~CAMERA_MOVE_UP;
						break;
					case SDL_SCANCODE_LEFT:
						(*buttonsHeld) &= ~CAMERA_YAW_LEFT;
						break;
					case SDL_SCANCODE_RIGHT:
						(*buttonsHeld) &= ~CAMERA_YAW_RIGHT;
						break;
					case SDL_SCANCODE_UP:
						(*buttonsHeld) &= ~CAMERA_PITCH_UP;
						break;
					case SDL_SCANCODE_DOWN:
						(*buttonsHeld) &= ~CAMERA_PITCH_DOWN;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
	return eventCount;
}