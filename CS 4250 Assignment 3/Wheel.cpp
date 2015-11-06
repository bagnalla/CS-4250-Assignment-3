#include "Wheel.h"
#include "Util.h"
#include "Cube.h"

namespace Bagnall
{
	// PUBLIC

	void Wheel::Init()
	{
		createPrototypeVertices();
	}

	Wheel::Wheel(int numOfSpokes)
	{
		float _theta = 0;
		float deltaTheta = M_PI / (numOfSpokes);
		for (int i = 0; i < numOfSpokes; i++)
		{
			Cube *spoke = new Cube();
			spoke->SetScale(1.1, 1.6, 0.15);
			spoke->SetRotationX(_theta);
			spoke->SetMaterial(Material::WhitePlastic());
			spokes.push_back(spoke);
			AddChild(spoke);
			_theta += deltaTheta;
		}
	}

	Wheel::~Wheel()
	{
		/*for (std::vector<Cube*>::iterator it = spokes.begin(); it != spokes.end(); it++)
			delete *it;*/
		//Object::~Object();
	}

	void Wheel::Update()
	{
		Object::Update();
	}

	void Wheel::DrawWithHierarchicalTransform() const
	{
		Object::DrawWithHierarchicalTransform();

		glDrawArrays(GL_TRIANGLE_STRIP, globalVertexOffset, vertexCount);

		for (std::vector<Cube*>::const_iterator it = spokes.begin(); it != spokes.end(); it++)
			(*it)->DrawWithHierarchicalTransform();
	}

	// PRIVATE

	int Wheel::globalVertexOffset, Wheel::vertexCount;

	void Wheel::createPrototypeVertices()
	{
		globalVertexOffset = Game::Vertices.size();

		std::vector<vec4> circle = Util::CreateCircle(20);
		std::vector<vec4> normals;
		std::vector<vec4> cylinder = Util::CreatePrism(circle, normals);
		cylinder = Util::TransformVertices(cylinder, Angel::Translate(vec4(0.5, 0.0, 0.0, 0.0)) * Util::RotateY(M_PI / 2.0));
		Game::Vertices.insert(Game::Vertices.end(), cylinder.begin(), cylinder.end());

		normals = Util::TransformVertices(normals, Util::RotateY(M_PI / 2.0));
		Game::Normals.insert(Game::Normals.end(), normals.begin(), normals.end());

		vertexCount = cylinder.size();
	}
}
