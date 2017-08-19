/**
 * @file XtNullModule.h
 * @author Rabbitlancer
 * @date 15 Aug 2017
 *
 * Behold the null module.
 * A null module is the module that occupies
 * the "broadcast" index 0. Null module is
 * nothing and does nothing. Just a waste of
 * space in general.
 * @see XtModuleManager
 */

#pragma once

#include <Modules/XtModule.h>

/**
 * Пустая функция для тестирования регистрации в AngelScript.
 */
void XTCALL whatAmIDoingHere();

/**
 * Нулевой модуль.
 * Предоставляет основные функции общего назначения в скриптовой подсистеме.
 * Помимо этого, не делает практически ничего, лишь занимет нулевой индекс в
 * менеджере модулей. Кроме того, служит примером для разработки простых модулей
 * без межмодульных зависимостей.
 */
class XtNullModule : public xt::modules::XtModule {
private:
    /**
     * Приватный конструктор.
     * Инициализируйте имя модуля здесь.
     */
    XtNullModule();
public:
    /**
     * Фабрика модуля.
     * Верните здесь указатель на новый объект вашего модуля.
     * @return
     */
    static xt::modules::XtModule *getInstance();

    /**
     * Реализация инициализации.
     * Зарегистрируйте здесь все ваши функции для скриптовой системы, модуль зависимостей
     * вашего модуля и в конце вызовите функцию linkModule().
     * @return Верните 0, если все прошло хорошо.
     * @see XtModule
     */
    int init() final;

    /**
     * Обработайте здесь событие ev, которое может вам прийти.
     * Ни в коем случае не освобождайте его память! Этим займтся очередь событий.
     * @param ev
     */
    void handleEvent(const xt::event::XtEvent *ev) final;
};