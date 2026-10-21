add_executable(VectorMTest VectorMTest.cc)
target_include_directories(VectorMTest PRIVATE "${PROJECT_SOURCE_DIR}/include")
add_test(NAME VectorMTest COMMAND VectorMTest)

add_executable(KinematicState2DTest KinematicState2DTest.cc)
target_include_directories(KinematicState2DTest PRIVATE "${PROJECT_SOURCE_DIR}/include")
add_test(NAME KinematicState2DTest COMMAND KinematicState2DTest)