cmake_minimum_required (VERSION 3.7.2)
include(ExternalProject)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/std:c++latest>)

# PACKAGE_DIR defines where externel dependencies will be built
# PACKAGE_DIR must be an absolute path
MESSAGE(PACKAGE_DIR=${PACKAGE_DIR})

# SFML
set(sfml_INSTALL_DIR ${PACKAGE_DIR}/sfml)

ExternalProject_Add(sfml
  PREFIX ${sfml_INSTALL_DIR}
  GIT_REPOSITORY https://github.com/LaurentGomila/SFML.git
  GIT_TAG c43b5991afe815ef92a812d67f8af12b0143adfd #master (21.05.17)
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${sfml_INSTALL_DIR} -DBUILD_SHARED_LIBS=OFF
)

# tgui
set(tgui_INSTALL_DIR ${PACKAGE_DIR}/tgui)

ExternalProject_Add(tgui
  PREFIX ${tgui_INSTALL_DIR}
  GIT_REPOSITORY https://github.com/texus/TGUI.git
  GIT_TAG 38e86e2f01520e1963a5f46bbc36447dd83fc622 #0.8-dev (21.05.17)
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${tgui_INSTALL_DIR} -DSFML_ROOT=${sfml_INSTALL_DIR} -DTGUI_SHARED_LIBS=OFF
)
add_dependencies(tgui sfml)

# json
set(json_INSTALL_DIR ${PACKAGE_DIR}/json)

ExternalProject_Add(json
  PREFIX ${json_INSTALL_DIR}
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG 9ff0cc0f0212cb1e85b83ce5d2907ba9531b6cae #2.1.1
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${json_INSTALL_DIR}
)

# UnitTest++
set(unittest_INSTALL_DIR ${PACKAGE_DIR}/unittest)

ExternalProject_Add(unittest
  PREFIX ${unittest_INSTALL_DIR}
  GIT_REPOSITORY https://github.com/unittest-cpp/unittest-cpp.git
  GIT_TAG d220612eba6a03f72fdd24149d3714337809aa3f #1.6.1
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${unittest_INSTALL_DIR}
)

# box2d
set(box2d_INSTALL_DIR ${PACKAGE_DIR}/box2d)

ExternalProject_Add ( box2d
    PREFIX ${box2d_INSTALL_DIR}
	GIT_REPOSITORY https://github.com/erincatto/Box2D.git
	GIT_TAG 71a6079b5fa717b8b56aad6a1130b74232989183 #master (20.03.17)
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${box2d_INSTALL_DIR} -DBOX2D_BUILD_EXAMPLES=OFF -DBOX2D_INSTALL_DOC=OFF -DBOX2D_BUILD_SHARED=OFF -DBOX2D_BUILD_STATIC=ON -DBOX2D_INSTALL=ON
	SOURCE_SUBDIR Box2D
)

# libnoise
set(libnoise_INSTALL_DIR ${PACKAGE_DIR}/libnoise)

ExternalProject_Add ( libnoise
    PREFIX ${libnoise_INSTALL_DIR}
	GIT_REPOSITORY https://github.com/eXpl0it3r/libnoise.git
	GIT_TAG 778ac138e86afbaeef7d260c8aaea3972384b433 #master (30.03.17)
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${libnoise_INSTALL_DIR} -DLIBNOISE_BUILD_SHARED_LIBS=FALSE -DLIBNOISE_BUILD_DOC=FALSE
)
