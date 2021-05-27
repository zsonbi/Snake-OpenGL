#include <GL\glut.h>
#include <iostream>
#include "game.h"
#include <conio.h>

#define COLUMNS 40
#define ROWS 40
#define FPS 30
#define WIDTH 1000
#define HEIGHT 1000

int xIndex = 1;
int yIndex = 1;
int dir = 0;

void display_callback() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawGrid();
	if (dir % 2 == 0) {
		xIndex += dir - 1;
	}
	else
	{
		yIndex -= dir - 2;
	}
	if (xIndex >= COLUMNS - 1) {
		xIndex = 1;
	}
	else if (xIndex < 1) {
		xIndex = ROWS - 2;
	}
	if (yIndex >= ROWS - 1) {
		yIndex = 1;
	}
	else if (yIndex < 1) {
		yIndex = ROWS - 2;
	}

	glRectd(xIndex, yIndex, xIndex + 1, yIndex + 1);
	glutSwapBuffers();
}

void reshape_callback(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer_callback, 0);
}

void keyboard_callback(int key, int, int) {
	switch (key)
	{
	case GLUT_KEY_LEFT:
		dir = 0;
		break;
	case GLUT_KEY_UP:
		dir = 1;
		break;
	case GLUT_KEY_RIGHT:
		dir = 2;
		break;
	case GLUT_KEY_DOWN:
		dir = 3;
		break;
	default:
		break;
	}
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	initGrid(COLUMNS, ROWS);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("snake");
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutTimerFunc(0, timer_callback, 0);
	glutSpecialFunc(keyboard_callback);
	init();
	glutMainLoop();

	return 0;
}