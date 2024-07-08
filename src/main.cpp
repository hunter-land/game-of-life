#include <iostream>
#include "cellBoard.hpp"
#include <vector>
#include <chrono>
#include <thread> //For sleeping between generation

int main(int argc, char** argv) {
	cellBoard board(3, 3, {1, 0, 0, 0, 1, 1, 1, 1, 0});

	if (argc > 1) {
		//User has given an initial board to use. Parse it
		std::vector<bool> cellValues;

		size_t width = std::stoul(argv[1]);
		size_t height = std::stoul(argv[2]);
		if (argc != width * height + 3) {
			std::cerr << "Dimension mis-match" << std::endl;
			std::cerr << "Usage: ./gol <width> <height> <cell values>" << std::endl;
		}

		cellValues.reserve(width * height);
		for (size_t i = 3; i < argc; i++) {
			bool cell = std::stoi(argv[i]);
			cellValues.push_back(cell);
		}

		board = cellBoard(width, height, cellValues);
	}

	//Run for 4 generations, printing each, with a 1s pause between them
	for (size_t i = 0; i < 5; i++) {
		std::cout << "Generation #" << i << ": " << std::endl;
		std::cout << board.str() << std::endl;

		board = board.futureGeneration();

		//Pause
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}
