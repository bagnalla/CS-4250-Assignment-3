/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Material struct. Contains the values
					necessary for a material. There are static methods for built-in
					materials as well as methods to create materials for a given
					color.

Date:				November 9, 2015

*************************************************************************************/

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Angel.h"
#include <vector>

namespace Bagnall
{
	struct Material
	{
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
		vec4 emission;
		float shininess;

		static std::vector<Material> StandardPlasticMaterials;
		static std::vector<Material> StandardRubberMaterials;

		static void Init();

		static Material Plastic(const vec4& color);

		static Material Rubber(const vec4& color);

		static Material Pewter();

		static Material Chrome();

		static Material Obsidian();

		static Material Silver();

		static Material Bronze();

		static Material Brass();

		static Material Pearl();

		static Material WhitePlastic();

		static Material BlackPlastic();

		static Material CyanPlastic();

		static Material GreenPlastic();

		static Material RedPlastic();

		static Material YellowPlastic();

		static Material BlackRubber();

		static Material WhiteRubber();

		static Material CyanRubber();

		static Material GreenRubber();

		static Material RedRubber();

		static Material YellowRubber();
	};
}

#endif
