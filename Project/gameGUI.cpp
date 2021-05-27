#include <GL/glut.h>
#include "game.h"
#include "gameGUI.h"

//Constants
#define SPEED 10	//Speed of the updates approximately this is the fps also
#define WIDTH 1000	//Width of the window
#define HEIGHT 1000	//Height of the window

//************************************************************
//Function declarations
void display_callback();
void reshape_callback(int, int);
void timer_callback(int);
void init();
void unit(int, int);
void drawGrid();

//************************************************************
//Keyboard event callback
void keyboard_callback(int key, int, int) {
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if (bannedDir == 0)
			return;
		dir = 0;
		break;
	case GLUT_KEY_UP:
		if (bannedDir == 1)
			return;
		dir = 1;
		break;
	case GLUT_KEY_RIGHT:
		if (bannedDir == 2)
			return;
		dir = 2;
		break;
	case GLUT_KEY_DOWN:
		if (bannedDir == 3)
			return;
		dir = 3;
		break;
	default:
		break;
	}
}

//**************************************************************
//Creates a new window and starts the snake game
void InitMainWindow(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("snake");
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutTimerFunc(0, timer_callback, 0);
	glutSpecialFunc(keyboard_callback);
	init();
	glutMainLoop();
}

//---------------------------------------------------------------------
//This runs every frame
void display_callback() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawGrid();
	Move();
	glRectd(posX, posY, posX + 1, posY + 1);
	glColor3f(0.0, 1.0, 0.0);
	for (int i = 0; i < bodyParts.Count() - 1; i++)
	{
		glRectd(bodyParts[i][0], bodyParts[i][1], bodyParts[i][0] + 1, bodyParts[i][1] + 1);
	}
	glColor3f(0.7, 0.2, 0.2);
	glRectd(foodPos[0], foodPos[1], foodPos[0] + 1, foodPos[1] + 1);

	glutSwapBuffers();
}

//----------------------------------------------------------------------
//This is called when the window is resized
void reshape_callback(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

//--------------------------------------------------------------------
//This controls the fps
void timer_callback(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / SPEED, timer_callback, 0);
}

//---------------------------------------------------------------------
//Sets the default background color and creates the snake game
void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	InitGame(ROWS / 2, COLUMNS / 2);
}

//---------------------------------------------------------------------
//Draws a rectangle
void unit(int x, int y) {
	if (x == 0 || y == 0 || y == ROWS - 1 || x == COLUMNS - 1) {
		glColor3f(1.0, 0.0, 0.0);
		glLineWidth(3.0);
	}
	else {
		glLineWidth(1.0);
		glColor3f(1.0, 1.0, 1.0);
	}
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + 1, y);
	glVertex2f(x + 1, y + 1);
	glVertex2f(x, y + 1);
	glEnd();
}

//-------------------------------------------------------------------
//Draws the grid
void drawGrid() {
	for (int i = 0; i < COLUMNS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			unit(i, j);
		}
	}
}