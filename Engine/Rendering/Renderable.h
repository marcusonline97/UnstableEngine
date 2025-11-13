#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>

#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/quaternion.hpp>

#include <glm/gtx/matrix_decompose.hpp>
#include "Shader.h"

class Renderable
{
protected:
	Renderable* parent = nullptr;

public:

	Renderable() = default;

	virtual void Render(Shader& aShader) = 0;

	void SetParent(Renderable* aParent) { parent = aParent; }

	glm::vec3 position{ 0.0f };
	glm::vec3 rotation{ 0.0f }; // Euler angles in degrees
	glm::vec3 scale{ 1.0f };

	glm::mat4 localTransform{ 1.0f };

	void SetLocalTransform(const glm::mat4& matrix)
	{
		localTransform = matrix;
	}

	glm::mat4 GetMatrix() const
	{
		glm::mat4 sceneMatrix = glm::translate(glm::mat4(1.0f), position);
		sceneMatrix = glm::rotate(sceneMatrix, rotation.x, glm::vec3(1, 0, 0));
		sceneMatrix = glm::rotate(sceneMatrix, rotation.y, glm::vec3(0, 1, 0));
		sceneMatrix = glm::rotate(sceneMatrix, rotation.z, glm::vec3(0, 0, 1));
		sceneMatrix = glm::scale(sceneMatrix, scale);

		glm::mat4 worldMatrix = sceneMatrix = localTransform;

		if (parent)
		{
			worldMatrix = parent->GetMatrix() * worldMatrix;
		}

		return worldMatrix;


	}

	void SetMatrix(const glm::mat4& matrix)
	{
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::vec3 scaleVec;
		glm::quat orientation;
		glm::vec3 translation;

		// decompose expects: matrix, scale, orientation (quat), translation, skew, perspective
		if (glm::decompose(matrix, scaleVec, orientation, translation, skew, perspective))
		{
			position = translation;
			scale = scaleVec;

			// eulerAngles returns radians; convert to degrees if you store degrees
			glm::vec3 eulerRad = glm::eulerAngles(orientation);
			rotation = glm::degrees(eulerRad);
		}
	}

}; #pragma once
