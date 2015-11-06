/*************************************************************************************

Program:			CS 4250 Assignment 3

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Fragment shader file. Simple pass-through shader.

Date:				

*************************************************************************************/

varying vec3 N;
varying vec3 L;
varying vec3 E;

uniform vec4 ambientProduct, diffuseProduct, specularProduct;
uniform mat4 modelView;
uniform vec4 lightPosition;
uniform float shininess;

uniform bool emissive;
uniform vec4 emissionColor;

void main()
{
	if (emissive) {
		gl_FragColor = emissionColor;
	}
	else {
		vec3 NN = normalize(N);
		vec3 EE = normalize(E);
		vec3 LL = normalize(L);
		vec4 ambient, diffuse, specular;
		vec3 H = normalize(LL+EE);
		float Kd = max(dot(LL, NN), 0.0);
		Kd = dot(LL, NN);
		float Ks = pow(max(dot(NN, H), 0.0), shininess);
		ambient = ambientProduct;
		diffuse = Kd*diffuseProduct;
		if (dot(LL, NN) < 0.0)
			specular = vec4(0.0, 0.0, 0.0, 1.0);
		else
			specular = Ks*specularProduct;
	
		gl_FragColor = vec4((ambient + diffuse + specular).xyz, 1.0);
	}
}
