#include "render.h"
#include "camera.h"
#include "game.h"

bool isWireframe = false;

void initRenderer(void)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
}

void toggleWireframe(void)
{
	if(isWireframe)
	{
		isWireframe = false;
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}
	else
	{
		isWireframe = true;
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}
}

void renderAll(GLuint shaderProgram, camera cam)
{
	renderTable(shaderProgram, cam);
	renderUI();
}

void renderTable(GLuint shaderProgram, camera cam)
{
	renderTiles(shaderProgram, cam);
	renderPlayerInventories();
	renderTableExtras();
}
//============================//
void renderTiles(GLuint shaderProgram, camera cam)
{
	//	Experimental state of this function!
	//	Expect most or all of this to be replaced.
	renderTile(shaderProgram, cam);
}

void renderTile(GLuint shaderProgram, camera cam)
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
	getViewMatrix(cam,viewMatrix);
	mat4 projectionMatrix = GLM_MAT4_IDENTITY_INIT;
	mat4 mvpMatrix = GLM_MAT4_IDENTITY_INIT;
	glm_perspective(glm_rad(90),cam.ar,0.1f,100.0f,projectionMatrix);
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

void renderSTL(GLuint shaderProgram, camera cam, STL stl)
{
	glUseProgram(shaderProgram);

	mat4 mvpMatrix = GLM_MAT4_IDENTITY_INIT;
	getModelViewProjectionMatrix(cam,glm_rad(90),stl->modelMatrix,mvpMatrix);
	glUniformMatrix4fv(trLoc,1,GL_FALSE,(float*)mvpMatrix);
	glUniformMatrix4fv(mmLoc,1,GL_FALSE,(float*)stl->modelMatrix);

	glBindBuffer(GL_ARRAY_BUFFER,stl->vertexBuffer);
	glDrawArrays(GL_TRIANGLES,0,stl->triangleCount * 3);
	glBindBuffer(GL_ARRAY_BUFFER,0);

	//GLuint indices[] = {0,1,2};

	//GLuint vertexIndices;
	//glGenBuffers(1,&vertexIndices);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vertexIndices);

	//for(int i=0; i<(stl->triangleCount>3632?3632:stl->triangleCount); i++)
	//{
	//	indices[0] = 0 + (i * 3);
	//	indices[1] = 1 + (i * 3);
	//	indices[2] = 2 + (i * 3);
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
	//	glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,NULL);
	//}
}

//============================//

void renderUI()
{
	return;
}