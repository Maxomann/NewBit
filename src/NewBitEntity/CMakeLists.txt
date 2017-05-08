set(EXECUTABLE_NAME NewBitEntity)

FILE(GLOB HEADER_FILES *.h)
FILE(GLOB SOURCE_FILES *.cpp)
add_library(${EXECUTABLE_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${EXECUTABLE_NAME} NewBitSignals)
nb_target_add_libraries(${EXECUTABLE_NAME})