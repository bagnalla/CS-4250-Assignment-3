/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the WorldTile class. Inherits from Object.
					Represents a square area of the world. Contains pointers to 
					connected neighbors. Also contains some members for the sole
					purpose of pathing algorithms for efficiency reasons.

Date:				November 9, 2015

*************************************************************************************/

#ifndef WORLDTILE_H
#define WORLDTILE_H

#include "Object.h"

namespace Bagnall
{
	class WorldTile : public Object
	{
	public:
		static void Init();

		WorldTile(int x, int y);

		void DrawWithHierarchicalTransform() const;

		bool GetPassable() const;

		void SetPassable(bool p);

		int GetX() const;

		int GetY() const;

		std::vector<WorldTile*> Neighbors;

		int d;
		WorldTile *parent;

		int segmentNumber;

	private:
		static int globalVertexOffset, vertexCount;
		static void createPrototypeVertices();

		bool passable;
		int x, y;
	};
}

#endif
