#include <iostream>
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

	Console::setWindowTitle("ASCII Survival");
	Console::setColour(Console::WHITE, Console::BLACK);
	Console::clear();

	// Display playername in centre of console
	Console::setCursorPosition(6, 64 - (playernameStr.length() / 2));
	cout << playernameStr;
	Console::setCursorPosition(7, 64);
	cin >> playerName;

	Console::clear();

	// Display Map size in centre of console
	Console::setCursorPosition(6, 64 - (mapSizeStr.length() / 2));
	cout << mapSizeStr << endl;
	Console::setCursorPosition(7, 64);
	cin >> mapSize;

	// Checks if the mapSize has
	// correct data type
	while (cin.fail()) {

		// Remove newline
		cin.clear();
		cin.ignore(1000, '\n');

		string validationStr = "Looks like you didn't enter an integer. Please try again";
		Console::setCursorPosition(9, 64 - (validationStr.length() / 2));
		cout << validationStr;

		// Clear input line
		Console::setCursorPosition(7, 64);
		for (int i = 0; i < 32; i++) {
			cout << ' ';
		}

		Console::setCursorPosition(7, 64);
		cin >> mapSize;

		// Clear validation string
		Console::setCursorPosition(9, 64 - (validationStr.length() / 2));
		for (int i = 0; i < validationStr.length(); i++) {
			cout << ' ';
		}
	}

	// Checks if the mapSize entered is valid
	while (mapSize < 18 || mapSize > 21) {
		string validationStr;

		// Set correct validation string depending on mapSize
		if (mapSize > 21) { validationStr = "Map size is too big!"; }
		else if (mapSize < 18) { validationStr = "Map size is too small!"; }
		Console::setCursorPosition(9, 64 - (validationStr.length() / 2));
		cout << validationStr;

		// Clear input line
		Console::setCursorPosition(7, 64);
		for (int i = 0; i < to_string(mapSize).length(); i++) {
			cout << ' ';
		}

		Console::setCursorPosition(7, 64);
		cin >> mapSize;

		// Clear validation string
		Console::setCursorPosition(9, 64 - (validationStr.length() / 2));
		for (int i = 0; i < validationStr.length(); i++) {
			cout << ' ';
		}
	}

	Console::clear();

	// Display difficulty list in centre of console
	Console::setCursorPosition(6, 64 - (difficultyStr.length() / 2));
	cout << difficultyStr;
	Console::setCursorPosition(7, 64 - (operateStr.length() / 2));
	cout << operateStr << endl << endl;

	while (isSelectingDifficulty) {
		Console::setCursorPosition(9, 64);

		// Limit options to select to be within
		// the size of the difficulty list
		if (option < 0) { option = 0; }
		else if (option >= difficultyList.size()) { option = difficultyList.size() - 1; }

		// Loop through all difficulties
		// and highlight the selected difficulty
		for (int i = 0; i < difficultyList.size(); i++) {
			if (i == option) { Console::setColour(Console::BLACK, Console::WHITE); }
			else { Console::setColour(Console::WHITE, Console::BLACK); }

			Console::setCursorPosition(Console::getCursorPosition().Y, (64 - (difficultyList[i].getName().length() / 2)) - 2);
			cout << "  " << difficultyList[i].getName() << "  " << endl;
		}

		// Get key pressed to
		// change or select the
		// current difficulty
		int key = _getch();
		switch (key) {
		case 72:
			// Up arrow
			option--;
			break;
		case 80:
			// Down arrow
			option++;
			break;
		case 13:
			// Enter
			selectedDifficulty = difficultyList[option];
			isSelectingDifficulty = false;
			break;
		}
	}

	Console::setColour(Console::WHITE, Console::BLACK);
	Console::clear();


	// Create new game instance
	Game* game = new Game(mapSize, mapSize, selectedDifficulty);


	// Only render map and controls once
	// Prevents from continuously re-rendering map
	game->drawMap();
	game->showControls();

	// Run render and update only whilst the game is running,
	// or only until player wants to quit
	while (game->isRunning() && !game->getPlayer().doQuit()) {
		game->render();
		game->update();
	}

	// Check if player has quit or
	// not after after game has ended
	if (!game->getPlayer().doQuit()) {
		string result;
		Console::COLOUR resultColour;

		// If player won, set console background to Green and result text to "won"
		// if not, set console background to Red and result text to "lost"
		if (game->hasPlayerWon()) {
			resultColour = Console::GREEN;
			result = "won";
		} else {
			resultColour = Console::RED;
			result = "lost";
		}

		// Set background to resultColour
		Console::setColour(resultColour, resultColour);
		Console::clear();

		// Print win/lost statement with
		// how many enemies were killed
		string gameResult = "You " + result + "!";
		string enemiesKilledStr = "Enemies killed: " + to_string(game->getKilledEnemies());
		Console::setColour(Console::WHITE, resultColour);
		Console::setCursorPosition(14, 64 - (gameResult.length() / 2));
		cout << gameResult << endl;
		Console::setCursorPosition(Console::getCursorPosition().Y, 64 - (enemiesKilledStr.length() / 2));
		cout << enemiesKilledStr << endl;
	} else {
		// Draw blank console due to player quit
		Console::setColour(Console::WHITE, Console::BLACK);
		Console::clear();
	}

	// Log game result to "result.txt"
	game->log(playerName, game->getPlayer().doQuit());
	game->stopLogging();
}