#pragma once
#ifndef __ELEMENT__
#define __ELEMENT__

class Position {
public:
	int x;
	int y;

	Position() {}

	Position(const int& x, const int& y) {
		this->x = x;
		this->y = y;
	}

	void operator= (const Position& p) {
		this->x = p.x;
		this->y = p.y;
	}
};

class Element {
private:
	int m_number;
	Position m_position;

public:
	Element() {}

	Element(const int& number,
		const int& x,
		const int& y) {
		m_number = number;
		m_position.x = x;
		m_position.y = y;
	}

	~Element() {}

	int getNumber() {
		return m_number;
	}

	void setNumber(const int& number) {
		m_number = number;
	}

	int getX() {
		return m_position.x;
	}

	int getY() {
		return m_position.y;
	}

	void setPosition(const int& x,
		const int& y) {
		m_position.x = x;
		m_position.y = y;
	}

	void operator= (const Element& e) {
		m_number = e.m_number;
		m_position = e.m_position;
	}
};


#endif // !__ELEMENT__

