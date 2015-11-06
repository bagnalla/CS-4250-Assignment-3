/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Object class. This is an abstract base
					class for objects in the game which can be translated, rotated,
					and scaled.

Date:				November 9, 2015

*************************************************************************************/

#ifndef OBJECT_H
#define OBJECT_H

#include "Angel.h"
#include "Game.h"
#include "Material.h"

namespace Bagnall
{
	enum MatrixChanged
	{
		TRANSLATION_CHANGED = 1 << 0,
		ROTATIONX_CHANGED = 1 << 1,
		ROTATIONY_CHANGED = 1 << 2,
		ROTATIONZ_CHANGED = 1 << 3,
		SCALE_CHANGED = 1 << 4,
		PARENT_CHANGED = 1 << 5
	};

	class Object
	{
	public:
		/**********************************************************************
		Function:		Object constructor
		Purpose:		Create an Object object.
		**********************************************************************/
		Object();

		/**********************************************************************
		Function:		Object destructor
		Purpose:		Perform necessary cleanup of the Object when it
						is destroyed.
		**********************************************************************/
		virtual ~Object();

		/**********************************************************************
		Function:		Update
		Purpose:		Virtual update method to be overridden by a subclass.
		**********************************************************************/
		virtual void Update();

		/**********************************************************************
		Function:		Draw
		Purpose:		Draw the Object object.
		Parameters:		bool select - draw id color if true
		**********************************************************************/
		virtual void Draw() const;

		virtual void DrawWithHierarchicalTransform() const;

		/**********************************************************************
		Function:		GetColor
		Purpose:		Getter for color member variable.
		**********************************************************************/
		vec4 GetColor() const;

		/**********************************************************************
		Function:		SetColor
		Purpose:		Setter for color member variable.
		Parameters:		vec4 color - new color value
		**********************************************************************/
		void SetColor(const vec4& color);

		Material GetMaterial() const;

		void SetMaterial(const Material& m);

		void UseMaterial(const Material& m) const;

		/**********************************************************************
		Function:		GetPosition
		Purpose:		Getter for position member variable.
		**********************************************************************/
		vec4 GetPosition() const;

		/**********************************************************************
		Function:		SetPosition
		Purpose:		Setter for position member variable.
		Parameters:		vec4 position - new position value
		**********************************************************************/
		void SetPosition(const vec4& position);

		/**********************************************************************
		Function:		Translate
		Purpose:		Perform translation on the object.
		Parameters:		vec4 translation - translation vector
		**********************************************************************/
		void Translate(const vec4& translation);

		/**********************************************************************
		Function:		GetRotationX
		Purpose:		Getter for rotationX member variable.
		**********************************************************************/
		float GetRotationX() const;

		/**********************************************************************
		Function:		SetRotationX
		Purpose:		Setter for rotationX member variable.
		Parameters:		float rotationX - new rotationX value
		**********************************************************************/
		void SetRotationX(float rotationX);

		/**********************************************************************
		Function:		RotateX
		Purpose:		Perform rotation on the object about the X axis.
		Parameters:		float x - rotation amount
		**********************************************************************/
		void RotateX(float x);

		/**********************************************************************
		Function:		GetRotationY
		Purpose:		Getter for rotationY member variable.
		**********************************************************************/
		float GetRotationY() const;

		/**********************************************************************
		Function:		SetRotationY
		Purpose:		Setter for rotationY member variable.
		Parameters:		float rotationY - new rotationY value
		**********************************************************************/
		void SetRotationY(float rotationY);

		/**********************************************************************
		Function:		RotateY
		Purpose:		Perform rotation on the object about the Y axis.
		Parameters:		float y - rotation amount
		**********************************************************************/
		void RotateY(float y);

		/**********************************************************************
		Function:		GetRotationZ
		Purpose:		Getter for rotationZ member variable.
		**********************************************************************/
		float GetRotationZ() const;

		/**********************************************************************
		Function:		SetRotationZ
		Purpose:		Setter for rotationZ member variable.
		Parameters:		float rotationZ - new rotationZ value
		**********************************************************************/
		void SetRotationZ(float rotationZ);

		/**********************************************************************
		Function:		RotateZ
		Purpose:		Perform rotation on the object about the Z axis.
		Parameters:		float z - rotation amount
		**********************************************************************/
		void RotateZ(float z);

		void LookAt(vec4 point);

		/**********************************************************************
		Function:		GetScaleX
		Purpose:		Getter for scaleX member variable.
		**********************************************************************/
		float GetScaleX() const;

		/**********************************************************************
		Function:		SetScaleX
		Purpose:		Setter for scaleX member variable.
		Parameters:		float scaleX - new scaleX value
		**********************************************************************/
		virtual void SetScaleX(float scaleX);

		/**********************************************************************
		Function:		ScaleX
		Purpose:		Perform scaling on the object in the X axis.
		Parameters:		float scaleFactorX - scale amount
		**********************************************************************/
		void ScaleX(float scaleFactorX);

		/**********************************************************************
		Function:		GetScaleY
		Purpose:		Getter for scaleY member variable.
		**********************************************************************/
		float GetScaleY() const;

		/**********************************************************************
		Function:		SetScaleY
		Purpose:		Setter for scaleY member variable.
		Parameters:		float scaleY - new scaleY value
		**********************************************************************/
		virtual void SetScaleY(float scaleY);

		/**********************************************************************
		Function:		ScaleY
		Purpose:		Perform scaling on the object in the Y axis.
		Parameters:		float scaleFactorY - scale amount
		**********************************************************************/
		void ScaleY(float scaleFactorY);

		/**********************************************************************
		Function:		GetScaleZ
		Purpose:		Getter for scaleZ member variable.
		**********************************************************************/
		float GetScaleZ() const;

		/**********************************************************************
		Function:		SetScaleZ
		Purpose:		Setter for scaleZ member variable.
		Parameters:		float scaleZ - new scaleZ value
		**********************************************************************/
		virtual void SetScaleZ(float scaleZ);

		/**********************************************************************
		Function:		ScaleZ
		Purpose:		Perform scaling on the object in the Z axis.
		Parameters:		float scaleFactorZ - scale amount
		**********************************************************************/
		void ScaleZ(float scaleFactorZ);

		/**********************************************************************
		Function:		SetScale
		Purpose:		Setter for scaleX, scaleY, and scaleZ.
		Parameters:		float scale - new scale value
		**********************************************************************/
		virtual void SetScale(float scale);

		/**********************************************************************
		Function:		SetPosition
		Purpose:		Setter for position member variable.
		Parameters:		vec4 position - new position value
		**********************************************************************/
		virtual void SetScale(float scaleX, float scaleY);

		virtual void SetScale(float scaleX, float scaleY, float scaleZ);

		/**********************************************************************
		Function:		Scale
		Purpose:		Perform scaling on the object in the X, Y, and Z axes.
		Parameters:		float scaleFactor - scale amount
		**********************************************************************/
		void Scale(float scaleFactor);

		/**********************************************************************
		Function:		GetModelView
		Purpose:		Getter for modelView member variable.
		**********************************************************************/
		mat4 GetModelView() const;

		mat4 GetHierarchicalTransform() const;

		void SetParentTransform(mat4 pt);

		void AddChild(Object *c);

	protected:
		vec4 color; // color of the object (for emission)

		vec4 position; // position of the object in world space
		mat4 translationMatrix;
		mat4 oldTranslationMatrix;

		vec3 theta; // rotation about the three axes
		mat4 rotationXMatrix;
		mat4 rotationYMatrix;
		mat4 rotationZMatrix;

		vec3 scale; // scale in the three axes
		mat4 scaleMatrix;

		unsigned int changedFlags;
		mat4 modelView; // model-view matrix

		std::vector<Object*> children;

		mat4 parentTransform;
		mat4 hierarchicalTransform;

		Material material;
		vec4 ambientProduct, diffuseProduct, specularProduct;

		/**********************************************************************
		Function:		computeTransform
		Purpose:		Compute the model view matrix by concatenating 
						translation, rotation, and scale matrices that are 
						generated from their corresponding scalar value
						members.
		**********************************************************************/
		void updateModelView();

		void updateChildrenParentTransforms();
	};
}

#endif
