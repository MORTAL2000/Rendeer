#pragma once

#include <vector>

#include "Shader.h"
#include "Entity.h"
#include "GBuffer.h"
#include "ScreenAlignedQuad.h"

class Display;
class ILight;

class DeferredRenderer
{
public:
	DeferredRenderer(Display& display);
	~DeferredRenderer();

	void BindForUsage() const;
	void Render(const std::vector<Entity *>& entities, const std::vector<ILight *>& lights, PerspectiveCamera& camera);

private:
	
	void RenderGeometryPass(const std::vector<Entity *>& entities, PerspectiveCamera& camera);
	void RenderLightPass(const std::vector<ILight *>& lights, PerspectiveCamera& camera);


	GBuffer gBuffer;
	ScreenAlignedQuad quad;

	Display& display;



	// Debug stuff etc.
	void RenderTextureToScreen(const Texture& texture);
	Shader *renderTextureShader;
};
