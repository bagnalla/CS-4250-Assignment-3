/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Cube class. Inherits from Object. A simple
					cube.

Date:				November 9, 2015

*************************************************************************************/

#ifndef CUBE_H
#define CUBE_H

#include "Object.h"

namespace Bagnall
{
	class Cube : public Object
	{
	public:
		static void Init()
		{
			createPrototypeVertices();
		}

		Cube() {}

		void Draw() const;

		void DrawWithHierarchicalTransform() const;

	private:
		static int globalVertexOffset, vertexCount;
		static void createPrototypeVertices();
	};
}

#endif
