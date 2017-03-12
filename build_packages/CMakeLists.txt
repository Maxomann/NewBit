include(ExternalProject)

# signals-cpp
set(signals_INSTALL_DIR ${PACKAGE_DIR}/signalscpp)
set(signals_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${signals_INSTALL_DIR})

ExternalProject_Add(signals
  PREFIX ${signals_INSTALL_DIR}
  GIT_REPOSITORY https://github.com/Kosta-Github/signals-cpp.git
  GIT_TAG a816a4e006678bd04bd4940acbcd6a0c30afe980 #master (12.03.17)
  INSTALL_DIR ${signals_INSTALL_DIR}
  CMAKE_ARGS ${signals_CMAKE_ARGS}
)

# SFML
set(sfml_INSTALL_DIR ${PACKAGE_DIR}/sfml)
set(sfml_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${sfml_INSTALL_DIR})

ExternalProject_Add(sfml
  PREFIX ${sfml_INSTALL_DIR}
  GIT_REPOSITORY https://github.com/LaurentGomila/SFML.git
  GIT_TAG e4ae4f9cc3c3588a3634f46f436f77c051a85325 #2.4.2
  INSTALL_DIR ${sfml_INSTALL_DIR}
  CMAKE_ARGS ${sfml_CMAKE_ARGS}
)

# SFML Thor
set(thor_INSTALL_DIR ${PACKAGE_DIR}/thor)
set(thor_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${thor_INSTALL_DIR} -DSFML_ROOT=${PACKAGE_DIR}/sfml )

ExternalProject_Add(thor
  PREFIX ${thor_INSTALL_DIR}
  GIT_REPOSITORY https://github.com/Bromeon/Thor.git
  GIT_TAG 3aee360fa6a54acb82637e71782863ac975705db #2.1 dev
  INSTALL_DIR ${thor_INSTALL_DIR}
  CMAKE_ARGS ${thor_CMAKE_ARGS}
)

add_dependencies(thor sfml)

# json
set(json_INSTALL_DIR ${PACKAGE_DIR}/json)
set(json_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${json_INSTALL_DIR})

ExternalProject_Add(json
  PREFIX ${json_INSTALL_DIR}
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG 6d2b5e377122955cb29889800cdbac653c2fae1e #2.0.7
  INSTALL_DIR ${json_INSTALL_DIR}
  CMAKE_ARGS ${json_CMAKE_ARGS}
)

# UnitTest++
set(unittest_INSTALL_DIR ${PACKAGE_DIR}/unittest)
set(unittest_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${unittest_INSTALL_DIR})

ExternalProject_Add(unittest
  PREFIX ${unittest_INSTALL_DIR}
  GIT_REPOSITORY https://github.com/unittest-cpp/unittest-cpp.git
  GIT_TAG d220612eba6a03f72fdd24149d3714337809aa3f #1.6.1
  INSTALL_DIR ${unittest_INSTALL_DIR}
  CMAKE_ARGS ${unittest_CMAKE_ARGS}
)