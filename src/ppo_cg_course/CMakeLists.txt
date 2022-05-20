cmake_minimum_required(VERSION 3.5)

project(ppo_cg_course LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -fPIC -std=c++11 -DQT_NO_VERSION_TAGGING")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${Qt5Gui_INCLUDE_DIRS})

add_executable(
    core_files
    core/main.cpp

    core/geometry/point/point_base.h
    core/geometry/point/point_3d.h
    core/geometry/point/point_3d.hpp
    core/geometry/point/point_3d.cpp

    core/geometry/point/point_2d.h
    core/geometry/point/point_2d.hpp
    core/geometry/point/point_2d.cpp

    core/geometry/vector/vector_3d.h
    core/geometry/vector/vector_3d.hpp

    core/heightmap/base_noise.h
    core/heightmap/perlin_noise/perlin_original.h
    core/heightmap/perlin_noise/perlin_original.hpp

    core/object/object_base.h
    core/object/terrain/base_terrain.h
    core/object/terrain/terrain.h
    core/object/terrain/terrain.hpp

    core/invisible/zbuffer/zbuffer_base.h
    core/invisible/zbuffer/zbuffer.h
    core/invisible/zbuffer/zbuffer.hpp
    core/invisible/zbuffer/zbuffer.cpp

    core/geometry/triangle/triangle_3d.h
    core/geometry/triangle/triangle_3d.hpp
    core/geometry/triangle/triangle_3d.cpp

    core/geometry/plane/plane.h
    core/geometry/plane/plane.cpp
)


enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(
  unit_all_tests
  unit_tests/tests_point_3d.cpp
  unit_tests/tests_vector_3d.cpp
  unit_tests/tests_perlin_noise.cpp
  unit_tests/tests_zbuffer.cpp
  unit_tests/tests_plane.cpp

  core/geometry/plane/plane.h
  core/geometry/plane/plane.cpp

  core/invisible/zbuffer/zbuffer.h
  core/invisible/zbuffer/zbuffer.cpp
)


include(GoogleTest)
gtest_discover_tests(unit_all_tests)

target_link_libraries(unit_all_tests Qt5::Gui
                                gtest gtest_main)
target_link_libraries(core_files Qt5::Gui)


