add_definitions(-DXT_ANDROID)
list(APPEND XT_SOURCES
        src/Core/Platform/Android
        src/Core/Render/OpenGL)
set(XT_ANDROID_DEPS android log EGL GLESv2)

macro(XtGenerate)
    set(PROJECT_NAME XtAndroid)
    message(">> Build ${PROJECT_NAME}.so")
    list(APPEND XT_DEPS ${XT_ANDROID_DEPS})
    #TODO: Use project name here!
    add_library(${PROJECT_NAME} SHARED ${XT_SOURCE_FILES})
endmacro()