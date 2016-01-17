project(cpp_challenge)
cmake_minimum_required(VERSION 2.8)

set(
  COMMON_SOURCE_FILES 
  image_helper.cc 
  network_helper.cc 
  serialization.cc 
  utility.cc)

set(
  TEST_SOURCE_FILES
  image_helper_test.cc
  serialization_test.cc
  utility_test.cc)

add_executable(server main.cc ${COMMON_SOURCE_FILES})
add_executable(server_tests ${COMMON_SOURCE_FILES} ${TEST_SOURCE_FILES})

set_target_properties(
  server 
  server_tests
  PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(LIBRARIES "-lzmq -lopencv_core -lopencv_imgcodecs")

target_link_libraries(server ${LIBRARIES})
target_link_libraries(server_tests ${LIBRARIES} "-lgtest -lgtest_main -pthread")
