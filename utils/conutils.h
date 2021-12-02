#pragma once
#ifndef __CONUTILS__
#define __CONUTILS__

#include <iostream>
#include <conio.h>

class Conutils {
public:
	static void newline() {
		std::cout << "\n";
	}

	static void clearscreen() {
		system("cls");
	}

	static void pause() {
		_getch();
	}
};

#endif
