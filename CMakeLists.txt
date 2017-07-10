cmake_minimum_required(VERSION 2.6)
project(ge-detector)

find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# Include CADMesh in your project.
#find_package(cadmesh)
#include_directories(${CADMESH_INCLUDE_DIRS})

# User code
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(ge-detector main.cpp ${sources} ${headers})
target_link_libraries(ge-detector ${Geant4_LIBRARIES})

#target_link_libraries(hpge_import cadmesh)
#target_link_libraries(hpge_import ${cadmesh_LIBRARIES})


#add_executable(hpge_import main.cpp)

install(TARGETS ge-detector RUNTIME DESTINATION bin)
