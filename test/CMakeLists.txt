# Include FetchContent
include(FetchContent)

# Fetch googletest library
FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(${PROJECT_NAME}_test_step test_sources.cpp)
target_link_libraries(${PROJECT_NAME}_test_step PRIVATE GTest::GTest)

add_test(test_step ${PROJECT_NAME}_test_step)