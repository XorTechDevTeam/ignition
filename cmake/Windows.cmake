add_definitions(-DXT_WINDOWS=${PLATFORM} -D_CRT_SECURE_NO_WARNINGS)

list(APPEND XT_SOURCES
        src/Core/Platform/Windows
        src/Core/Render/DirectX)

macro(XtGenerate)
	if (PLATFORM STREQUAL "WIN32")
		message(STATUS ">> Build .exe")
		add_executable(${PROJECT_NAME} WIN32 ${XT_SOURCE_FILES})
	else()
		message(STATUS ">> Build .dll")
    	add_library(${PROJECT_NAME} SHARED ${XT_SOURCE_FILES})
	endif()
endmacro()