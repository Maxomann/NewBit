set(EXECUTABLE_NAME NewBitPackageManagerTest)

FILE(GLOB HEADER_FILES src/*.h)
FILE(GLOB SOURCE_FILES src/*.cpp)
add_executable(${EXECUTABLE_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${EXECUTABLE_NAME} NewBitPackageManager)
nb_target_add_libraries(${EXECUTABLE_NAME})

add_custom_command(
	TARGET ${EXECUTABLE_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_CURRENT_LIST_DIR}/data/
			$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/data/)