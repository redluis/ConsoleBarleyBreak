#pragma once
#ifndef __GAME__
#define __GAME__

#include <iostream>

#include "field.h"
#include "..\utils\conutils.h"

using namespace std;

class Game {
	Field field;
private:
	void setup() {
		setlocale(LC_ALL, "rus");
	}

	void startMenu() {
		printTitle();
		try {
			cout << "\t������� ������ ���� (3-9): ";
			int size;
			cin >> size;

			if (Field::isSizeValid(size)) {
				field = Field(size);
			} else {
				throw "�������� ������ ����";
			}

		} catch (int e) {
			throw "������������ ��� �����";
		}

		Conutils::clearscreen();
	}

	void startGame() {
		field.fillElements(RIGHT);
		field.printField();
		cout << "\t������� ����� ������ ��� ������)\n\n\n";
		Conutils::pause();
		field.fillElements(RANDOM);

		while (true) {
			Conutils::clearscreen();
			field.printField();

			if (field.checkWin()) {
				cout << "����������, �� ��������!";
				Conutils::pause();
				return;
			}

			cout << "\t������� ����� ��� ������������: ";
			int num;
			cin >> num;

			Element elem = field.getByValue(num);

			if (field.isSwipeable(elem)) {
				field.swipe(elem);
			} else {
				cout << "\t����� ������������� �� �����\n";
				Conutils::pause();
			}
		}
	}
public:
	Game() {}

	void start() {
		setup();
		startMenu();
		startGame();
	}

private:
	void printTitle() {
		cout
			<< "\n\n"
			<< "     ******   **     **   ******  ********\n"
			<< "     **   **   **   **   **   **     **\n"
			<< "     **   **    ** **   **    **     **\n"
			<< "     *****       ***    ********     **\n"
			<< "     ***         **     **    **     **\n"
			<< "     **         **      **    **     **\n"
			<< "     **        **       **    **     **\n\n"

			<< "     **     **    ******   ******  **   **\n"
			<< "     **     **   **   **  **       **   **\n"
			<< "     ****   **  **    **  **       **   **\n"
			<< "     ** **  **  ********   ******  *******\n"
			<< "     **  ** **  **    **        ** **   **\n"
			<< "     **   ****  **    **        ** **   **\n"
			<< "     **     **  **    **  *******  **   **\n\n"

			<< "                **   **   **\n"
			<< "                **  **    **\n"
			<< "                ****      **\n"
			<< "                ***       **\n"
			<< "                ** **     **\n"
			<< "                **   **   **\n"
			<< "                **   **   **\n\n\n";
	}
};

#endif // !__GAME__
