#include "WorldTile.h"
#include "Util.h"

namespace Bagnall
{
	// PUBLIC

	void WorldTile::Init()
	{
		createPrototypeVertices();
	}

	WorldTile::WorldTile(int xx, int yy)
	{
		passable = true;
		x = xx;
		y = yy;
		SetPosition(vec4(x, y, 0.0, 1.0));
		Object::Update();
	}

	void WorldTile::DrawWithHierarchicalTransform() const
	{
		Object::DrawWithHierarchicalTransform();

		/*if (!passable)
			UseMaterial(Material::RedRubber());*/

		glDrawArrays(GL_TRIANGLE_STRIP, globalVertexOffset, vertexCount);
	}

	bool WorldTile::GetPassable() const
	{
		return passable;
	}

	void WorldTile::SetPassable(bool p)
	{
		passable = p;
		if (!passable)
		{
			for (std::vector<WorldTile*>::iterator it = Neighbors.begin(); it != Neighbors.end(); it++)
			{
				WorldTile *neighbor = *it;
				neighbor->Neighbors.erase(std::find(neighbor->Neighbors.begin(), neighbor->Neighbors.end(), this));
			}
			Neighbors.clear();
		}
	}

	int WorldTile::GetX() const
	{
		return x;
	}

	int WorldTile::GetY() const
	{
		return y;
	}

	// PRIVATE

	int WorldTile::globalVertexOffset;
	int WorldTile::vertexCount;

	void WorldTile::createPrototypeVertices()
	{
		globalVertexOffset = Game::Vertices.size();
		std::vector<vec4> rectangle = Util::CreateRectangle(1.0);
		Game::Vertices.insert(Game::Vertices.end(), rectangle.begin(), rectangle.end());
		vertexCount = rectangle.size();

		std::vector<vec4> normals;
		for (std::vector<vec4>::iterator it = rectangle.begin(); it != rectangle.end(); it++)
			normals.push_back(Angel::normalize(vec4(0.0, 0.0, -1.0, 0.0)));
		Game::Normals.insert(Game::Normals.end(), normals.begin(), normals.end());
	}
}