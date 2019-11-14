#include <GL/glut.h>
#include <string>

#define ESC 27
#define unused(x) ((void) x)
#define window_width (600)
#define window_height (600)

static void on_keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Art scene");

    glClearColor(0.75, 0.75, 0.75, 0);
    glutKeyboardFunc(on_keyboard);
    glEnable(GL_DEPTH_TEST);

	glutMainLoop();

	return 0;
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

