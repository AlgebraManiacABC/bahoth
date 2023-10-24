#include "render.h"
#include "game.h"

void renderAll(GLuint shaderProgram, camera cam, float aspectRatio)
{
	renderTable(shaderProgram, cam, aspectRatio);
	renderUI();
}

void renderTable(GLuint shaderProgram, camera cam, float aspectRatio)
{
	renderTiles(shaderProgram, cam, aspectRatio);
	renderPlayerInventories();
	renderTableExtras();
}
//============================//
void renderTiles(GLuint shaderProgram, camera cam, float aspectRatio)
{
	//	Experimental state of this function!
	//	Expect most or all of this to be replaced.
	renderTile(shaderProgram, cam, aspectRatio);
}

void renderTile(GLuint shaderProgram, camera cam, float aspectRatio)
{
	//	Experimental state of this function!
	//	Expect most or all of this to be replaced.

	//	Let's say we want to render the foyer, ignoring the texture and other connected tiles.
	//	I'm going to get a camera set up first.
	//	We take the tile position, and add or subtract tileWidth/2 to x or z to get the borders of the tile.
	//	We can simply create two triangles with these newfound vertices and use them to render.
	//	Here's the most basic example:
	tile t;
	t.x = 0;
	t.z = 0;
	float tileVertices[] =	//	xyz of each vertex
	{
		t.x + (tileWidth/2.0), 0.5f, t.z + (tileWidth/2.0), // Front-right
		t.x + (tileWidth/2.0), -0.5f, t.z - (tileWidth/2.0), // Back-right
		t.x - (tileWidth/2.0), 0.5f, t.z + (tileWidth/2.0), // Front-left

		t.x + (tileWidth/2.0), -0.5f, t.z - (tileWidth/2.0),
		t.x - (tileWidth/2.0), 0.5f, t.z + (tileWidth/2.0),
		t.x - (tileWidth/2.0), -0.5f, t.z - (tileWidth/2.0) // Back-left
	};
	GLuint vbo;
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(tileVertices),tileVertices,GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);
	glEnableVertexAttribArray(0);

	mat4 translationMatrix = GLM_MAT4_IDENTITY_INIT;
	mat4 rotationMatrix = GLM_MAT4_IDENTITY_INIT;
	mat4 modelMatrix = GLM_MAT4_IDENTITY_INIT;
	glm_mat4_mul(translationMatrix,rotationMatrix,modelMatrix);
	mat4 viewMatrix = GLM_MAT4_IDENTITY_INIT;
	mat4 projectionMatrix = GLM_MAT4_IDENTITY_INIT;
	mat4 mvpMatrix = GLM_MAT4_IDENTITY_INIT;
	vec3 dir =
	{
		cosf(cam.pitch) * sinf(cam.yaw),
		sinf(cam.pitch),
		cosf(cam.pitch) * cosf(cam.yaw)
	};

	glm_look((vec3){cam.x,cam.y,cam.z},dir,worldUp,viewMatrix);
	glm_perspective(glm_rad(90),aspectRatio,0.1f,100.0f,projectionMatrix);
	glm_mat4_mul(projectionMatrix,viewMatrix,mvpMatrix);
	glm_mat4_mul(mvpMatrix,modelMatrix,mvpMatrix);
	glUniformMatrix4fv(trLoc,1,GL_FALSE,(float*)mvpMatrix);
	glDrawArrays(GL_TRIANGLES,0,6);
}

void renderPlayerInventories()
{
	return;
}

void renderTableExtras()
{
	return;
}
//============================//

void renderUI()
{
	return;
}