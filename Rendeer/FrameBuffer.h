#pragma once

#include <GL/glew.h>

class Texture;

/*
A frame buffer for adding textures to render to. To create and add a default depth and stencil attatchment to
the frame buffer, use this code fragment (except with the OO interface which is not capable of doing this yet):

glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, mWidth, mHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, mDepth, 0);

*/

class FrameBuffer
{
public:
	FrameBuffer(bool attachDefaultDepthStencilRenderBuffer = false);
	~FrameBuffer();

	void AttachTexture(const Texture& texture, GLenum attatchment) const;

	bool IsComplete(GLenum *statusIfNotComplete = nullptr) const;

	inline void Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);
	}

private:
	GLuint frameBufferHandle;

	// TODO:Maybe do some RAM store of the components attatched to the GPU memory framebuffer.
	// Just to keep track of everything.
};
