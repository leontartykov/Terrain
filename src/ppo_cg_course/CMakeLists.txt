cmake_minimum_required(VERSION 3.5)

project(ppo_cg_course LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}
    core/main.cpp

    #core/data_access/data_access_base.h
    #core/data_access/data_access_file/data_access_file_base.h
    #core/data_access/data_access_file/data_access_file.h
    #core/data_access/data_access_file/data_access_file.hpp

    #core/data_access/data_access_image/data_access_image_base.h
    #core/data_access/data_access_image/data_access_image_bmp.h
    #core/data_access/data_access_image/data_access_image_bmp.hpp
    #core/data_access/data_access_image/bmp_structure.h

    core/geometry/point/point_base.h
    core/geometry/point/point_3d.h
    core/geometry/point/point_3d.hpp
)


target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

enable_testing()
add_executable(
  unit_tests
  #unit_tests/data_access/tests_file.cpp
  #unit_tests/data_access/tests_image.cpp
  unit_tests/tests_point_3d.cpp
)
target_link_libraries(
  unit_tests
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
