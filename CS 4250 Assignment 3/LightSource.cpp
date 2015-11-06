#include "LightSource.h"

namespace Bagnall
{
	// PUBLIC

	void LightSource::Init()
	{
		/*Default.ambient = vec4(0.66, 0.66, 0.66, 1.0);
		Default.diffuse = vec4(0.66, 0.66, 0.66, 1.0);
		Default.specular = vec4(0.66, 0.66, 0.66, 1.0);*/
		Default.ambient = vec4(1.0, 1.0, 1.0, 1.0);
		Default.diffuse = vec4(1.0, 1.0, 1.0, 1.0);
		Default.specular = vec4(1.0, 1.0, 1.0, 1.0);
		/*Default.ambient = vec4(0.75, 0.75, 0.75, 1.0);
		Default.diffuse = vec4(0.75, 0.75, 0.75, 1.0);
		Default.specular = vec4(0.75, 0.75, 0.75, 1.0);*/
		Default.position = vec4(0.0, 0.0, 0.0, 1.0);
	}

	LightSource LightSource::Default;
}
