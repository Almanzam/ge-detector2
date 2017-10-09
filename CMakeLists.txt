 cmake_minimum_required(VERSION 3.8)
 project(ge-detector)
 
#find_package(Geant4 REQUIRED STATIC VERSION 10.3.2)
#find_package(ROOT REQUIRED)
# list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
 
 
 set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
 set(BUILD_SHARED_LIBRARIES OFF)
 set(CMAKE_EXE_LINKER_FLAGS "-static")
#include(${Geant4_USE_FILE})
 include_directories(${PROJECT_SOURCE_DIR}/include
                     /home/almanzam/geant4/include/Geant4/)
#EXECUTE_PROCESS(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
 EXECUTE_PROCESS(COMMAND /home/daq/geant4/bin/geant4-config --cflags OUTPUT_VARIABLE GEANT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  ${GEANT_CXX_FLAGS} -std=c++11")
 
 # Include CADMesh in your project.
 #find_package(cadmesh)
 #include_directories(${CADMESH_INCLUDE_DIRS})
 
 
 # User code
 file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
 file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
 file(GLOB staticlibs /home/almanzam/geant-build/geant_static.a)
#file(GLOB rootstaticlibs /home/almanzam/ROOT/root-build/lib/*.a /home/almanzam/ROOT/root/lib/libmathtext.a /home/almanzam/ROOT/root-build/lib/*.a /home/almanzam/ROOT/root-build/interpreter/llvm/src/lib/*.a /home/almanzam/ROOT/root-build/root_static.a)
#EXECUTE_PROCESS(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
 EXECUTE_PROCESS(COMMAND /home/almanzam/geant4/bin/geant4-config --libs OUTPUT_VARIABLE GEANT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
 set(CMAKE_EXE_LINKER_FLAGS "${GEANT_LD_FLAGS} -lcurl -lboost_regex -lcurl -licuuc")
 add_executable(ge-detector main.cpp ${sources} ${headers})
 target_link_libraries(ge-detector ${staticlibs} /home/almanzam/Xerces/xerces-install/lib/libxerces-c.a /home/almanzam/Expat/expat/lib/libexpat.a )
 #target_link_libraries(hpge_import cadmesh)
 #target_link_libraries(hpge_import ${cadmesh_LIBRARIES})
 # CPPFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)
 # EXTRALIBS += $(shell $(ROOTSYS)/bin/root-config --libs)
 # LDLIBS += $(shell $(ROOTSYS)/bin/root-config --libs) 
 
 #add_executable(hpge_import main.cpp)
 
install(TARGETS ge-detector RUNTIME DESTINATION bin)
