cmake_minimum_required(VERSION 3.20.0)

project(PlaceDescriptionServiceTest)
set(target_name "test")

include_directories($ENV{GTEST_HOME}/googlemock/include $ENV{GTEST_HOME}/googletest/include $ENV{JSONCPP_HOME}/include $ENV{CURL_HOME}/include)
link_directories($ENV{GTEST_HOME}/out/build/lib $ENV{JSONCPP_HOME}/lib $ENV{CURL_HOME}/lib)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")

set(sources 
   main.cpp 
   CurlHttpTest.cpp
   CurlHttp.cpp
   AddressExtractorTest.cpp
   AddressExtractor.cpp
   PlaceDescriptionServiceTest.cpp
   PlaceDescriptionService.cpp)

add_executable(${target_name} ${sources})

target_link_libraries(${target_name} pthread)
target_link_libraries(${target_name} gmock)
target_link_libraries(${target_name} gtest)
target_link_libraries(${target_name} jsoncpp)
target_link_libraries(${target_name} curl)

target_compile_features(${target_name} PUBLIC cxx_std_17)
