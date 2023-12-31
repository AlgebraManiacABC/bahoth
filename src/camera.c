#include "camera.h"
#include "debug.h"
#include "game.h"

camera initCamera(float aspectRatio)
{
	camera cam;
	cam.ar    = aspectRatio;
	cam.x     = 0.0;
	cam.y     = 0.0;
	cam.z     = 1.0;
	cam.pitch = 0.0;
	cam.yaw   = 0.0;
	cam.pos[0]= 0.0;
	cam.pos[1]= 0.0;
	cam.pos[2]= 1.0;
	return cam;
}

void placeCamera(camera cam, vec3 pos, float pitch, float yaw)
{
}

void getViewMatrix(camera cam, mat4 viewMatrix)
{
	vec3 dir =
	{
		cosf(cam.pitch) * sinf(cam.yaw),
		sinf(cam.pitch),
		cosf(cam.pitch) * cosf(cam.yaw)
	};

	glm_look((vec3){cam.x,cam.y,cam.z},dir,worldUp,viewMatrix);
}

void getProjectionMatrix(camera cam, float fovy, mat4 projMatrix)
{
	glm_perspective(fovy,cam.ar,NEARZ,FARZ,projMatrix);
}

void getModelViewProjectionMatrix(camera cam, float fovy, mat4 modelMatrix, mat4 mvpMatrix)
{
	mat4 viewMatrix = GLM_MAT4_IDENTITY_INIT;
	getViewMatrix(cam,viewMatrix);
	mat4 projMatrix = GLM_MAT4_IDENTITY_INIT;
	getProjectionMatrix(cam,fovy,projMatrix);

	glm_mat4_mul(projMatrix,viewMatrix,mvpMatrix);
	glm_mat4_mul(mvpMatrix,modelMatrix,mvpMatrix);
}

void updateCameraAspectRatio(camera * cam, float aspectRatio)
{
	cam->ar = aspectRatio;
}

void moveCamera(camera * cam, Uint32 cameraBitfield)
{
	if((cameraBitfield & CAMERA_MOVE_LEFT) && !(cameraBitfield & CAMERA_MOVE_RIGHT))
	{
		//	Move camera left
		cam->x += (CAM_UPF)*sinf(cam->yaw + glm_rad(90));
		cam->z += (CAM_UPF)*cosf(cam->yaw + glm_rad(90));
	}
	else if(cameraBitfield & CAMERA_MOVE_RIGHT)
	{
		//	Move camera right
		cam->x += (CAM_UPF)*sinf(cam->yaw - glm_rad(90));
		cam->z += (CAM_UPF)*cosf(cam->yaw - glm_rad(90));
	}

	if((cameraBitfield & CAMERA_MOVE_FORWARD) && !(cameraBitfield & CAMERA_MOVE_BACKWARD))
	{
		//	Move camera forward
		cam->x += (CAM_UPF)*sinf(cam->yaw);
		cam->z += (CAM_UPF)*cosf(cam->yaw);
	}
	else if(cameraBitfield & CAMERA_MOVE_BACKWARD)
	{
		//	Move camera backward
		cam->x -= (CAM_UPF)*sinf(cam->yaw);
		cam->z -= (CAM_UPF)*cosf(cam->yaw);
	}

	if((cameraBitfield & CAMERA_MOVE_UP) && !(cameraBitfield & CAMERA_MOVE_DOWN))
	{
		//	Move camera up
		cam->y += (CAM_UPF);
	}
	else if(cameraBitfield & CAMERA_MOVE_DOWN)
	{
		//	Move camera down
		cam->y -= (CAM_UPF);
	}

	if((cameraBitfield & CAMERA_YAW_LEFT) && !(cameraBitfield & CAMERA_YAW_RIGHT))
	{
		//	Turn camera left
		cam->yaw += (CAM_UPF);
		if(cam->yaw > glm_rad(360))
			cam->yaw -= glm_rad(360);
	}
	else if(cameraBitfield & CAMERA_YAW_RIGHT)
	{
		//	Turn camera right
		cam->yaw -= (CAM_UPF);
		if(cam->yaw < 0)
			cam->yaw += glm_rad(360);
	}

	if((cameraBitfield & CAMERA_PITCH_UP) && !(cameraBitfield & CAMERA_PITCH_DOWN))
	{
		//	Angle camera up
		cam->pitch += (CAM_UPF);
		if(cam->pitch >= glm_rad(90))
			cam->pitch = glm_rad(90 - 0.001f);
	}
	else if(cameraBitfield & CAMERA_PITCH_DOWN)
	{
		//	Angle camera down
		cam->pitch -= (CAM_UPF);
		if(cam->pitch <= glm_rad(-90))
			cam->pitch = glm_rad(-90 + 0.001f);
	}
}