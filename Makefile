BIN_DIR = exe
CXX = g++
CPPFLAGS = -Wall -g -std=c++11

all: $(BIN_DIR)/.dirstamp $/scrabble
	$(CXX) $(CPPFLAGS) $^ -o $@

$/scrabble: Move.h Board.cpp Move.cpp ConsolePrinter.cpp Exceptions.h Player.cpp Tile.h Bag.cpp Dictionary.cpp Gameclass.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)