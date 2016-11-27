cmake_minimum_required (VERSION 3.6.0)
project(NewBit)

function(nb_target_add_libraries TARGET_NAME)

	# SFML
	set(CMAKE_MODULE_PATH "${PACKAGE_DIR}/sfml/cmake/Modules" ${CMAKE_MODULE_PATH})
	set(SFML_ROOT "${PACKAGE_DIR}/sfml")
	find_package(SFML 2 REQUIRED system window graphics network audio)
	if(SFML_FOUND)
		target_include_directories(${TARGET_NAME} PUBLIC ${SFML_INCLUDE_DIR})
		target_link_libraries(${TARGET_NAME} ${SFML_LIBRARIES})
	endif()

	# json
	target_include_directories(${TARGET_NAME} PUBLIC "${PACKAGE_DIR}/json/include")

endfunction()

if(BUILD_PACKAGES)
	add_subdirectory(build_packages)
else()
	set(EXECUTABLE_NAME NewBitEntity)

	FILE(GLOB HEADER_FILES NewBitEntity/src/*.h)
	FILE(GLOB SOURCE_FILES NewBitEntity/src/*.cpp)
	add_library(${EXECUTABLE_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})

	####

	# add_subdirectory(NewBitCore)
	set(EXECUTABLE_NAME NewBitCore)

	FILE(GLOB HEADER_FILES NewBitCore/src/*.h)
	FILE(GLOB SOURCE_FILES NewBitCore/src/*.cpp)
	add_executable(${EXECUTABLE_NAME} ${HEADER_FILES} ${SOURCE_FILES})
	target_link_libraries(${EXECUTABLE_NAME} NewBitEntity)

	nb_target_add_libraries(${EXECUTABLE_NAME})

	####

	include_directories(./)
endif()