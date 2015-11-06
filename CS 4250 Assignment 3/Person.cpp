#include "Person.h"
#include "Line.h"
#include "Cube.h"
#include "Sphere.h"
#include "Cart.h"
#include "Game.h"
#include "World.h"
#include "WorldTile.h"
#include "PathFinder.h"
#include "Util.h"

namespace Bagnall
{
	// PUBLIC

	std::vector<Person*> Person::People;

	void Person::ClearPeople()
	{
		for (int i = 0; i < People.size();)
			delete People[i];
	}

	Person::Person()
	{
		velocity = 0.00125;

		head = new Sphere();
		head->Scale(0.25);
		head->Translate(vec4(0.0, 0.0, -0.25, 0.0));
		head->SetMaterial(rand() % 2 ? Material::WhitePlastic() : Material::BlackPlastic());
		AddChild(head);

		body = new Cube();
		body->Scale(0.5);
		body->Translate(vec4(0.0, 0.0, 0.25, 0.0));
		body->SetColor(vec4((double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX), 1.0));
		body->SetMaterial(Material::Plastic(body->GetColor()));
		AddChild(body);

		cart = NULL;

		People.push_back(this);

		waypoints = NULL;
	}

	Person::~Person()
	{
		GetOffCart();

		/*delete head;
		delete body;*/
		delete waypoints;

		People.erase(std::find(People.begin(), People.end(), this));
	}

	void Person::Update()
	{
		if (position.x != position.x)
			std::cout << "wtf\n";
		if (cart != NULL)
		{
			SetPosition(Angel::Translate(vec4(0.0, 0.0, -0.25, 0.0)) * cart->GetPosition());
			SetRotationX(cart->GetRotationX());
			SetRotationY(cart->GetRotationY());
			SetRotationZ(cart->GetRotationZ());
		}
		else if (waypoints != NULL)
		{
			move(velocity * Game::GameSpeedFactor());
			clampToPassableTiles();
		}

		Object::Update();
	}

	void Person::Draw() const
	{
		head->DrawWithHierarchicalTransform();
		body->DrawWithHierarchicalTransform();

		if (Game::DebugMode)
		{
			Line::LineObject.SetColor(body->GetColor());
			glLineWidth(2.0);

			if (waypoints != NULL)
			{
				Line::LineObject.SetTransformFromPoints(position + vec4(0.0, 0.0, -0.1, 0.0), (*waypoints)[waypointCounter] + vec4(0.0, 0.0, -0.1, 0.0));
				Line::LineObject.Draw();
				for (int i = waypointCounter; i < waypoints->size() - 1; i++)
				{
					Line::LineObject.SetTransformFromPoints((*waypoints)[i] + vec4(0.0, 0.0, -0.1, 0.0), (*waypoints)[i + 1] + vec4(0.0, 0.0, -0.1, 0.0));
					Line::LineObject.Draw();
				}
			}
		}
	}

	bool Person::GetInCart(Cart *c)
	{
		if (c->AddPerson(this))
		{
			cart = c;
			return true;
		}
		return false;
	}

	void Person::GetOffCart()
	{
		if (cart != NULL)
		{
			cart->RemovePerson();
			cart = NULL;
		}
	}

	void Person::RandomizePosition()
	{
		float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (Game::GameWorld->GetWidth() - 1);
		float y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (Game::GameWorld->GetHeight() - 1);
		int index_x = static_cast<int>(x + 0.5);
		int index_y = static_cast<int>(y + 0.5);

		WorldTile ***worldTilesArray = Game::GameWorld->GetWorldTilesArray();
		while (!worldTilesArray[index_x][index_y]->GetPassable())
		{
			x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (Game::GameWorld->GetWidth() - 1);
			y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (Game::GameWorld->GetHeight() - 1);
			index_x = static_cast<int>(x + 0.5);
			index_y = static_cast<int>(y + 0.5);
		}

		SetPosition(vec4(x, y, -0.25, 1.0));
	}

	PathFinder pf;
	void Person::ChooseNewDestination()
	{
		WorldTile ***worldTilesArray = Game::GameWorld->GetWorldTilesArray();

		delete waypoints;
		waypoints = NULL;

		WorldTile *source = Game::GameWorld->WorldTileAtPosition(position);

		if (source->Neighbors.size() == 0)
		{
			currentWaypoint = source->GetPosition();
			waypointCounter = 0;
			return;
		}

		std::vector<WorldTile*> worldTileSegment = Game::GameWorld->Segments[source->segmentNumber];

		while (waypoints == NULL)
		{
			WorldTile *destination = worldTileSegment[rand() % worldTileSegment.size()];

			if (!destination->GetPassable() || destination == source)
				continue;

			// RETURNS PATH IN REVERSE, SO DEST AND SOURCE ARE SWAPPED
			waypoints = pf.DijkstraShortestPath(worldTileSegment, destination, source);
			waypoints->erase(waypoints->begin());
			//waypoints = pf.SmoothPath(*path);
		}

		currentWaypoint = (*waypoints)[0];
		waypointCounter = 0;
	}

	// PRIVATE

	void Person::move(float real_move_amount)
	{
		vec4 displacement = Util::ChopZ(currentWaypoint - position);
		float len = length(displacement);
		if (len == 0 && Game::GameWorld->WorldTileAtPosition(position)->Neighbors.size() == 0)
			return;
		if (len <= real_move_amount)
		{
			SetPosition(currentWaypoint + vec4(0.0, 0.0, -0.25, 0.0));
			if (++waypointCounter == waypoints->size())
				ChooseNewDestination();
			currentWaypoint = (*waypoints)[waypointCounter];

			// recursive call until real_move_amount is used up
			move(real_move_amount - len);
			return;
		}

		vec4 direction = normalize(displacement);
		if (direction.x != direction.x)
			std::cout << "wtf\n";
		vec4 translation = direction * real_move_amount;
		Translate(translation);
	}

	void Person::clampToPassableTiles()
	{
		bool chooseNewDest = false;
		WorldTile *tile = Game::GameWorld->WorldTileAtPosition(position);
		while (!tile->GetPassable())
		{
			RandomizePosition();
			chooseNewDest = true;
			tile = Game::GameWorld->WorldTileAtPosition(position);
			std::cout << "a person got into a bad spot\n";
		}
		if (chooseNewDest)
			ChooseNewDestination();
	}
}