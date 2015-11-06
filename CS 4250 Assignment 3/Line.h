/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Line class. Inherits from Object. A simple
					line.

Date:				November 9, 2015

*************************************************************************************/

#ifndef LINE2_H
#define LINE2_H

#include "Angel.h"
#include "Object.h"
#include "Util.h"
#include "Material.h"

namespace Bagnall
{
	class Line : public Object
	{
	public:
		static Line LineObject;

		static void Init();

		Line() {}

		void Update();

		void Draw() const;

		void SetTransformFromPoints(vec4 p1, vec4 p2);

	private:
		static int globalVertexOffset; // position of vertices in global vertex array
		static void createPrototypeVertices();
	};
}

#endif
