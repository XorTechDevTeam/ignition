//
// Created by droncode on 8/25/17.
//
#pragma once

#include <XtCommon.h>
#include <Core/FileSystem/XtFileMode.h>
#include <Core/FileSystem/XtWriteMode.h>
#include <Core/FileSystem/XtFileOperationError.h>

namespace xt {
namespace filesystem {
    class IXtFileSystem {
    protected:
        String              _fsBaseDirectory;
        Set<String>         _fsCache;
        bool                _fsReadOnly;
        std::mutex          _fsLocker;
    public:
        IXtFileSystem(const String& baseDirectory, bool readOnly = false) :
                _fsBaseDirectory(baseDirectory),
                _fsReadOnly(readOnly) {}

        virtual ~IXtFileSystem() {
            _fsCache.clear();
        }
        /**
         * @brief Получение списка файлов в данной файловой системе
         * @return сет из файлов в данной файловой системе
         */
        virtual Set<String> getFiles() const { return _fsCache; }
        /**
         * @brief Проверка существования файла
         * @param filename      - путь к файлу
         * @param ignoreCache   - если стоит true, то поиск будет произведен средствами ОС, если false, то средствами кэша
         * @return результат проверки
         */
        virtual bool fileExists(const String& filename, bool ignoreCache = false) = 0;
        /**
         * @brief Геттер для свойства ОС "только для чтения"
         * @return значение параметра "только для чтения"
         */
        virtual bool isReadOnlyFS() const { return _fsReadOnly; }
        /**
         * @brief Команда на обновление кэша файловой системы.
         * @note старайтесь использовать данную команду КАК МОЖНО РЕЖЕ
         * @details на самом деле данная команда создает задачу для менеджера задач, на обновление кэша. Стоит это учитывать при разработке
         */
        virtual void reloadCache() = 0;
        /**
         * @brief Удаляет из кэша файл (в каждой конкретной реализации уже зависит удаление из ОС) если это разрешенио флагом
         * @param filename - имя файла
         */
        virtual void removeFile(const String& filename) {
            if (!_fsReadOnly) {
                Guard funcGuard(_fsLocker);

                _fsCache.erase(filename);
            }
        }
        /**
         * @brief Запрашивает у ОС создание файла с определенными флагами доступа (см XtFileMode)
         * @param filename имя файла
         * @param mode режим доступа
         * @return успешность операции
         */
        virtual bool createFile(const String& filename, const int mode) = 0;
        /**
         * @brief Асинхронное чтение файла в вектор байт
         * @param filename - имя файла
         * @param dataCallback - callback ф-ия с результатом выполнения, именем файла и вектором байт
         * @param offset смещение относительно начала файла
         * @param length максимальная длина буфера (0 - весь файл, до лимита XT_MAX_FILE_BUFFER)
         */
        virtual void readFileBuffer(const String& filename,
                                    std::function<void(XtFileOperationError,
                                                       const String&,
                                                       const Vector<uint8_t>&)> dataCallback,
                                    size_t offset,
                                    size_t length) = 0;
        /**
         * @brief Асинхронное чтение файла в строку
         * @param filename имя файла
         * @param dataCallback callback ф-ия с результатом выполнения, именем файла и строкой
         * @param offset смещение относительно начала файла
         * @param length максимальная длина буфера (0 - весь файл, до лимита XT_MAX_FILE_BUFFER)
         */
        virtual void readFileString(const String& filename,
                                    std::function<void(XtFileOperationError,
                                                       const String&,
                                                       const String&)> dataCallback,
                                    size_t offset,
                                    size_t length) = 0;
        /**
         * @brief Записывает в файл строку
         * @param file - имя файла
         * @param data - строка, записываемая в файл
         * @param mode - режим записи
         * @param fileOffset - игнорируется во всех режимах, кроме XT_OFFSET
         * @param bufferOffset - смещение, относительно буффера.
         * @param bufferLength - длина буффера
         * @return информация о результате операции
         */
        virtual XtFileOperationError writeFile(const String& file,
                                               const String& data,
                                               XtWriteMode mode,
                                               size_t fileOffset,
                                               size_t bufferOffset,
                                               size_t bufferLength) = 0;

        String getFileSystemBaseDir() const { return _fsBaseDirectory; }
    protected:
        /**
         * @brief Добавляет запись в кэш файловой системы
         * @param filename имя файла
         */
        void appendCache(const String& filename) {
            Guard funcGuard(_fsLocker);
            _fsCache.insert(filename);
        }
    };
}
}