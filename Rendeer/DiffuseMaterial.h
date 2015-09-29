#pragma once

#include "IMaterial.h"

#include "Texture2D.h"

class DiffuseMaterial : public IMaterial
{
public:

	DiffuseMaterial();

	virtual void UpdateUniforms(const DeferredRenderer& renderer,
	                            const Transform& transform,
	                            const Camera& camera);

	// No real need to restrict access to these

	Texture2D *diffuseTexture;
	Texture2D *normalMap;

	float specularIntensity{1.0f};
	float shininess{0.0f};

};
