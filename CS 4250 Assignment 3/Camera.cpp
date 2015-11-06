#include "Camera.h"
#include "Util.h"
#include "Coaster.h"
#include "Cart.h"
#include "World.h"
#include "FpsTracker.h"

namespace Bagnall
{
	// PUBLIC

	Camera::Camera()
	{
		lookTheta = vec3();
		lookDirection = vec4(0.0, 1.0, 0.0, 0.0);
		holdingA = holdingD = holdingW = holdingS = false;
		zoomOut = 0.0;
		fixedPosition = vec4(Game::GameWorld->GetWidth() / 2.0, Game::GameWorld->GetHeight() / 2.0, -5.0, 1.0);
	}

	void Camera::Update()
	{
		if (mode == CAMERA_MODE_COASTER)
		{
			if (coaster == NULL)
				return;

			std::vector<Cart*> carts = *coaster->GetCarts();

			if (carts.size() == 0)
				return;

			if (coasterPosition >= carts.size())
				coasterPosition = carts.size() - 1;

			SetPosition(carts[coasterPosition]->GetPosition() + vec4(0.0, 0.0, -1.0, 0.0));
		}
		else if (mode == CAMERA_MODE_FIXED)
		{
			std::vector<Cart*> carts = *coaster->GetCarts();

			if (coaster == NULL || carts.size() == 0)
				return;

			if (coasterPosition >= carts.size())
				coasterPosition--;

			lookDirection = Angel::normalize(carts[coasterPosition]->GetPosition() - position);
		}
		else if (mode == CAMERA_MODE_FREE)
		{
			if (holdingA)
				SetPosition(position + Util::RotateZ(lookTheta.z) * Util::RotateX(lookTheta.x) * (Util::RotateZ(M_PI / 2.0) * Util::RotateX(-lookTheta.x) * Util::RotateZ(-lookTheta.z) * lookDirection) * FpsTracker::GetFrameTimeMs() / 100.0);
			if (holdingD)
				SetPosition(position - Util::RotateZ(lookTheta.z) * Util::RotateX(lookTheta.x) * (Util::RotateZ(M_PI / 2.0) * Util::RotateX(-lookTheta.x) * Util::RotateZ(-lookTheta.z) * lookDirection) *FpsTracker::GetFrameTimeMs() / 100.0);
			if (holdingW)
				SetPosition(position + lookDirection * FpsTracker::GetFrameTimeMs() / 100.0);
			if (holdingS)
				SetPosition(position - lookDirection * FpsTracker::GetFrameTimeMs() / 100.0);
		}

		/*vec4 cameraOffset = vec4(0, 0, -1.0, 0);

		vec4 lookPos = playerPos + cameraOffset + lookDirection;
		vec4 abovePlayerPos = playerPos + cameraOffset;
		vec4 cameraDisplacement = -Angel::normalize(lookDirection) * 1;
		cameraPos = abovePlayerPos + cameraDisplacement;
		cameraPos.z = std::min(-0.5, (double)cameraPos.z);*/

		updateGameCamera();
	}

	void Camera::KeyPress(unsigned char k, int x, int y)
	{
		switch (k)
		{
		case 'a':
			holdingA = true;
			break;
		case 'd':
			holdingD = true;
			break;
		case 'w':
			holdingW = true;
			break;
		case 's':
			holdingS = true;
			break;
		case 32:
			SetPosition(position + vec4(0, 0, -1, 0));
			break;
		case 'z':
			SetPosition(position + vec4(0, 0, 1, 0));
			break;
		case '1':
			SetMode(CAMERA_MODE_COASTER);
			break;
		case '2':
			SetPosition(fixedPosition);
			SetMode(CAMERA_MODE_FIXED);
			break;
		case '3':
			SetMode(CAMERA_MODE_FREE);
			break;
		case 9:
			if (mode == CAMERA_MODE_COASTER || mode  == CAMERA_MODE_FIXED)
				RotateCoasterPosition();
			break;
		}
	}

	void Camera::KeyUp(unsigned char k, int x, int y)
	{
		switch (k)
		{
		case 'a':
			holdingA = false;
			break;
		case 'd':
			holdingD = false;
			break;
		case 'w':
			holdingW = false;
			break;
		case 's':
			holdingS = false;
			break;
		}
	}

	void Camera::SpecialKeyPress(int k, int x, int y)
	{
		switch (k)
		{
		case GLUT_KEY_UP:
			zoomOut = std::max(zoomOut - 0.05 * FpsTracker::GetFrameTimeMs(), 0.0);
			break;
		case GLUT_KEY_DOWN:
			zoomOut = zoomOut + 0.05 * FpsTracker::GetFrameTimeMs();
			break;
		}
	}

	void Camera::MouseMotion(int x, int y)
	{
		//float deltaThetaZ = (x - Game::WindowSize.x / 2) / 10000.0 * Game::GameSpeedFactor();
		float deltaThetaZ = (x - Game::WindowSize.x / 2) / 1000.0;
		lookTheta.z = Util::WrapAngle(lookTheta.z - deltaThetaZ);
		//SetRotationZ(lookTheta.z);

		//float deltaThetaX = (y - Game::WindowSize.y / 2) / 10000.0 * Game::GameSpeedFactor();
		float deltaThetaX = (y - Game::WindowSize.y / 2) / 1000.0;
		lookTheta.x = Util::Clamp<float>(lookTheta.x + deltaThetaX, -M_PI / 2.0 + 0.1, M_PI / 2.0 - 0.1);

		mat4 rotation = Util::RotateZ(lookTheta.z) * Util::RotateX(lookTheta.x);
		lookDirection = rotation * (vec4(0, 1, 0, 0));

		updateGameCamera();
	}

	void Camera::SetMode(CameraMode m)
	{
		mode = m;
	}

	void Camera::SetCoaster(Coaster *c)
	{
		coaster = c;
	}

	void Camera::RotateCoasterPosition()
	{
		coasterPosition = ++coasterPosition % (*coaster->GetCarts()).size();
	}

	void Camera::SetZoomOut(float z)
	{
		zoomOut = z;
	}

	// PRIVATE

	void Camera::updateGameCamera()
	{
		vec4 lookPos;
		if (mode == CAMERA_MODE_FIXED && coaster->GetCarts()->size())
			lookPos = (*coaster->GetCarts())[coasterPosition]->GetPosition();
		else
			lookPos = position + lookDirection;

		Game::Camera = Angel::LookAt(position + (-lookDirection * zoomOut), lookPos, vec4(0, 0, 1, 0));
		glUniformMatrix4fv(Game::CameraLoc, 1, GL_TRUE, Game::Camera);

 		glUniform4fv(Game::CameraPositionLoc, 1, position);
	}
}
