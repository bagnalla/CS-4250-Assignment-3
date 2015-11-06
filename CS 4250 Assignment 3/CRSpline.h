/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the CRSpline class. This class is used to
					generate sets of vertices along a curve. The author of this code
					is Radu Gruian and it was taken from the page linked below.

Date:				November 9, 2015

*************************************************************************************/

// FROM http://www.codeproject.com/Articles/30838/Overhauser-Catmull-Rom-Splines-for-Camera-Animatio

#ifndef CRSPLINE_H
#define CRSPLINE_H

#include "Angel.h"
#include <vector>

class CRSpline
{
public:

	// Constructors and destructor
	CRSpline();
	CRSpline(const CRSpline&);
	~CRSpline();

	// Operations
	void AddSplinePoint(const vec4& v);
	vec4 GetInterpolatedSplinePoint(float t);   // t = 0...1; 0=vp[0] ... 1=vp[max]
	int GetNumPoints();
	vec4& GetNthPoint(int n);

	// Static method for computing the Catmull-Rom parametric equation
	// given a time (t) and a vector quadruple (p1,p2,p3,p4).
	static vec4 Eq(float t, const vec4& p1, const vec4& p2, const vec4& p3, const vec4& p4);

private:
	std::vector<vec4> vp;
	float delta_t;
};

#endif
