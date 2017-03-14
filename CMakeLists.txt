cmake_minimum_required (VERSION 3.6.0)
project(NewBit)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

function(nb_target_add_libraries TARGET_NAME)

	# signals-cpp
	target_include_directories(${TARGET_NAME} PUBLIC "${PACKAGE_DIR}/signalscpp/src/signals")
	MESSAGE("${PACKAGE_DIR}/signalscpp/src/signals")

	# SFML
	set(CMAKE_MODULE_PATH "${PACKAGE_DIR}/sfml/cmake/Modules")
	set(SFML_ROOT "${PACKAGE_DIR}/sfml")
	find_package(SFML 2 REQUIRED system window graphics network audio)
	if(SFML_FOUND)
		target_include_directories(${TARGET_NAME} PUBLIC ${SFML_INCLUDE_DIR})
		target_link_libraries(${TARGET_NAME} ${SFML_LIBRARIES})
	endif()

	# Thor
	set(CMAKE_MODULE_PATH "${PACKAGE_DIR}/thor/cmake/Modules")
	set(THOR_ROOT "${PACKAGE_DIR}/thor")
	find_package(THOR 2 REQUIRED)
	if(THOR_FOUND)
		target_include_directories(${TARGET_NAME} PUBLIC ${THOR_INCLUDE_DIR})
		target_link_libraries(${TARGET_NAME} ${THOR_LIBRARY})
	endif()

	# json
	target_include_directories(${TARGET_NAME} PUBLIC "${PACKAGE_DIR}/json/include")

	# UnitTest++
	set(UnitTest++_DIR "${PACKAGE_DIR}/unittest/lib/cmake/UnitTest++")
	find_package (UnitTest++)
	if(UnitTest++_FOUND)
		target_include_directories(${TARGET_NAME} PUBLIC ${UTPP_INCLUDE_DIRS})
		target_link_libraries(${TARGET_NAME} "${PACKAGE_DIR}/unittest/lib/UnitTest++.lib")

	endif()

endfunction()

# MAIN

if(BUILD_LIB)
	add_subdirectory(build_packages)
else()

	include_directories(.)

	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

	add_subdirectory(NewBitSignals)

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

endif()