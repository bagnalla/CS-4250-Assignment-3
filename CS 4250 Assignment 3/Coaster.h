/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Coaster class. Inherits from Object. A 
					coaster object is always associated with a Track object. It is 
					basically a manager object for Carts which are linked together to
					form a Coaster.

Date:				November 9, 2015

*************************************************************************************/

#ifndef COASTER_H
#define COASTER_H

#include "Object.h"

namespace Bagnall
{
	class Track;
	class Cart;
	class Cube;

	class Coaster : public Object
	{
	public:
		Coaster(Track *t, float v);

		~Coaster();

		void Update();

		void Draw() const;

		void AddCart();

		void RemoveCart();

		const std::vector<Cart*>* GetCarts();

		float GetVelocity();

		void SetVelocity(float v);

	private:
		Track *track;
		std::vector<Cart*> carts;
		std::vector<Cube*> links;
		float velocity;
		int nextCartPosition;

		void initializeCarts(int numOfCarts);

		void initializeCartLocations();
	};
}

#endif
