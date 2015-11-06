/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Sphere class. Inherits from Object. A
					simple sphere.

Date:				November 9, 2015

*************************************************************************************/

#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"

namespace Bagnall
{
	class Sphere : public Object
	{
	public:
		static void Init();

		Sphere();

		~Sphere();

		void Draw() const;

		void DrawWithHierarchicalTransform() const;

	private:
		static int globalVertexOffset, vertexCount;
		static void createPrototypeVertices();
	};
}

#endif
