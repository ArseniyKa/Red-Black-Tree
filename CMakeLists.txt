cmake_minimum_required(VERSION 3.18)

if(NOT DEFINED CMAKE_C_COMPILER)
  set(CMAKE_C_COMPILER "clang")
endif()

if(NOT DEFINED CMAKE_CXX_COMPILER)
  set(CMAKE_CXX_COMPILER "clang++")
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

message("Build type is ${CMAKE_BUILD_TYPE}")
message("======================================")

project(RBTree LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

# for google tests
enable_testing()
add_subdirectory(submodules/googletest)
add_subdirectory(tests)
#################   for main function   ##################

add_executable(RBTree
  main.cpp
  src/BinaryTree.cpp
  src/RedBlackTree.cpp
  src/RemovingRBNode.cpp
)

target_include_directories(RBTree PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    include
)
target_link_libraries(RBTree Qt${QT_VERSION_MAJOR}::Core)

#################   lib for google unit tests   ##################


add_library(_bst_tree
   src/BinaryTree.cpp
   src/RedBlackTree.cpp
   src/RemovingRBNode.cpp
)

target_link_libraries(_bst_tree Qt${QT_VERSION_MAJOR}::Core)
target_include_directories(_bst_tree PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    include
)

