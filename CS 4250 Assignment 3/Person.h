/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Person class. Inherits from Object. A
					Person object is composed of a head and a body. It can be attached
					to a Cart object. Otherwise, it will walk around randomly and use
					a PathFinder object to dictate its movement paths.

Date:				November 9, 2015

*************************************************************************************/

#ifndef PERSON_H
#define PERSON_H

#include "Object.h"

namespace Bagnall
{
	class Cube;
	class Sphere;
	class Cart;

	class Person : public Object
	{
	public:
		static std::vector<Person*> People;

		static void ClearPeople();

		Person();

		~Person();

		void Update();

		void Draw() const;

		bool GetInCart(Cart *c);

		void GetOffCart();

		void RandomizePosition();

		void ChooseNewDestination();

	private:
		Sphere *head;
		Cube *body;

		Cart *cart;

		float velocity;
		std::vector<vec4> *waypoints;
		vec4 currentWaypoint;
		int waypointCounter;

		void move(float real_move_amount);

		void clampToPassableTiles();
	};
}

#endif
