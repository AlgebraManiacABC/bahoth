#include "stl.h"
#include "debug.h"

STL loadSTLFromFile(const char * filename)
{
	if(!filename)
	{
		setError(ERR_CODE,ERR_NULLP);
		return NULL;
	}

	STL stl = malloc(sizeof(STL_s));
	if(!stl)
	{
		setError(ERR_CODE,ERR_NOMEM);
		return NULL;
	}

	glm_mat4_copy(GLM_MAT4_IDENTITY,stl->modelMatrix);

	//vec3 min = {0,0,0};
	//vec3 max = {0,0,0};

	FILE * fp = fopen(filename,"rb");
	if(!fp)
	{
		setError(ERR_CODE,ERR_NOFIL);
		free(stl);
		return NULL;
	}

	char magic[6] = {0};
	fread(magic,sizeof(char),5,fp);
	if(strcmp(magic,"solid") != 0)	//	Binary
	{
		fseek(fp, sizeof(char)*80, SEEK_SET);
		fread(&(stl->triangleCount),sizeof(Uint32),1,fp);
		fprintf(stderr,"Binary file detected with %d triangles!\n",stl->triangleCount);
		stl->triangles = malloc(sizeof(STL_triangle_s)*stl->triangleCount);
		if(!stl->triangles)
		{
			setError(ERR_CODE,ERR_NOMEM);
			free(stl);
			fclose(fp);
			return NULL;
		}
		for(int i=0; i<stl->triangleCount; i++)
		{
			fread(&(stl->triangles[i].normal1),sizeof(vec3),1,fp);
			glm_vec3_copy(stl->triangles[i].normal1,stl->triangles[i].normal2);
			glm_vec3_copy(stl->triangles[i].normal1,stl->triangles[i].normal3);
			fread(&(stl->triangles[i].v1),sizeof(vec3),1,fp);
			fread(&(stl->triangles[i].v2),sizeof(vec3),1,fp);
			fread(&(stl->triangles[i].v3),sizeof(vec3),1,fp);
			fseek(fp,sizeof(Uint16),SEEK_CUR);
			//fread(&(stl->triangles[i].attribByteCount),sizeof(Uint16),1,fp);
		}
	}
	else	//	Ascii
	{
		setError(ERR_MESG,"ASCII STL files are currently unimplemented.");
		fclose(fp);
		free(stl);
		return NULL;
	}

	fclose(fp);

	glGenBuffers(1,&stl->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER,stl->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(STL_triangle_s)*(stl->triangleCount),stl->triangles,GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3/*floats per vertex*/,GL_FLOAT,GL_FALSE,sizeof(vec3)*2/*size of data per vertex*/,NULL/*Positional data first*/);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,3/*floats per normal*/,GL_FLOAT,GL_FALSE,sizeof(vec3)*2/*size of data per vertex*/,(void*)sizeof(vec3)/*Normal data second*/);

	glBindBuffer(GL_ARRAY_BUFFER,0);

	return stl;
}

void placeSTL(STL stl, vec3 pos)
{
	glm_mat4_copy(GLM_MAT4_IDENTITY,stl->modelMatrix);
	glm_translate(stl->modelMatrix,pos);
}

void translateSTL(STL stl, vec3 pos)
{
	glm_translate(stl->modelMatrix,pos);
}

void rotateSTL(STL stl, vec3 rot)
{
	glm_rotate_y(stl->modelMatrix,rot[0],stl->modelMatrix);
	glm_rotate_x(stl->modelMatrix,rot[1],stl->modelMatrix);
	glm_rotate_z(stl->modelMatrix,rot[2],stl->modelMatrix);
}

void scaleSTLTo(STL stl, Uint32 dir, float value)
{
}

void scaleSTLBy(STL stl, Uint32 dir, float value)
{
}