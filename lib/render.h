#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <cglm/cglm.h>
#include "camera.h"
#include "stl.h"

//	What am I rendering? (in a hypothetical renderAll() function)
//
//	* Table (dependent on camera position)
//	 - Tiles (Current floor)
//	  > Need to find placement (where's "center?" - landing, perhaps; Good enough for now)
//	 - Characters, tokens, chips, monsters, etc. (their data should suffice to render outside of tile rendering)
//	 - Inventories (Players' items, etc, that can be seen by others)
//
//	* UI (independent on camera position)
//	 - Character stats
//	 - Any turn counters
//	 - Game time, etc.
//	 - Indicators

void initRenderer(void);

void toggleWireframe(void);

void renderAll(GLuint shaderProgram, camera cam);

void renderTable(GLuint shaderProgram, camera cam);
//===//
void renderTiles(GLuint shaderProgram, camera cam);
	void renderTile(GLuint shaderProgram, camera cam);
void renderPlayerInventories();
void renderTableExtras();

void renderSTL(GLuint shaderProgram, camera cam, STL stl);
//===//

void renderUI();

#endif