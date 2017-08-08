/**
 * XorTech Source Code
 */
#pragma once

namespace xt {
    namespace patterns {
        template <class T>
        class XtSingleton {
        private:
            static T* _instance;
        public:
            // Constructor & Destructor
            XtSingleton() = default;
            virtual ~XtSingleton() = default;

            XtSingleton<T>(const XtSingleton<T>& copy) = delete;
            XtSingleton<T>& operator=(const XtSingleton<T>& copy) = delete;

            static void release() {
                if (_instance) {
                    delete _instance;
                    _instance = nullptr;
                }
            }

            static T* getInstance() {
                if (!_instance) {
                    _instance = new T;
                }
                return _instance;
            }
        };

        template <class T> T* XtSingleton<T>::_instance = nullptr;
    }
}