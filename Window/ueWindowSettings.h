#pragma once

//Probably some other bloated helper classes here aswell

//Some serialization
#include <string>

class ueWindowSettings
{
public:
	std::string WindowTitle{ "UnstableEngine 0.1" };

	unsigned int windowWidth = 1920, windowHeight = 1080;
	unsigned int widthMin = 500, heightMin = 500;

	//Add Icon

	bool isRezisable = true;
	bool shouldDisplayCursor = true;
	bool isCappedFps = false;

	//Serialization
};