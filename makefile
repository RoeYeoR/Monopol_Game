# Define the source files
SOURCES = main.cpp Board.cpp Chance.cpp CommunityChest.cpp EdgeSquare.cpp ElectricCompany.cpp  MonopolManager.cpp Player.cpp Point2D.cpp Street.cpp Tax.cpp Train.cpp WaterCompany.cpp

# Define the object files
OBJECTS = $(SOURCES:.cpp=.o)

# Define the SFML include and library paths
INCLUDE_PATH = "C:\Users\Roi\Documents\Libraries\SFML-2.6.1\include"
LIBRARY_PATH = "C:\Users\Roi\Documents\Libraries\SFML-2.6.1\lib"

# Compiler and linker flags
CXX = g++
CXXFLAGS = -I$(INCLUDE_PATH) 
LDFLAGS = -L$(LIBRARY_PATH)  -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows

# Target for building everything
all: compile link

# Compile phase
compile: $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link phase
link:
	$(CXX) $(OBJECTS) -o main $(LDFLAGS)

# Clean up object files
clean:
	rm -f *.o main
