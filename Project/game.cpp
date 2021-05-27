#include<GL/glut.h>
#include "game.h"
#include "gameGUI.h"
#include "List.h"
#include <iostream>
#include <array>
#include <string>

using namespace std;

//Varriables
//Position of the head
int posX, posY;
//To state when the game is over
bool over;
//The direction the snake is looking (0-left,1-up,2-right,3-down)
int dir;
//The coordinates bodyparts of the snake the last element is always the head
List<array<int, 2>> bodyParts;
//the position of the food
array<int, 2> foodPos;
//The direction where the snake can't go so the user accidentally don't go the exact opposite direction and lose
int bannedDir = -1;

//*******************************************************************
//Creates a random food on the field
void CreateNewFoodPos() {
	do
	{
		foodPos[0] = rand() % (COLUMNS - 3) + 1;
		foodPos[1] = rand() % (ROWS - 3) + 1;
		//So the food can't spawn in the snake's body
		bool found = false;
		for (size_t i = 0; i < bodyParts.Count(); i++)
		{
			if (bodyParts[i][0] == foodPos[0] && bodyParts[i][1] == foodPos[1])
			{
				found = true;
				break;
			}
		}
		//if the food is not in the snake's body then return
		if (!found)
			return;
	} while (true);
}

//-----------------------------------------------------------------
//Creates a new game
void InitGame(int x, int y) {
	posX = x;
	posY = y;
	over = false;
	bodyParts.Add({ posX,posY });
	srand(time(0) * 15);
	CreateNewFoodPos();
}

//-----------------------------------------------------------
//Returns true if the snake went into itself
bool CollisionTest() {
	for (size_t i = 0; i < bodyParts.Count() - 1; i++)
	{
		if (bodyParts.Last()[0] == bodyParts[i][0] && bodyParts.Last()[1] == bodyParts[i][1])
			return true;
	}
	return false;
}

//------------------------------------------------------------
//Move a snake forward into the direction it is looking
void Move() {
	//If the game is over do nothing
	if (over)
		return;

	//Determines which pos to increment
	if (dir % 2 == 0) {
		posX += dir - 1;
		if (bodyParts.Count() > 1)
			bannedDir = (dir - 2) * -1;
	}
	else
	{
		posY -= dir - 2;
		if (bodyParts.Count() > 1)
			bannedDir = (dir - 4) * -1;
	}
	//If it went into the wall end the game
	if (posX >= COLUMNS - 1) {
		posX = COLUMNS - 2;
		over = true;
		return;
	}
	else if (posX < 1) {
		posX = 1;
		over = true;
		return;
	}
	if (posY >= ROWS - 1) {
		posY = ROWS - 2;
		over = true;
		return;
	}
	else if (posY < 1) {
		posY = 1;
		over = true;
		return;
	}
	//Move the god damn snake
	bodyParts.Add({ posX,posY });
	//debug code
	cout << "posX: " + to_string(bodyParts.Last()[0]) + " posY: " + to_string(bodyParts.Last()[1]) << endl;
	if (posX == foodPos[0] && posY == foodPos[1]) {
		CreateNewFoodPos();
	}
	else {
		//Remove one part if it hasn't eaten
		bodyParts.RemoveAt(0);
	}
	//Check for collision
	over = CollisionTest();
}