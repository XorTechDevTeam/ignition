//
// Created by droncode on 8/25/17.
//
#include "XtFileSystemManager.h"

namespace xt {
namespace filesystem {
    XtFileSystemManager::XtFileSystemManager() {
        LOGMSG("*** XtFileSystemManager init ***");
    }

    XtFileSystemManager::~XtFileSystemManager() {
        for (auto& fs : _fsList) {
            if (fs) {
                delete fs;
                fs = nullptr;
            }
        }
        _fsList.clear();
        _fsOrder.clear();
    }

    void XtFileSystemManager::addFileSystem(IXtFileSystem *fsPtr) {
        if (fsPtr) {
            Guard addFuncGuard(_fsLocker);
            _fsList.emplace_back(fsPtr);

            LOGMSG("XtFileSystemManager : add new fs at %s ***", fsPtr->getFileSystemBaseDir().c_str());

            const Set<String> source = fsPtr->getFiles();
            for (auto file : source) {
                _fsOrder.insert(std::pair<String, IXtFileSystem*>(file, fsPtr));
            }
        }
    }

    void XtFileSystemManager::removeFileSystem(IXtFileSystem *fsPtr) {
        if (fsPtr) {
            Guard addFuncGuard(_fsLocker);
            _fsList.erase(std::find(_fsList.begin(), _fsList.end(), fsPtr));

            for (auto it = _fsOrder.begin(); it != _fsOrder.end();) {
                if ((*it).second == fsPtr) {
                    _fsOrder.erase(it++);
                } else {
                    ++it;
                }
            }
        }
    }

    Vector<IXtFileSystem*> XtFileSystemManager::getFileSystemList() const {
        return _fsList;
    }

    bool XtFileSystemManager::isFileExists(const String &filename, bool ignoreCache) {
        Guard addFuncGuard(_fsLocker);

        for (auto &fs : _fsList) {
            if (fs->fileExists(filename, ignoreCache)) return true;
        }
        return false;
    }

    IXtFileSystem* XtFileSystemManager::getFileSystem(const String &filename) {
        Guard addFuncGuard(_fsLocker);

        const auto iter = _fsOrder.find(filename);
        if (iter != _fsOrder.end()) {
            return (*iter).second;
        } else {
            return nullptr;
        }
    }

    void XtFileSystemManager::addOrderCache(const String &filename, IXtFileSystem *fs) {
        Guard addFuncGuard(_fsLocker);

        if (fs && fs->fileExists(filename)) {
            _fsOrder.insert(std::pair<String, IXtFileSystem *>(filename, fs));
        }
    }

    void XtFileSystemManager::removeOrderCache(const String &filename) {
        Guard addFuncGuard(_fsLocker);
        _fsOrder.erase(filename);
    }
}
}