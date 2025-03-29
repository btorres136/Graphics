find_package(SDL2 CONFIG REQUIRED)
find_package(GLEW REQUIRED)

add_executable(Game main.cpp map.cpp game.cpp player.cpp game_gl.cpp vao.cpp vbo.cpp ebo.cpp shader.cpp)
target_link_libraries(Game
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    GLEW::GLEW
)