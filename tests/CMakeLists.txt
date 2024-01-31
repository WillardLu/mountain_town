find_package(GTest REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(mountain_town_test
  lib_test.cpp
  string/basic_test.cpp
  ${PROJECT_SOURCE_DIR}/src/string/basic.cpp)

target_link_libraries(mountain_town_test
 PRIVATE
  GTest::GTest)

target_include_directories(mountain_town_test
 PUBLIC
  ${PROJECT_SOURCE_DIR}/src/)