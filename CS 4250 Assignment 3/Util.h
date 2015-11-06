/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Util class. This class is a container
					for static utility functions.

Date:				November 9, 2015

*************************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include "Angel.h"
#include "CRSpline.h"
#include "Game.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace Bagnall
{
	class Line;

	class Util
	{
	public:
		/**********************************************************************
		Function:		CreateCatmullRomCurve
		Purpose:		Generate vertices along a curve using a Catmull-Rom
		spline function.
		Parameters:		vec4 previousPoint - control point 0
		vec4 point1 - control point 1
		vec4 point2 - control point 2
		vec4 afterPoint - control point 3
		float curviness - determines the number of points along
		the curve to generate
		Calls:			CRSpline::Eq
		**********************************************************************/
		static std::vector<vec4> CreateCatmullRomCurve(const vec4& p0, const vec4& p1, const vec4& p2, const vec4& p3, float curviness);

		/**********************************************************************
		Function:		CreateBlob
		Purpose:		Generate a "blob" of vertices based on a set of input
		vertices. The resulting set of vertices will be similar
		to the input but with extra points along curves around
		them.
		Parameters:		float curviness - determines the number of points along
		the curves to generate
		vec4 verts[] - the input vertices
		int numOfVerts - the number of input vertices
		Preconditions:	There must be at least three input vertices.
		Calls:			CRSpline::Eq
		**********************************************************************/
		static std::vector<vec4> CreateBlob(float curviness, const vec4 verts[], int numOfVerts);

		/**********************************************************************
		Function:		CreateCircle
		Purpose:		Generate a circle of vertices around a given point
		with a given radius.
		Parameters:		vec4 position - center position of the circle
		float radius - radius of the circle
		int numberOfVertices - the # of vertices to generate
		**********************************************************************/
		static std::vector<vec4> CreateCircle(int numberOfVertices);

		static std::vector<vec4> CreateSphere(int definition);

		/**********************************************************************
		Function:		CreateCircle
		Purpose:		Generate the vertices for a cube.
		Parameters:		float size - the height/width/depth of the cube
		**********************************************************************/
		static std::vector<vec4> CreateCube(float size);

		static std::vector<vec4> CreateCubeNormals();

		static std::vector<vec4> CreateRectangle(float size);

		static std::vector<vec4> CreateRectangleGeometry();

		static std::vector<vec4> CreateWeirdShape(const std::vector<vec4>& originalShape, int n);

		static std::vector<vec4> CreatePointyShape(const std::vector<vec4>& originalShape, int n);

		static std::vector<vec4> CreateSpiralShape(const std::vector<vec4>& originalShape, std::vector<vec4>& normals, int n, float deltaThetaZ);

		static std::vector<vec4> CreatePointySpiralShape(const std::vector<vec4>& originalShape, std::vector<vec4>& normals, int n, float deltaThetaZ);

		static std::vector<vec4> CreatePrism(const std::vector<vec4>& originalShape, std::vector<vec4>& normals);

		static std::vector<vec4> CreateCylinderNormals(const std::vector<vec4>& circle);

		static std::vector<vec4> CreateSphereNormals(std::vector<vec4> vertices);

		static std::vector<vec4> TranslateVertices(const std::vector<vec4>& vertices, vec4 translate);

		static std::vector<vec4> TranslateScaleVertices(const std::vector<vec4>& vertices, vec4 translate, vec3 scale);

		static std::vector<vec4> TranslateRotateScaleVertices(const std::vector<vec4>& vertices, vec4 translate, vec3 rotate, vec3 scale);

		static std::vector<vec4> RotateVerticesAboutYAxis(const std::vector<vec4>& vertices, float deltaThetaY);

		static std::vector<vec4> TransformVertices(const std::vector<vec4>& vertices, mat4 transform);

		/**********************************************************************
		Function:		ChopZ
		Purpose:		Return a copy of the input vector with the Z component
		set to zero.
		Parameters:		vec4 v - input vector
		**********************************************************************/
		static vec4 ChopZ(const vec4& v);

		static vec4 ChopW(const vec4& v);

		/**********************************************************************
		Function:		Distance
		Purpose:		Compute the distance between two given points.
		Parameters:		vec4 p1 - point 1
		vec4 p2 - point 2
		**********************************************************************/
		static float Distance(const vec4& p1, const vec4& p2);

		static float Distance(const vec2& p1, const vec2& p2);

		/**********************************************************************
		Function:		DistanceSquared
		Purpose:		Compute the distance between two given points squared.
		Parameters:		vec4 p1 - point 1
		vec4 p2 - point 2
		**********************************************************************/
		static float DistanceSquared(const vec4& p1, const vec4& p2);

		static float DistanceSquared(const vec2& p1, const vec2& p2);

		static vec4 Product(const vec4& v1, const vec4& v2)
		{
			return vec4(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z, v1.w*v2.w);
		}

		static vec4 Cross(const vec4& a, const vec4& b)
		{
			return vec4(a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x,
				0.0);
		}

		/**********************************************************************
		Function:		Identity
		Purpose:		Returns a 4x4 identity matrix.
		**********************************************************************/
		static mat4 Identity();

		/**********************************************************************
		Function:		TimeToString
		Purpose:		Converts a time value in milliseconds to a formatted
		string.
		Parameters:		int time - time value in milliseconds
		**********************************************************************/
		static std::string TimeToString(int time);

		/**********************************************************************
		Function:		WrapAngle
		Purpose:		Wrap an angle to the range [0, 2*PI)
		Parameters:		float theta - angle in radians
		**********************************************************************/
		static float WrapAngle(float theta);

		static mat4 RotateX(float theta);

		static mat4 RotateY(float theta);

		static mat4 RotateZ(float theta);

		static mat4 InverseTranslation(const mat4& translation);

		static mat4 Perspective(const GLfloat fovy, const GLfloat aspect, const GLfloat zNear, const GLfloat zFar);

		static float Pitch(vec4 displacement);

		static mat4 LookAt(vec4 eye, vec4 dest);

		template<class T>
		static std::string ToString(const T& value)
		{
			std::stringstream sstream;
			sstream << value;
			return sstream.str();
		}

		template<class T>
		static std::string ToStringWithLeadingZeroes(const T& value, const int numOfZeroes)
		{
			std::stringstream sstream;
			sstream << std::setfill('0') << std::setw(numOfZeroes) << value;
			return sstream.str();
		}

		template <typename T>
		static T Clamp(const T& n, const T& lower, const T& upper)
		{
			return std::max(lower, std::min(n, upper));
		}
	};
}

#endif
