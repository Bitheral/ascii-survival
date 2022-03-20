#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stdio.h>
#include <Windows.h>

#include "Controller.h"

using namespace std;

int main() {

	Controller controller;
	controller.start();

	Sleep(5000);
	char c = getchar();
	return 0;
}