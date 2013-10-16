//
//  main.c
//  OpenGL Project
//
//  Created by Vishwajit Kolathur on 05/10/13.
//
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//  MACRO DEFINES
//  Starting Cordinate
#define START_CORD -5.0f
//  Ending Coordinate
#define END_CORD 5.0f
//  Duration of Animation
#define TIME_MAX 10
//  Time step, 1/timestep is fps
#define DELTA_T 0.125f
//  Angle of max, measured with x-axis
#define ANGLE_MAX 25
//  Frame Rate / 1000
#define FRAME_RATE 85
//  END DEFINES

//  Function Declerations
void capsule(void);
void body(void);
void display(void);
void animate(int time);
//  End Declerations


void capsule(){
    /*  A function to draw the basic functional unit of my worm
     *  uses a simple capsule like shape for each segment the
     *  capsule shape is a combination of 2 spheres and a cube
     *  the entire structure is aligned along the x - axis
     */
    glColor3f(0.8, 0.8, 0.8f);
    glutSolidSphere(0.1f,32,32);
    glPushMatrix();
    glTranslatef(0.5f, 0, 0);
    glutSolidSphere(0.1f,32,32);
    glPopMatrix();
    glPushMatrix();
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadratic,0.1f,0.1f,0.5f,32,32);
    glPopMatrix();
    return;
}
void body(){
    /*  A function to draw the basic functional unit of my worm
     *  uses a simple capsule like shape for each segment the
     *  capsule shape is a combination of 2 spheres and a cube
     *  the entire structure is aligned along the x - axis
     */
    glColor3f(0.8, 0.8, 0.8f);
    glPushMatrix();
    glTranslatef(0.5f, 0, 0);
    glutSolidSphere(0.1f,32,32);
    glPopMatrix();
    glPushMatrix();
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadratic,0.1f,0.1f,0.5f,32,32);
    glPopMatrix();
    return;
}
void display()
{
    /*
     *  A Simple display function to run the entire show
     *  static variables are used to save past state of
     *  the worm, and reflect future motion based on state
     */    static float trans;
    static float timer;
    static float dt;
    if(dt == 0.0f){
        dt = DELTA_T;
        trans = START_CORD;
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0 * 64/48.0, 2.0 * 64/48.0, -2.0, 2.0, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //  Angular (maybe isometric) view
    gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //  Side View
    //gluLookAt(1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //  Top View
    //gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(0,0,1.0,1.0);
    glTranslatef(trans, 0.0, 0.0);
    capsule();
    glTranslatef(0.5f, 0.0, 0.0);
    glRotatef(ANGLE_MAX*(timer), 0.0, 0.0, 1.0f);
    body();
    glTranslatef(0.5f, 0.0, 0.0);
    glRotatef(-2*ANGLE_MAX*(timer), 0.0, 0.0, 1.0f);
    body();
    glTranslatef(0.5f, 0.0, 0.0);
    glRotatef(ANGLE_MAX*(timer), 0.0, 0.0, 1.0f);
    body();
    if(timer == 1 || (timer==0 && dt<0)){
        dt = -dt;
    }
#ifdef __APPLE__
    glSwapAPPLE();
#else
    glSwapBuffers();
#endif
    trans = trans + 0.1f*timer;
    timer = timer + dt;
    
    
}
void animate(int value){
    /*  Inorder to make a system independent frame by frame animation
     *  this function calls itself every 66ms by using the Timer funct
     *  by calling itself, it registers the next call and calls redisp
     *  causing the display function to be called.
     */
    if(value >= 150)
        return;
    glutTimerFunc(FRAME_RATE, animate, ++value);
    glutPostRedisplay();
    return;
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutCreateWindow(" Three D viewing");
    glClearColor(10.0f,10.0f,10.0f, 1.0f);
    glViewport(0, 0, 640, 480);
    //  To include Depth Calculations
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    //  To enable lighting
    //  Initializing light coordinates
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    //  Creating the lights
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //  Enabling Smooth Shading
    glShadeModel(GL_SMOOTH);
    //  Enabling material colouring
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    //  GLUT Display Function
    glutDisplayFunc(display);
    animate(0);
    glutMainLoop();
    return 0;
}