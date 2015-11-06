#include "Cube.h"
#include "Coaster.h"
#include "Cart.h"
#include "Person.h"

namespace Bagnall
{
	// PUBLIC

	Coaster::Coaster(Track *t, float v)
	{
		track = t;
		velocity = v;
		nextCartPosition = 0;
	}

	Coaster::~Coaster()
	{
		for (std::vector<Cart*>::iterator it = carts.begin(); it != carts.end(); it++)
			delete (*it);
		for (std::vector<Cube*>::iterator it = links.begin(); it != links.end(); it++)
			delete (*it);
	}

	void Coaster::Update()
	{
		/*concurrency::parallel_for_each(std::begin(carts), std::end(carts), [&](Cart *cart) {
		cart->Update();
		});*/

		for (std::vector<Cart*>::iterator it = carts.begin(); it != carts.end(); it++)
			(*it)->Update();

		//for (auto it = links.begin(); it != links.end(); it++)
		// do something
	}

	void Coaster::Draw() const
	{
		for (std::vector<Cart*>::const_iterator it = carts.begin(); it != carts.end(); it++)
			(*it)->Draw();

		//for (auto it = links.begin(); it != links.end(); it++)
		//	(*it)->Draw();
	}

	void Coaster::AddCart()
	{
		Cart *cart = new Cart(track);
		cart->SetMaterial(Material::Pewter());
		cart->Scale(0.5);
		cart->SetVelocity(velocity);
		cart->SetParentTransform(Angel::Translate(vec4(0.0, 0.0, -cart->GetScaleZ() / 2.0, 0.0)));
		carts.push_back(cart);
		if (carts.size() > 1)
			carts[nextCartPosition++]->SetTrackLocation(nextCartPosition - 1, carts[0]->GetTrackLocation());
		else
			nextCartPosition++;

		if (rand() % 3 != 0)
		{
			Person *person = new Person();
			person->Scale(0.5);
			person->Translate(vec4(0.0, 0.0, -1.0, 0.0));
			person->GetInCart(cart);
		}
	}

	void Coaster::RemoveCart()
	{
		if (carts.size() == 0)
			return;

		delete carts[carts.size() - 1];
		carts.pop_back();
		nextCartPosition--;
	}

	const std::vector<Cart*>* Coaster::GetCarts()
	{
		return &carts;
	}

	float Coaster::GetVelocity()
	{
		return velocity;
	}

	void Coaster::SetVelocity(float v)
	{
		velocity = v;
		for (std::vector<Cart*>::iterator it = carts.begin(); it != carts.end(); it++)
			(*it)->SetVelocity(v);
	}

	// PRIVATE

	void Coaster::initializeCarts(int numOfCarts)
	{
		for (int i = 0; i < numOfCarts; i++)
		{
			AddCart();
		}
	}

	void Coaster::initializeCartLocations()
	{
		for (nextCartPosition; nextCartPosition < carts.size(); nextCartPosition++)
		{
			carts[nextCartPosition]->SetTrackLocation(nextCartPosition, 0);
		}
	}
}
