cmake_minimum_required(VERSION 2.8)

project(SpaceJunk)

set(YAML_LIB yaml/Yaml.cpp)
set(SOURCE_DIR src/)

# SFML lib
include_directories(/usr/include/)

#YAML lib
add_library(YAML STATIC ${YAML_LIB})

include_directories(${SOURCE_DIR})
add_executable(${PROJECT_NAME} 
  ${SOURCE_DIR}action.cpp
  ${SOURCE_DIR}actionmanager.cpp
  ${SOURCE_DIR}appcontroller.cpp
  ${SOURCE_DIR}bullet.cpp
  ${SOURCE_DIR}create_gameobject_action.cpp
  ${SOURCE_DIR}drawer.cpp
  ${SOURCE_DIR}event.cpp
  ${SOURCE_DIR}exitwidget.cpp
  ${SOURCE_DIR}field.cpp
  ${SOURCE_DIR}game.cpp
  ${SOURCE_DIR}gameobject.cpp
  ${SOURCE_DIR}hierarchynode.cpp
  ${SOURCE_DIR}main.cpp
  ${SOURCE_DIR}merrors.cpp
  ${SOURCE_DIR}sceneevent.cpp
  ${SOURCE_DIR}ship.cpp
  ${SOURCE_DIR}ui.cpp
  ${SOURCE_DIR}vector.cpp
  ${SOURCE_DIR}widget.cpp
  
  ${SOURCE_DIR}events/inputevent.cpp
  ${SOURCE_DIR}events/keyboarddata.cpp
  ${SOURCE_DIR}events/mousebuttondata.cpp
  ${SOURCE_DIR}events/mousemotiondata.cpp
  ${SOURCE_DIR}events/systemevents_to_inputevents_converter.cpp
)

target_link_libraries(${PROJECT_NAME} YAML ${SFML_DIR})
