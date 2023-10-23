#include <cglm/cglm.h>

typedef struct camera
{
	float x;
	float y;
	float z;
	float psi;	// Yaw (lateral rotation - 0 is along xy-plane, facing +x)
	float theta;// Pitch (vertical rotation - 0 is along xz-plane)
	//float phi;	// Roll (unimplemented - would not be useful)

}	camera;