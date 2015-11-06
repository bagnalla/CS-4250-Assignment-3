/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Track class. Inherits from Object. A track
					object generates itself in the middle of the game world and uses
					a cosine function create the curves. This class is a bit
					complicated and messy compared to everything else.

Date:				November 9, 2015

*************************************************************************************/

#ifndef TRACK_H
#define TRACK_H

#include "Object.h"

namespace Bagnall
{
	class Cube;

	class Track : public Object
	{
	public:
		Track(std::vector<vec4> points, float vFactor, float zFactor, float trackW, int globalVertexOffset, int totalVertexCount);
		Track(std::vector<vec4> points, float vFactor, float zFactor, float trackWidth);

		~Track();

		void Update();

		void DrawWithHierarchicalTransform() const;

		void ApplyHierarchicalTransform();

		std::vector<vec4>* GetPath();

		std::vector<vec4>* GetOuterVertices();

		int GetGlobalVertexOffset() const;
		int GetTotalVertexCount() const;

	private:
		int globalVertexOffsetTrack, vertexCountTrack;
		int globalVertexOffsetRail1, vertexCountRail1;
		int globalVertexOffsetRail2, vertexCountRail2;
		int globalVertexOffsetCurvyPath, vertexCountCurvyPath;

		float trackWidth;
		std::vector<vec4> path;
		std::vector<vec4> curvyPath;
		std::vector<vec4> curvyPathNormals;
		std::vector<vec4> outerVertices;

		std::vector<Cube*> ties;

		void init(std::vector<vec4> points, float vFactor, float zFactor, float trackW, int globalVertexOffset, int totalVertexCount);

		void createPath(std::vector<vec4> points, float vFactor, float zFactor);

		void createVertices(int globalVertexOffset, int totalVertexCount);

		void createTies();

		void repositionPath();
	};
}

#endif
