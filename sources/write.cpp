#include <GL/glut.h>
#include <iostream>

void draw_name(std::string name)
{
    int current_width = glutGet(GLUT_WINDOW_WIDTH);
    int current_height = glutGet(GLUT_WINDOW_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    gluOrtho2D(0.0, current_width, current_height, 0.0);

    glRasterPos2i(current_width - 200.0f, current_height - 95.0f);
    for (char letter : name)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
    }
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
