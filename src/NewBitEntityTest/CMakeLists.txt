set(EXECUTABLE_NAME NewBitEntityTest)

FILE(GLOB HEADER_FILES *.h)
FILE(GLOB SOURCE_FILES *.cpp)
add_executable(${EXECUTABLE_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${EXECUTABLE_NAME} NewBitEntity NewBitSignals)
nb_target_add_libraries(${EXECUTABLE_NAME})