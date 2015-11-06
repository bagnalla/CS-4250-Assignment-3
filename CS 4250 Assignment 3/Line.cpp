#include "Line.h"

namespace Bagnall
{
	// PUBLIC

	Line Line::LineObject;

	void Line::Init()
	{
		createPrototypeVertices();
	}

	void Line::Update()
	{
		Object::Update();
	}

	void Line::Draw() const
	{
		Object::Draw();
		glUniform1i(Game::EmissiveLoc, 1);
		glUniform4fv(Game::EmissionColorLoc, 1, color);
		glDrawArrays(GL_LINES, globalVertexOffset, 2);
		glUniform1i(Game::EmissiveLoc, 0);
	}

	void Line::SetTransformFromPoints(vec4 p1, vec4 p2)
	{
		/*SetPosition((p1 + p2) / 2.0);
		SetScaleY(Util::Distance(p1, p2));
		LookAt(p2);
		RotateZ(-M_PI / 2.0);*/
		vec4 displacement = p2 - p1;
		modelView = Angel::Translate((p1 + p2) / 2.0)
			* Util::RotateZ(atan2(displacement.y, displacement.x) - M_PI / 2.0)
			* Util::RotateX(atan2(displacement.z, Angel::length(Util::ChopZ(displacement))))
			* Angel::Scale(1.0, Util::Distance(p1, p2), 1.0);
	}

	// PRIVATE

	int Line::globalVertexOffset;
	void Line::createPrototypeVertices()
	{
		globalVertexOffset = Game::Vertices.size();
		Game::Vertices.push_back(vec4(0.0, 0.5, 0.0, 1.0));
		Game::Vertices.push_back(vec4(0.0, -0.5, 0.0, 1.0));
		Game::Normals.push_back(vec4(0.0, 0.0, -1.0, 0.0));
		Game::Normals.push_back(vec4(0.0, 0.0, -1.0, 0.0));
	}
}
