#pragma once
#ifndef UE_FILECHANGENOTIFIER_H
#define UE_FILECHANGENOTIFIER_H

//#include "ueCommon.h"

#include "../Core/ueGameEngine.h"
#include "uePath.h"

#include <plog/Log.h>

#include <chrono>
#include <filesystem>
#include <string>
#include <vector>

#include "ueSTL/ueString.h"
#include "jleSTL/jleVectorMap.h"
#include "jleSTL/jleVectorSet.h"

#include <WickedEngine/JobSystem.h>

class ueFileIndexer
{
public:
    explicit ueFileIndexer(const std::vector<std::string>& directories,
        bool notifyAdd = true,
        bool notifyMod = true,
        bool notifyErase = true);

    ~ueFileIndexer();

    void periodicSweepThreaded();

    void periodicSweep();

    // Gets all indexed files in the system
    const ueVectorSet<uePath>& getIndexedFiles();

    // Gets all indexed files in the system, with a specified file extension
    const ueVectorSet<uePath>& getIndexedFiles(const ueString& extension);

    const ueVectorSet<uePath>* getIndexedFilesPtr(const ueString& extension);

    void setNotifyAddedCallback(std::function<void(const uePath&)> callback);
    void setNotifyModificationCallback(std::function<void(const jlePath&)> callback);
    void setNotifyEraseCallback(std::function<void(const jlePath&)> callback);

private:
    void sweep(std::vector<jlePath>& erased, std::vector<jlePath>& added, std::vector<jlePath>& modified);

    void notifyAdded(const jlePath& path);

    void notifyModification(const jlePath& path);

    void notifyErase(const uePath& path);

    bool _notifyAdd;
    bool _notifyModify;
    bool _notifyErase;

    std::function<void(const uePath&)> _notifyAddedCallback;
    std::function<void(const uePath&)> _notifyModificationCallback;
    std::function<void(const uePath&)> _notifyEraseCallback;

    std::vector<std::string> _directories;

    jleVectorSet<jlePath> _indexedFiles;

    jleVectorMap<jleString, jleVectorSet<jlePath>> _indexedFilesWithExtension;

    std::vector<uePath> _erased;
    std::vector<uePath> _added;
    std::vector<uePath> _modified;
    wi::jobsystem::context _sweepingCtx;

    std::unordered_map<std::string, std::filesystem::file_time_type> _pathsMonitored;
};

#endif // UE_FILECHANGENOTIFIER_H