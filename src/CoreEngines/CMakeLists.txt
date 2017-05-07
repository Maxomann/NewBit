set(EXECUTABLE_NAME CoreEngines)

FILE(GLOB_RECURSE HEADER_FILES *.h)
FILE(GLOB_RECURSE SOURCE_FILES *.cpp)
add_library(${EXECUTABLE_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${EXECUTABLE_NAME} NewBitCore NewBitPackageManager NewBitSignals)
nb_target_add_libraries(${EXECUTABLE_NAME})
