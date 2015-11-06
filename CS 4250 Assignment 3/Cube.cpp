#include "Cube.h"
#include "Util.h"

namespace Bagnall
{
	// PUBLIC

	void Cube::Draw() const
	{
		Object::Draw();
		glDrawArrays(GL_TRIANGLES, globalVertexOffset, vertexCount);
	}

	void Cube::DrawWithHierarchicalTransform() const
	{
		Object::DrawWithHierarchicalTransform();
		glDrawArrays(GL_TRIANGLES, globalVertexOffset, vertexCount);
	}

	// PRIVATE

	int Cube::globalVertexOffset, Cube::vertexCount;

	void Cube::createPrototypeVertices()
	{
		std::vector<vec4> cube = Util::CreateCube(1.0);
		std::vector<vec4> normals = Util::CreateCubeNormals();

		vertexCount = cube.size();
		globalVertexOffset = Game::Vertices.size();
		Game::Vertices.insert(Game::Vertices.end(), cube.begin(), cube.end());
		Game::Normals.insert(Game::Normals.end(), normals.begin(), normals.end());
	}
}