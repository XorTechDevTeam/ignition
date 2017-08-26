//
// Created by droncode on 8/26/17.
//

#pragma once

#include <XtCommon.h>

#include <Core/FileSystem/XtFileMode.h>
#include <Core/FileSystem/XtWriteMode.h>
#include <Core/FileSystem/IXtFileSystem.h>
#include <Core/FileSystem/XtFileOperationError.h>

namespace xt {
namespace platform {
    using namespace xt::filesystem;

    class XtLinuxFileSystem : public IXtFileSystem {
    public:
        XtLinuxFileSystem();

        bool fileExists(const String& filename, bool ignoreCache) override;

        void reloadCache() override;

        void removeFile(const String& filename) override;

        bool createFile(const String& filename, const int mode) override;

        void readFileBuffer(const String& filename,
                            std::function<void(XtFileOperationError,
                                               const String&,
                                               const Vector<uint8_t>&)> dataCallback,
                            size_t offset,
                            size_t length) override;

        void readFileString(const String& filename,
                            std::function<void(XtFileOperationError,
                                               const String&,
                                               const String&)> dataCallback,
                            size_t offset,
                            size_t length) override;

        XtFileOperationError writeFile(const String& file,
                                       const String& data,
                                       XtWriteMode mode,
                                       size_t fileOffset,
                                       size_t bufferOffset,
                                       size_t bufferLength) override;
    private:
        /**
         * @brief Данная ф-ия блокирует все операции с текущей FS и загружает список каталогов начиная от своего базового пути
         */
        void loadFsCache();
        /**
         * @brief Рекурсивно обрабатывает ближайшие каталоги и записывает в кэш все файлы
         * @param directory - стартовый каталог
         */
        void loadDirectory(const char* directory);
    };
}
}


