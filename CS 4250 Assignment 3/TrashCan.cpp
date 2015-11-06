#include "TrashCan.h"
#include "World.h"
#include "WorldTile.h"
#include "Wheel.h"
#include "Util.h"

namespace Bagnall
{
	// PUBLIC

	void TrashCan::Init()
	{
		createPrototypeVertices();
	}

	std::vector<TrashCan*> TrashCan::TrashCans;

	void TrashCan::ClearTrashCans()
	{
		for (int i = 0; i < TrashCans.size();)
			delete TrashCans[i];
	}

	TrashCan::TrashCan()
	{
		SetMaterial(Material::Chrome());

		lid = new Wheel(2);
		lid->SetScale(0.05, 0.3, 0.3);
		lid->RotateY(M_PI / 2.0);
		lid->Translate(vec4(0.0, 0.0, -0.5, 0.0));
		lid->SetMaterial(Material::Chrome());
		AddChild(lid);

		TrashCans.push_back(this);
	}

	TrashCan::~TrashCan()
	{
		Game::GameWorld->WorldTileAtPosition(position)->SetPassable(true);
		TrashCans.erase(std::find(TrashCans.begin(), TrashCans.end(), this));
		//delete lid;
	}

	void TrashCan::Update()
	{
		Object::Update();
	}

	void TrashCan::Draw() const
	{
		Object::Draw();
		glDrawArrays(GL_TRIANGLE_STRIP, globalVertexOffset, vertexCount);
		lid->DrawWithHierarchicalTransform();
	}

	void TrashCan::DrawWithHierarchicalTransform() const
	{
		Object::DrawWithHierarchicalTransform();
		glDrawArrays(GL_TRIANGLE_STRIP, globalVertexOffset, vertexCount);
		lid->DrawWithHierarchicalTransform();
	}

	void TrashCan::SetRandomLocationInSegment(std::vector<WorldTile*> segment)
	{
		WorldTile *tile = segment[rand() % segment.size()];
		tile->SetPassable(false);
		SetPosition(tile->GetPosition());
	}

	// PRIVATE

	int TrashCan::globalVertexOffset, TrashCan::vertexCount;

	void TrashCan::createPrototypeVertices()
	{
		globalVertexOffset = Game::Vertices.size();

		std::vector<vec4> circle = Util::CreateCircle(10);
		std::vector<vec4> normals;
		std::vector<vec4> cylinder = Util::CreatePrism(circle, normals);
		cylinder = Util::TransformVertices(cylinder, Angel::Scale(0.25, 0.25, 0.5));

		vertexCount = cylinder.size();
		Game::Vertices.insert(Game::Vertices.end(), cylinder.begin(), cylinder.end());
		Game::Normals.insert(Game::Normals.end(), normals.begin(), normals.end());
	}
}
