add_definitions(-DXT_WINDOWS=${PLATFORM})
#TODO: Add sources & deps

macro(XtGenerate)
	message(STATUS ">> Build .dll")
    add_library(${PROJECT_NAME} SHARED ${XT_SOURCE_FILES})
endmacro()