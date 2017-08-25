//
// Created by droncode on 8/25/17.
//

#pragma once

#include <XtCommon.h>
#include <Core/FileSystem/IXtFileSystem.h>

namespace xt {
namespace filesystem {
    class XtFileSystemManager {
    private:
        Vector<IXtFileSystem*>               _fsList;
        UnorderedMap<String, IXtFileSystem*> _fsOrder;
        std::mutex                           _fsLocker;
    public:
        XtFileSystemManager();
        ~XtFileSystemManager();
        /**
         * @brief регистрирует новую файловую систему
         * @param fsPtr - указатель на файловую систему. Очисткой памяти из под указателя занимается менеджер
         */
        void addFileSystem(IXtFileSystem* fsPtr);
        /**
         * @brief удаляет файловую систему и очищает память
         * @param fsPtr - указатель на файловую систему
         */
        void removeFileSystem(IXtFileSystem* fsPtr);
        /**
         * @brief Возвращает вектор всех доступных файловых систем
         * @return вектор файловых систем
         */
        Vector<IXtFileSystem*> getFileSystemList() const;
        /**
         * @brief Проверяет существование файла в файловых системах
         * @param filename - имя файла
         * @param ignoreCache - игнорировать ли кэш?
         * @return существование файла
         */
        bool isFileExists(const String& filename, bool ignoreCache = false);
        /**
         * @brief Возвращает указатель на файловую систему, которая фладеет файлом
         * @param filename - имя файла
         * @note Если несколько ФС владеет файлами, у которых одинаковые названия, то будет возвращена первая.
         *       Для получения всех ФС, фладеющих файлами стоит использовать метод getFileSystemList
         * @return указатель на файловую систему, либо nullptr
         */
        IXtFileSystem* getFileSystem(const String& filename);
        /**
         * @brief Регистрирует сопоставление имени файла и родительской ФС.
         * @param filename имя файла
         * @param fs указатель на ФС
         */
        void addOrderCache(const String& filename, IXtFileSystem* fs);
        /**
         * @brief Удаляет запись о регистрации сопоставления имени файла и родительской ФС
         * @param filename имя файла
         */
        void removeOrderCache(const String& filename);
    };
}
}


