/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Camera class. Inherits from Object. A
					Camera object handles mouse and keyboard events and updates the
					camera matrix in the vertex shader.

Date:				November 9, 2015

*************************************************************************************/

#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"

namespace Bagnall
{
	class Coaster;

	enum CameraMode
	{
		CAMERA_MODE_COASTER,
		CAMERA_MODE_FIXED,
		CAMERA_MODE_FREE
	};

	class Camera : public Object
	{
	public:
		/**********************************************************************
		Function:		Camera constructor
		Purpose:		Create a camera object
		**********************************************************************/
		Camera();

		/**********************************************************************
		Function:		Update
		Purpose:		Update the camera object
		**********************************************************************/
		void Update();

		/**********************************************************************
		Function:		KeyPress
		Purpose:		Handler for key presses (key down)
		Parameters:		unsigned char k - the key pressed
						int x - mouse x position
						int y - mouse y position
		**********************************************************************/
		void KeyPress(unsigned char k, int x, int y);

		/**********************************************************************
		Function:		KeyUp
		Purpose:		Handler for key presses (key up)
		Parameters:		unsigned char k - the key pressed
						int x - mouse x position
						int y - mouse y position
		**********************************************************************/
		void KeyUp(unsigned char k, int x, int y);

		/**********************************************************************
		Function:		SpecialKeyPress
		Purpose:		Handler for special key presses (key down)
		Parameters:		int k - the key pressed
						int x - mouse x position
						int y - mouse y position
		**********************************************************************/
		void SpecialKeyPress(int k, int x, int y);

		/**********************************************************************
		Function:		SpecialKeyPress
		Purpose:		Handler for mouse motion
		Parameters:		int x - mouse x position
						int y - mouse y position
		**********************************************************************/
		void MouseMotion(int x, int y);

		/**********************************************************************
		Function:		SetMode
		Purpose:		Set the camera mode
		Parameters:		CameraMode m - new mode
		**********************************************************************/
		void SetMode(CameraMode m);

		/**********************************************************************
		Function:		SetCoaster
		Purpose:		Set the coaster for the camera to follow
		Parameters:		Coaster *c - the coaster
		**********************************************************************/
		void SetCoaster(Coaster *c);

		/**********************************************************************
		Function:		RotateCoasterPosition
		Purpose:		Change the cart on the coaster that the camera follows
		**********************************************************************/
		void RotateCoasterPosition();

		/**********************************************************************
		Function:		SetZoomOut
		Purpose:		Set the zoom out value.
		Parameters:		float z - new zoom out value
		**********************************************************************/
		void SetZoomOut(float z);

	private:
		bool holdingA; // holding 'a' key
		bool holdingD; // holding 'd' key
		bool holdingW; // holding 'w' key
		bool holdingS; // holding 's' key
		vec3 lookTheta; // rotation values of the camera
		vec4 lookDirection; // look direction vector of the camera
		float zoomOut; // zoom out value

		CameraMode mode; // camera mode

		Coaster *coaster; // coaster to follow
		int coasterPosition; // index of cart in the coaster to follow
		vec4 fixedPosition; // position of the camera for fixed mode

		/**********************************************************************
		Function:		updateGameCamera
		Purpose:		Update the camera matrix in the vertex shader
		**********************************************************************/
		void updateGameCamera();
	};
}

#endif
