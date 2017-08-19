/**
 * @file XtModuleManager.h
 * @author Rabbitlancer
 * @date 15 Aug 2017
 *
 * Header file describing XtModuleManager class.
 * @see XtModule
 */

#pragma once

#include <XtCommon.h>
#include <Core/Event/XtEventQueue.h>
#include <Modules/XtModuleCommon.h>
#include <Modules/XtModule.h>

namespace xt {
    namespace modules {
        /**
         * Менеджер модулей.
         * Реализован классом-одиночкой, что позволяет получить к нему доступ из любой части кода,
         * в частности, из модулей. Предоставляет весь необходимый функционал по регистрации модулей
         * и их обмену событиями.
         */
        class XtModuleManager  {
        private:
            static XtModuleManager *_instance;  /**< Указатель на экземпляр менеджера модулей. */
            Vector<XtModule*> modules;          /**< Контейнер зарегистрированных модулей. */

            event::XtEventQueue *_evQueue;      /**< Очередь событий.
                                                 * @see XtEventQueue
                                                 */
            XtModuleManager();  /**< Приватный конструктор. Инициализирует контейнеры и ссылки. */
            ~XtModuleManager(); /**< Приватный деструктор. Освобождает занятую память. */
        public:
            /**
             * Фабрика менеджера модулей.
             * @return Возвращает указатель на объект-одиночку.
             */
            static XtModuleManager *getInstance();

            /**
             * Освобождает память, занятую одиночкой.
             */
            static void release();

            XtModuleManager(const XtModuleManager& copy)            = delete;
            XtModuleManager(const XtModuleManager&& move)           = delete;
            XtModuleManager& operator=(const XtModuleManager& copy) = delete;
            XtModuleManager& operator=(XtModuleManager&& move)      = delete;

            /**
             * Инициализирует менеджер модулей.
             * В числе прочего, добавляет в нулевой индекс нулевой модуль.
             * @return Возвращает 0, если инициализирован успешно.
             * @see XtNullModule
             */
            int init();

            /**
             * Регистрирует модуль module в менеджере.
             * @param module: указатель на модуль, требующий регистрации.
             * @return Возвращает значение XtModRC.
             * @see XtModRC
             */
            XtModRC addModule(XtModule *module);

            /**
             * Отправляет сообщение ev в очередь событий.
             * Всего лишь перенаправляет вызов от модуля к очереди событий.
             * @param ev: указатель на событие.
             */
            void sendEvent(event::XtEvent *ev);

            /**
             * Отправляет событие ev требуемому модулю на обработку.
             * @param ev: направляемое событие.
             */
            void dispatchEvent(event::XtEvent *ev);

            /**
             * Разрешает очередь событий.
             * По факту просто делает соответствующий вызов в очереди событий.
             * @see XtEventQueue
             */
            void resolveEvents();
        };
    }
}