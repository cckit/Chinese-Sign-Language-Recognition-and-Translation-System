#include <GL\glut.h>
#include <cstring>

static int selectedIndex = 0;

extern void drawString(char *text, float x, float y, bool selected);

namespace WelcomePanel{
	void updateUI(){
		drawString("Welcome Page", 20, 400, false);
	}
}
