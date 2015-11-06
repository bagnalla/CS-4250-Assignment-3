attribute vec4 vPosition;
attribute vec4 vNormal;

varying vec3 N;
varying vec3 L;
varying vec3 E;

uniform vec2 windowSize;
uniform vec4 lightPosition;
uniform vec4 cameraPosition;
uniform mat4 lightModelView;
uniform mat4 modelView;
uniform mat4 camera;
uniform mat4 projection;
uniform bool transformNormal;

void main()
{
	gl_Position = projection * camera * modelView * vPosition/vPosition.w;

	vec4 lightPos = lightModelView * lightPosition;

	N = (modelView * vNormal).xyz;
	E = cameraPosition.xyz - (modelView * vPosition).xyz;
	if (lightPos.w == 0.0)
		L = lightPos.xyz;
	else
		L = lightPos.xyz - (modelView * vPosition).xyz;
}
