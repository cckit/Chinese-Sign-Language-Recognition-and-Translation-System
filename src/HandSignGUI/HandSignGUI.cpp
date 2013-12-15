// HandSignGUI.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"
#include "Main.h"
#include <XnCppWrapper.h>

using namespace HandSignGUI;

/*bool isDataUpdated = false;
bool isSkeletonTracing = false;
float rightHandPositionRatio = 0.0;
bool isClicked = false;
int recognizedSign = -1;
bool isSwipeLeft = false;
bool isSwipeRight = false;*/

extern bool isKinectError;
extern void sentenceInit();

void setState(int index){

}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	sentenceInit();
#ifndef NO_KINECT
	startKinect();
#endif

	if(isKinectError){
		//WelcomePanel::instance->SetStyle()
	}

	Application::Run(gcnew Form1());

	return 0;
}
