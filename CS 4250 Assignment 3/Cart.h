/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Cart class. Inherits from Object. A Cart
					object is always associated with a Track object. It is given a
					starting point on the track and moves along the track over time.
					A cart may also contain a Person object, but the Person object
					is responsible for maintaining its own position relative to the
					Cart.

Date:				November 9, 2015

*************************************************************************************/

#ifndef CART_H
#define CART_H

#include "Object.h"

namespace Bagnall
{
	class Track;
	class Person;
	class Cube;
	class Wheel;

	class Cart : public Object
	{
	public:

		Cart(Track *t);

		~Cart();

		void Update();

		void Draw() const;

		void SetVelocity(float v);

		void SetTrackLocation(int location, int positionOfFirstCart);

		int GetTrackLocation();

		bool AddPerson(Person *p);

		void RemovePerson();

	private:
		Track *track;
		std::vector<Cube*> cubes;
		std::vector<Wheel*> wheels;

		Person *person;

		vec4 currentWaypoint;
		int waypointCounter;

		float velocity;
		float totalMovementThisUpdate;

		void move(float real_move_amount);

		void rotate();
		
		void rotateWheels(float moveDistance);
	};
}

#endif
