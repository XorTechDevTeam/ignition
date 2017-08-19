/**
 * @file XtLogic.h
 * @author Rabbitlancer
 * @date 17 Aug 2017
 *
 * Заголовочный файл для окружения AngelScript.
 */

#pragma once

#include <XtCommon.h>
#include <angelscript.h>

namespace xt {
    namespace logic {
        /**
         * Основной класс игровой логики.
         * Содержит в себе окружение AngelScript и некоторые интерфейсные функции.
         * Кроме того, реализован классом-одиночкой, поэтому доступен из любой части кода
         * (в особенности модулям, которым надо регистрировать свои функции в скриптовом
         * окружении).
         */
        class XtLogic {
        private:
            static XtLogic *_instance;  /**< Указатель на объект класса. */

            asIScriptEngine *asEngine;  /**< Указатель на виртуальную машину AngelScript. */

            XtLogic();  /**< Приватный конструктор, инициализирующий окружение. (Отрефакторить?)*/
            ~XtLogic(); /**< Приватный деструктор, завершающий работу с AngelScript. */

            void messageCallback(const asSMessageInfo *msg, void *param);   /**< MessageCallback для AngelScript.
                                                                             * Сейчас не делает ничего.
                                                                             */
        public:
            /**
             * Фабрика для одиночки.
             * @return Возвращает указатель на объект-менеджер логики.
             */
            static XtLogic *getInstance();

            /**
             * Освобождает объект.
             */
            static void release();

            /**
             * Регистрирует глобальную функцию в скриптовом окружении.
             * @param name: сигнатура функции, например: "void foo(int)".
             * @param m: результат работы макроса asFUNCTION(foo), возвращающего указатель на используемую функцию.
             * @return Возвращает код успешности при регистрации функции: 0, если функция зарегистрирована успешно.
             * @see registerMethod()
             */
            int registerFunction(String name, asSFuncPtr m);

            /**
             * Регистрирует метод name объекта object в скриптовом окружении.
             * @param name: сигнатура функции, например: "void foo(int)".
             * @param object: имя объекта, например: "MyClass".
             * @param m: результат работы макроса asMETHOD(MyClass, foo), возвращающего указатель на используемый
             * метод класса.
             * @return Возвращает код успешности при регистрации метода: 0, если метод зарегистрирован успешно.
             * @see registerFunction()
             */
            int registerMethod(String name, String object, asSFuncPtr m);
        };
    }
}