#include "Sun.h"
#include "Util.h"
#include "Sphere.h"
#include "World.h"

namespace Bagnall
{
	// PUBLIC

	Sun::Sun(vec4 col, float v)
	{
		sphere = new Sphere();
		sphere->SetMaterial(Material::WhitePlastic());
		AddChild(sphere);
		color = col;
		velocity = v;
		createPath();
		SetPosition(path[0]);
		currentWaypoint = path[1];
		waypointCounter = 2;
	}
	Sun::~Sun()
	{
		//delete sphere;
	}

	void Sun::Update()
	{
		move(velocity * Game::GameSpeedFactor());

		Object::Update();

		updateLightModelView();
	}

	void Sun::Draw() const
	{
		Object::Draw();
		glUniform1i(Game::EmissiveLoc, 1);
		glUniform4fv(Game::EmissionColorLoc, 1, color);
		sphere->DrawWithHierarchicalTransform();
		glUniform1i(Game::EmissiveLoc, 0);
	}

	// PRIVATE

	void Sun::updateLightModelView()
	{
		glUniformMatrix4fv(Game::LightModelViewLoc, 1, GL_TRUE, modelView);
	}

	void Sun::createPath()
	{
		path = Util::CreateCircle(100);
		path = Util::TransformVertices(path, Angel::Translate(vec4(Game::GameWorld->GetWidth() / 2.0, Game::GameWorld->GetHeight() / 2.0, -15.0, 0.0)) * Angel::Scale(Game::GameWorld->GetWidth(), Game::GameWorld->GetHeight(), 1.0));
		//path = Util::TransformVertices(path, Angel::Translate(vec4(Game::GameWorld->GetWidth() / 2.0, Game::GameWorld->GetHeight() / 2.0, -20.0, 0.0)) * Angel::Scale(Game::GameWorld->GetWidth()*10.0, Game::GameWorld->GetHeight()*10.0, 1.0));
	}

	void Sun::move(float real_move_amount)
	{
		vec4 displacement = currentWaypoint - position;
		float len = length(displacement);
		if (len <= real_move_amount)
		{
			SetPosition(currentWaypoint);
			waypointCounter = ++waypointCounter % path.size();
			currentWaypoint = path[waypointCounter];

			// recursive call until real_move_amount is used up
			move(real_move_amount - len);
			return;
		}

		vec4 direction = normalize(displacement);
		vec4 translation = direction * real_move_amount;
		Translate(translation);
	}
}
