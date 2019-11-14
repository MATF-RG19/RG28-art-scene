#include <GL/glut.h>
#include <string>

#define window_width (600)
#define window_height (600)

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Art scene");

    glClearColor(0.75, 0.75, 0.75, 0);
    glEnable(GL_DEPTH_TEST);

	glutMainLoop();

	return 0;
}
