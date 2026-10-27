add_executable(VectorMTest VectorMTest.cc)
target_include_directories(VectorMTest PRIVATE "${PROJECT_SOURCE_DIR}/include")
add_test(NAME VectorMTest COMMAND VectorMTest)

add_executable(KinematicState2DTest KinematicState2DTest.cc)
target_include_directories(KinematicState2DTest PRIVATE "${PROJECT_SOURCE_DIR}/include")
add_test(NAME KinematicState2DTest COMMAND KinematicState2DTest)


add_executable(Particle2DTest Particle2DTest.cc)
target_include_directories(Particle2DTest PRIVATE "${PROJECT_SOURCE_DIR}/include")
add_test(NAME Particle2DTest COMMAND Particle2DTest )
