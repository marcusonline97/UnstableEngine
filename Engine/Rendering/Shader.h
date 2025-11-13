#pragma once
#include <string>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);

	// Primary API (matches current implementation in Shader.cpp / RenderPass.cpp)
	void Start();
	void End();

	// Backwards-compatible aliases (some files call Use/EndUse)
	inline void Use() { Start(); }
	inline void EndUse() { End(); }

	std::string LoadFile(const char* aPath); // Move this to asset loading later
	//Custom uniform setters

	unsigned int LoadVertexShader(const char* aPath);
	unsigned int LoadFragmentShader(const char* aPath);
private:
	unsigned int shaderProgram = 0;
};