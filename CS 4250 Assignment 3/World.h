/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the World class. Inherits from Object. A World
					object is composed of a collection of WorldTiles, Cubes (walls),
					and a Track. The WorldTiles are stored as a 2D array that is
					aligned with the world coordinates that allow for easy
					constant-time lookup of the tile that corresponds to a given
					location.

Date:				November 9, 2015

*************************************************************************************/

#ifndef WORLD_H
#define WORLD_H

#include "Object.h"
//#include <unordered_map>
#include <map>
#include <vector>

namespace Bagnall
{
	class Cube;
	class Track;
	class WorldTile;

	class World : public Object
	{
	public:
		World(int w, int h, float trackZFactor);

		~World();

		void Update();

		void Draw() const;

		Track* GetTrack();

		int GetWidth();

		int GetHeight();

		std::vector<WorldTile*>* GetWorldTiles();

		WorldTile*** GetWorldTilesArray();

		WorldTile* WorldTileAtPosition(vec4 position);

		void AssignSegmentNumbers();

		void RecreateTrack(float trackZFactor);

		std::map<int, std::vector<WorldTile*> > Segments;

	private:
		int width;
		int height;
		WorldTile ***worldTilesArray;
		std::vector<WorldTile*> worldTiles;
		std::vector<Cube*> walls;
		Track *track;

		std::map<WorldTile*, bool> visited; // used by AssignSegmentNumbers

		void createTrack(float trackZFactor, int globalVertexOffset, int totalVertexCount);

		void blockOffTilesUnderTrack();

		void assignSegmentNumbersRecursive(WorldTile *tile, int segmentNumber);
	};
}

#endif
