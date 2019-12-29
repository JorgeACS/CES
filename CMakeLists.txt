cmake_minimum_required(VERSION 3.1)

project(Heart)

## If you want to link SFML statically
 set(SFML_STATIC_LIBRARIES TRUE)
## In most cases better set in the CMake cache
 set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)


set(PROJECT_HEADERS
        Entities/Player.h
        Utilities/Point.h
        Input/Controller.h
        LevelManager/Stage.h
        Entities/Platform.h
        Utilities/Camera.h
        Utilities/GameStates.h
        Utilities/CircularList.h
        Entities/Enemy.h
        Entities/GameObject.h
        Containers/TextureContainer.h
        Utilities/MenuStates.h
        SoundManager/SoundManager.h
        Containers/SoundBufferContainer.h
        Utilities/Transition.h
        Utilities/Window.h
        )
set(PROJECT_SOURCES
        main.cpp
        Entities/Player.cpp
        Utilities/Point.cpp
        Input/Controller.cpp
        LevelManager/Stage.cpp
        Entities/Platform.cpp
        Utilities/Camera.cpp
        Utilities/CircularList.cpp
        Entities/Enemy.cpp
        Entities/GameObject.cpp
        Containers/TextureContainer.cpp
        SoundManager/SoundManager.cpp
        Containers/SoundBufferContainer.cpp
        Utilities/Transition.cpp
        )
set(GCC_COVERAGE_COMPILE_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
add_executable(Heart ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_link_libraries(Heart sfml-graphics sfml-audio)