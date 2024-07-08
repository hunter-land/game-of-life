#include "cellBoard.hpp"
#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>

//Rules for the game of life:
//Live with < 2 adjacent dies (Underpopulation)
//Live with 2-3 adjacent lives (Sustained)
//Live with > 3 adjacent dies (Overpopulation)
//Dead with 3 adjacent is born (Reproduction)

//Can be simplified to:
//adj < 2 || adj > 3 := Death
//adj == 3 := Life

constexpr size_t cellBoard::cellIndex(size_t x, size_t y) const {
	/*Pattern-\
	| 0  1  2 |
	| 3  4  5 |
	\--------*/
	return y * m_width + x;
}

cellBoard::cellBoard(size_t width, size_t height) {
	m_width = width;
	m_height = height;
	m_board.resize(width * height);
}

cellBoard::cellBoard(size_t width, size_t height, const std::vector<bool>& initial) {
	if (initial.size() != width * height) {
		throw std::logic_error("Initial board dimension mismatch");
	}

	m_width = width;
	m_height = height;
	m_board = initial;
}

cellBoard cellBoard::futureGeneration(size_t generations) const { //Get state of board in the future (n generations later)
	//Create a new board based off of this one
	//Repeat this n times
	cellBoard prev = *this;
	for (size_t i = 0; i < generations; i++) {
		cellBoard next = prev; //Create board of the next generation

		for (size_t x = 0; x < m_width; x++) {
			for (size_t y = 0; y < m_height; y++) {
				uint8_t adj = prev.adjacentLivingCells(x, y);
				//Based on rules, should this cell be alive or dead?
				if (adj < 2 || adj > 3) {
					//Cell dies if alive
					next.setCell(x, y, false);
				} else if (adj == 3) {
					//Cell is born
					next.setCell(x, y, true);
				} else {
					//No change
				}
			}
		}

		prev = next; //Next becomes previous for new generation
	}

	return prev; //This is previous only in context of the loop. By this point, it is the desired iteration of *this board
}

constexpr size_t cellBoard::width() const {
	return m_width;
}

constexpr size_t cellBoard::height() const {
	return m_height;
}

uint8_t cellBoard::adjacentLivingCells(size_t x, size_t y) const { //Return uint8_t since it's the smallest width type that fits all possible returns
	uint8_t adj = 0;
	for (int8_t xOffset = -1; xOffset <= 1; xOffset++) {
		for (int8_t yOffset = -1; yOffset <= 1; yOffset++) {
			if (xOffset == 0 && yOffset == 0) {
				continue; //Skip ourselves, only count adjacent cells
			} else if (x + xOffset < m_width && x + xOffset >= 0 && y + yOffset < m_height && y + yOffset >= 0) {
				size_t i = cellIndex(x + xOffset, y + yOffset);
				adj += m_board[i];
			} else {
				//Cells outside of the board are considered to never be alive, so no action is needed
			}
		}
	}
	return adj;
}

bool cellBoard::getCell(size_t x, size_t y) const {
	if (x >= m_width || y >= m_height) {
		throw std::logic_error("Invalid coordinates");
	}

	size_t i = cellIndex(x, y);
	return m_board[i];
}

void cellBoard::setCell(size_t x, size_t y, bool val) {
	if (x >= m_width || y >= m_height) {
		throw std::logic_error("Invalid coordinates");
	}

	size_t i = cellIndex(x, y);
	m_board[i] = val;
}

std::string cellBoard::str() const {
	const std::string filled = "■";
	const std::string empty = "□";

	std::string out;

	for (size_t y = 0; y < m_height; y++) {
		for (size_t x = 0; x < m_width; x++) {
			out += getCell(x, y) ? filled : empty;
		}
		out += '\n'; //Newline between rows
	}

	return out;
}
