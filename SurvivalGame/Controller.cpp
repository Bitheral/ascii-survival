#include <conio.h>

#include "Controller.h"
#include "Game.h"

void Controller::start() {

	// Player-specific inputs
	int mapSize;
	string playerName, playernameStr, mapSizeStr;


	// Difficulty selection
	string difficultyStr, operateStr;
	Difficulty selectedDifficulty;
	bool isSelectingDifficulty = true;
	int option = 0;
	vector<Difficulty> difficultyList{ Difficulty("Easy", 5, 4), Difficulty("Medium", 10, 8), Difficulty("Hard", 15, 12) };

	// Input headings
	playernameStr = "Player name:";
	mapSizeStr = "Enter size of map: (Number between 18-21)";
	difficultyStr = "Select Difficulty";
	operateStr = "Use arrow keys to select, enter to choose";

	Console::setWindowTitle("Survival Game");
	Console::setColour(Console::WHITE, Console::BLACK);
	Console::clear();

	Console::setCursorPosition(6, 64 - (playernameStr.length() / 2));
	cout << playernameStr;
	Console::setCursorPosition(7, 64);
	cin >> playerName;

	Console::clear();

	Console::setCursorPosition(6, 64 - (mapSizeStr.length() / 2));
	cout << mapSizeStr << endl;
	Console::setCursorPosition(7, 64);
	cin >> mapSize;

	Console::clear();

	Console::setCursorPosition(6, 64 - (difficultyStr.length() / 2));
	cout << difficultyStr;
	Console::setCursorPosition(7, 64 - (operateStr.length() / 2));
	cout << operateStr << endl << endl;

	while (isSelectingDifficulty) {
		Console::setCursorPosition(9, 64);
		if (option < 0) { option = 0; }
		else if (option >= difficultyList.size()) { option = difficultyList.size() - 1; }

		for (int i = 0; i < difficultyList.size(); i++) {
			if (i == option) { Console::setColour(Console::BLACK, Console::WHITE); }
			else { Console::setColour(Console::WHITE, Console::BLACK); }

			Console::setCursorPosition(Console::getCursorPosition().Y, (64 - (difficultyList[i].getName().length() / 2)) - 2);
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
	}

	Console::setColour(Console::WHITE, Console::BLACK);
	Console::clear();

	Game* game = new Game(mapSize, mapSize, selectedDifficulty);

	game->drawMap();
	game->showControls();

	while (game->isRunning() && !game->getPlayer().doQuit()) {
		game->render();
		game->update();
	}

	if (!game->getPlayer().doQuit()) {
		string result;
		Console::COLOUR resultColour;
		if (game->hasPlayerWon()) {
			resultColour = Console::GREEN;
			result = "won";
		} else {
			resultColour = Console::RED;
			result = "lost";
		}

		Console::setColour(resultColour, resultColour);
		Console::clear();

		Sleep(2);

		string gameResult = "You " + result + "!";
		string enemiesKilledStr = "Enemies killed: " + to_string(game->getKilledEnemies());
		Console::setColour(Console::WHITE, resultColour);
		Console::setCursorPosition(14, 64 - (gameResult.length() / 2));
		cout << gameResult << endl;
		Console::setCursorPosition(Console::getCursorPosition().Y, 64 - (enemiesKilledStr.length() / 2));
		cout << enemiesKilledStr << endl;
	} else {
		Console::setColour(Console::WHITE, Console::BLACK);
		Console::clear();
	}

	game->log(playerName, game->getPlayer().doQuit());
	game->stopLogging();
}