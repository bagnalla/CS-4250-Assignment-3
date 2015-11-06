/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Implementation file for the Object class.

Date:				October 19, 2015

*************************************************************************************/

#include "Object.h"
#include "Material.h"
#include "Util.h"
#include "LightSource.h"

namespace Bagnall
{
	// PUBLIC

	Object::Object()
	{
		position = vec4();
		//color = vec4(0.0, 0.0, 0.0, 1.0);
		theta = vec3();
		scale = vec3(1.0, 1.0, 1.0);
		SetMaterial(Material::Plastic(vec4(1.0, 1.0, 1.0, 1.0)));
		parentTransform = Util::Identity();
		changedFlags = INT_MAX;
	}

	Object::~Object()
	{
		for (std::vector<Object*>::iterator it = children.begin(); it != children.end(); it++)
			delete *it;
	}

	void Object::Update()
	{
		updateModelView();
		for (std::vector<Object*>::iterator it = children.begin(); it != children.end(); it++)
			(*it)->Update();
	}
	
	void Object::Draw() const
	{
		glUniformMatrix4fv(Game::ModelViewLoc, 1, GL_TRUE, modelView);
		//glUniform4fv(Game::ColorLoc, 1, color);
		glUniform4fv(Game::AmbientProductLoc, 1, ambientProduct);
		glUniform4fv(Game::DiffuseProductLoc, 1, diffuseProduct);
		glUniform4fv(Game::SpecularProductLoc, 1, specularProduct);
		glUniform1f(Game::ShininessLoc, material.shininess);
	};

	void Object::DrawWithHierarchicalTransform() const
	{
		glUniformMatrix4fv(Game::ModelViewLoc, 1, GL_TRUE, hierarchicalTransform);
		//glUniform4fv(Game::ColorLoc, 1, color);
		glUniform4fv(Game::AmbientProductLoc, 1, ambientProduct);
		glUniform4fv(Game::DiffuseProductLoc, 1, diffuseProduct);
		glUniform4fv(Game::SpecularProductLoc, 1, specularProduct);
		glUniform1f(Game::ShininessLoc, material.shininess);
	};

	vec4 Object::GetColor() const
	{
		return color;
	}
	void Object::SetColor(const vec4& c)
	{
		color = c;
	}

	Material Object::GetMaterial() const
	{
		return material;
	}
	void Object::SetMaterial(const Material& m)
	{
		material = m;
		ambientProduct = Util::Product(material.ambient, LightSource::Default.ambient);
		diffuseProduct = Util::Product(material.diffuse, LightSource::Default.diffuse);
		specularProduct = Util::Product(material.specular, LightSource::Default.specular);
	}
	void Object::UseMaterial(const Material& m) const
	{
		glUniform4fv(Game::AmbientProductLoc, 1, m.ambient * LightSource::Default.ambient);
		glUniform4fv(Game::DiffuseProductLoc, 1, m.diffuse * LightSource::Default.diffuse);
		glUniform4fv(Game::SpecularProductLoc, 1, m.specular * LightSource::Default.specular);
		glUniform1f(Game::ShininessLoc, m.shininess);
	}

	vec4 Object::GetPosition() const
	{
		return position;
	}
	void Object::SetPosition(const vec4& p)
	{
		vec4 translation = p - position;
		Translate(translation);
	}
	void Object::Translate(const vec4& translation)
	{
		position += translation;
		changedFlags |= TRANSLATION_CHANGED;
	}

	float Object::GetRotationX() const
	{
		return theta.x;
	}
	void Object::SetRotationX(float rotX)
	{
		float x = rotX - theta.x;
		RotateX(x);
	}
	void Object::RotateX(float x)
	{
		/*modelView = Angel::Translate(position)
			* Util::RotateZ(theta.z) * Util::RotateY(theta.y) * Util::RotateX(theta.x + x)
			* Util::RotateX(-theta.x) * Util::RotateY(-theta.y) * Util::RotateZ(-theta.z)
			* Angel::Translate(-position)
			* modelView;*/
		theta.x = Util::WrapAngle(theta.x + x);
		changedFlags |= ROTATIONX_CHANGED;
	}

	float Object::GetRotationY() const
	{
		return theta.y;
	}
	void Object::SetRotationY(float rotY)
	{
		float y = rotY - theta.y;
		RotateY(y);
	}
	void Object::RotateY(float y)
	{
		/*modelView = Angel::Translate(position)
			* Util::RotateZ(theta.z) * Util::RotateY(theta.y + y)
			* Util::RotateY(-theta.y) * Util::RotateZ(-theta.z)
			* Angel::Translate(-position)
			* modelView;*/
		theta.y = Util::WrapAngle(theta.y + y);
		changedFlags |= ROTATIONY_CHANGED;
	}

	float Object::GetRotationZ() const
	{
		return theta.z;
	}
	void Object::SetRotationZ(float rotZ)
	{
		float z = rotZ - theta.z;
		RotateZ(z);
	}
	void Object::RotateZ(float z)
	{
		/*modelView = Angel::Translate(position)
			* Util::RotateZ(theta.z + z)
			* Util::RotateZ(-theta.z)
			* Angel::Translate(-position)
			* modelView;*/
		theta.z = Util::WrapAngle(theta.z + z);
		changedFlags |= ROTATIONZ_CHANGED;
	}
	
	void Object::LookAt(vec4 point)
	{
		vec4 displacement = point - position;
		SetRotationZ(atan2(displacement.y, displacement.x));
		SetRotationX(atan2(displacement.z, Angel::length(Util::ChopZ(displacement))));
	}

	float Object::GetScaleX() const
	{
		return scale.x;
	}
	void Object::SetScaleX(float x)
	{
		scale.x = x;
		changedFlags |= SCALE_CHANGED;
	}
	void Object::ScaleX(float scaleFactorX)
	{
		SetScaleX(scale.x * scaleFactorX);
	}

	float Object::GetScaleY() const
	{
		return scale.y;
	}
	void Object::SetScaleY(float y)
	{
		scale.y = y;
		changedFlags |= SCALE_CHANGED;
	}
	void Object::ScaleY(float scaleFactorY)
	{
		SetScaleY(scale.y * scaleFactorY);
	}

	float Object::GetScaleZ() const
	{
		return scale.z;
	}
	void Object::SetScaleZ(float z)
	{
		scale.z = z;
		changedFlags |= SCALE_CHANGED;
	}
	void Object::ScaleZ(float scaleFactorZ)
	{
		SetScaleZ(scale.z * scaleFactorZ);
	}

	void Object::SetScale(float s)
	{
		scale.x = scale.y = scale.z = s;
		changedFlags |= SCALE_CHANGED;
	}
	void Object::SetScale(float x, float y)
	{
		scale.x = x;
		scale.y = y;
		changedFlags |= SCALE_CHANGED;
	}
	void Object::SetScale(float x, float y, float z)
	{
		scale.x = x;
		scale.y = y;
		scale.z = z;
		changedFlags |= SCALE_CHANGED;
	}
	void Object::Scale(float scaleFactor)
	{
		scale.x *= scaleFactor;
		scale.y *= scaleFactor;
		scale.z *= scaleFactor;
		changedFlags |= SCALE_CHANGED;
	}

	mat4 Object::GetModelView() const
	{
		return modelView;
	}
	mat4 Object::GetHierarchicalTransform() const
	{
		return hierarchicalTransform;
	}

	void Object::AddChild(Object *c)
	{
		c->SetParentTransform(hierarchicalTransform);
		children.push_back(c);
	}

	void Object::SetParentTransform(mat4 pt)
	{
		parentTransform = pt;
		changedFlags |= PARENT_CHANGED;
	}

	// PROTECTED

	void Object::updateModelView()
	{
		if (changedFlags)
		{
			// if our model view actually changed and not just the parent one
			if (changedFlags != PARENT_CHANGED)
			{
				if (changedFlags & TRANSLATION_CHANGED)
				{
					oldTranslationMatrix = translationMatrix;
					translationMatrix = Angel::Translate(position);
				}
				if (changedFlags & ROTATIONX_CHANGED)
					rotationXMatrix = Util::RotateX(theta.x);
				if (changedFlags & ROTATIONY_CHANGED)
					rotationYMatrix = Util::RotateY(theta.y);
				if (changedFlags & ROTATIONZ_CHANGED)
					rotationZMatrix = Util::RotateZ(theta.z);
				if (changedFlags & SCALE_CHANGED)
					scaleMatrix = Angel::Scale(scale);

				// if only translation change just change the translation instead of computing everything again
				if (changedFlags == TRANSLATION_CHANGED)
					modelView = translationMatrix * Util::InverseTranslation(oldTranslationMatrix) * modelView;
				else
					modelView = translationMatrix * rotationZMatrix * rotationYMatrix * rotationXMatrix * scaleMatrix;
			}

			hierarchicalTransform = parentTransform * modelView;

			updateChildrenParentTransforms();

			changedFlags = 0;
		}
	}

	void Object::updateChildrenParentTransforms()
	{
		for (std::vector<Object*>::iterator it = children.begin(); it != children.end(); it++)
			(*it)->SetParentTransform(hierarchicalTransform);
	}
}
