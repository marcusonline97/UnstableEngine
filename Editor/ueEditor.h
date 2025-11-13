#pragma once

//#include  create build configuration

//#if UE_BUILD_EDITOR


#include "../Engine/Core/ueGameEngine.h"

#include <vector>
#include <string>

class ueCamera;




class ueEditor;
inline ueEditor* gEditor;

class ueEditor : public ueGameEngine
{

};

//create a shit ton of files to handle all the classes we need. 