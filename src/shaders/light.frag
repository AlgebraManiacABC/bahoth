#version 330 core
out vec4 FragColor;
in vec3 bNormal;
in vec3 bPos;

void main()
{
	vec3 objectColor = vec3(1.0f, 1.0f, 1.0f);	//	White, for now.
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);	//	White light
	vec3 lightPos = vec3(100.0f, 500.0f, -200.0f);	//	Arbitrary placement

	//	Ambient light
	float ambientIntensity = 0.5f;	//	Out of 1.0f
	vec3 ambient = ambientIntensity * lightColor;
	vec3 intermediate = ambient * objectColor;

	//	Diffuse light
	vec3 norm = normalize(bNormal);
	vec3 lightDir = normalize(lightPos - bPos);
	float diffuseFactor = max(0, dot(norm,lightDir));
	vec3 diffuse = diffuseFactor * lightColor;

	vec3 result = (intermediate + diffuse) * objectColor;

	FragColor = vec4(result, 1.0f);
}