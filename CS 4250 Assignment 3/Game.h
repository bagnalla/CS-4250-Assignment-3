/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Game class. This is basically just a
					container for global variables of the program.

Date:				November 9, 2015

*************************************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Angel.h"

namespace Bagnall
{
	class World;

	class Game
	{
	public:
		static std::string StatusMessage; // message to display in window title bar

		static float GameSpeed; // game speed multiplier
		static float ViewDistance;
		static float WorldScale;

		static bool DebugMode; // debug mode toggle
		
		static GLuint WindowSizeLoc; // location of windowSize in vshader
		static GLuint ColorLoc; // location of color in vshader
		static GLuint ModelViewLoc; // location of transform in vshader
		static GLuint CameraLoc; // location of projection in vshader
		static GLuint ProjectionLoc; // location of projection in vshader
		static GLuint CameraPositionLoc;
		static GLuint LightPositionLoc;
		static GLuint AmbientProductLoc;
		static GLuint DiffuseProductLoc;
		static GLuint SpecularProductLoc;
		static GLuint ShininessLoc;
		static GLuint LightModelViewLoc;
		static GLuint EmissiveLoc;
		static GLuint EmissionColorLoc;

		static std::vector<vec4> Vertices; // global vertices array
		static std::vector<vec4> Normals; // global normals array

		static vec2 WindowSize; // size of window x, y

		static mat4 Camera; // camera matrix
		static mat4 Projection; // projection matrix

		static World *GameWorld;

		static float GameSpeedFactor();
	};
}

#endif
