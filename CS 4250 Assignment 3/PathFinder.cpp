#include "PathFinder.h"
#include "WorldTile.h"

namespace Bagnall
{
	std::vector<vec4>* PathFinder::DijkstraShortestPath(World *world, WorldTile *source, WorldTile *destination)
	{
		Q.Clear();

		std::vector<WorldTile*> worldTiles = (*world->GetWorldTiles());
		for (std::vector<WorldTile*>::iterator it = worldTiles.begin(); it != worldTiles.end(); it++)
		{
			WorldTile *tile = *it;
			Q.Push(tile, INT_MAX);
			tile->d = INT_MAX;
		}
		Q.ChangeValue(source, 0);
		source->d = 0;
		source->parent = NULL;

		while (Q.Size())
		{
			std::pair<WorldTile*, int> u = Q.Top();
			Q.Pop();

			if (u.second == INT_MAX)
				return NULL;

			if (u.first == destination)
				return tracePath(u.first);

			relax(u);
		}

		return NULL;
	}

	std::vector<vec4>* PathFinder::DijkstraShortestPath(std::vector<WorldTile*> segment, WorldTile *source, WorldTile *destination)
	{
		Q.Clear();

		for (std::vector<WorldTile*>::iterator it = segment.begin(); it != segment.end(); it++)
		{
			WorldTile *tile = *it;
			Q.Push(tile, INT_MAX);
			tile->d = INT_MAX;
		}
		Q.ChangeValue(source, 0);
		source->d = 0;
		source->parent = NULL;

		while (Q.Size())
		{
			std::pair<WorldTile*, int> u = Q.Top();
			Q.Pop();

			if (u.first == destination)
				return tracePath(u.first);

			relax(u);
		}

		return NULL;
	}

	// PRIVATE

	void PathFinder::relax(std::pair<WorldTile*, int> u)
	{
		for (std::vector<WorldTile*>::iterator it = u.first->Neighbors.begin(); it != u.first->Neighbors.end(); it++)
		{
			WorldTile *neighbor = *it;
			if (neighbor->GetPassable() && neighbor->d > u.second + 1)
			{
				Q.ChangeValue(neighbor, u.second + 1);
				neighbor->d = u.second + 1;
				neighbor->parent = u.first;
			}
		}
	}

	std::vector<vec4>* PathFinder::tracePath(WorldTile* u)
	{
		std::vector<vec4> *path = new std::vector<vec4>();
		path->push_back(u->GetPosition());
		WorldTile *parent = u->parent;
		while (parent != NULL)
		{
			path->push_back(parent->GetPosition());
			parent = parent->parent;
		}
		return path;
	}
}
