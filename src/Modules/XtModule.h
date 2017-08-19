/**
 *	@file XtModule.h
 *	@author Rabbitlancer
 *	@date 14 Aug 2017
 *
 *	Header file describing a module interface.
 *	A module is a (sometimes optional) part of
 *	XorTech engine, providing shared communication
 *	capabilities using event queue.
 *
 *	@see XtEventQueue
 *	@see XtModuleManager
 */

#pragma once

#include <Modules/XtModuleCommon.h>

#include <Core/Event/XtEvent.h>
#include <Modules/XtDependencyUnit.h>

namespace xt {
	namespace modules {
		/**
		 * Абстрактный класс модуля.
		 * Реализует некоторый основной функционал.
		 */
		class XtModule {
		protected:
			unsigned int _id;	/**< Хранит в себе ID модуля после регистрации. */
			String moduleName;	/**< Символьное название модуля. Должно быть уникальным в данном проекте. */
            XtDependencyUnit depUnit; /**< Хранилище зависимостей модуля.
									   * Должно быть проинициализировано определенным образом.
									   * Содержит в себе названия модулей-зависимостей и адреса переменных,
									   * используемых для хранения ID этих модулей внутри кода данного модуля.
									   * @see XtDependencyUnit
									   */
		public:
			/**
			 * Виртуальный инициализатор модуля.
			 * Внутри него должны быть проинициализированы модуль зависимостей, а в конце -
			 * сделан вызов к linkModule().
			 * @return Функция должна вернуть 0 при успешной компоновке модуля, иначе необходимо вернуть другое
			 * число и движок не запустится.
			 */
            virtual int init() = 0;
			/**
			 * Виртуальный деструктор.
			 */
            virtual ~XtModule() = default;
			/**
			 * Сеттер ID модуля.
			 * Не использовать вручную, иначе вся линковка модулей летит к... ну вы поняли.
			 * @param id: новый ID модуля.
			 */
			void setId(unsigned int id);

			/**
			 * Начинает процесс линковки модуля в менеджере модулей.
			 * @return Возвращает значение XtModRC в зависимости от успешности регистрации модуля.
			 * @see XtModRC
			 */
			XtModRC linkModule();

			/**
			 * Отправляет событие ev в очередь событий.
			 * После вызова этой функции модуль теряет контроль над событием. НЕ модифицируйте событие после
			 * отправки. Освобождением ресурсов события займется очередь событий.
			 * @param ev: указатель на XtEvent для отправки.
			 * @see XtEvent
			 */
			void sendEvent(event::XtEvent *ev);

			/**
			 * Виртуальный метод обработки событий.
			 * Опишите в данном методе все, что вы хотите делать, если придет событие, на которое вы подписаны
			 * или которое предназначено вам. НЕ освобождайте ресурсы события. Оно еще может кому-то пригодиться.
			 * @param ev: указатель на XtEvent, требующий обработки.
			 */
			virtual void handleEvent(const event::XtEvent *ev) = 0;

			/**
			 * Метод-геттер имени модуля.
			 * @return Возвращает строку-значение moduleName.
			 */
			String getName();

			/**
			 * Метод-геттер модуля зависимостей данного модуля.
			 * @return Возвращает указатель на XtDependencyUnit, связанный с данным модулем.
			 */
			XtDependencyUnit *getDependencies();
		};
	}
}