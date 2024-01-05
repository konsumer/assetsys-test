cmake_minimum_required(VERSION 3.18)
project(assetsys-test
  DESCRIPTION "null0 game engine"
  HOMEPAGE_URL "https://github.com/konsumer/assetsys-test"
  VERSION 0.0.1
  LANGUAGES C
)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
  mattiasgustavsson
  GIT_REPOSITORY https://github.com/mattiasgustavsson/libs.git
  GIT_TAG main
  GIT_PROGRESS TRUE
  GIT_SHALLOW 1
)

FetchContent_MakeAvailable(mattiasgustavsson)
include_directories(${mattiasgustavsson_SOURCE_DIR})

add_executable(${PROJECT_NAME} main.c )