cmake_minimum_required(VERSION 3.18)

if(NOT DEFINED CMAKE_C_COMPILER)
  set(CMAKE_C_COMPILER "clang")
endif()

if(NOT DEFINED CMAKE_CXX_COMPILER)
  set(CMAKE_CXX_COMPILER "clang++")
endif()

project(RBTree LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

enable_testing()
add_subdirectory(submodules/googletest)
add_subdirectory(tests)
#add_executable(test_app test_main.cpp)

add_executable(RBTree
  main.cpp
  BinaryTree.cpp
)

add_library(_bst_tree
   BinaryTree.cpp
)

target_link_libraries(RBTree Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(_bst_tree Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS RBTree
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
