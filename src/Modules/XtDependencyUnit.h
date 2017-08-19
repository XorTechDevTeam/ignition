/**
 * @file DependencyUnit.h
 * @author Rabbitlancer
 * @date 15 Aug 2017
 *
 * Header for DependencyUnit class.
 * DependencyUnit handles data about the module's
 * dependent modules (the ones that module will
 * send events to).
 * @see XtModule
 * @see XtEvent
 */

#pragma once

namespace xt {
    namespace modules {
        /**
         * Класс-хранилище зависимостей модуля.
         * Хранит в себе карту, связывающую названия модулей с
         * указатели на используемые в коде индексы отправления
         * событий.
         */
        class XtDependencyUnit {
        private:
            UnorderedMap<String, int*> deps; /**< Контейнер зависимостей. */
            UnorderedMap<String, int*>::const_iterator cur; /**< Итератор текущей зависимости. */
        public:
            /**
             * Публичный конструктор.
             * Инициализирует карту зависимостей с итератором.
             */
            XtDependencyUnit();

            /**
             * Публичный деструктор.
             * Освобождает карту зависимостей.
             */
            ~XtDependencyUnit();

            /**
             * Добавляет зависимость в хранилище.
             * @param depName: имя модуля-зависимости.
             * @param index: адрес переменной, используемой для хранения ID модуля-зависимости.
             */
            void addDependency(String depName, int *index);

            /**
             * Получает зависимость из хранилища.
             * @return Возвращает итератор пары имени модуля-зависимости и переменной, используемой для
             * хранения ID этого модуля.
             */
            UnorderedMap<String, int*>::const_iterator nextDependency();

            /**
             * Возвращает конечный итератор.
             * @return Возвращает итератор позиции после конца.
             */
            UnorderedMap<String, int*>::const_iterator end();
        };
    }
}