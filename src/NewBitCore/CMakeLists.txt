set(EXECUTABLE_NAME NewBitCore)

FILE(GLOB HEADER_FILES *.h)
FILE(GLOB SOURCE_FILES *.cpp)
add_executable(${EXECUTABLE_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${EXECUTABLE_NAME} NewBitEntity NewBitSignals)
set_target_properties(${EXECUTABLE_NAME} PROPERTIES ENABLE_EXPORTS true)
nb_target_add_libraries(${EXECUTABLE_NAME})

add_custom_command(
	TARGET NewBitCore POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_CURRENT_LIST_DIR}/../../binaryFiles/
			$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/)