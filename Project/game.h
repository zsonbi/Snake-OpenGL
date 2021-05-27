#pragma once
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "List.h"
#include <array>
/// <summary>
/// Creates a new snake game
/// </summary>
/// <param name="row">Where the snake should start</param>
/// <param name="col">Where the snake should start</param>
void InitGame(int, int);
/// <summary>
/// Moves the snake
/// </summary>
void Move();
/// <summary>
/// The direction where the snake is looking (0-left,1-up,2-right,3-down)
/// </summary>
extern int dir;
/// <summary>
/// The x cord of the head
/// </summary>
extern int posX;
/// <summary>
/// The y cord of the head
/// </summary>
extern int posY;
/// <summary>
/// If the game is over
/// </summary>
extern bool over;
/// <summary>
/// Position of the food
/// </summary>
extern std::array<int, 2> foodPos;
/// <summary>
/// Positions of the bodyparts
/// </summary>
extern List<std::array<int, 2>> bodyParts;
//The direction where the snake can't go so the user accidentally don't go the exact opposite direction and lose
extern int bannedDir;
#endif // GAME_H_INCLUDED
