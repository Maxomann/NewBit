cmake_minimum_required (VERSION 3.6.0)
project(NewBit)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/std:c++latest>)

function(nb_target_add_libraries TARGET_NAME)
	set(CMAKE_MODULE_PATH "${PACKAGE_DIR}\\sfml\\cmake\\Modules;${PACKAGE_DIR}\\tgui\\cmake\\Modules")

	if(WIN32)
		set(CMAKE_INCLUDE_PATH "c:\\Program Files (x86)\\GnuWin32\\include;c:\\Program Files (x86)\\OpenAL 1.1 SDK\\include")
		set(CMAKE_LIBRARY_PATH "c:\\Program Files (x86)\\GnuWin32\\lib;c:\\Program Files (x86)\\OpenAL 1.1 SDK\\libs")

		#OpenGl
		find_package(OPENGL REQUIRED)
		if(OPENGL_FOUND)
			target_include_directories(${TARGET_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
			target_link_libraries(${TARGET_NAME} ${OPENGL_LIBRARIES})
		endif()

		#OpenAl
		find_package(OPENAL REQUIRED)
		if(OPENAL_FOUND)
			target_include_directories(${TARGET_NAME} PUBLIC ${OPENAL_INCLUDE_DIR})
			target_link_libraries(${TARGET_NAME} ${OPENAL_LIBRARIES})
		endif()

		#Freetype
		find_package(FreeType REQUIRED)
		if(FREETYPE_FOUND)
			target_include_directories(${TARGET_NAME} PUBLIC ${FREETYPE_INCLUDE_DIRS})
			target_link_libraries(${TARGET_NAME} ${FREETYPE_LIBRARIES})
		endif()

		#JPEG
		find_package(JPEG REQUIRED)
		if(JPEG_FOUND)
			target_include_directories(${TARGET_NAME} PUBLIC ${JPEG_INCLUDE_DIR})
			target_link_libraries(${TARGET_NAME} ${JPEG_LIBRARIES})
		endif()

		#winmm
		target_link_libraries(${TARGET_NAME} winmm)

		#GDI
		FIND_LIBRARY(GDI REQUIRED)
		if(GDI_FOUND)
			target_include_directories(${TARGET_NAME} PUBLIC ${GDI_INCLUDE_DIR})
			target_link_libraries(${TARGET_NAME} ${GDI_LIBRARIES})
		endif()

		#FLAC
		FIND_LIBRARY(FLAC REQUIRED)
		if(FLAC_FOUND)
			target_include_directories(${TARGET_NAME} PUBLIC ${FLAC_INCLUDE_DIR})
			target_link_libraries(${TARGET_NAME} ${FLAC_LIBRARIES})
		endif()

		#VORBIS
		FIND_LIBRARY(VORBIS REQUIRED)
		if(VORBIS_FOUND)
			target_include_directories(${TARGET_NAME} PUBLIC ${VORBIS_INCLUDE_DIR})
			target_link_libraries(${TARGET_NAME} ${VORBIS_LIBRARIES})
		endif()

		#EGL
		FIND_LIBRARY(EGL REQUIRED)
		if(EGL_FOUND)
			target_include_directories(${TARGET_NAME} PUBLIC ${EGL_INCLUDE_DIR})
			target_link_libraries(${TARGET_NAME} ${EGL_LIBRARIES})
		endif()

		#ws2_32
		target_link_libraries(${TARGET_NAME} wsock32 ws2_32)
	else()
		MESSAGE(FATAL_ERROR "External dependencies must be configured for this plattform")
	endif()

	# SFML
	set(SFML_ROOT "${PACKAGE_DIR}/sfml")
	set(SFML_STATIC_LIBRARIES TRUE)
	find_package(SFML 2 REQUIRED system window graphics network audio)
	if(SFML_FOUND)
		target_include_directories(${TARGET_NAME} PUBLIC ${SFML_INCLUDE_DIR})
		target_link_libraries(${TARGET_NAME} ${SFML_LIBRARIES})
	endif()

	# tgui
	set(TGUI_ROOT "${PACKAGE_DIR}/tgui")
	find_package(TGUI REQUIRED)
	if(TGUI_FOUND)
		target_include_directories(${TARGET_NAME} PUBLIC ${TGUI_INCLUDE_DIR})
		target_link_libraries(${TARGET_NAME} ${TGUI_LIBRARY})
	endif()

	# json
	target_include_directories(${TARGET_NAME} PUBLIC "${PACKAGE_DIR}/json/include")

	# box2d
	

	# UnitTest++
	set(UnitTest++_DIR "${PACKAGE_DIR}/unittest/lib/cmake/UnitTest++")
	find_package (UnitTest++)
	if(UnitTest++_FOUND)
		target_include_directories(${TARGET_NAME} PUBLIC ${UTPP_INCLUDE_DIRS})
		target_link_libraries(${TARGET_NAME} "${PACKAGE_DIR}/unittest/lib/UnitTest++.lib")
	endif()

endfunction()

# MAIN
include_directories(.)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(NewBitSignals)
add_subdirectory(NewBitSignalsTest)
add_dependencies(NewBitSignalsTest NewBitSignals)

add_subdirectory(NewBitPackageManager)
add_subdirectory(NewBitPackageManagerTest)
add_dependencies(NewBitPackageManagerTest NewBitPackageManager)

add_subdirectory(NewBitEntity)
add_dependencies(NewBitEntity NewBitSignals)
add_subdirectory(NewBitEntityTest)
add_dependencies(NewBitEntityTest NewBitEntity NewBitSignals)

add_subdirectory(NewBitTexturePacker)
add_subdirectory(NewBitTexturePackerTest)
add_dependencies(NewBitTexturePackerTest NewBitTexturePacker)

add_subdirectory(NewBitCore)
add_dependencies(NewBitCore NewBitEntity NewBitSignals)

add_subdirectory(CoreEngines)
add_dependencies(CoreEngines NewBitCore NewBitTexturePacker NewBitPackageManager NewBitSignals)