cmake_minimum_required(VERSION 3.21)

project(Y0LSF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_LTO "Enable Link Time Optimization" ON)
option(ASI_VER "Build .asi version of the mod" ON)

set(COMPILE_DEFS WIN32_LEAN_AND_MEAN NOMINMAX NOGDI)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

if(ASI_VER)
  message(STATUS "Building asi version")
  set(OUT_NAME ${PROJECT_NAME})
  set(OUT_SUFFIX .asi)
  list(APPEND COMPILE_DEFS ASI_VER)
else()
  message(STATUS "Building normal version")
  set(OUT_NAME dxgi)
  set(OUT_SUFFIX .dll)
endif()

if(NOT CMAKE_BUILD_TYPE)
  message(NOTICE "No build type specified. Defaulting to Debug")
  set(CMAKE_BUILD_TYPE Debug)
endif()

add_library(${PROJECT_NAME} SHARED
  src/main.cpp
  src/core/hooks.cpp
  src/core/mem.cpp
  src/core/utils.cpp
  src/proxy/proxy.cpp
)

include(FetchContent)

FetchContent_Declare(
  minhook
  GIT_REPOSITORY https://github.com/TsudaKageyu/minhook
  GIT_TAG        origin/master
  GIT_SHALLOW    ON
)
FetchContent_MakeAvailable(minhook)

if(ENABLE_LTO AND CMAKE_BUILD_TYPE STREQUAL Release)
  include(CheckIPOSupported)

  message(STATUS "Checking Link Time Optimization support")
  check_ipo_supported(RESULT IPO_AVAILABLE OUTPUT IPO_ERROR)

  if(IPO_AVAILABLE)
    message(STATUS "Enabling Link Time Optimization")
    set_target_properties(${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    message(STATUS "Link Time Optimization not available <${IPO_ERROR}>")
  endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE minhook)
target_compile_definitions(${PROJECT_NAME} PRIVATE ${COMPILE_DEFS})

set_target_properties(${PROJECT_NAME} PROPERTIES
  OUTPUT_NAME               ${OUT_NAME}
  SUFFIX                    ${OUT_SUFFIX}
  RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/_out
)