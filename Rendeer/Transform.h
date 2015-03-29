#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Shader;

/*
Defines a left-handed coordinate system.
*/

class Transform
{
public:
	/*
	Transform(
		glm::vec3 position = glm::vec3(0.0, 0.0, 0.0),
		glm::vec3 rotation = glm::vec3(0.0, 0.0, 0.0),
		float scale = 1.0f
	);
	*/

	Transform(
		glm::vec3 position = glm::vec3(0.0, 0.0, 0.0),
		glm::quat rotation = glm::angleAxis(1.0f, glm::vec3(0.0)),
		float scale = 1.0f
	);

	glm::mat4 GetModelMatrix() const;

	// TODO: Modifiers (like translate)!

	inline glm::vec3 GetPosition() const
	{
		return position;
	}
	
	inline glm::quat GetRotation() const
	{
		return rotation;
	}

	inline float GetScale() const
	{
		return scale;
	}

	inline Transform* SetPosition(const glm::vec3& newPosition)
	{
		this->position = newPosition;
		return this;
	}
	
	inline Transform* SetRotation(const glm::vec3 axis, float angle)
	{
		this->rotation = glm::angleAxis(angle, glm::normalize(axis));
		return this;
	}

	inline Transform* SetRotation(const glm::quat newRotation)
	{
		this->rotation = glm::normalize(newRotation);
		return this;
	}
	
	inline Transform* SetScale(float newScale)
	{
		this->scale = newScale;
		return this;
	}

private:
	glm::vec3 position;
	glm::quat rotation;
	float scale;
};