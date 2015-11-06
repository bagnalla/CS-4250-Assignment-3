/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the TrashCan class. Inherits from Object. A
					TrashCan object has a cylindrical body and a Wheel object for a
					lid. When created, it will mark the tile in the world
					where it is located as impassable.

Date:				November 9, 2015

*************************************************************************************/

#ifndef TRASHCAN_H
#define TRASHCAN_H

#include "Object.h"

namespace Bagnall
{
	class Wheel;
	class WorldTile;

	class TrashCan : public Object
	{
	public:
		static void Init();

		static std::vector<TrashCan*> TrashCans;

		static void ClearTrashCans();

		TrashCan();

		~TrashCan();

		void Update();

		void Draw() const;

		void DrawWithHierarchicalTransform() const;

		void SetRandomLocationInSegment(std::vector<WorldTile*> segment);

	private:

		static int globalVertexOffset, vertexCount;
		static void createPrototypeVertices();

		Wheel *lid;
	};
}

#endif
