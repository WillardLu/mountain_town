find_package(GTest REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(mountain_town_test
  mountain_town_test.cpp
  math/random_test.cpp
  neural_network/nlp/basic_test.cpp
  string/basic_test.cpp
  string/toml_test.cpp
  ${PROJECT_SOURCE_DIR}/src/mountain_town/math/random.cpp
  ${PROJECT_SOURCE_DIR}/src/mountain_town/neural_network/nlp/basic.cpp
  ${PROJECT_SOURCE_DIR}/src/mountain_town/string/basic.cpp
  ${PROJECT_SOURCE_DIR}/src/mountain_town/string/toml.cpp)

target_link_libraries(mountain_town_test
 PRIVATE
  GTest::GTest)

target_include_directories(mountain_town_test
 PUBLIC
  ${PROJECT_SOURCE_DIR}/src/)