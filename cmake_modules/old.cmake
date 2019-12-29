cmake_minimum_required(VERSION 3.7)
project(untitled)

set(CMAKE_CXX_STANDARD 11)


add_executable(untitled ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(untitled ${SFML_LIBRARIES})
    set(SOURCE_FILES main.cpp Entities/Player.h Utilities/Point.h Entities/Player.cpp Utilities/Point.cpp Input/Controller.h Input/Controller.cpp LevelManager/Stage.h LevelManager/Stage.cpp Entities/Platform.h Entities/Platform.cpp Utilities/Camera.h Utilities/Camera.cpp Utilities/GameStates.h Utilities/CircularList.h Utilities/CircularList.cpp Entities/Enemy.h Entities/Enemy.cpp Entities/GameObject.h Entities/GameObject.cpp Containers/TextureContainer.h Containers/TextureContainer.cpp Utilities/MenuStates.h SoundManager/SoundManager.h SoundManager/SoundManager.cpp Containers/SoundBufferContainer.h Containers/SoundBufferContainer.cpp Utilities/Transition.cpp Utilities/Transition.h Utilities/Window.h)
endif()