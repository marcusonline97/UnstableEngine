#pragma once

//Might make a wrapper head later

#include <string>
// Wrappers for paths defined in CMakeLists

#if UE_BUILD_EDITOR || !defined(NDEBUG)

#define UE_Q(x) #x
#define UE_QUOTE(x) UE_Q(x)

static const std::string UE_ENGINE_PATH{ UE_QUOTE(JLE_ENGINE_PATH_CMAKE) };
#else
static const std::string UE_ENGINE_PATH{ "" };
#endif

static const std::string UE_ENGINE_RESOURCES_PATH{ UE_ENGINE_PATH + "EngineResources" };
static const std::string UE_EDITOR_RESOURCES_PATH{ UE_ENGINE_PATH + "EditorResources" };
static const std::string UE_BINARY_RESOURCES_PATH{ "" };


#if UE_BUILD_EDITOR || !defined(NDEBUG)
static const std::string GAME_RESOURCES_DIRECTORY{ UE_QUOTE(GAME_RESOURCES_DIRECTORY_CMAKE) };
#else
static std::string GAME_RESOURCES_DIRECTORY{ "GameResources" };
#endif
static const std::string ENGINE_RESOURCES_PREFIX{ "ER:" };
static const std::string EDITOR_RESOURCES_PREFIX{ "ED:" };
static const std::string GAME_RESOURCES_PREFIX{ "GR:" };
static const std::string BINARY_RESOURCES_PREFIX{ "BI:" };

enum class ueRootFolder {
    None,            // Opens the file path directly
    EngineResources, // Uses the prefix "ER:"
    EditorResources, // Uses the prefix "ED:"
    GameResources,   // Uses the prefix "GR:"
    BinaryFolder     // Uses the prefix "BI:"
};