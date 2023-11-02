#include "game.h"
#include "render.h"
#include "shaders.h"
#include "camera.h"
#include "stl.h"
#include "debug.h"

GLuint trLoc;
GLuint mmLoc;
float tileWidth = 1.0f;
vec3 worldUp = {0.0f, 1.0f, 0.0f};

void gameLoop(SDL_Window *w)
{
	int ww, wh;
	SDL_GetWindowSize(w,&ww,&wh);
	const char * STLFilename = "../teapot.stl";
	STL teapot = loadSTLFromFile(STLFilename);
	if(!teapot)
	{
		fprintf(stderr,"Error loading STL %s: %s\n",STLFilename,getError());
		return;
	}
	rotateSTL(teapot,(vec3){0,glm_rad(-90),0});
	initRenderer();
	GLuint sp = createProgram(2,
		createShader("../src/shaders/transform.vert",GL_VERTEX_SHADER),
		createShader("../src/shaders/light.frag",GL_FRAGMENT_SHADER));
	if(!sp)
	{
		fprintf(stderr,"Error creating program: %s\n",getError());
		return;
	}
	glUseProgram(sp);
	//glClearColor(1.0f,1.0f,1.0f,1.0f);
	trLoc = glGetUniformLocation(sp,"transform");
	mmLoc = glGetUniformLocation(sp,"modelMatrix");

	camera cam = initCamera(ww/wh);
	int x, y;

	Uint32 buttonsHeld = (0b0);
	bool shouldClose = false;
	while(!shouldClose)
	{
		(void)handleEvents(&shouldClose, &cam, &buttonsHeld);
		if(shouldClose) return;
		moveCamera(&cam,buttonsHeld);
		moveSTL(teapot,buttonsHeld,&x,&y,ww,wh,cam);

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
					case SDL_SCANCODE_PAGEDOWN:
						(*buttonsHeld) |= MODEL_SCALE_DOWN;
						break;
					case SDL_SCANCODE_PAGEUP:
						(*buttonsHeld) |= MODEL_SCALE_UP;
						break;
					case SDL_SCANCODE_RETURN:
						toggleWireframe();
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
					case SDL_SCANCODE_PAGEDOWN:
						(*buttonsHeld) &= ~MODEL_SCALE_DOWN;
						break;
					case SDL_SCANCODE_PAGEUP:
						(*buttonsHeld) &= ~MODEL_SCALE_UP;
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