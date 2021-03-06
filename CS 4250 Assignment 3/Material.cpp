#include "Material.h"
#include <vector>

namespace Bagnall
{
	// PUBLIC

	std::vector<Material> Material::StandardPlasticMaterials;
	std::vector<Material> Material::StandardRubberMaterials;

	void Material::Init()
	{
		StandardPlasticMaterials.push_back(BlackPlastic());
		StandardPlasticMaterials.push_back(WhitePlastic());
		StandardPlasticMaterials.push_back(CyanPlastic());
		StandardPlasticMaterials.push_back(GreenPlastic());
		StandardPlasticMaterials.push_back(RedPlastic());
		StandardPlasticMaterials.push_back(YellowPlastic());

		StandardRubberMaterials.push_back(BlackRubber());
		StandardRubberMaterials.push_back(WhiteRubber());
		StandardRubberMaterials.push_back(CyanRubber());
		StandardRubberMaterials.push_back(GreenRubber());
		StandardRubberMaterials.push_back(RedRubber());
		StandardRubberMaterials.push_back(YellowRubber());
	}

	Material Material::Plastic(const vec4& color)
	{
		Material m;
		m.ambient = vec4(0.0, 0.0, 0.0, 1.0) * color;
		m.diffuse = vec4(0.55, 0.55, 0.55, 1.0) * color;
		m.specular = vec4(0.7, 0.7, 0.7, 1.0) * color;
		m.emission = vec4(0.0, 0.0, 0.0, 1.0) * color;
		m.shininess = .25*128.0;
		return m;
	}

	Material Material::Rubber(const vec4& color)
	{
		Material m;
		m.ambient = vec4(0.05, 0.05, 0.05, 1.0) * color;
		m.diffuse = vec4(0.5, 0.5, 0.5, 1.0) * color;
		m.specular = vec4(0.7, 0.7, 0.7, 1.0) * color;
		m.emission = vec4(0.0, 0.0, 0.0, 1.0) * color;
		m.shininess = .078125*128.0;
		return m;
	}

	Material Material::Pewter()
	{
		Material m;
		m.ambient = vec4(0.105882, 0.058824, 0.113725, 1.0);
		m.diffuse = vec4(0.427451, 0.470588, 0.541176, 1.0);
		m.specular = vec4(0.333333, 0.333333, 0.521569, 1.0);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 9.84615;
		return m;
	}

	Material Material::Chrome()
	{
		Material m;
		m.ambient = vec4(0.25, 0.25, 0.25, 1.0);
		m.diffuse = vec4(0.4, 0.4, 0.4, 1.0);
		m.specular = vec4(0.774597, 0.774597, 0.774597, 1.0);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 76.8;
		return m;
	}

	Material Material::Obsidian()
	{
		Material m;
		m.ambient = vec4(0.05375, 0.05, 0.06625, 0.82);
		m.diffuse = vec4(0.18275, 0.17, 0.22525, 0.82);
		m.specular = vec4(0.332741, 0.328634, 0.346435, 0.82);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 38.4;
		return m;
	}

	Material Material::Silver()
	{
		Material m;
		m.ambient = vec4(0.19225, 0.19225, 0.19225, 1);
		m.diffuse = vec4(0.50754, 0.50754, 0.50754, 1);
		m.specular = vec4(0.508273, 0.508273, 0.508273, 1);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 51.2;
		return m;
	}

	Material Material::Bronze()
	{
		Material m;
		m.ambient = vec4(0.2125, 0.1275, 0.054, 1);
		m.diffuse = vec4(0.714, 0.4284, 0.18144, 1);
		m.specular = vec4(0.393548, 0.271906, 0.166721, 1);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 25.6;
		return m;
	}

	Material Material::Brass()
	{
		Material m;
		m.ambient = vec4(0.329412, 0.223529, 0.027451, 1);
		m.diffuse = vec4(0.780392, 0.568627, 0.113725, 1);
		m.specular = vec4(0.992157, 0.941176, 0.807843, 1);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 0.21794872*128.0;
		return m;
	}

	Material Material::Pearl()
	{
		Material m;
		m.ambient = vec4(0.25, 0.20725, 0.20725, 1);
		m.diffuse = vec4(1, 0.829, 0.829, 1);
		m.specular = vec4(0.296648, 0.296648, 0.296648, 1);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 0.088*128.0;
		return m;
	}

	Material Material::WhitePlastic()
	{
		Material m;
		m.ambient = vec4(0.0, 0.0, 0.0, 1.0);
		m.diffuse = vec4(0.55, 0.55, 0.55, 1.0);
		m.specular = vec4(0.7, 0.7, 0.7, 1.0);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 32.0;
		return m;
	}

	Material Material::BlackPlastic()
	{
		Material m;
		m.ambient = vec4(0.0, 0.0, 0.0, 1.0);
		m.diffuse = vec4(0.01, 0.01, 0.01, 1.0);
		m.specular = vec4(0.5, 0.5, 0.5, 1.0);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 32.0;
		return m;
	}

	Material Material::CyanPlastic()
	{
		Material m;
		m.ambient = vec4(0.0, 0.1, 0.06, 1.0);
		m.diffuse = vec4(0.0, 0.50980392, 0.50980392, 1.0);
		m.specular = vec4(0.50196078, 0.50196078, 0.50196078, 1.0);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 32.0;
		return m;
	}

	Material Material::GreenPlastic()
	{
		Material m;
		m.ambient = vec4(0.0, 0.0, 0.0, 1.0);
		m.diffuse = vec4(0.1, 0.35, 0.1, 1.0);
		m.specular = vec4(0.45, 0.55, 0.45, 1.0);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 32.0;
		return m;
	}

	Material Material::RedPlastic()
	{
		Material m;
		m.ambient = vec4(0.0, 0.0, 0.0, 1.0);
		m.diffuse = vec4(0.5, 0.0, 0.0, 1.0);
		m.specular = vec4(0.7, 0.6, 0.6, 1.0);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 32.0;
		return m;
	}

	Material Material::YellowPlastic()
	{
		Material m;
		m.ambient = vec4(0.0, 0.0, 0.0, 1.0);
		m.diffuse = vec4(0.5, 0.5, 0.0, 1.0);
		m.specular = vec4(0.6, 0.6, 0.5, 1.0);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 32.0;
		return m;
	}

	Material Material::BlackRubber()
	{
		Material m;
		m.ambient = vec4(0.02, 0.02, 0.02, 1.0);
		m.diffuse = vec4(0.01, 0.01, 0.01, 1.0);
		m.specular = vec4(0.4, 0.4, 0.4, 1.0);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 10.0;
		return m;
	}

	Material Material::WhiteRubber()
	{
		Material m;
		m.ambient = vec4(0.05, 0.05, 0.05, 1.0);
		m.diffuse = vec4(0.5, 0.5, 0.5, 1.0);
		m.specular = vec4(0.7, 0.7, 0.7, 1.0);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 10.0;
		return m;
	}

	Material Material::CyanRubber()
	{
		Material m;
		m.ambient = vec4(0.0, 0.05, 0.05, 1.0);
		m.diffuse = vec4(0.4, 0.5, 0.5, 1.0);
		m.specular = vec4(0.04, 0.7, 0.7, 1.0);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 10.0;
		return m;
	}

	Material Material::GreenRubber()
	{
		Material m;
		m.ambient = vec4(0.0, 0.05, 0.0, 1.0);
		m.diffuse = vec4(0.4, 0.5, 0.4, 1.0);
		m.specular = vec4(0.04, 0.7, 0.04, 1.0);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 10.0;
		return m;
	}

	Material Material::RedRubber()
	{
		Material m;
		m.ambient = vec4(0.05, 0.0, 0.0, 1.0);
		m.diffuse = vec4(0.5, 0.4, 0.4, 1.0);
		m.specular = vec4(0.7, 0.04, 0.04, 1.0);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 10.0;
		return m;
	}

	Material Material::YellowRubber()
	{
		Material m;
		m.ambient = vec4(0.05, 0.05, 0.0, 1.0);
		m.diffuse = vec4(0.5, 0.5, 0.4, 1.0);
		m.specular = vec4(0.7, 0.7, 0.04, 1.0);
		m.emission = vec4(0.0, 0.0, 0.0, 1.0);
		m.shininess = 10.0;
		return m;
	}
}