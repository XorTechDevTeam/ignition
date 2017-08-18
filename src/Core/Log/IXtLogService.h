//
// Created by droncode on 8/15/17.
//
#pragma once

#include <XtCommon.h>

namespace xt {
namespace log {
    /**
     * @brief Абстрактный класс сервиса логирования. Каждая платформа определяет его по своему.
     */
    class IXtLogService {
    public:
        /**
         * @brief Метод для записи готового лога в журнал
         * @param message - сообщение в лог
         */
        virtual void writeLog(const std::string& message) = 0;
    };
}
}