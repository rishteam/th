CXX=g++
CXXFLAGS=-std=c++14
# Include and link path
ifeq ($(OS),Windows_NT)
	INC_PATH=-I./thirdparty/SFML-2.5.1/include
	LIB_PATH=-L./thirdparty/SFML-2.5.1/lib
else
	# Other plaform
endif

INC_PATH += -I./include

D_LIB=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lfmt
S_LIB=-DSFML_STATIC -static -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lfmt
S_LIB+=-lopengl32 -lfreetype -lwinmm -lgdi32
S_LIB+=-lopenal32 -lvorbisenc -lvorbisfile -lvorbis -lFLAC -lm -logg
LIBS=$(S_LIB)

ifeq ($(LIBS), $(S_LIB))
	DEFINE=-DSFML_STATIC
endif

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux) # Linux
endif
ifeq ($(UNAME_S),Darwin) # macOS
	LIBS=$(D_LIB)
endif

EXE=th
SOURCES=main.cpp game.cpp
SOURCES+= player.cpp bullet.cpp entity.cpp utils.cpp
SOURCES+= animation.cpp resManager.cpp log.cpp

OBJS=$(addsuffix .o, $(basename $(notdir $(SOURCES))))

%.o:src/%.cpp
	$(CXX) $(CXXFLAGS) $(INC_PATH) $(LIB_PATH) $(DEFINE) -c $< -o $@

all: $(EXE)
	@echo Build complete for $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INC_PATH) $(LIB_PATH) $^ $(LIBS) -o $@

.PHONY: clean
clean:
	$(RM) -f $(OBJS) $(EXE)