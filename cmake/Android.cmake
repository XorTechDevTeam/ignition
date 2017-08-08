add_definitions(-DXT_ANDROID)

macro(XtGenerate)
    message(">> Build .so")
    add_library(${PROJECT_NAME} SHARED ${XT_SOURCE_FILES})
endmacro()