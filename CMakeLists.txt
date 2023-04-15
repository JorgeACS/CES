cmake_minimum_required(VERSION 3.21)
project(Heart LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
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
add_executable(Heart ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_link_libraries(Heart PRIVATE sfml-graphics sfml-audio)
target_compile_features(Heart PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
 add_custom_command(TARGET Heart POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Heart> $<TARGET_FILE_DIR:Heart> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS Heart)
