CXX = clang++
CXXFLAGS = -std=c++17 -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lGLEW -framework OpenGL

SRC = main.cpp Game.cpp Player.cpp GameGL.cpp EBO.cpp VAO.cpp VBO.cpp
OBJ = $(SRC:%.cpp=build/%.o)
TARGET = build/game

all: $(TARGET)

# Regla para compilar y enlazar el ejecutable
$(TARGET): $(OBJ)
	@mkdir -p build
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)

# Regla para compilar .cpp a .o en build/
build/%.o: %.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build


