//
// Created by droncode on 8/9/17.
//

#pragma once

namespace xt {
    namespace render {
        /**
         * @brief Базовый класс для любого рендера. Содержит основные методы для работы с GPU
         */
        class IXtRenderDevice {
        protected:
            bool _fullscreen;
            int _width;
            int _height;
        public:
            /**
             * @brief Конструктор рендера.
             * @param width         - ширина
             * @param height        - высота
             * @param fullscreen    - полноэкранный режим
             */
            IXtRenderDevice(int width, int height, bool fullscreen = false) : _width(width),
                                                                              _height(height),
                                                                              _fullscreen(fullscreen) {}

            virtual ~IXtRenderDevice() = default;
            /**
             * @brief Основная инициализация рендера
             * @return результат инциализации
             */
            virtual bool init() = 0;
            /**
             * @brief Изменение размеров области видимости
             * @param width   - новая ширина
             * @param height  - новая высота
             */
            virtual void changeViewport(int width, int height) = 0;
            /**
             * @brief Отрисовка одного кадра
             * @param delta - разница во времени между кадрами
             */
            virtual void drawFrame(float delta) = 0;
            /**
             * @brief Переинициализация компонентов
             * @return результат операции
             */
            virtual bool reInit() { return true; }
        };
    }
}