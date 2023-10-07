#ifdef _WIN32
#include<windows.h>
#endif
#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#define GL_SILENCE_DEPRECATION

#define XMAX 1200
#define YMAX 700
#define SPACESHIP_SPEED 20
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3




bool keyStates[256] = {false};
bool direction[4] = {false};
bool laser1Dir[2] = {false};
bool laser2Dir[2] = {false};

int alienLife1 = 100;
int alienLife2 = 100;
bool gameOver = false;
float xOne = 500, yOne = 0;
float xTwo = 500, yTwo = 0;
bool laser1 = false, laser2 = false;


GLint m_viewport[4];
bool mButtonPressed = false;
float mouseX, mouseY;
enum view {INTRO, MENU, INSTRUCTIONS, GAME, GAMEOVER};
view viewPage = INTRO; // initial value
void displayRasterText(float x ,float y ,float z ,char *stringToDisplay) {
	glRasterPos3f(x, y, z);
	for(char* c = stringToDisplay; *c != '\0'; c++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , *c);
	}
}

void init()
{
	glClearColor(0.0,0.0,0.0,0);
	glColor3f(1.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    gluOrtho2D(-1200,1200,-700,700);
	glMatrixMode(GL_MODELVIEW);
}


void introScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1.0, 0.0, 0.0);
	displayRasterText(-425, 490, 0.0,"NMAM INSTITUTE OF TECHNOLOGY");
		glColor3f(1.0, 1.0, 1.0);
	displayRasterText(-700, 385, 0.0,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
		glColor3f(0.0, 0.0, 1.0);
	displayRasterText(-225, 300, 0.0,"A MINI PROJECT ON ");
		glColor3f(1.0, 0.0, 1.0);
	displayRasterText(-125, 225, 0.0,"Stack Simulation");
   		glColor3f(1.0, 0.7, 0.8);
	  displayRasterText(-800, -100, 0.0," STUDENT NAMES");
	  	glColor3f(1.0, 1.0, 1.0);
	displayRasterText(-800, -200, 0.0," Rajath ");
	displayRasterText(-800, -285, 0.0," Yashaswi ");
		glColor3f(1.0, 0.0, 0.0);
	displayRasterText(500, -100, 0.0,"Under the Guidance of");
		glColor3f(1.0, 1.0, 1.0);
	displayRasterText(500, -200, 0.0,"Puneeth");
		glColor3f(1.0, 0.0, 0.0);
	displayRasterText(-250, -400, 0.0,"Academic Year 2022-2023");
        glColor3f(1.0, 1.0, 1.0);
	displayRasterText(-300, -550, 0.0,"Press ENTER To Start ");
	glFlush();
 	glutSwapBuffers();

}




void passiveMotionFunc(int x,int y) {

	//when mouse not clicked
	mouseX = float(x)/(m_viewport[2]/1200.0)-600.0;  //converting screen resolution to ortho 2d spec
	mouseY = -(float(y)/(m_viewport[3]/700.0)-350.0);

	//Do calculations to find value of LaserAngle
	//somethingMovedRecalculateLaserAngle();
	glutPostRedisplay();
}

void mouseClick(int buttonPressed ,int state ,int x, int y) {

	if(buttonPressed == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		mButtonPressed = true;
	else
		mButtonPressed = false;
	glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y)
{
	keyStates[key] = true;
	glutPostRedisplay();
}

void refresh() {
	glutPostRedisplay();
}

void keyReleased(unsigned char key, int x, int y) {
	keyStates[key] = false;
}

void keyOperations() {
	if(keyStates[13] == true && viewPage == INTRO) {
		viewPage = MENU;
		printf("view value changed to %d", viewPage);
		printf("enter key pressed\n");
	}
	if(viewPage == GAME) {
		laser1Dir[0] = laser1Dir[1] = false;
		laser2Dir[0] = laser2Dir[1] = false;
		if(keyStates['c'] == true) {
			laser2 = true;
			if(keyStates['w'] == true) 	laser2Dir[0] = true;
			if(keyStates['s'] == true) 	laser2Dir[1] = true;
		}
		else {
			laser2 = false;
			if(keyStates['d'] == true) xTwo-=SPACESHIP_SPEED;
			if(keyStates['a'] == true) xTwo+=SPACESHIP_SPEED;
			if(keyStates['w'] == true) yTwo+=SPACESHIP_SPEED;
			if(keyStates['s'] == true) yTwo-=SPACESHIP_SPEED;
		}

		if(keyStates['m'] == true) {
			laser1 = true;
			if(keyStates['i'] == true) laser1Dir[0] = true;
			if(keyStates['k'] == true) laser1Dir[1] = true;
		}
		else {
			laser1 = false;
			if(keyStates['l'] == true) xOne+=SPACESHIP_SPEED;
			if(keyStates['j'] == true) xOne-=SPACESHIP_SPEED;
			if(keyStates['i'] == true) yOne+=SPACESHIP_SPEED;
			if(keyStates['k'] == true) yOne-=SPACESHIP_SPEED;
		}
	}
}



void startScreenDisplay()
{
system("F:\\cg\\project\\info\\bin\\Debug\\info.exe");
exit(0);
}




void display()
{
    keyOperations();
	glClear(GL_COLOR_BUFFER_BIT);

	switch (viewPage)
	{
		case INTRO:
			introScreen();

			break;

        case MENU:
			startScreenDisplay();
			break;
	}
	glFlush();
	glLoadIdentity();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1200, 600);
    glutCreateWindow("STACK");
    init();
	glutIdleFunc(refresh);
    glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyReleased);
	glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(passiveMotionFunc);
    glGetIntegerv(GL_VIEWPORT ,m_viewport);
    glutDisplayFunc(display);
    glutMainLoop();
}
