#include "World.h"
#include "WorldTile.h"
#include "Cube.h"
#include "Track.h"

namespace Bagnall
{
	// PUBLIC

	World::World(int w, int h, float trackZFactor)
	{
		width = w;
		height = h;

		worldTiles.reserve(width * height);

		// create worldTiles array
		worldTilesArray = new WorldTile**[width];
		for (int i = 0; i < width; i++)
			worldTilesArray[i] = new WorldTile*[height];

		// create world tiles and put them in array
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				WorldTile *worldTile = new WorldTile(i, j);
				worldTile->SetMaterial(Material::Plastic(vec4(34.0 / 255.0, 139.0 / 255.0, 34.0 / 255.0, 1.0)));
				worldTilesArray[i][j] = worldTile;
				worldTiles.push_back(worldTile);
				AddChild(worldTile);
			}
		}

		// initialize neighbor pointers
		for (std::vector<WorldTile*>::iterator it = worldTiles.begin(); it != worldTiles.end(); it++)
		{
			WorldTile *tile = *it;
			int tileX = (int)tile->GetPosition().x;
			int tileY = (int)tile->GetPosition().y;

			if (tileX > 0)
				tile->Neighbors.push_back(worldTilesArray[tileX - 1][tileY]);
			if (tileX < width - 1)
				tile->Neighbors.push_back(worldTilesArray[tileX + 1][tileY]);
			if (tileY > 0)
				tile->Neighbors.push_back(worldTilesArray[tileX][tileY - 1]);
			if (tileY < height - 1)
				tile->Neighbors.push_back(worldTilesArray[tileX][tileY + 1]);
		}

		// create north wall
		Cube *wall = new Cube();
		wall->SetScale(w + 1.0, 0.5, 2.0);
		wall->Translate(vec4(w / 2.0 - 0.5, h - 0.25, -1.0, 0.0));
		wall->SetMaterial(Material::RedRubber());
		AddChild(wall);
		walls.push_back(wall);

		// create south wall
		wall = new Cube();
		wall->SetScale(w + 1.0, 0.5, 2.0);
		wall->Translate(vec4(w / 2.0 - 0.5, -0.75, -1.0, 0.0));
		wall->SetMaterial(Material::RedRubber());
		AddChild(wall);
		walls.push_back(wall);

		// create west wall
		wall = new Cube();
		wall->SetScale(0.5, h + 0.5, 2.0);
		wall->Translate(vec4(-0.75, h / 2.0 - 0.5, -1.0, 0.0));
		wall->SetMaterial(Material::RedRubber());
		AddChild(wall);
		walls.push_back(wall);

		// create east wall
		wall = new Cube();
		wall->SetScale(0.5, h + 0.5, 2.0);
		wall->Translate(vec4(w - 0.25, h / 2.0 - 0.5, -1.0, 0.0));
		wall->SetMaterial(Material::RedRubber());
		AddChild(wall);
		walls.push_back(wall);

		createTrack(trackZFactor, Game::Vertices.size(), 0);

		blockOffTilesUnderTrack();
	}

	World::~World()
	{
		for (int i = 0; i < width; i++)
		{
			//for (int j = 0; j < height; j++)
			//	delete worldTilesArray[i][j];
			delete[] worldTilesArray[i];
		}
		delete[] worldTilesArray;

		//for (std::vector<Cube*>::iterator it = walls.begin(); it != walls.end(); it++)
		//	delete *it;

		delete track;
	}

	void World::Update()
	{
		Object::Update();
		track->Update();
	}

	void World::Draw() const
	{
		for (std::vector<WorldTile*>::const_iterator it = worldTiles.begin(); it != worldTiles.end(); it++)
			(*it)->DrawWithHierarchicalTransform();
		for (std::vector<Cube*>::const_iterator it = walls.begin(); it != walls.end(); it++)
			(*it)->DrawWithHierarchicalTransform();
		track->DrawWithHierarchicalTransform();
	}

	Track* World::GetTrack()
	{
		return track;
	}

	int World::GetWidth()
	{
		return width;
	}
	int World::GetHeight()
	{
		return height;
	}

	std::vector<WorldTile*>* World::GetWorldTiles()
	{
		return &worldTiles;
	}

	WorldTile*** World::GetWorldTilesArray()
	{
		return worldTilesArray;
	}

	WorldTile* World::WorldTileAtPosition(vec4 pos)
	{
		int index_x = static_cast<int>(pos.x + 0.5);
		int index_y = static_cast<int>(pos.y + 0.5);
		return worldTilesArray[index_x][index_y];
	}

	void World::AssignSegmentNumbers()
	{
		visited.clear();
		for (std::vector<WorldTile*>::iterator it = worldTiles.begin(); it != worldTiles.end(); it++)
			visited[*it] = false;

		int segmentNumberCounter = 0;

		while (true)
		{
			for (std::vector<WorldTile*>::iterator it = worldTiles.begin(); it != worldTiles.end(); it++)
			{
				if (visited[*it] == false)
				{
					visited[*it] = true;
					(*it)->segmentNumber = segmentNumberCounter;
					assignSegmentNumbersRecursive(*it, segmentNumberCounter++);
					goto LOOP_END;
				}
			}
			break;
		LOOP_END:;
		}

		Segments.clear();
		for (std::vector<WorldTile*>::iterator it = worldTiles.begin(); it != worldTiles.end(); it++)
		{
			Segments[(*it)->segmentNumber].push_back(*it);
		}
	}

	void World::RecreateTrack(float trackZFactor)
	{
		int globalVertexOffset = track->GetGlobalVertexOffset();
		int totalVertexCount = track->GetTotalVertexCount();
		delete track;
		createTrack(trackZFactor, globalVertexOffset, totalVertexCount);
		//glBufferSubData(GL_ARRAY_BUFFER, globalVertexOffset, sizeof(vec4)*totalVertexCount, &Game::Vertices[globalVertexOffset]);
		//glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec4)*Game::Vertices.size() + globalVertexOffset, sizeof(vec4)*totalVertexCount, &Game::Normals[globalVertexOffset]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec4)*Game::Vertices.size(), &Game::Vertices[0]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec4)*Game::Vertices.size(), sizeof(vec4)*Game::Normals.size(), &Game::Normals[0]);
	}

	// PRIVATE

	void World::createTrack(float trackZFactor, int globalVertexOffset, int totalVertexCount)
	{
		std::vector<vec4> trackPoints;
		trackPoints.push_back(worldTilesArray[width / 3][height / 3]->GetPosition() - vec4(width / 2.0, height / 2.0, 0.0, 0.0));
		trackPoints.push_back(worldTilesArray[width - width / 3][height / 3]->GetPosition() - vec4(width / 2.0, height / 2.0, 0.0, 0.0));
		trackPoints.push_back(worldTilesArray[width - width / 3][height - height / 3]->GetPosition() - vec4(width / 2.0, height / 2.0, 0.0, 0.0));
		trackPoints.push_back(worldTilesArray[width / 3][height - height / 3]->GetPosition() - vec4(width / 2.0, height / 2.0, 0.0, 0.0));

		track = new Track(trackPoints, 125.0, trackZFactor, 0.1, globalVertexOffset, totalVertexCount);
		track->SetMaterial(Material::Rubber(vec4(102.0/255.0, 51.0/255.0, 0.0, 1.0)));
		track->Translate(vec4(width / 2.0, height / 2.0, -1.0, 0.0));
		//AddChild(track);
		track->ApplyHierarchicalTransform();
	}

	void World::blockOffTilesUnderTrack()
	{
		std::vector<vec4> trackOuterVertices = *track->GetOuterVertices();

		for (std::vector<vec4>::iterator it = trackOuterVertices.begin(); it != trackOuterVertices.end(); it++)
		{
			vec4 v = *it;
			WorldTile *tile = worldTilesArray[static_cast<int>(v.x + 0.5)][static_cast<int>(v.y + 0.5)];
			if (tile->GetPassable())
			{
				tile->SetPassable(false);
			}
		}
	}

	void World::assignSegmentNumbersRecursive(WorldTile *tile, int segmentNumber)
	{
		for (std::vector<WorldTile*>::iterator it = tile->Neighbors.begin(); it != tile->Neighbors.end(); it++)
		{
			if (visited[*it] == false)
			{
				visited[*it] = true;
				(*it)->segmentNumber = segmentNumber;
				assignSegmentNumbersRecursive(*it, segmentNumber);
			}
		}
	}
}
