#pragma once
#ifndef GAMEGUI_H_INCLUDED
#define GAMEGUI_H_INCLUDED
/// <summary>
/// Number of rows in the matrix
/// </summary>
static const int ROWS = 20;
/// <summary>
/// Number of columns in the matrix
/// </summary>
static const int COLUMNS = 20;
/// <summary>
///	Starts the game and the creates the window
/// </summary>
/// <param name="argc">Fogalmam sincs</param>
/// <param name="argv">Fogalmam sincs</param>
void InitMainWindow(int, char**);
#endif // !GAMEGUI_H
