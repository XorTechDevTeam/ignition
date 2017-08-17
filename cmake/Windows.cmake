add_definitions(-DXT_WINDOWS=${PLATFORM} -D_CRT_SECURE_NO_WARNINGS)

set(XT_WIN32_DIRECTXSDK_DIR "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)")
set(XT_WIN32_TARGET_ARCH x86)	#TODO: В будущем замутить определение и нормальный выбор SDK

list(APPEND XT_SOURCES
        src/Core/Platform/Windows
        src/Core/Render/DirectX)

macro(XtGenerate)
	if (PLATFORM STREQUAL "WIN32")
		list(APPEND XT_DEPS dxgi d3d11 d3dx11 d3dx10)
		
		#init dxsdk
		link_directories("${XT_WIN32_DIRECTXSDK_DIR}/Lib/${XT_WIN32_TARGET_ARCH}")
		include_directories("${XT_WIN32_DIRECTXSDK_DIR}/Include")

		message(STATUS ">> DX SDK Config: ")
		message(STATUS ">> DX SDK LIBS: ${XT_WIN32_DIRECTXSDK_DIR}/Lib/${XT_WIN32_TARGET_ARCH}")
		message(STATUS ">> DX SDK INC : ${XT_WIN32_DIRECTXSDK_DIR}/Include")

		message(STATUS ">> Build .exe")
		add_executable(${PROJECT_NAME} WIN32 ${XT_SOURCE_FILES})
	else()
		message(STATUS ">> Build .dll")
    	add_library(${PROJECT_NAME} SHARED ${XT_SOURCE_FILES})
	endif()
endmacro()