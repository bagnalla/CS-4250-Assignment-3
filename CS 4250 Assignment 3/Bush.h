/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Bush class. Inherits from Object. There
					are two types of bushes defined in the BushType enum and each
					Bush object must be passed one of those enum values when
					constructed. When created, it will mark the tile in the world
					where it is located as impassable.

Date:				November 9, 2015

*************************************************************************************/

#ifndef BUSH_H
#define BUSH_H

#include "Object.h"

namespace Bagnall
{
	// forward declarations
	class Cube;

	enum BushType
	{
		BUSH_TYPE_ROUND,
		BUSH_TYPE_SWIRLY
	};

	class Bush : public Object
	{
	public:
		/**********************************************************************
		Function:		Init
		Purpose:		Static initialization for the Bush class
		**********************************************************************/
		static void Init();

		static std::vector<Bush*> Bushes; // static list of bushes

		/**********************************************************************
		Function:		ClearBushes
		Purpose:		Clear the static list of bushes
		**********************************************************************/
		static void ClearBushes();

		/**********************************************************************
		Function:		Bush constructor
		Purpose:		Create a bush object of a given type
		Parameters:		BushType t - type of the bush
		**********************************************************************/
		Bush(BushType t);

		/**********************************************************************
		Function:		Bush destructor
		Purpose:		Cleanup of bush object
		**********************************************************************/
		~Bush();

		/**********************************************************************
		Function:		Update
		Purpose:		Update a bush object for the current update cycle.
		**********************************************************************/
		void Update();

		/**********************************************************************
		Function:		Draw
		Purpose:		Draw a bush object.
		**********************************************************************/
		void Draw() const;

		/**********************************************************************
		Function:		DrawWithHierarchicalTransform
		Purpose:		Draw a bush object with its model view matrix
						concatenated with the parent object's model view
						matrix.
		**********************************************************************/
		void DrawWithHierarchicalTransform() const;

		/**********************************************************************
		Function:		RandomizeLocation
		Purpose:		Choose a random passable location in the world to
						position the bush and mark the WorldTile at that
						location as passable.
		**********************************************************************/
		void RandomizeLocation();

	private:

		static int globalVertexOffsetRound; // location of round bush vertices
		static int vertexCountRound; // # of round bush vertices
		static int globalVertexOffsetSwirly; // location of swirly bush vertices
		static int vertexCountSwirly; // # of swirly bush vertices

		/**********************************************************************
		Function:		createPrototypeVertices
		Purpose:		Create the prototype vertices that are shared among
						all bush objects.
		**********************************************************************/
		static void createPrototypeVertices();

		BushType type; // the type of the bush
		std::vector<Cube*> fence; // the fence around the bush
	};
}

#endif
