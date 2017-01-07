include(ExternalProject)
set(PACKAGE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" )

# SFML
set(sfml_INSTALL_DIR ${PACKAGE_DIR}/sfml)
set(sfml_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${sfml_INSTALL_DIR})

ExternalProject_Add(sfml
  PREFIX ${sfml_INSTALL_DIR}
  GIT_REPOSITORY https://github.com/LaurentGomila/SFML.git
  GIT_TAG b3e44568dfbd76bd81dca3ef11d6f2763446bbb7 #2.4.1
  INSTALL_DIR ${sfml_INSTALL_DIR}
  CMAKE_ARGS ${sfml_CMAKE_ARGS}
)

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
