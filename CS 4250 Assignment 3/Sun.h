/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Sun class. Inherits from Object. A sun
					object follows a cyclical path and updates the light source
					model view matrix in the vertex shader.

Date:				November 9, 2015

*************************************************************************************/

#ifndef SUN_H
#define SUN_H

#include "Object.h"

namespace Bagnall
{
	class Sphere;

	class Sun : public Object
	{
	public:
		Sun(vec4 col, float v);

		~Sun();

		void Update();

		void Draw() const;

	private:
		Sphere *sphere;
		vec4 color;
		float velocity;

		std::vector<vec4> path;
		vec4 currentWaypoint;
		int waypointCounter;

		void updateLightModelView();

		void createPath();

		void move(float real_move_amount);
	};
}

#endif
