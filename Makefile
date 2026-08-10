CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2 -Iinclude
LDFLAGS   = $(shell pkg-config --libs raylib) -lGL -lm -lpthread -ldl -lrt -lX11

SRC_DIR := src
OBJ_DIR := obj
SRCS    := $(wildcard $(SRC_DIR)/*.cpp)
OBJS    := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
TARGET  := build/game

EMSDK       ?= $(HOME)/emsdk
RAYLIB_SRC  ?= $(HOME)/raylib-src/src
RAYLIB_WEB  := $(RAYLIB_SRC)/libraylib.web.a
WEB_DIR     := build/web
WEB_HTML    := $(WEB_DIR)/index.html
WEB_ZIP     := build/conway_game_of_life_itch.zip
EMSDK_ENV   := . $(EMSDK)/emsdk_env.sh >/dev/null 2>&1 &&

.PHONY: all clean run debug web web-zip

all: $(TARGET)

$(TARGET): $(OBJS) | $(dir $(TARGET))
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

$(dir $(TARGET)):
	mkdir -p $@

$(WEB_DIR):
	mkdir -p $@

$(RAYLIB_WEB):
	git clone --depth 1 --branch 6.0 https://github.com/raysan5/raylib $(dir $(RAYLIB_SRC))
	$(EMSDK_ENV) $(MAKE) -C $(RAYLIB_SRC) PLATFORM=PLATFORM_WEB

$(WEB_HTML): $(SRCS) $(RAYLIB_WEB) shell.html | $(WEB_DIR)
	$(EMSDK_ENV) em++ -o $@ $(SRCS) -I$(RAYLIB_SRC) -std=c++17 -O2 \
	  $(RAYLIB_WEB) \
	  -sUSE_GLFW=3 \
	  -sASYNCIFY \
	  -sASYNCIFY_STACK_SIZE=1048576 \
	  -sSTACK_SIZE=1MB \
	  -sTOTAL_MEMORY=128MB \
	  -sALLOW_MEMORY_GROWTH=1 \
	  -sFORCE_FILESYSTEM=1 \
	  -sEXPORTED_RUNTIME_METHODS=ccall \
	  -sMINIFY_HTML=0 \
	  --embed-file assets/fonts \
	  --shell-file shell.html

web: $(WEB_HTML)

web-zip: $(WEB_HTML) | $(dir $(TARGET))
	cd $(WEB_DIR) && rm -f ../../$(WEB_ZIP) && zip -r ../../$(WEB_ZIP) index.html index.js index.wasm

run: $(TARGET)
	./$(TARGET)

debug: CXXFLAGS += -g -O0 -DDEBUG
debug: all

clean:
	rm -rf $(OBJ_DIR) build
