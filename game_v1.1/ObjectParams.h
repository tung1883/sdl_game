#pragma once

#include <iostream>
class ObjectParams {
public:
	ObjectParams(std::string textureID, int x, int y, int width, int height, int numFrames = 1, int numRows = 1)
		:m_textureID(textureID), m_x(x), m_y(y), m_width(width), m_height(height), m_numFrames(numFrames), m_numRows(numRows)
	{};

	int getX() const { return m_x; };
	int getY() const { return m_y; };
	int getWidth() const { return m_width; };
	int getHeight() const { return m_height; };
	int getFrames() const { return m_numFrames; };
	int getRows() const { return m_numRows; };
	std::string getID() const { return m_textureID; };

private:
	std::string m_textureID;

	int m_x;
	int m_y;

	int m_width;
	int m_height;

	int m_numFrames;
	int m_numRows;
};