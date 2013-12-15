#include <GL\glut.h>
#include <cstring>

static int selectedIndex = 0;

extern void drawString(char *text, float x, float y, bool selected);

namespace MainMenuPanel{
	void updateUI(){
		drawString("MainMenu Page", 20, 400, false);
		drawString("Vocab Button", 20, 40, selectedIndex==0);
		drawString("WordList Button", 20, 80, selectedIndex==1);
		drawString("Game Button", 20, 120, selectedIndex==2);
		drawString("Exit Button", 20, 160, selectedIndex==3);
	}
}
