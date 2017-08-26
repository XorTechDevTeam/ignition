//
// Created by droncode on 8/26/17.
//

#include "XtLinuxFileSystem.h"

namespace xt {
namespace platform {
    XtLinuxFileSystem::XtLinuxFileSystem() : IXtFileSystem("", false) {
        char dirBuffer[512];
        if (getcwd(dirBuffer, sizeof(dirBuffer)) != nullptr) {
            _fsBaseDirectory = String(dirBuffer);
            loadFsCache();
            LOGMSG("> LinuxFS: base dir : %s | total files : %lld", dirBuffer, _fsCache.size());
        } else {
            LOGMSG("> LinuxFS: unable to detect work directory (errno=%d)", errno);
        }
    }

    bool XtLinuxFileSystem::fileExists(const String &filename, bool ignoreCache) {
        bool result;

        if (ignoreCache) {
            struct stat fStat;
            bzero(&fStat, sizeof(struct stat));

            const int rx = stat(filename.c_str(), &fStat);
            result = (rx == 0 && S_ISREG(fStat.st_mode));
        } else {
            result = (_fsCache.find(filename) != _fsCache.end());
        }
        return result;
    }

    void XtLinuxFileSystem::reloadCache() {
        Guard fl(_fsLocker);

        _fsCache.clear();
        loadFsCache();
    }

    void XtLinuxFileSystem::removeFile(const String &filename) {
        Guard fl(_fsLocker);

        _fsCache.erase(filename);
        unlink(filename.c_str());
    }

    bool XtLinuxFileSystem::createFile(const String &filename, const int mode) {
        Guard  fl(_fsLocker);
        if (_fsCache.find(filename) != _fsCache.end()) return true;

        int flags = O_CREAT | O_NONBLOCK;

        if (mode & XtFileMode::XT_READ && mode & XtFileMode::XT_WRITE) {
            flags |= O_RDWR;
        } else {
            if (mode & XtFileMode::XT_READ) {
                flags |= O_RDONLY;
            } else {
                flags |= O_WRONLY;
            }
        }

        if (mode & XtFileMode::XT_APPEND) flags |= O_APPEND;

        int fd = open(filename.c_str(), flags);
        if (fd >= 0) {
            close(fd);
            _fsCache.insert(filename);
            return true;
        }
        LOGMSG("> LinuxFS: Unable to open %s", filename.c_str());
        return false;
    }

    void XtLinuxFileSystem::readFileBuffer(const String &filename,
                                           std::function<void(XtFileOperationError,
                                                              const String &,
                                                              const Vector<uint8_t>&)> dataCallback,
                                           size_t offset,
                                           size_t length) {

    }

    void XtLinuxFileSystem::readFileString(const String &filename,
                                           std::function<void(XtFileOperationError,
                                                              const String &,
                                                              const String &)> dataCallback,
                                           size_t offset,
                                           size_t length) {

    }

    XtFileOperationError XtLinuxFileSystem::writeFile(const String &file,
                                                      const String &data,
                                                      XtWriteMode mode,
                                                      size_t fileOffset,
                                                      size_t bufferOffset,
                                                      size_t bufferLength) {
        if (_fsCache.find(file) != _fsCache.end()) {
            //TODO:
        } else return XtFileOperationError::XT_FILE_NOT_EXISTS;
    }

    void XtLinuxFileSystem::loadFsCache() {
        loadDirectory(_fsBaseDirectory.c_str());
    }

    void XtLinuxFileSystem::loadDirectory(const char *directory) {
        DIR* dr = nullptr;

        dr = opendir(directory);
        if (!dr) {
            LOGMSG("> LinuxFS: unable to scan %s directory", directory);
            return;
        }

        while (true) {
            struct dirent * ent = nullptr;
            char * dirname      = nullptr;

            ent = readdir(dr);
            if (!ent) {
                break;
            }

            dirname = ent->d_name;
            if (!(ent->d_type & DT_DIR)) {
                _fsCache.insert(formatString("%s/%s", directory, dirname));
            }

            if (ent->d_type & DT_DIR) {
                if (strcmp(dirname, "..") != 0 && strcmp(dirname, ".") != 0) {
                    loadDirectory(formatString("%s/%s", directory, dirname).c_str());
                }
            }
        }
        closedir(dr);
    }
}
}