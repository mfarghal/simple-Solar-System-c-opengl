#include <windows.h>
#include <gl/gl.h>
#include "glut.h"
#include <math.h>
#include <iostream>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

using namespace std;

void drawfunc(void);
void keyfunc(unsigned char, int, int);
void skeyfunc(int, int, int);
void myglinit(void);
void reshape (int , int );
void OnMouseFunc(int button, int state,int x, int y);

// width and height of the window/form
int width, height;
// aspect ratio which is equal to width/height
double aspectRatio;
// width and hight of Coordinates system used 
double cs = 4;


int main(int argc, char **argv) {

	// width and height of the window
	width =800; 
	height = 600;



	// initialize the glut system and create a window
	glutInitWindowSize(width, height);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("example");

	// initialize some OpenGL state
	myglinit();

	// set callback functions.  drawfunc is the function that gets
	// called automatically as fast as possible.  keyfunc only is
	// invoked if the user hits a keyboard key.

	glutDisplayFunc(drawfunc);
	glutKeyboardFunc(keyfunc);
	glutSpecialFunc(skeyfunc);
	glutReshapeFunc(reshape);
	glutMouseFunc(OnMouseFunc);
	// start the main glut loop, no code runs after this
	glutMainLoop();

}

// draw x/y Coordinates two line
// this function preserve model view transformation so that does not affect whatever drawn after it
void DrawXYFrame()
{

	glMatrixMode(GL_MODELVIEW); 
	glPushMatrix(); // save old matrix value
	glLoadIdentity(); // draw the line at the center of the screen
	glScalef(cs*aspectRatio,cs,1); // scale to match and cover all screen
	glLineWidth(2);
	glBegin(GL_LINES);

	glColor3f(1,1,1);
	glVertex2f(0,-1);

	glColor3f(1,1,1);
	glVertex2f(0,1);
	
	
	glColor3f(1,1,1);
	glVertex2f(-1,0);

	glColor3f(1,1,1);
	glVertex2f(1,0);
	glEnd();

	glPopMatrix(); // restore  previous matrix value 
}


// draw a single point on the screen
void DrawPoint()
{
	glPointSize(5);
	glBegin(GL_POINTS);

	glColor3f(1,0,0);
	glVertex2f(0,0);
	glEnd();
}

// draw a square with line loop
void DrawLSquare()
{
	glLineWidth(5);
	glBegin(GL_LINE_LOOP);

	glColor3f(1,1,0);
	glVertex2f(0,0);

	glColor3f(0,0,1);
	glVertex2f(1,0);


	glColor3f(0,1,0);
	glVertex2f(1,1);
	glColor3f(1,0,0);
	glVertex2f(0,1);
	
	glEnd();
	
}

// draw a shaded square using triangle strip 
// r,g,b are the color of the square
void DrawUSquare(float r , float g , float b)
{
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(r,g,b);
	glVertex2f(0,0);
	glVertex2f(1,0);
	glVertex2f(0,1);
	glVertex2f(1,1);
	glEnd();
	DrawLSquare();
}

// draw unit circle
void DrawCircle()
{
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	double ry =1, rx =1 ;
	
    for (int i=0; i <= 360; i+=5)
	{
		glColor3f((float)2*i/360,(float)i/360,.5);
		const float DEG2RAD = 3.14159/180;
		float  angle = (float)i*DEG2RAD;
		glVertex2f(cos(angle)*rx,sin(angle)*ry);
	}
	glEnd();
}

double Xpos  , Ypos;
double angel = 0;
// main draw function, gets called over and over, as fast as possible
void drawfunc(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);//using model view transformation 
	
	//glTranslatef(Xpos,Ypos,0);
	glLoadIdentity();//load identity matrix for transformation 
	glTranslatef(Xpos,Ypos,0);
	glRotatef(angel,0,0,1);
	glPushMatrix();

	
	glScalef(0.25,0.25,1);
	
	glutWireTorus(1,2,5,10);
	glPopMatrix();

	
	glTranslatef(2,2,0);
	glPushMatrix();
	glRotatef(angel,0,0,1);
	glScalef(0.25,0.25,1);
	glutWireTorus(1,1,40,10);
	glPopMatrix();
	glRotatef(angel,0,0,1);
	glTranslatef(.5,.5,0);
	glRotatef(angel,0,0,1);
	glScalef(0.1,0.1,1);
	glutWireTorus(1,1,40,10);

	angel+=0.25;
	DrawXYFrame();

	// in double buffer mode so we swap to avoid a flicker
	glutSwapBuffers();

	// instruct event system to call 'drawfunc' again
	glutPostRedisplay();
}


// normal keys event handler 
void keyfunc(unsigned char k, int x, int y) {


	switch (k) {
	case 27:
		// escape key
		exit(0);
		break;
	case 'w':
		angel+=2;
		break;
	case 's':
		angel-=2;
		break;
	}

}

void skeyfunc(int k, int x, int y) {


	switch (k) {
	case GLUT_KEY_UP:
		Ypos+=.25;
		break;
	case GLUT_KEY_DOWN:
		Ypos-=.25;
		break;
	case GLUT_KEY_LEFT:
		Xpos-=.25;
		break;
	case GLUT_KEY_RIGHT:
		Xpos+=.25;
		break;
	}

}
// mouse Events
void OnMouseFunc(int button, int state,int x, int y)
{
	// state value [ GLUT_UP or GLUT_DOWN ]
	float yy;
	double xx ;
	y = height-y;
	// coveert form coordinates into veiw coordinates
	xx = (2*cs*aspectRatio)* (x-width/2)/(double)width;
	yy = (2*cs)* (y-height/2)/(double)height;
	switch ( button ) {
	case GLUT_LEFT_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	case GLUT_MIDDLE_BUTTON:
		break;
	default:
		break;
	}
}

void reshape (int w, int h)
{
	//glutInitWindowSize (w, h);

	width = w ;
	height = h ;
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
    aspectRatio  = (double)width / (double)height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-cs*aspectRatio, cs*aspectRatio, -cs, cs, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// set some OpenGL state variables
void myglinit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,0);
}

