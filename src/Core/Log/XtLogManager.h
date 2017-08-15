//
// Created by droncode on 8/15/17.
//
#pragma once

#include <Core/Log/IXtLogService.h>

namespace xt {
namespace log {
    /**
     * @brief Основной прокси для логов.
     *        Распределяет какая конкретно реализация будет отвечать за логирование.
     */
    class XtLogManager {
    private:
        static XtLogManager *_instance;
        /**
         * @brief Указатель на сервис обработчик. По умолчанию nullptr
         */
        IXtLogService*      _service;
    public:
        XtLogManager();
        ~XtLogManager();

        XtLogManager(const XtLogManager &copy) = delete;
        XtLogManager(XtLogManager &&move) = delete;
        XtLogManager &operator=(const XtLogManager &copy) = delete;
        XtLogManager &operator=(XtLogManager &&move)      = delete;

        static XtLogManager *getInstance();
        static void release();

        /**
         * @brief Вызывает сервис логов для записи лога в журнал
         * @param format - формат строки
         * @param ...    - список аргументов
         */
        void operator()(const char *format, ...);
    };
}
}