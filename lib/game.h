#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <cglm/cglm.h>
#include <time.h>

//typedef struct timespec time_s;

#define FPS (60.0)

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
 * 
 * @returns The number of events polled 
 */
int handleEvents(bool *shouldClose);

#endif