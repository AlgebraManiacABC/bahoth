#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>

typedef uint32_t Uint32;

typedef struct camera
{
	float x;
	float y;
	float z;
	vec3 pos;
	float yaw;	// Yaw in radians (rotation about y axis - 0==2pi is facing -z)
	float pitch;// Pitch in radians (looking up/down - 0 is along xz-plane ("horizon"); -pi/2 <= pitch <= pi/2)
	float ar;

}	camera;

camera initCamera(float aspectRatio);

void getViewMatrix(camera cam, mat4 viewMatrix);
void getProjectionMatrix(camera cam, float fovy, mat4 projMatrix);
void getModelViewProjectionMatrix(camera cam, float fovy, mat4 modelMatrix, mat4 mvpMatrix);

void updateCameraAspectRatio(camera * cam, float aspectRatio);

void moveCamera(camera * cam, Uint32 buttonsHeld);

#endif