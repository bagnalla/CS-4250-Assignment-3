/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Wheel class. Inherits from Object. A wheel
					object has a flat cylindrical body and a number of spokes which
					are Cube objects.

Date:				November 9, 2015

*************************************************************************************/

#ifndef WHEEL_H
#define WHEEL_H

#include "Object.h"

namespace Bagnall
{
	class Cube;

	class Wheel : public Object
	{
	public:
		static void Init();

		Wheel(int numOfSpokes);

		~Wheel();

		void Update();

		void DrawWithHierarchicalTransform() const;

	private:
		static int globalVertexOffset, vertexCount;
		static void createPrototypeVertices();

		std::vector<Cube*> spokes;
	};
}

#endif
