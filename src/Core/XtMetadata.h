/**
 * @file XtMetadata.h
 * @author Rabbitlancer
 * @date 15 Aug 2017
 *
 * Заголовок класса метаданных сборки.
 * Метаданные включают в себя сведения о платформе,
 * версию движка и доступные модули.
 */

#pragma once

#include <XtCommon.h>

namespace xt {
    /**
     * Тип платформы, на которой работает XorTech.
     */
    enum XtPlatformType {
        PTLinux,        /**< Да ладно, это линух! */
        PTOSX,          /**< Да ладно, это макось! */
        PTWindows32,    /**< Да ладно, это винда32! */
        PTWindowsUWP,   /**< Да ладно, это виндомаркет! */
        PTAndroid,      /**< Да ладно, это ведроид! */
        PTiOS,          /**< Да ладно, это яОСь! */
        PTEmscripten    /**< А это мы в вебе. */
    };

    /**
     * Класс метаданных о текущей сборке движка XorTech.
     */
    class XtMetadata {
    private:
        XtPlatformType platformName;    /**< Тип платформы.
                                         * @see XtPlatformType
                                         */
        String subplatformName;         /**< Подтип платформы.
                                         * В Linux это дистрибутив.
                                         * В Windows - версия Windows.
                                         * В Emscripten - текующий User-Agent.
                                         */
        int platformVerMajor;           /**< Старшая версия платформы. */
        int platformVerMinor;           /**< Младшая версия платформы. */
        int xorTechVerMajor;            /**< Старшая версия сборки XorTech. */
        int xorTechVerMinor;            /**< Младшая версия сборки XorTech. */
        //TODO: modules

        /**
         * Собирает информацию о текущей сборке.
         */
        void init();
    public:
        /**
         * Публичный конструктор метаданных.
         * Сразу после создания объект содержит в себе все данные и годен к использованию.
         */
        XtMetadata();

        /**
         * Метод-геттер типа платформы.
         * @return Возвращает тип платформы.
         */
        XtPlatformType getPlatformName() const;

        /**
         * Метод-геттер подтипа платформы.
         * @return Возвращает строку-подтип платформы.
         */
        const String &getSubplatformName() const;

        /**
         * Метод-геттер старшей версии платформы.
         * @return Возвращает число: старшую версию платформы.
         */
        int getPlatformVerMajor() const;

        /**
         * Метод-геттер младшей версии платформы.
         * @return Возвращает число: младшую версию платформы.
         */
        int getPlatformVerMinor() const;

        /**
         * Метод-геттер старшей версии сборки.
         * @return Возвращает число: старшую версию сборки.
         */
        int getXorTechVerMajor() const;

        /**
         * Метод-геттер младшей версии сборки.
         * @return Возвращает число: младшую версию сборки.
         */
        int getXorTechVerMinor() const;
    };
}