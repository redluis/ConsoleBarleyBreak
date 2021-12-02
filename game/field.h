#pragma once
#ifndef __FIELD__
#define __FIELD__

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>

#include "element.h"
#include "..\utils\conutils.h"

enum FillingType {
	RANDOM,
	RIGHT
};

class Field {
private:
	int m_size;
	std::vector<std::vector<Element>> m_elements;
	Position m_emptyPosition;
	static const int m_low = 3;
	static const int m_high = 9;

public:
	Field() {
		m_size = m_low;
	}

	Field (const int& size) {
		if (size < m_low || size > m_high) {
			throw "Невалидный размер поля";
		}
		m_size = size;
	}

	~Field() {};

	void fillElements(FillingType type) {
		switch (type) {
		case RANDOM:
			fillRandom();
			break;
		case RIGHT:
			fillRight();
			break;
		default:
			throw "Неизвестный тип заполнения поля!";
		}
	}

	Element getByValue(const int& num) {
		for (auto row : m_elements) {
			for (auto element : row) {
				if (element.getNumber() == num) {
					return element;
				}
			}
		}
	}

	bool checkWin() {
		int amount = m_size * m_size - 1;

		for (int i(0); i < m_size; ++i) {
			for (int j(0); j < m_size; ++j) {
				if (amount != m_elements[i][j].getNumber()) {
					return false;
				}
				amount--;
			}
		}

		return true;
	}

	bool isSwipeable(Element e) {
		return (abs(m_emptyPosition.x - e.getX()) == 1) && (m_emptyPosition.y - e.getY() == 0) ||
			(m_emptyPosition.x - e.getX() == 0) && (abs(m_emptyPosition.y - e.getY()) == 1);
	}

	void swipe(Element e) {
		int x1 = e.getX();
		int y1 = e.getY();
		int x2 = m_emptyPosition.x;
		int y2 = m_emptyPosition.y;

		int temp = m_elements[x1][y1].getNumber();
		m_elements[x1][y1].setNumber(0);
		m_elements[x2][y2].setNumber(temp);

		m_emptyPosition.x = x1;
		m_emptyPosition.y = y1;
	}

	void printField() {
		for (auto row : m_elements) {
			Conutils::newline();
			Conutils::newline();
			Conutils::newline();
			for (auto element : row) {
				std::cout << "\t" << element.getNumber();
			}
		}

		Conutils::newline();
		Conutils::newline();
		Conutils::newline();
	}

	static bool isSizeValid(const int& size) {
		return size <= m_high && size >= m_low;
	}

	void operator= (const Field field) {
		m_size = field.m_size;
		m_elements = field.m_elements;
	}

private:
	void fillRandom() {
		std::vector<Element> elems;

		for (auto row : m_elements) {
			for (auto element : row) {
				elems.push_back(element);
			}
		}

		auto engine = std::default_random_engine{};
		std::shuffle(std::begin(elems), std::end(elems), engine);

		for (int i(0); i < m_size; ++i) {
			for (int j(0); j < m_size; ++j) {
				m_elements[i][j].setPosition(i, j);
				int num = elems.back().getNumber();
				m_elements[i][j].setNumber(num);
				elems.pop_back();
			}
		}

		m_emptyPosition = Position(getByValue(0).getX(), getByValue(0).getY());
	}

	void fillRight() {
		int remaining = m_size * m_size - 1;

		m_elements.resize(m_size);

		for (int i(0); i < m_size; ++i) {
			for (int j(0); j < m_size; ++j) {
				int num = remaining;
				m_elements[i].push_back(Element(num, i, j));
				remaining--;
			}
		}

		m_emptyPosition = Position(getByValue(0).getX(), getByValue(0).getY());
	}
};

#endif // !__FIELD__

