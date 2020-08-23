#include <GL/glut.h>
#include <string>
#include <iostream>
#include "./headers/pso.hpp"
#include <unistd.h>
#include <cmath>
#include <cstdlib>

#define ESC 27
#define unused(x) ((void)x)
#define window_width (1000)
#define window_height (1000)
#define window_position (500)

static void register_callbacks(void);
static void on_keyboard(unsigned char, int, int);
static void on_display(void);
static void init(void);
static void window_init(int, char **);
static void on_reshape(int, int);
static void init_material(void);
static void init_lights(void);
static void draw_coosys(void);

int main(int argc, char **argv)
{
    window_init(argc, argv);
    init();
    register_callbacks();
    glutMainLoop();

    return 0;
}

static void window_init(int argc, char **argv)
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
    // Needed for the fog
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_FOG);
    GLfloat fogColor[] = {0.5, 0.5, 0.5, 0};

    glFogfv(GL_FOG_COLOR, fogColor);
    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogf(GL_FOG_DENSITY, 0.2);
    glHint(GL_FOG_HINT, GL_NICEST);
}

static void register_callbacks(void)
{
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
}

static void on_keyboard(unsigned char key, int x, int y)
{
    unused(x);
    unused(y);

    switch (key)
    {
    case ESC:
        exit(0);
        break;
    }
}

static void on_reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, (float)width / height, 1, 50);
}

void renderString(GLdouble x, GLdouble y, const std::string &word)
{
    glColor3f(1, 0, 0);
    glRasterPos2d(x, y);
    for (unsigned i = 0; i < word.size(); ++i)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, word[i]);
    }
}

static void init_lights(void)
{
    const float ambient[] = {0.1, 0.1, 0.1, 1};
    const float diffuse[] = {0.7, 0.7, 0.7, 1};
    const float position[] = {1, 1, 1, 0};
    const float specular[] = {0.9, 0.9, 0.9, 1};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}

static void init_material(void)
{
    GLfloat ambient[] = {0.3, 0, 0, 1};
    GLfloat diffuse[] = {1, 1, 0, 1};
    GLfloat specular[] = {1, 1, 1, 1};
    GLfloat shininess = 30;
    // Da bi se normalno osvetlilo
    // Uvek kad se seku predmeti
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

#define size (10)

static void draw_snowflake(float angle)
{
    glPushMatrix();
    glRotatef(cos(size) * angle, 1, 1, 1);
    draw_coosys();
    glPopMatrix();
    glPushMatrix();
    glRotatef(sin(size) * angle, 1, 0, 1);
    draw_coosys();
    glPopMatrix();
}

static void draw_coosys(void)
{
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glEnd();
}

static void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Camera setup
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 5, 5,
              0, 0, 0,
              1, 0, 1);

    //init_lights();
    init_material();
    // Write intro

    // Enabling fog for certain amount of time
    // usleep(3000);
    // glDisable(GL_FOG);
    // glLoadIdentity();
    // TODO ------------- Different PSO for couple of secs
    PSO().start();
    // glPushMatrix();
    // glLoadIdentity();
    // renderString(40, 30, "hello");
    // glPopMatrix();
    //draw_coosys();
    glutSolidCube(3);
    for (int i = 0; i < 15; ++i)
    {
        glTranslatef(i, 0, 0);
        glColor3f(0, 1, 0);
        glutSolidCube(i);
    }

    glutPostRedisplay();
    glutSwapBuffers();
}
