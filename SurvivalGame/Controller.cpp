#include <conio.h>

#include "Controller.h"
#include "Game.h"

void Controller::start() {

	int consoleTextWidth = Console::getTextBufferSize().X;
	int consoleTextHeight = Console::getTextBufferSize().Y;

	vector<Difficulty> difficultyList;
	difficultyList.push_back(Difficulty("Easy", 5, 4));
	difficultyList.push_back(Difficulty("Medium", 10, 8));
	difficultyList.push_back(Difficulty("Hard", 15, 12));

	bool isSelectingDifficulty = true;
	Difficulty selectedDifficulty;
	int option = 0;

	Console::clear();
	string difficultyStr =  "Select Difficulty";
	string operateStr = "Use arrow keys to select";
	Console::setCursorPosition(6, (consoleTextWidth / 2) - (difficultyStr.length() / 2));
	cout << difficultyStr;
	Console::setCursorPosition(7, (consoleTextWidth / 2) - (operateStr.length() / 2));
	cout << operateStr << endl << endl;

	while (isSelectingDifficulty) {
		if (option < 0) { option = 0; }
		else if (option >= difficultyList.size()) { option = difficultyList.size() - 1; }
		
		for (int i = 0; i < difficultyList.size(); i++) {
			if (i == option) {
				Console::setColour(Console::BLACK, Console::WHITE);
			}
			else {
				Console::setColour(Console::WHITE, Console::BLACK);
			}

			Console::setCursorPosition(Console::getCursorPosition().Y, ((consoleTextWidth / 2) - (difficultyList[i].getName().length() / 2)) - 2);
			cout << "  " << difficultyList[i].getName() << "  " << endl;
		}

		int key = _getch();
		switch (key) {
		case 72:
			option--;
			break;
		case 80:
			option++;
			break;
		case 13:
			selectedDifficulty = difficultyList[option];
			isSelectingDifficulty = false;
			break;
		}
		Console::setCursorPosition(9, 0);
	}

	Console::setColour(Console::WHITE, Console::BLACK);
	Console::clear();

	Game game = Game(15, 15, selectedDifficulty);

	game.drawMap();

	while (game.isRunning() && !game.getPlayer().doQuit()) {
		game.render();
		game.update();
	}

	game.stopLogging();

	Console::setCursorPosition(20, 0);
}