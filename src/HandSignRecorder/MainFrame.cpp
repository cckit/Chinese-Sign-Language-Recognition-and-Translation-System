#include "CommonGUI.h"
#include <GL\glut.h>
#include <vector>
#include <iostream>
#include <windows.h>
#include "lodepng.h"
using namespace std;

bool isValidate = false;
extern GUI_PAGE guiPage;
static vector<unsigned char> backImage;

static int welcomeScreenIndex, menuScreenIndex;
static unsigned windowWidth = 800, windowHeight = 1024; 
static unsigned width = 1024, height = 1024;

extern void loadImage(vector <unsigned char> &dest, unsigned width, unsigned height, string fileName);

void keyPressed(unsigned char c, int x, int y);
void timer(int p);
void updateUI();
void idleUI();
void displayAs2D();

void initUI(int &argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);

	welcomeScreenIndex = glutCreateWindow("Chinese Sign Language Translator");

	//glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);
	//glClearColor(1.0, 0.0, 1.0, 1.0);

	glDisable(GL_DEPTH_TEST);
	displayAs2D();

	glutKeyboardFunc(keyPressed);
	glutDisplayFunc(updateUI);
	//glutIdleFunc(idleUI);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void keyPressed(unsigned char c, int x, int y){
	switch(c){
	case 27:
		glutDestroyWindow(1);
		exit(0);
		break;
	case 'e':
		guiPage = MAIN_MENU_PAGE;
		break;
	case 'x':
		guiPage = WELCOME_PAGE;
		break;
	}

	glutPostRedisplay();
}

void drawString(char *text, float x, float y, bool selected){
	int len = strlen(text);

	if(selected)
		glColor3d(128, 128, 0);
	else
		glColor3d(255, 255, 255);

	if(x>=0 && y>=0)
		glRasterPos2f(x, y);


	for(int i=0; i<len; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}
}

void drawImage(unsigned char *source, float x, float y, unsigned width, unsigned height){
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, source);
	glEnable(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBegin(GL_QUADS); 
	glTexCoord2f(0.0f, 0.0f); glVertex2d(x, y);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(x, y+height);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(x+width, y+height);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(x+width, y);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void displayAs2D(){
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	glOrtho (0, windowWidth, windowHeight, 0, 0, 1);
	glMatrixMode (GL_MODELVIEW);
}
/*
void idleUI(){
	static int frame = 0;
	static int lastUpdate = 0;
	static char buf[20];

	glutPostRedisplay();

	static int currentTime = glutGet(GLUT_ELAPSED_TIME);
	frame++;

	if((currentTime + lastUpdate ) >= 1000){
		printf("FPS: %d", frame);
		
		frame = 0;
		lastUpdate = currentTime;
	}

	Sleep(1);
}
*/
void updateUI(){
	static int x = 0;
	static int y = 0;

	//if(!isValidate){
	glClear(GL_COLOR_BUFFER_BIT);

	//displayAs2D();

	drawImage(&backImage[0], 0, 0, width, height);
	if(guiPage == WELCOME_PAGE){
		WelcomePanel::updateUI();
	}else if(guiPage == MAIN_MENU_PAGE){
		MainMenuPanel::updateUI();
	}else{
		
	}

	/*glBegin(GL_TRIANGLES);
		glVertex2f(0, 0); glVertex2f(windowWidth, windowHeight);
		glVertex2f(0, windowHeight);
	glEnd();*/

	glutSwapBuffers();
	isValidate = true;
	//}
}

/*int main(int argc, char** argv){
	loadImage(backImage, width, height, "images/left2.png");

	initUI(argc, argv);
	//menuScreenIndex = glutCreateSubWindow(welcomeScreenIndex, 0, 0, 400, 300);
	glutMainLoop();
	
	return 0;
}*/