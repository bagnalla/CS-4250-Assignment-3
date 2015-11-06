/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the PathFinder class. It provides methods for
					computing the shortest path between two tiles in the world. It
					currently only implements Dijkstra's shortest path algorithm with
					no heuristics or anything fancy.

Date:				November 9, 2015

*************************************************************************************/

#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "World.h"
#include "MinHeap.h"

namespace Bagnall
{
	class PathFinder
	{
	public:

		std::vector<vec4>* DijkstraShortestPath(World *world, WorldTile *source, WorldTile *destination);

		std::vector<vec4>* DijkstraShortestPath(std::vector<WorldTile*> segment, WorldTile *source, WorldTile *destination);

		/*std::vector<vec4>* SmoothPath(const std::vector<vec4>& path);*/

	private:

		MinHeap<WorldTile*, int> Q;

		void relax(std::pair<WorldTile*, int> u);

		std::vector<vec4>* tracePath(WorldTile* u);
	};
}

#endif
