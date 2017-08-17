add_definitions(-DXT_LINUX)
list(APPEND XT_SOURCES
        src/Core/Platform/Linux
        src/Core/Render/OpenGL)
set(XT_LINUX_DEPS glfw pthread dl rt GL)

macro(XtGenerate)
    list(APPEND XT_DEPS ${XT_LINUX_DEPS})
    #
    #   Add GLFW3
    add_subdirectory(src/3rd/glfw)
    list(APPEND XT_DEPS glfw)
    include_directories(src/3rd/glfw/include)

    add_executable(${PROJECT_NAME} ${XT_SOURCE_FILES})
endmacro()