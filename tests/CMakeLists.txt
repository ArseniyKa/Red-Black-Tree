add_executable(
  _tree_test
  BSTreeTest.cpp
)

target_link_libraries(_tree_test PUBLIC gtest_main _bst_tree)
