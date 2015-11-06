/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Implementation file for the Util class.

Date:				October 19, 2015

*************************************************************************************/

#include "Util.h"

namespace Bagnall
{
	// PUBLIC

	std::vector<vec4> Util::CreateCatmullRomCurve(const vec4& p0, const vec4& p1, const vec4& p2, const vec4& p3, float curviness)
	{
		float weightIncrement = 1.0 / curviness;

		std::vector<vec4> vectors;
		for (float s = weightIncrement; s < 1.0; s += weightIncrement)
		{
			vectors.push_back(CRSpline::Eq(s, p0, p1, p2, p3));
		}

		vectors.push_back(p2);

		return vectors;
	}

	// need at least 3 vertices
	std::vector<vec4> Util::CreateBlob(float curviness, const vec4 verts[], int numOfVerts)
	{
		std::vector<vec4> vertices;

		std::vector<vec4> curve = CreateCatmullRomCurve(verts[numOfVerts - 1], verts[0], verts[1], verts[2], curviness);
		vertices.insert(vertices.end(), curve.begin(), curve.end());

		for (int i = 1; i < numOfVerts - 2; i++)
		{
			curve = CreateCatmullRomCurve(verts[i - 1], verts[i], verts[i + 1], verts[i + 2], curviness);
			vertices.insert(vertices.end(), curve.begin(), curve.end());
		}

		curve = CreateCatmullRomCurve(verts[numOfVerts - 3], verts[numOfVerts - 2], verts[numOfVerts - 1], verts[0], curviness);
		vertices.insert(vertices.end(), curve.begin(), curve.end());

		curve = CreateCatmullRomCurve(verts[numOfVerts - 2], verts[numOfVerts - 1], verts[0], verts[1], curviness);
		vertices.insert(vertices.end(), curve.begin(), curve.end());

		vertices.push_back(vertices[0]);

		return vertices;
	}

	std::vector<vec4> Util::CreateCircle(int numberOfVertices)
	{
		std::vector<vec4> vertices;
		float increment = (2 * M_PI) / (numberOfVertices - 1);
		for (float theta = 0.0f; theta <= 2 * M_PI; theta += increment)
			vertices.push_back(vec4(cos(theta), sin(theta), 0, 1));
		vertices.push_back(vec4(1.0, 0, 0, 1));
		return vertices;
	}

	std::vector<vec4> Util::CreateSphere(int definition)
	{
		float deltaTheta = M_PI / definition;
		float theta = 0;
		std::vector<vec4> sphere;

		std::vector<vec4> originalRing = Util::CreateCircle(definition * 2);
		std::vector<vec4> ring1 = originalRing;
		std::vector<vec4> ring2;

		for (int i = 0; i < definition + 1; i++)
		{
			theta += deltaTheta;
			ring2 = RotateVerticesAboutYAxis(originalRing, theta);

			for (int j = 0; j < ring1.size(); j++)
			{
				sphere.push_back(ring1[j]);
				sphere.push_back(ring2[j]);
			}

			sphere.push_back(ring1[0]);
			sphere.push_back(ring2[0]);

			ring1 = ring2;
			ring2 = RotateVerticesAboutYAxis(originalRing, theta);
		}

		/*	for (int j = 0; j < ring1.size(); j++)
			{
				sphere.push_back(originalRing[j]);
				sphere.push_back(ring2[j]);
			}
			sphere.push_back(originalRing[0]);
			sphere.push_back(ring2[0]);*/

		return sphere;
	}

	std::vector<vec4> Util::CreateCube(float size)
	{
		// taken from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/
		vec4 verts[] = { vec4(-size / 2.0, -size / 2.0, -size / 2.0, 1.0),
			vec4(-size / 2.0, -size / 2.0, size / 2.0, 1.0),
			vec4(-size / 2.0, size / 2.0, size / 2.0, 1.0),

			vec4(size / 2.0, size / 2.0, -size / 2.0, 1.0),
			vec4(-size / 2.0, -size / 2.0, -size / 2.0, 1.0),
			vec4(-size / 2.0, size / 2.0, -size / 2.0, 1.0),

			vec4(size / 2.0, -size / 2.0, size / 2.0, 1.0),
			vec4(-size / 2.0, -size / 2.0, -size / 2.0, 1.0),
			vec4(size / 2.0, -size / 2.0, -size / 2.0, 1.0),

			vec4(size / 2.0, size / 2.0, -size / 2.0, 1.0),
			vec4(size / 2.0, -size / 2.0, -size / 2.0, 1.0),
			vec4(-size / 2.0, -size / 2.0, -size / 2.0, 1.0),

			vec4(-size / 2.0, -size / 2.0, -size / 2.0, 1.0),
			vec4(-size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(-size / 2.0, size / 2.0, -size / 2.0, 1.0),

			vec4(size / 2.0, -size / 2.0, size / 2.0, 1.0),
			vec4(-size / 2.0, -size / 2.0, size / 2.0, 1.0),
			vec4(-size / 2.0, -size / 2.0, -size / 2.0, 1.0),

			vec4(-size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(-size / 2.0, -size / 2.0, size / 2.0, 1.0),
			vec4(size / 2.0, -size / 2.0, size / 2.0, 1.0),

			vec4(size / 2.0, -size / 2.0, -size / 2.0, 1.0),
			vec4(size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(size / 2.0, -size / 2.0, size / 2.0, 1.0),

			vec4(size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(size / 2.0, -size / 2.0, -size / 2.0, 1.0),
			vec4(size / 2.0, size / 2.0, -size / 2.0, 1.0),

			vec4(size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(size / 2.0, size / 2.0, -size / 2.0, 1.0),
			vec4(-size / 2.0, size / 2.0, -size / 2.0, 1.0),

			vec4(size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(-size / 2.0, size / 2.0, -size / 2.0, 1.0),
			vec4(-size / 2.0, size / 2.0, size / 2.0, 1.0),

			vec4(size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(-size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(size / 2.0, -size / 2.0, size / 2.0, 1.0)
		};

		std::vector<vec4> v;
		v.assign(verts, verts + 36);
		return v;
	}


	std::vector<vec4> Util::CreateCubeNormals()
	{
		vec4 verts[] = { vec4(-1.0, 0.0, 0.0, 0.0),
			vec4(-1.0, 0.0, 0.0, 0.0),
			vec4(-1.0, 0.0, 0.0, 0.0),

			vec4(0.0, 0.0, -1.0, 0.0),
			vec4(0.0, 0.0, -1.0, 0.0),
			vec4(0.0, 0.0, -1.0, 0.0),

			vec4(0.0, -1.0, 0.0, 0.0),
			vec4(0.0, -1.0, 0.0, 0.0),
			vec4(0.0, -1.0, 0.0, 0.0),

			vec4(0.0, 0.0, -1.0, 0.0),
			vec4(0.0, 0.0, -1.0, 0.0),
			vec4(0.0, 0.0, -1.0, 0.0),
			vec4(-1.0, 0.0, 0.0, 0.0),
			vec4(-1.0, 0.0, 0.0, 0.0),
			vec4(-1.0, 0.0, 0.0, 0.0),

			vec4(0.0, -1.0, 0.0, 0.0),
			vec4(0.0, -1.0, 0.0, 0.0),
			vec4(0.0, -1.0, 0.0, 0.0),

			vec4(0.0, 0.0, 1.0, 0.0),
			vec4(0.0, 0.0, 1.0, 0.0),
			vec4(0.0, 0.0, 1.0, 0.0),
			vec4(1.0, 0.0, 0.0, 0.0),
			vec4(1.0, 0.0, 0.0, 0.0),
			vec4(1.0, 0.0, 0.0, 0.0),
			vec4(1.0, 0.0, 0.0, 0.0),
			vec4(1.0, 0.0, 0.0, 0.0),
			vec4(1.0, 0.0, 0.0, 0.0),
			vec4(0.0, 1.0, 0.0, 0.0),
			vec4(0.0, 1.0, 0.0, 0.0),
			vec4(0.0, 1.0, 0.0, 0.0),
			vec4(0.0, 1.0, 0.0, 0.0),
			vec4(0.0, 1.0, 0.0, 0.0),
			vec4(0.0, 1.0, 0.0, 0.0),
			vec4(0.0, 0.0, 1.0, 0.0),
			vec4(0.0, 0.0, 1.0, 0.0),
			vec4(0.0, 0.0, 1.0, 0.0)
		};

		std::vector<vec4> v;
		v.assign(verts, verts + 36);
		return v;
	}

	std::vector<vec4> Util::CreateRectangle(float size)
	{
		std::vector<vec4> v;
		v.push_back(vec4(-size / 2.0, -size / 2.0, 0.0, 1.0));
		v.push_back(vec4(size / 2.0, -size / 2.0, 0.0, 1.0));
		v.push_back(vec4(-size / 2.0, size / 2.0, 0.0, 1.0));
		v.push_back(vec4(size / 2.0, size / 2.0, 0.0, 1.0));
		return v;
	}

	std::vector<vec4> Util::CreateRectangleGeometry()
	{
		std::vector<vec4> v;
		v.push_back(vec4(-1.0 / 2.0, 1.0 / 2.0, 0.0, 1.0));
		v.push_back(vec4(-1.0 / 2.0, -1.0 / 2.0, 0.0, 1.0));
		v.push_back(vec4(1.0 / 2.0, -1.0 / 2.0, 0.0, 1.0));
		v.push_back(vec4(1.0 / 2.0, 1.0 / 2.0, 0.0, 1.0));
		return v;
	}

	std::vector<vec4> Util::CreateWeirdShape(const std::vector<vec4>& originalShape, int n)
	{
		float deltaTheta = M_PI / (n - 1);
		float theta = 0;
		std::vector<vec4> shape;

		std::vector<vec4> originalRing = originalShape;
		std::vector<vec4> ring1 = originalRing;

		for (int i = 0; i < n; i++)
		{
			theta += deltaTheta;
			std::vector<vec4> ring2 = RotateVerticesAboutYAxis(originalRing, theta);

			for (int j = 0; j < ring1.size(); j++)
			{
				shape.push_back(ring1[j]);
				shape.push_back(ring2[j]);
			}

			shape.push_back(ring1[0]);
			shape.push_back(ring2[0]);

			ring1 = ring2;
			ring2 = RotateVerticesAboutYAxis(originalRing, theta);
		}

		return shape;
	}

	std::vector<vec4> Util::CreatePointyShape(const std::vector<vec4>& originalShape, int n)
	{
		float deltaTheta = M_PI / 2.0 / n;
		float theta = 0;
		std::vector<vec4> shape;

		std::vector<vec4> ring1 = originalShape;

		for (int i = 0; i < n; i++)
		{
			theta += deltaTheta;
			std::vector<vec4> ring2 = TranslateScaleVertices(originalShape, vec4(0.0, 0.0, (float)(i + 1) / n, 0.0), vec3(cos(theta), cos(theta), 0.0));

			for (int j = 0; j < ring1.size(); j++)
			{
				shape.push_back(ring1[j]);
				shape.push_back(ring2[j]);
			}

			shape.push_back(ring1[0]);
			shape.push_back(ring2[0]);

			ring1 = ring2;
			ring2 = TranslateScaleVertices(originalShape, vec4(0.0, 0.0, (float)(i + 1) / n, 0.0), vec3(cos(theta), cos(theta), 0.0));
		}

		ring1 = originalShape;
		theta = 0;

		for (int i = 0; i < n; i++)
		{
			theta += deltaTheta;
			std::vector<vec4> ring2 = TranslateScaleVertices(originalShape, vec4(0.0, 0.0, (float)(-i - 1) / n, 0.0), vec3(cos(theta), cos(theta), 0.0));

			for (int j = 0; j < ring1.size(); j++)
			{
				shape.push_back(ring1[j]);
				shape.push_back(ring2[j]);
			}

			shape.push_back(ring1[0]);
			shape.push_back(ring2[0]);

			ring1 = ring2;
			ring2 = TranslateScaleVertices(originalShape, vec4(0.0, 0.0, (float)(-i - 1) / n, 0.0), vec3(cos(theta), cos(theta), 0.0));
		}

		return shape;
	}

	std::vector<vec4> Util::CreateSpiralShape(const std::vector<vec4>& originalShape, std::vector<vec4>& normals, int n, float deltaThetaZ)
	{
		normals.clear();

		float deltaTheta = M_PI / 2.0 / n;
		float theta = 0, thetaZ = 0;
		std::vector<vec4> shape;

		std::vector<vec4> ring1 = originalShape;
		std::vector<vec4> ring2;

		for (int i = 0; i < ring1.size(); i++)
		{
			shape.push_back(vec4(0.0, 0.0, 0.0, 1.0));
			shape.push_back(ring1[i]);
			normals.push_back(vec4(0.0, 0.0, 1.0, 0.0));
			normals.push_back(vec4(0.0, 0.0, 1.0, 0.0));
		}

		for (int i = 0; i < n; i++)
		{
			theta += deltaTheta;
			thetaZ += deltaThetaZ;
			ring2 = TransformVertices(originalShape, Angel::Translate(vec4(0.0, 0.0, (float)(-i - 1) / n, 0.0)) * Util::RotateZ(thetaZ));

			std::vector<vec4> norms2 = TransformVertices(originalShape, Util::RotateZ(thetaZ));

			for (int j = 0; j < ring1.size(); j++)
			{
				shape.push_back(ring1[j]);
				shape.push_back(ring2[j]);
				normals.push_back(Angel::normalize(vec4(ring1[j].x, ring1[j].y, 0.0, 0.0)));
				normals.push_back(Angel::normalize(vec4(ring2[j].x, ring2[j].y, 0.0, 0.0)));
			}

			ring1 = ring2;
		}

		for (int i = 0; i < ring2.size(); i++)
		{
			shape.push_back(vec4(0.0, 0.0, -1.0, 1.0));
			shape.push_back(ring2[i]);
			normals.push_back(vec4(0.0, 0.0, -1.0, 0.0));
			normals.push_back(vec4(0.0, 0.0, -1.0, 0.0));
		}

		return shape;
	}

	std::vector<vec4> Util::CreatePointySpiralShape(const std::vector<vec4>& originalShape, std::vector<vec4>& normals, int n, float deltaThetaZ)
	{
		normals.clear();

		float deltaTheta = M_PI / 2.0 / n;
		float theta = 0, thetaZ = 0;
		std::vector<vec4> shape;

		std::vector<vec4> ring1 = originalShape;
		std::vector<vec4> ring2;

		for (int i = 0; i < ring1.size(); i++)
		{
			shape.push_back(vec4(0.0, 0.0, 0.0, 1.0));
			shape.push_back(ring1[i]);
			normals.push_back(vec4(0.0, 0.0, 1.0, 0.0));
			normals.push_back(vec4(0.0, 0.0, 1.0, 0.0));
		}

		for (int i = 0; i < n; i++)
		{
			theta += deltaTheta;
			thetaZ += deltaThetaZ;
			ring2 = TranslateRotateScaleVertices(originalShape, vec4(0.0, 0.0, (float)(-i - 1) / n, 0.0), vec3(0.0, 0.0, thetaZ), vec3(cos(theta), cos(theta), 0.0));

			for (int j = 0; j < ring1.size(); j++)
			{
				shape.push_back(ring1[j]);
				shape.push_back(ring2[j]);
				normals.push_back(Angel::normalize(vec4(ring1[j].x, ring1[j].y, -sin(theta) / 4.0, 0.0)));
				normals.push_back(Angel::normalize(vec4(ring2[j].x, ring2[j].y, -sin(theta) / 4.0, 0.0)));
			}

			ring1 = ring2;
		}

		return shape;
	}

	std::vector<vec4> Util::CreatePrism(const std::vector<vec4>& originalShape, std::vector<vec4>& normals)
	{
		normals.clear();
		std::vector<vec4> shape;

		std::vector<vec4> ring1 = originalShape;
		std::vector<vec4> ring2 = TranslateVertices(originalShape, vec4(0.0, 0.0, -1.0, 0.0));

		for (int i = 0; i < ring1.size(); i++)
		{
			shape.push_back(vec4(0.0, 0.0, 0.0, 1.0));
			shape.push_back(ring1[i]);
			normals.push_back(vec4(0.0, 0.0, 1.0, 0.0));
			normals.push_back(vec4(0.0, 0.0, 1.0, 0.0));
		}

		for (int i = 0; i < ring1.size(); i++)
		{
			shape.push_back(ring1[i]);
			shape.push_back(ring2[i]);
			normals.push_back(vec4(ring1[i].x, ring1[i].y, ring1[i].z, 0.0));
			normals.push_back(vec4(ring1[i].x, ring1[i].y, ring1[i].z, 0.0));
		}

		for (int i = 0; i < ring2.size(); i++)
		{
			shape.push_back(vec4(0.0, 0.0, -1.0, 1.0));
			shape.push_back(ring2[i]);
			normals.push_back(vec4(0.0, 0.0, -1.0, 0.0));
			normals.push_back(vec4(0.0, 0.0, -1.0, 0.0));
		}

		return shape;
	}

	std::vector<vec4> Util::CreateCylinderNormals(const std::vector<vec4>& circle)
	{
		std::vector<vec4> normals;

		for (int i = 0; i < circle.size() * 2; i++)
			normals.push_back(vec4(0.0, 0.0, 1.0, 0.0));
		for (int i = 0; i < circle.size(); i++)
		{
			normals.push_back(Angel::normalize(circle[i]));
			normals.push_back(Angel::normalize(circle[i]));
		}
		normals.push_back(vec4(1.0, 0.0, 0.0, 0.0));
		normals.push_back(vec4(1.0, 0.0, 0.0, 0.0));
		for (int i = 0; i < circle.size() * 2; i++)
			normals.push_back(vec4(0.0, 0.0, -1.0, 0.0));

		return normals;
	}

	std::vector<vec4> Util::CreateSphereNormals(std::vector<vec4> vertices)
	{
		std::vector<vec4> normals;
		for (std::vector<vec4>::iterator it = vertices.begin(); it != vertices.end(); it++)
		{
			vec4 normal = *it;
			normal.w = 0.0;
			normals.push_back(Angel::normalize(normal));
		}
		return normals;
	}

	std::vector<vec4> Util::TranslateVertices(const std::vector<vec4>& vertices, vec4 translate)
	{
		std::vector<vec4> scaledVertices;
		for (std::vector<vec4>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
			scaledVertices.push_back(Angel::Translate(translate) * *it);
		return scaledVertices;
	}

	std::vector<vec4> Util::TranslateScaleVertices(const std::vector<vec4>& vertices, vec4 translate, vec3 scale)
	{
		std::vector<vec4> scaledVertices;
		for (std::vector<vec4>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
			scaledVertices.push_back(Angel::Translate(translate) * Angel::Scale(scale) * *it);
		return scaledVertices;
	}

	std::vector<vec4> Util::TranslateRotateScaleVertices(const std::vector<vec4>& vertices, vec4 translate, vec3 rotate, vec3 scale)
	{
		std::vector<vec4> scaledVertices;
		for (std::vector<vec4>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
			scaledVertices.push_back(Angel::Translate(translate) * Util::RotateZ(rotate.z) * Util::RotateY(rotate.y) * Util::RotateX(rotate.x) * Angel::Scale(scale) * *it);
		return scaledVertices;
	}

	std::vector<vec4> Util::RotateVerticesAboutYAxis(const std::vector<vec4>& vertices, float deltaThetaY)
	{
		std::vector<vec4> rotatedVertices;
		for (std::vector<vec4>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
			rotatedVertices.push_back(Angel::RotateY((deltaThetaY / DegreesToRadians)) * *it);
		return rotatedVertices;
	}

	std::vector<vec4> Util::TransformVertices(const std::vector<vec4>& vertices, mat4 transform)
	{
		std::vector<vec4> transformedVertices;
		for (std::vector<vec4>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
		{
			transformedVertices.push_back(transform * *it);
		}
		return transformedVertices;
	}

	vec4 Util::ChopZ(const vec4& v)
	{
		return vec4(v.x, v.y, 0.0, v.w);
	}

	vec4 Util::ChopW(const vec4& v)
	{
		return vec4(v.x, v.y, v.z, 0.0);
	}

	float Util::Distance(const vec4& p1, const vec4& p2)
	{
		return length(p1 - p2);
	}

	float Util::Distance(const vec2& p1, const vec2& p2)
	{
		return length(p1 - p2);
	}

	float Util::DistanceSquared(const vec4& p1, const vec4& p2)
	{
		vec4 displacement = p2 - p1;
		return dot(displacement, displacement);
	}

	float Util::DistanceSquared(const vec2& p1, const vec2& p2)
	{
		vec2 displacement = p2 - p1;
		return dot(displacement, displacement);
	}

	mat4 Util::Identity()
	{
		mat4 c;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				c[i][j] = 0.0;
		for (int i = 0; i < 4; i++)
			c[i][i] = 1.0;
		return c;
	}

	std::string Util::TimeToString(int time)
	{
		time /= 1000;

		int seconds = time % 60;
		time /= 60;

		int minutes = time % 60;
		time /= 60;

		return (time != 0 ? ToStringWithLeadingZeroes(time, 2) + ":" : "")
			+ ToStringWithLeadingZeroes(minutes, 2) + ":"
			+ ToStringWithLeadingZeroes(seconds, 2);
	}

	float Util::WrapAngle(float theta)
	{
		return fmod(theta, (float)(M_PI*2.0));
	}

	mat4 Util::RotateX(float theta)
	{
		mat4 c;
		c[2][2] = c[1][1] = cos(theta);
		c[2][1] = sin(theta);
		c[1][2] = -c[2][1];
		return c;
	}

	mat4 Util::RotateY(float theta)
	{
		mat4 c;
		c[2][2] = c[0][0] = cos(theta);
		c[0][2] = sin(theta);
		c[2][0] = -c[0][2];
		return c;
	}

	mat4 Util::RotateZ(float theta)
	{
		mat4 c;
		c[0][0] = c[1][1] = cos(theta);
		c[1][0] = sin(theta);
		c[0][1] = -c[1][0];
		return c;
	}

	mat4 Util::InverseTranslation(const mat4& translation)
	{
		mat4 t = translation;
		t[0][3] *= -1;
		t[1][3] *= -1;
		t[2][3] *= -1;
		return t;
	}

	mat4 Util::Perspective(const GLfloat fovy, const GLfloat aspect, const GLfloat zNear, const GLfloat zFar)
	{
		GLfloat top = tan(fovy*DegreesToRadians / 2) * zNear;
		GLfloat right = top * aspect;

		mat4 c;
		c[0][0] = zNear / right;
		c[1][1] = zNear / -top;
		c[2][2] = -(zFar + zNear) / (zFar - zNear);
		c[2][3] = -2.0*zFar*zNear / (zFar - zNear);
		c[3][2] = -1.0;
		c[3][3] = 0.0;
		return c;
	}

	float Util::Pitch(vec4 displacement)
	{
		vec4 absDisplacement = vec4(abs(displacement.x), abs(displacement.y), abs(displacement.z), 0.0);
		float sum = absDisplacement.x + absDisplacement.y;
		if (sum == 0)
			return 0.0;
		float xWeight = absDisplacement.x / sum;
		float yWeight = 1.0 - xWeight;
		float thetaX = (xWeight * atan2(displacement.z, absDisplacement.x) + yWeight * atan2(displacement.z, absDisplacement.y)) * 0.75;
		return thetaX;
	}

	mat4 Util::LookAt(vec4 eye, vec4 dest)
	{
		vec4 displacement = dest - eye;
		return Util::RotateX(atan2(displacement.z, Angel::length(Util::ChopZ(displacement)))) * Util::RotateZ(atan2(displacement.y, displacement.x));
	}
}
