#pragma once

#include <memory>
#include <vector>

//Camera

#include "ueCamera.h"
#include "ueGameEngine.h"
//profiler
//scene


#include <execution>
#include <fstream>
#include <iostream>
#include <typeinfo>

class ueGame
{
public:
	ueGame();

	virtual ~ueGame() = default;

	virtual void update(float dt)
	{

	}

	virtual void start()
	{

	}

	void updateActiveScenes(float dt);


};