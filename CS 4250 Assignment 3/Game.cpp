/*************************************************************************************

Program:			CS 4250 Assignment 1: Drone

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Implementation file for the Game class.

Date:				September 28, 2015

*************************************************************************************/

#include "Game.h"
#include "Angel.h"
#include "Util.h"
#include "FpsTracker.h"
#include "World.h"

namespace Bagnall
{
	std::string Game::StatusMessage = "Roller Coaster";

	float Game::GameSpeed = 1.0;
	float Game::ViewDistance = 100.0;
	float Game::WorldScale = 50.0;

	bool Game::DebugMode;

	GLuint Game::WindowSizeLoc;
	GLuint Game::ColorLoc;
	GLuint Game::ModelViewLoc;
	GLuint Game::CameraLoc;
	GLuint Game::ProjectionLoc;
	GLuint Game::CameraPositionLoc;
	GLuint Game::LightPositionLoc;
	GLuint Game::AmbientProductLoc;
	GLuint Game::DiffuseProductLoc;
	GLuint Game::SpecularProductLoc;
	GLuint Game::ShininessLoc;
	GLuint Game::LightModelViewLoc;
	GLuint Game::EmissiveLoc;
	GLuint Game::EmissionColorLoc;

	std::vector<vec4> Game::Vertices;
	std::vector<vec4> Game::Normals;
	
	vec2 Game::WindowSize;

	mat4 Game::Camera = Util::Identity();
	mat4 Game::Projection = Util::Identity();

	World *Game::GameWorld = NULL;

	float Game::GameSpeedFactor()
	{
		return GameSpeed * FpsTracker::GetFrameTimeMs();
	}
}
