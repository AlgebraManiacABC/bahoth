#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <cglm/cglm.h>
#include <math.h>
#include <time.h>
#include "camera.h"

#define CAMERA_MOVE_LEFT     (1)
#define CAMERA_MOVE_RIGHT    (1<<1)
#define CAMERA_MOVE_FORWARD  (1<<2)
#define CAMERA_MOVE_BACKWARD (1<<3)
#define CAMERA_MOVE_UP       (1<<4)
#define CAMERA_MOVE_DOWN     (1<<5)
#define CAMERA_YAW_LEFT      (1<<6)
#define CAMERA_YAW_RIGHT     (1<<7)
#define CAMERA_PITCH_UP      (1<<8)
#define CAMERA_PITCH_DOWN    (1<<9)

#define MODEL_YAW_POSITIVE   (1<<10)
#define MODEL_YAW_NEGATIVE   (1<<11)
#define MODEL_PITCH_POSITIVE (1<<12)
#define MODEL_PITCH_NEGATIVE (1<<13)
#define MODEL_ROLL_POSITIVE  (1<<14)
#define MODEL_ROLL_NEGATIVE  (1<<15)
#define MODEL_SCALE_UP       (1<<16)
#define MODEL_SCALE_DOWN     (1<<17)

#define LEFT_MOUSE_DOWN      (1<<18)
#define RIGHT_MOUSE_DOWN     (1<<19)

#define FPS (60.0f)
#define CAM_UPS (1.0f)	//	Units per second
#define CAM_UPF (CAM_UPS/FPS)	//	Units per frame

typedef struct tile
{
	float x;
	float z;

}	tile;

extern float tileWidth;
extern GLuint trLoc;
extern vec3 worldUp;

/**
 * Main game loop.
 * 
 * @param w The `SDL_Window *` created with a gl context
 */
void gameLoop(SDL_Window *w);

/**
 * Polls all incoming events through SDL
 * 
 * @param shouldClose Address to a bool which is set if SDL_QUIT (etc) is received
 * @param cam The camera struct, which will be updated depending on movement
 * 
 * @returns The number of events polled 
 */
int handleEvents(bool *shouldClose, camera * cam, Uint32 * buttonsHeld);

#endif