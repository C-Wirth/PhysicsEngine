add_executable(VectorMTest VectorMTest.cc)
target_include_directories(VectorMTest PRIVATE "${PROJECT_SOURCE_DIR}/include")
add_test(NAME VectorMTest COMMAND VectorMTest)