cmake_minimum_required(VERSION 2.8)

project(SpaceJunk)

set(YAML_LIB yaml/yaml.cpp)
set(SOURCE_DIR src/)

# SFML dep
find_library(SFML REQUIRED)

add_library(YAML STATIC ${YAML_LIB})

include_directories(${SOURCE_DIR})
add_executable(${PROJECT_NAME} ${SOURCE_DIR}main.cpp)

target_link_libraries(main YAML)