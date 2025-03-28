cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
project(Game)


find_package(SDL2 CONFIG REQUIRED)
find_package(GLEW REQUIRED)

add_executable(Game main.cpp Map.cpp Game.cpp Player.cpp GameGL.cpp VAO.cpp VBO.cpp EBO.cpp)
target_link_libraries(Game
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    GLEW::GLEW
)
