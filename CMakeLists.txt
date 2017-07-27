cmake_minimum_required(VERSION 3.8)
project(ge-detector)

find_package(Geant4 REQUIRED ui_all vis_all)
find_package(ROOT REQUIRED)
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})



include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR}
                    ${ROOT_INCLUDE_DIR}
                    $ENV{ROOTSYS}/bin/include)
EXECUTE_PROCESS(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}")

# Include CADMesh in your project.
#find_package(cadmesh)
#include_directories(${CADMESH_INCLUDE_DIRS})


# User code
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)


EXECUTE_PROCESS(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_EXE_LINKER_FLAGS ${ROOT_LD_FLAGS})
add_executable(ge-detector main.cpp ${sources} ${headers})
target_link_libraries(ge-detector ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
#target_link_libraries(hpge_import cadmesh)
#target_link_libraries(hpge_import ${cadmesh_LIBRARIES})
# CPPFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)
# EXTRALIBS += $(shell $(ROOTSYS)/bin/root-config --libs)
# LDLIBS += $(shell $(ROOTSYS)/bin/root-config --libs) 

#add_executable(hpge_import main.cpp)

install(TARGETS ge-detector RUNTIME DESTINATION bin)
