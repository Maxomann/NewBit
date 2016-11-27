set(EXECUTABLE_NAME NewBitCore)

FILE(GLOB HEADER_FILES src/*.h)
FILE(GLOB SOURCE_FILES src/*.cpp)
add_executable(${EXECUTABLE_NAME} ${HEADER_FILES} ${SOURCE_FILES})

nb_target_add_libraries(${EXECUTABLE_NAME})