#include "Track.h"
#include "Util.h"
#include "Cube.h"
#include "Material.h"

#define VERTEX_REDUCTION_FACTOR 4

namespace Bagnall
{
	// PUBLIC

	Track::Track(std::vector<vec4> points, float vFactor, float zFactor, float trackW, int globalVertexOffset, int totalVertexCount)
	{
		init(points, vFactor, zFactor, trackW, globalVertexOffset, totalVertexCount);
	}

	Track::Track(std::vector<vec4> points, float vFactor, float zFactor, float trackW)
	{
		init(points, vFactor, zFactor, trackW, Game::Vertices.size(), 0);
	}

	Track::~Track()
	{
	/*	for (std::vector<Cube*>::iterator it = ties.begin(); it != ties.end(); it++)
			delete *it;*/
	}

	void Track::Update()
	{
		Object::Update();
	}

	void Track::DrawWithHierarchicalTransform() const
	{
		Object::DrawWithHierarchicalTransform();

		glDrawArrays(GL_TRIANGLE_STRIP, globalVertexOffsetTrack, vertexCountTrack);

		UseMaterial(Material::Silver());
		glDrawArrays(GL_TRIANGLE_STRIP, globalVertexOffsetRail1, vertexCountRail1);
		glDrawArrays(GL_TRIANGLE_STRIP, globalVertexOffsetRail2, vertexCountRail2);

		if (Game::DebugMode)
		{
			glLineWidth(3.0);
			glUniform1i(Game::EmissiveLoc, 1);
			glUniform4fv(Game::EmissionColorLoc, 1, vec4(1.0, 1.0, 1.0, 1.0));
			glDrawArrays(GL_LINE_LOOP, globalVertexOffsetCurvyPath, vertexCountCurvyPath);
			glUniform1i(Game::EmissiveLoc, 0);
		}

		for (std::vector<Cube*>::const_iterator it = ties.begin(); it != ties.end(); it++)
			(*it)->DrawWithHierarchicalTransform();
	}

	void Track::ApplyHierarchicalTransform()
	{
		Object::Update();
		path = Util::TransformVertices(path, hierarchicalTransform);
		curvyPath = Util::TransformVertices(curvyPath, hierarchicalTransform);
		outerVertices = Util::TransformVertices(outerVertices, hierarchicalTransform);
	}

	std::vector<vec4>* Track::GetPath()
	{
		return &curvyPath;
	}

	std::vector<vec4>* Track::GetOuterVertices()
	{
		return &outerVertices;
	}
	
	int Track::GetGlobalVertexOffset() const
	{
		return globalVertexOffsetTrack;
	}
	int Track::GetTotalVertexCount() const
	{
		return vertexCountTrack + vertexCountRail1 + vertexCountRail2 + vertexCountCurvyPath;
	}

	// PRIVATE

	void Track::init(std::vector<vec4> points, float vFactor, float zFactor, float trackW, int globalVertexOffset, int totalVertexCount)
	{
		trackWidth = trackW;
		createPath(points, vFactor, zFactor);
		createVertices(globalVertexOffset, totalVertexCount);
		createTies();
		path.pop_back();
		curvyPath.pop_back();
		repositionPath();
		Object::Update();
	}

	void Track::createPath(std::vector<vec4> points, float vFactor, float zFactor)
	{
		path = Util::CreateBlob(vFactor, &points[0], points.size());
		path = Util::TransformVertices(path, Angel::Translate(vec4(0.0, 0.0, -0.5, 0.0)));
		curvyPath = path;
		for (int i = 0; i < curvyPath.size(); i++)
		{
			curvyPath[i].z += -cos(i / zFactor) / 1.5;
		}
	}

	void Track::createVertices(int globalVertexOffset, int totalVertexCount)
	{
		if (globalVertexOffset != Game::Vertices.size())
		{
			Game::Vertices.erase(Game::Vertices.begin() + globalVertexOffset, Game::Vertices.begin() + globalVertexOffset + totalVertexCount);
			Game::Normals.erase(Game::Normals.begin() + globalVertexOffset, Game::Normals.begin() + globalVertexOffset + totalVertexCount);
		}

		// MAIN STRUCTURE
		std::vector<vec4> topInside = Util::TransformVertices(curvyPath, Angel::Scale(1.0 - trackWidth / 2.0, 1.0 - trackWidth / 2.0, 1.0));
		std::vector<vec4> topOutsideCurvy = Util::TransformVertices(curvyPath, Angel::Scale(1.0 + trackWidth / 2.0, 1.0 + trackWidth / 2.0, 1.0));
		std::vector<vec4> bottomInside = Util::TransformVertices(path, Angel::Translate(vec4(0.0, 0.0, 1.5, 0.0)) * Angel::Scale(1.0 - trackWidth / 2.0, 1.0 - trackWidth / 2.0, 1.0));
		outerVertices = Util::TransformVertices(path, Angel::Translate(vec4(0.0, 0.0, 1.5, 0.0)) * Angel::Scale(1.0 + trackWidth / 2.0, 1.0 + trackWidth / 2.0, 1.0));

		std::vector<vec4> vertices;
		std::vector<vec4> normals;

		for (int i = 0; i < path.size(); i += 1)
		{
			if (i < path.size() - 1)
				curvyPathNormals.push_back(Angel::normalize(Util::ChopW(Angel::cross(topInside[i + 1] - topInside[i], topOutsideCurvy[i] - topInside[i]))));
			else
				curvyPathNormals.push_back(Angel::normalize(Util::ChopW(Angel::cross(topInside[0] - topInside[i], topOutsideCurvy[i] - topInside[i]))));
		}

		for (int i = 0; i < path.size(); i += VERTEX_REDUCTION_FACTOR)
		{
			vertices.push_back(topInside[i]);
			vertices.push_back(topOutsideCurvy[i]);
			normals.push_back(vec4(0.0, 0.0, -1.0, 0.0));
			normals.push_back(vec4(0.0, 0.0, -1.0, 0.0));
		}

		for (int i = 0; i < path.size(); i += VERTEX_REDUCTION_FACTOR)
		{
			vertices.push_back(topOutsideCurvy[i]);
			vertices.push_back(outerVertices[i]);
			normals.push_back(Angel::normalize(vec4(topOutsideCurvy[i].x, topOutsideCurvy[i].y, 0.0, 0.0)));
			normals.push_back(Angel::normalize(vec4(outerVertices[i].x, outerVertices[i].y, 0.0, 0.0)));
		}

		for (int i = 0; i < path.size(); i += VERTEX_REDUCTION_FACTOR)
		{
			vertices.push_back(outerVertices[i]);
			vertices.push_back(bottomInside[i]);
			normals.push_back(vec4(0.0, 0.0, 1.0, 0.0));
			normals.push_back(vec4(0.0, 0.0, 1.0, 0.0));
		}

		for (int i = 0; i < path.size(); i += VERTEX_REDUCTION_FACTOR)
		{
			vertices.push_back(bottomInside[i]);
			vertices.push_back(topInside[i]);
			normals.push_back(-Angel::normalize(vec4(bottomInside[i].x, bottomInside[i].y, 0.0, 0.0)));
			normals.push_back(-Angel::normalize(vec4(topInside[i].x, topInside[i].y, 0.0, 0.0)));
		}

		vertexCountTrack = vertices.size();
		globalVertexOffsetTrack = globalVertexOffset;
		Game::Vertices.insert(Game::Vertices.end(), vertices.begin(), vertices.end());
		Game::Normals.insert(Game::Normals.end(), normals.begin(), normals.end());


		// RAIL 1
		vertices.clear();
		normals.clear();
		std::vector<vec4> r1 = topInside; // bottom inside
		std::vector<vec4> r2 = Util::TransformVertices(topInside, Angel::Scale(1.01, 1.01, 1.0)); // bottom outside
		std::vector<vec4> r3 = Util::TransformVertices(topInside, Angel::Translate(vec4(0.0, 0.0, -0.05, 0.0)) * Angel::Scale(1.01, 1.01, 1.0)); // top outside
		std::vector<vec4> r4 = Util::TransformVertices(topInside, Angel::Translate(vec4(0.0, 0.0, -0.05, 0.0))); // top inside

		for (int i = 0; i < path.size(); i += VERTEX_REDUCTION_FACTOR)
		{
			vertices.push_back(r1[i]);
			vertices.push_back(r2[i]);
			normals.push_back(vec4(0.0, 0.0, 1.0, 0.0));
			normals.push_back(vec4(0.0, 0.0, 1.0, 0.0));
		}

		for (int i = 0; i < path.size(); i += VERTEX_REDUCTION_FACTOR)
		{
			vertices.push_back(r2[i]);
			vertices.push_back(r3[i]);
			normals.push_back(Angel::normalize(vec4(r2[i].x, r2[i].y, r2[i].z, 0.0)));
			normals.push_back(Angel::normalize(vec4(r3[i].x, r3[i].y, r3[i].z, 0.0)));
		}

		for (int i = 0; i < path.size(); i += VERTEX_REDUCTION_FACTOR)
		{
			vertices.push_back(r3[i]);
			vertices.push_back(r4[i]);
			normals.push_back(vec4(0.0, 0.0, -1.0, 0.0));
			normals.push_back(vec4(0.0, 0.0, -1.0, 0.0));
		}

		for (int i = 0; i < path.size(); i += VERTEX_REDUCTION_FACTOR)
		{
			vertices.push_back(r4[i]);
			vertices.push_back(r1[i]);
			normals.push_back(-Angel::normalize(vec4(r4[i].x, r4[i].y, r4[i].z, 0.0)));
			normals.push_back(-Angel::normalize(vec4(r1[i].x, r1[i].y, r1[i].z, 0.0)));
		}

		vertexCountRail1 = vertices.size();
		globalVertexOffsetRail1 = globalVertexOffsetTrack + vertices.size();
		Game::Vertices.insert(Game::Vertices.end(), vertices.begin(), vertices.end());
		Game::Normals.insert(Game::Normals.end(), normals.begin(), normals.end());

		// RAIL 2
		vertices.clear();
		normals.clear();
		r1 = topOutsideCurvy; // bottom outside
		r2 = Util::TransformVertices(topOutsideCurvy, Angel::Scale(0.99, 0.99, 1.0)); // bottom inside
		r3 = Util::TransformVertices(topOutsideCurvy, Angel::Translate(vec4(0.0, 0.0, -0.05, 0.0)) * Angel::Scale(0.99, 0.99, 1.0)); // top inside
		r4 = Util::TransformVertices(topOutsideCurvy, Angel::Translate(vec4(0.0, 0.0, -0.05, 0.0))); // top outside

		for (int i = 0; i < path.size(); i += VERTEX_REDUCTION_FACTOR)
		{
			vertices.push_back(r1[i]);
			vertices.push_back(r2[i]);
			normals.push_back(vec4(0.0, 0.0, 1.0, 0.0));
			normals.push_back(vec4(0.0, 0.0, 1.0, 0.0));
		}

		for (int i = 0; i < path.size(); i += VERTEX_REDUCTION_FACTOR)
		{
			vertices.push_back(r2[i]);
			vertices.push_back(r3[i]);
			normals.push_back(-Angel::normalize(vec4(r2[i].x, r2[i].y, r2[i].z, 0.0)));
			normals.push_back(-Angel::normalize(vec4(r3[i].x, r3[i].y, r3[i].z, 0.0)));
		}

		for (int i = 0; i < path.size(); i += VERTEX_REDUCTION_FACTOR)
		{
			vertices.push_back(r3[i]);
			vertices.push_back(r4[i]);
			normals.push_back(vec4(0.0, 0.0, -1.0, 0.0));
			normals.push_back(vec4(0.0, 0.0, -1.0, 0.0));
		}

		for (int i = 0; i < path.size(); i += VERTEX_REDUCTION_FACTOR)
		{
			vertices.push_back(r4[i]);
			vertices.push_back(r1[i]);
			normals.push_back(Angel::normalize(vec4(r4[i].x, r4[i].y, r4[i].z, 0.0)));
			normals.push_back(Angel::normalize(vec4(r1[i].x, r1[i].y, r1[i].z, 0.0)));
		}

		vertexCountRail2 = vertices.size();
		globalVertexOffsetRail2 = globalVertexOffsetRail1 + vertices.size();
		Game::Vertices.insert(Game::Vertices.end(), vertices.begin(), vertices.end());
		Game::Normals.insert(Game::Normals.end(), normals.begin(), normals.end());
	}

	void Track::createTies()
	{
		for (int i = 0; i < curvyPath.size() - 1; i += 4)
		{
			Cube *tie = new Cube();
			tie->SetScale(trackWidth * 4.0, 0.075, 0.040);
			tie->SetPosition(curvyPath[i]);
			tie->SetMaterial(Material::Brass());
			vec4 displacement = curvyPath[i + 1] - curvyPath[i];
			tie->SetRotationZ(atan2(displacement.y, displacement.x) - M_PI / 2.0);
			tie->SetRotationX(Util::Pitch(displacement));
			ties.push_back(tie);
			AddChild(tie);
		}
	}

	void Track::repositionPath()
	{
		//curvyPath = Util::TransformVertices(curvyPath, Angel::Translate(vec4(0.0, 0.0, -0.05, 0.0)));
		for (int i = 0; i < curvyPath.size(); i++)
		{
			curvyPath[i] = curvyPath[i] + curvyPathNormals[i] * 0.075;
			//Game::Vertices[globalVertexOffsetCurvyPath + i] = curvyPath[i] = curvyPath[i] + curvyPathNormals[i] * 0.075;
		}

		globalVertexOffsetCurvyPath = Game::Vertices.size();
		Game::Vertices.insert(Game::Vertices.end(), curvyPath.begin(), curvyPath.end());
		Game::Normals.insert(Game::Normals.end(), curvyPathNormals.begin(), curvyPathNormals.end());
		vertexCountCurvyPath = curvyPath.size();
	}
}
