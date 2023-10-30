#include "stl.h"
#include "debug.h"
#include "game.h"

void updateMaxMin(vec3 v, vec3 max, vec3 min)
{
	if(v[0] > max[0]) max[0] = v[0];
	if(v[1] > max[1]) max[1] = v[1];
	if(v[2] > max[2]) max[2] = v[2];

	if(v[0] < min[0]) min[0] = v[0];
	if(v[1] < min[1]) min[1] = v[1];
	if(v[2] < min[2]) min[2] = v[2];
}

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

	vec3 min = {0,0,0};
	vec3 max = {0,0,0};

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
			updateMaxMin(stl->triangles[i].v1,max,min);
			fread(&(stl->triangles[i].v2),sizeof(vec3),1,fp);
			updateMaxMin(stl->triangles[i].v2,max,min);
			fread(&(stl->triangles[i].v3),sizeof(vec3),1,fp);
			updateMaxMin(stl->triangles[i].v3,max,min);
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

	glm_vec3_sub(max,min,stl->size);

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
	mat4 roty = GLM_MAT4_IDENTITY_INIT;
	mat4 rotx = GLM_MAT4_IDENTITY_INIT;
	mat4 rotz = GLM_MAT4_IDENTITY_INIT;
	glm_rotate_y(GLM_MAT4_IDENTITY,rot[0],roty);
	glm_rotate_x(GLM_MAT4_IDENTITY,rot[1],rotx);
	glm_rotate_z(GLM_MAT4_IDENTITY,rot[2],rotz);
	glm_mat4_mul(stl->modelMatrix,rotz,stl->modelMatrix);
	glm_mat4_mul(rotx,roty,rotx);
	glm_mat4_mul(stl->modelMatrix,rotx,stl->modelMatrix);
}

float arcballGet(vec2 posi, vec2 posf, int ww, int wh, vec3 axis)
{
	posi[0] = (posi[0] / (ww/2.0)) - 1;
	posi[1] = (posi[1] / -(ww/2.0)) + 1;
	posf[0] = (posf[0] / (ww/2.0)) - 1;
	posf[1] = (posf[1] / -(ww/2.0)) + 1;
	//fprintf(stderr,"Normalized Screen Pos: { %.2ff, %.2ff} -> { %.2ff, %.2ff }\n",posi[0],posi[1],posf[0],posf[1]);

	//	Pythagorean theorum: 1 = x*x + y*y + z*z

	bool normalizedi = false;
	bool normalizedf = false;
	//	First point
	vec3 veci = {posi[0], posi[1], 0};
	float sqrPosi = (posi[0]*posi[0]) + (posi[1]*posi[1]);
	if(sqrPosi <= 1.0f)
	//	Point on cube, safe to sqrt
		veci[2] = sqrt(1 - sqrPosi);
	else
	{
	//	Off cube, unsafe to sqrt; just get closest point
		glm_normalize(veci);
		normalizedi = true;
	}

	//	Second point
	vec3 vecf = {posf[0], posf[1], 0};
	float sqrPosf = (posf[0]*posf[0]) + (posf[1]*posf[1]);
	if(sqrPosf <= 1.0f)
		vecf[2] = sqrt(1 - sqrPosf);
	else
	{
		glm_normalize(vecf);
		normalizedf = true;
	}
	(void)(normalizedf & normalizedi);

	//fprintf(stderr,"i{ %.2ff, %.2ff, %.2ff } || f{ %.2ff, %.2ff, %.2ff }\n",veci[0],veci[1],veci[2],vecf[0],vecf[1],vecf[2]);
	float dot = glm_dot(veci,vecf);
	float spinFactor = 1.0f;
	float angle = spinFactor * acos(dot > 1.0? (dot < -1.0? -1.0: 1.0): dot);
	glm_cross(veci,vecf,axis);
	//fprintf(stderr,"Arcball created: Angle = %.2ff; { %.2ff, %.2ff, %.2ff } (dot was %.2ff)%c%c%c\n",glm_deg(angle),axis[0],axis[1],axis[2], dot,
		//(normalizedi?'i':' '),(normalizedf?'f':' '),(dot>1.0 || dot < -1.0?'!':' '));
	return angle;
}

void getSTLDimensionRatio(STL stl, vec3 ratio)
{
	GLuint max_index = 0;
	if(stl->size[1] > stl->size[max_index]) max_index = 1;
	if(stl->size[2] > stl->size[max_index]) max_index = 2;

	ratio[0] = stl->size[0] / stl->size[max_index];
	ratio[1] = stl->size[1] / stl->size[max_index];
	ratio[2] = stl->size[2] / stl->size[max_index];
}

void scaleSTLTo(STL stl, Uint32 dir, float value)
{
	//	Scale down all dimensions equally so the max length is 1.0
	vec3 ratios = {0};
	getSTLDimensionRatio(stl,ratios);
	//	Scale everything down to (1,1,1)
	vec3 unify = {0};
	if(stl->size[0]) unify[0] = (1/stl->size[0]);
	if(stl->size[1]) unify[1] = (1/stl->size[1]);
	if(stl->size[2]) unify[2] = (1/stl->size[2]);
	glm_scale(stl->modelMatrix,unify);
	//	Scale everything back up to where it needs to be
	vec3 scale = {1.0, 1.0, 1.0};
	switch(dir)
	{
		case STL_Y:
			scale[0] = value;
			break;
		case STL_X:
			scale[1] = value;
			break;
		case STL_Z:
			scale[2] = value;
			break;
		default:
			scale[0] = value * ratios[0];
			scale[1] = value * ratios[1];
			scale[2] = value * ratios[2];
			break;
	}
	glm_scale(stl->modelMatrix,scale);
}

void scaleSTLBy(STL stl, Uint32 dir, float value)
{
	vec3 scale = {1.0, 1.0, 1.0};
	switch(dir)
	{
		case STL_Y:
			scale[0] = value;
			break;
		case STL_X:
			scale[1] = value;
			break;
		case STL_Z:
			scale[2] = value;
			break;
		default:
			scale[0] = value;
			scale[1] = value;
			scale[2] = value;
			break;
	}
	glm_scale(stl->modelMatrix,scale);
}

void moveSTL(STL stl, Uint32 buttonsHeld, int *x, int *y, int ww, int wh, camera cam)
{
	if( (buttonsHeld & MODEL_SCALE_UP) && !(buttonsHeld & MODEL_SCALE_DOWN) )
	{
		scaleSTLBy(stl,STL_ALL,1.10);
	}
	else if( (buttonsHeld & MODEL_SCALE_DOWN) && !(buttonsHeld & MODEL_SCALE_UP) )
	{
		scaleSTLBy(stl,STL_ALL,1/1.10);
	}

	static bool dragging = false;
	static int oldx, oldy;
	static mat4 oldModelMatrix;
	if(!dragging)
	{
		oldx = *x;
		oldy = *y;
	}

	Uint32 mouseState = SDL_GetMouseState(x,y);
	if(mouseState & SDL_BUTTON_LEFT)
	{
		if(!dragging)
		{
			glm_mat4_copy(stl->modelMatrix,oldModelMatrix);
		}
		dragging = true;
	}
	else
		dragging = false;

	int dx = (*x-oldx), dy = (*y-oldy);
	if(dragging)
	{
		if(!dx && !dy) return;
		//float dragFactor = 0.5f;
		//rotateSTL(stl,(vec3){0, -dragFactor*glm_rad(dy), dragFactor*glm_rad(dx)});
		vec3 arcballAxis = {0};
		float arcballAngle = arcballGet((vec2){oldx,oldy},(vec2){*x,*y},ww,wh,arcballAxis);
		//	arcballAxis is currently in camera coordinates; need converted to object coordinates
		mat4 modelViewMatrix;
		getViewMatrix(cam,modelViewMatrix);
		glm_mat4_mul(modelViewMatrix,oldModelMatrix,modelViewMatrix);
		mat3 transformToObjectFromCamera;
		glm_mat4_pick3(modelViewMatrix,transformToObjectFromCamera);
		glm_mat3_inv(transformToObjectFromCamera,transformToObjectFromCamera);
		glm_mat3_mulv(transformToObjectFromCamera,arcballAxis,arcballAxis);
		//	arcballAxis should now be in object coordinates
		mat4 newModelMatrix;
		glm_mat4_copy(oldModelMatrix,newModelMatrix);
		glm_rotate(newModelMatrix,arcballAngle,arcballAxis);
		glm_mat4_copy(newModelMatrix,stl->modelMatrix);
	}
}