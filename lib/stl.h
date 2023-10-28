#ifndef STL_H
#define STL_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <cglm/cglm.h>
#include <GL/glew.h>

#define STL_Y 0
#define STL_X 1
#define STL_Z 2
#define STL_ALL 3

typedef struct STL_triangle
{
	vec3 v1;
	vec3 normal1;
	vec3 v2;
	vec3 normal2;
	vec3 v3;
	vec3 normal3;
	//Uint16 attribByteCount;

}	STL_triangle_s, *STL_triangle, *STL_triangles;

typedef struct STL
{
	Uint32 triangleCount;
	STL_triangles triangles;
	vec3 size;	//	Diffs between max/min x/y/z
	mat4 modelMatrix;
	GLuint vertexBuffer;

}	STL_s, *STL;


STL loadSTLFromFile(const char * filename);

void placeSTL(STL stl, vec3 pos);
void translateSTL(STL stl, vec3 pos);

/**
 * Rotates STL `stl` by yaw, then pitch, then roll, as given in `rot`
 * 
 * @param stl The STL to be rotated
 * @param rot a vec3 containing, in order, yaw, pitch, and roll
 */
void rotateSTL(STL stl, vec3 rot);

void scaleSTLTo(STL stl, Uint32 dir, float value);
void scaleSTLBy(STL stl, Uint32 dir, float value);

void moveSTL(STL stl, Uint32 buttonsHeld, int *x, int *y);

#endif