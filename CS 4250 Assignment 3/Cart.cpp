#include "Cart.h"
#include "Cube.h"
#include "Wheel.h"
#include "Track.h"
#include "Person.h"
#include "Util.h"

namespace Bagnall
{
	// PUBLIC

	Cart::Cart(Track *t)
	{
		track = t;
		SetPosition((*t->GetPath())[(*t->GetPath()).size() - 1]);
		currentWaypoint = (*t->GetPath())[0];
		waypointCounter = 2;

		for (int i = 0; i < 5; i++)
		{
			Cube *cube = new Cube();
			cube->SetMaterial(Material::Pewter());
			cubes.push_back(cube);
			AddChild(cube);
		}
		cubes[0]->SetScale(0.8, 0.9, 0.2);
		cubes[1]->SetScale(0.9, 0.1, 0.5);
		cubes[2]->SetScale(0.9, 0.1, 0.5);
		cubes[3]->SetScale(0.1, 0.9, 0.5);
		cubes[4]->SetScale(0.1, 0.9, 0.5);

		cubes[0]->Translate(vec4(0.0, 0.0, 0.4, 0.0));
		cubes[1]->Translate(vec4(0.0, 0.5, 0.25, 0.0));
		cubes[2]->Translate(vec4(0.0, -0.5, 0.25, 0.0));
		cubes[3]->Translate(vec4(-0.4, 0.0, 0.25, 0.0));
		cubes[4]->Translate(vec4(0.4, 0.0, 0.25, 0.0));

		for (int i = 0; i < 6; i++)
		{
			Wheel *wheel = new Wheel(4);
			wheel->Scale(0.12);
			wheel->ScaleX(0.45);
			wheel->SetMaterial(Material::BlackRubber());
			wheels.push_back(wheel);
			AddChild(wheel);
		}

		wheels[0]->Translate(vec4(-0.5, -0.4, 0.5, 0.0));
		wheels[1]->Translate(vec4(-0.5, 0.0, 0.5, 0.0));
		wheels[2]->Translate(vec4(-0.5, 0.4, 0.5, 0.0));
		wheels[3]->Translate(vec4(0.5, -0.4, 0.5, 0.0));
		wheels[4]->Translate(vec4(0.5, 0.0, 0.5, 0.0));
		wheels[5]->Translate(vec4(0.5, 0.4, 0.5, 0.0));

		person = NULL;
	}

	Cart::~Cart()
	{
		/*for (std::vector<Cube*>::iterator it = cubes.begin(); it != cubes.end(); it++)
			delete (*it);
		for (std::vector<Wheel*>::iterator it = wheels.begin(); it != wheels.end(); it++)
			delete (*it);*/

		delete person;
	}

	void Cart::Update()
	{
		totalMovementThisUpdate = 0;

		move(velocity * Game::GameSpeedFactor());

		rotateWheels(totalMovementThisUpdate);

		rotate();

		Object::Update();
	}

	void Cart::Draw() const
	{
		Object::DrawWithHierarchicalTransform();

		for (std::vector<Cube*>::const_iterator it = cubes.begin(); it != cubes.end(); it++)
			(*it)->DrawWithHierarchicalTransform();

		for (std::vector<Wheel*>::const_iterator it = wheels.begin(); it != wheels.end(); it++)
			(*it)->DrawWithHierarchicalTransform();
	}

	void Cart::SetVelocity(float v)
	{
		velocity = v;
	}

	void Cart::SetTrackLocation(int location, int positionOfFirstCart)
	{
		float lengthAccum = 0.0;
		std::vector<vec4> path = *(track->GetPath());
		int i;
		for (i = positionOfFirstCart; ; i--)
		{
			if (i == 0)
			{
				lengthAccum += Util::Distance(path[0], path[path.size() - 1]);
				i = path.size() - 1;
			}
			else
				lengthAccum += Util::Distance(path[i], path[i - 1]);

			if (lengthAccum >= scale.y * location * 1.2)
				break;
		}

		SetPosition(path[i]);
		waypointCounter = (i + 1) % path.size();
		currentWaypoint = path[waypointCounter];
	}

	int Cart::GetTrackLocation()
	{
		return waypointCounter == 0 ? (*track->GetPath()).size() - 1 : waypointCounter - 1;
	}

	bool Cart::AddPerson(Person *p)
	{
		if (person != NULL)
			return false;
		person = p;
		return true;
	}

	void Cart::RemovePerson()
	{
		person = NULL;
	}

	// PRIVATE

	void Cart::move(float real_move_amount)
	{
		vec4 displacement = currentWaypoint - position;
		float len = length(displacement);
		if (len <= real_move_amount)
		{
			SetPosition(currentWaypoint);
			totalMovementThisUpdate += len;
			waypointCounter = ++waypointCounter % track->GetPath()->size();
			currentWaypoint = (*track->GetPath())[waypointCounter];

			// recursive call until real_move_amount is used up
			move(real_move_amount - len);
			return;
		}

		vec4 direction = normalize(displacement);
		vec4 translation = direction * real_move_amount;
		totalMovementThisUpdate += length(translation);
		Translate(translation);
	}

	void Cart::rotate()
	{
		//vec4 displacement = currentWaypoint - position;
		//if (Angel::length(displacement) == 0)
		//	return;

		//displacement = Angel::normalize(displacement);

		//float thetaZ = atan2(displacement.y, displacement.x);
		//SetRotationZ(thetaZ - M_PI / 2.0);

		///*vec4 absDisplacement = vec4(abs(displacement.x), abs(displacement.y), abs(displacement.z), 0.0);
		//float sum = absDisplacement.x + absDisplacement.y;
		//if (sum == 0)
		//	return;
		//float xWeight = absDisplacement.x / sum;
		//float yWeight = 1.0 - xWeight;
		//float thetaX = (xWeight * atan2(displacement.z, absDisplacement.x) + yWeight * atan2(displacement.z, absDisplacement.y)) * 0.75;
		//SetRotationX(thetaX);*/
		//SetRotationX(Util::Pitch(displacement));

		LookAt(currentWaypoint);
		RotateZ(-M_PI / 2.0);
	}

	void Cart::rotateWheels(float moveDistance)
	{
		//if (isnan(moveDistance))
		if (moveDistance != moveDistance)
			return;

		float wheelRotation = moveDistance / wheels[0]->GetScaleZ();
		for (std::vector<Wheel*>::iterator it = wheels.begin(); it != wheels.end(); it++)
			(*it)->RotateX(velocity >= 0 ? wheelRotation : -wheelRotation);
	}
}
