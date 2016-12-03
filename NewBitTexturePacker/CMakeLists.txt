set(EXECUTABLE_NAME NewBitTexturePacker)

FILE(GLOB HEADER_FILES src/*.h)
FILE(GLOB SOURCE_FILES src/*.cpp)
add_library(${EXECUTABLE_NAME} ${HEADER_FILES} ${SOURCE_FILES})

nb_target_add_libraries(${EXECUTABLE_NAME})