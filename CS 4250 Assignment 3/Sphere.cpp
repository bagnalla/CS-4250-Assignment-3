#include "Sphere.h"
#include "Util.h"

namespace Bagnall
{
	// PUBLIC

	void Sphere::Init()
	{
		createPrototypeVertices();
	}

	Sphere::Sphere() {}

	Sphere::~Sphere() {}

	void Sphere::Draw() const
	{
		Object::Draw();
		glDrawArrays(GL_TRIANGLE_STRIP, globalVertexOffset, vertexCount);
	}

	void Sphere::DrawWithHierarchicalTransform() const
	{
		Object::DrawWithHierarchicalTransform();
		glDrawArrays(GL_TRIANGLE_STRIP, globalVertexOffset, vertexCount);
	}

	// PRIVATE

	int Sphere::globalVertexOffset, Sphere::vertexCount;

	void Sphere::createPrototypeVertices()
	{
		std::vector<vec4> sphere = Util::CreateSphere(6.0);
		std::vector<vec4> normals = Util::CreateSphereNormals(sphere);

		vertexCount = sphere.size();
		globalVertexOffset = Game::Vertices.size();
		Game::Vertices.insert(Game::Vertices.end(), sphere.begin(), sphere.end());
		Game::Normals.insert(Game::Normals.end(), normals.begin(), normals.end());
	}
}