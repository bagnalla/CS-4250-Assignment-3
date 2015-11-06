/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the LightSource struct. It contains the values
					necessary for a light source and provides a default LightSource.

Date:				November 9, 2015

*************************************************************************************/

#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "Angel.h"

namespace Bagnall
{
	struct LightSource
	{
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
		vec4 position;

		static void Init();

		static LightSource Default;
	};
}

#endif
