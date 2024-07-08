#pragma once
#include <vector>
#include <cstdint>
#include <string>

class cellBoard {
protected:
	std::vector<bool> m_board;
	size_t m_width;
	size_t m_height;

	constexpr size_t cellIndex(size_t x, size_t y) const;
public:
	cellBoard(size_t width, size_t height);
	cellBoard(size_t width, size_t height, const std::vector<bool>& initial);

	cellBoard futureGeneration(size_t generations = 1) const; //Get state of board in the future (n generations later)

	constexpr size_t width() const;
	constexpr size_t height() const;

	uint8_t adjacentLivingCells(size_t x, size_t y) const;
	bool getCell(size_t x, size_t y) const;
	void setCell(size_t x, size_t y, bool val);

	std::string str() const;
};
