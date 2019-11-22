#include <GL/glut.h>
#include <string>
#include <iostream>
#include "./headers/pso.hpp"

#define ESC 27
#define unused(x) ((void) x)
#define window_width (1000)
#define window_height (1000)
#define window_position (500)

static void register_callbacks(void);
static void on_keyboard(unsigned char, int, int);
static void on_display(void);
static void init(void);
static void window_init(int, char**);

int main(int argc, char** argv)
{
    window_init(argc, argv);
    init();
    register_callbacks();
	glutMainLoop();

	return 0;
}

static void window_init(int argc, char** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(window_position, window_position);
    glutCreateWindow("Art scene");
}

static void init(void)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(1, 1, 1, 1);
}

static void on_keyboard(unsigned char key, int x, int y)
{
    unused(x);
    unused(y);

    switch (key) {
    case ESC:
        exit(0);
        break;
    }
}

static void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    PSO().start();
    glutPostRedisplay();
    glutSwapBuffers();
}

static void register_callbacks(void) {
    glutKeyboardFunc(on_keyboard);
    glutDisplayFunc(on_display); 
}
