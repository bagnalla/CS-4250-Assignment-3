#include "Bush.h"
#include "Util.h"
#include "Game.h"
#include "Cube.h"
#include "World.h"
#include "WorldTile.h"

namespace Bagnall
{
	// PUBLIC

	void Bush::Init()
	{
		createPrototypeVertices();
	}

	void Bush::ClearBushes()
	{
		for (int i = 0; i < Bushes.size();)
			delete Bushes[i];
	}

	Bush::Bush(BushType t)
	{
		type = t;
		SetMaterial(Material::GreenPlastic());

		// top fence
		Cube *cube = new Cube();
		cube->SetScale(1.0, 0.1, 0.1);
		cube->Translate(vec4(0.0, 0.45, 0.0, 0.0));
		cube->SetMaterial(Material::CyanRubber());
		fence.push_back(cube);
		AddChild(cube);

		// bottom fence
		cube = new Cube();
		cube->SetScale(1.0, 0.1, 0.1);
		cube->Translate(vec4(0.0, -0.45, 0.0, 0.0));
		cube->SetMaterial(Material::CyanRubber());
		fence.push_back(cube);
		AddChild(cube);

		// left fence
		cube = new Cube();
		cube->SetScale(0.1, 1.0, 0.1);
		cube->Translate(vec4(-0.45, 0.0, 0.0, 0.0));
		cube->SetMaterial(Material::CyanRubber());
		fence.push_back(cube);
		AddChild(cube);

		// right fence
		cube = new Cube();
		cube->SetScale(0.1, 1.0, 0.1);
		cube->Translate(vec4(0.45, 0.0, 0.0, 0.0));
		cube->SetMaterial(Material::CyanRubber());
		fence.push_back(cube);
		AddChild(cube);

		RandomizeLocation();

		Bushes.push_back(this);

		Update();
	}

	Bush::~Bush()
	{
		Game::GameWorld->WorldTileAtPosition(position)->SetPassable(true);
		Bushes.erase(std::find(Bushes.begin(), Bushes.end(), this));
	}

	void Bush::Update()
	{
		Object::Update();
	}

	void Bush::Draw() const
	{
		Object::Draw();

		if (type == Bagnall::BUSH_TYPE_ROUND)
			glDrawArrays(GL_TRIANGLE_STRIP, globalVertexOffsetRound, vertexCountRound);
		else
			glDrawArrays(GL_TRIANGLE_STRIP, globalVertexOffsetSwirly, vertexCountSwirly);

		for (std::vector<Cube*>::const_iterator it = fence.begin(); it != fence.end(); it++)
			(*it)->DrawWithHierarchicalTransform();
	}

	void Bush::DrawWithHierarchicalTransform() const
	{
		Object::DrawWithHierarchicalTransform();

		if (type == Bagnall::BUSH_TYPE_ROUND)
			glDrawArrays(GL_TRIANGLE_STRIP, globalVertexOffsetRound, vertexCountRound);
		else
			glDrawArrays(GL_TRIANGLE_STRIP, globalVertexOffsetSwirly, vertexCountSwirly);

		for (std::vector<Cube*>::const_iterator it = fence.begin(); it != fence.end(); it++)
			(*it)->DrawWithHierarchicalTransform();
	}

	void Bush::RandomizeLocation()
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

		worldTilesArray[index_x][index_y]->SetPassable(false);
		SetPosition(worldTilesArray[index_x][index_y]->GetPosition());

		Game::GameWorld->WorldTileAtPosition(position)->SetMaterial(Material::RedRubber());
	}

	// PRIVATE

	int Bush::globalVertexOffsetRound, Bush::vertexCountRound;
	int Bush::globalVertexOffsetSwirly, Bush::vertexCountSwirly;

	std::vector<Bush*> Bush::Bushes;

	void Bush::createPrototypeVertices()
	{
		// ROUND BUSH
		globalVertexOffsetRound = Game::Vertices.size();
		std::vector<vec4> sphere = Util::CreateSphere(6);
		std::vector<vec4> normals = Util::CreateSphereNormals(sphere);
		sphere = Util::TransformVertices(sphere, Angel::Translate(vec4(0.0, 0.0, -0.5, 0.0)) * Angel::Scale(0.4, 0.4, 0.65));
		vertexCountRound = sphere.size();
		Game::Vertices.insert(Game::Vertices.end(), sphere.begin(), sphere.end());
		Game::Normals.insert(Game::Normals.end(), normals.begin(), normals.end());

		// SWIRLY BUSH
		globalVertexOffsetSwirly = Game::Vertices.size();
		std::vector<vec4> rect = Util::CreateRectangleGeometry();
		std::vector<vec4> blob = Util::CreateBlob(2.0, &rect[0], rect.size());
		blob = Util::TransformVertices(blob, Angel::Scale(1.1, 1.1, 1.0));
		std::vector<vec4> swirly = Util::CreatePointySpiralShape(blob, normals, 30, 0.3);
		swirly = Util::TransformVertices(swirly, Angel::Scale(0.5, 0.5, 1.3));
		vertexCountSwirly = swirly.size();
		Game::Vertices.insert(Game::Vertices.end(), swirly.begin(), swirly.end());
		Game::Normals.insert(Game::Normals.end(), normals.begin(), normals.end());
	}
}
