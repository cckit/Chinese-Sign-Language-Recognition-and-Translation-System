#include "Common.h"
#include "KinectDevice.h"
#include "SceneDrawer.h"
#include <iostream>

extern void updateRecord();
extern void updateSkeleton(DepthGenerator &depth);
extern Context context;

extern KinectDevice g_motor;
extern DepthGenerator g_depth;
extern UserGenerator g_user;

void updateAllData(){
	context.WaitOneUpdateAll(g_depth);
	//updateRecord();
	//updateSkeleton(g_depth);
}

#ifndef SHOW_GUI

extern XnBool g_bNeedPose;
extern XnChar g_strPose[20];
extern XnBool g_bDrawBackground;
extern XnBool g_bDrawPixels;
extern XnBool g_bDrawSkeleton;
extern XnBool g_bPrintID;
extern XnBool g_bPrintState;

extern XnBool g_bPrintFrameID;
extern XnBool g_bMarkJoints;

#ifndef USE_GLES
#if (XN_PLATFORM == XN_PLATFORM_MACOSX)
#include <GLUT/glut.h>
#else
#include "glut.h"
#endif
#else
#include "opengles.h"
#endif

#define GL_WIN_SIZE_X 720
#define GL_WIN_SIZE_Y 480

XnBool g_bPause = false;
XnBool g_bRecord = false;

XnBool g_bQuit = false;



//---------------------------------------------------------------------------
// Code
//---------------------------------------------------------------------------

void CleanupExit()
{
	//scriptNode.Release();
	g_depth.Release();
	g_user.Release();
	context.Release();

	exit (1);
}

// this function is called each frame
void glutDisplay (void)
{

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Setup the OpenGL viewpoint
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	xn::SceneMetaData sceneMD;
	xn::DepthMetaData depthMD;
	g_depth.GetMetaData(depthMD);

	glOrtho(0, depthMD.XRes(), depthMD.YRes(), 0, -1.0, 1.0);
	glDisable(GL_TEXTURE_2D);

	if (!g_bPause)
	{
		// Read next available data
		updateAllData();
	}

#ifdef SLOW_UPDATE_GUI
	if(g_user.GetFrameID()%FRAME_PER_READ){
		return;
	}
#endif

	// Process the data
	g_depth.GetMetaData(depthMD);
	g_user.GetUserPixels(0, sceneMD);

	DrawDepthMap(depthMD, sceneMD);

	glutSwapBuffers();

}

void glutIdle (void)
{
	if (g_bQuit) {
		CleanupExit();
	}

	// Display the frame
	glutPostRedisplay();
}

void glutKeyboard (unsigned char key, int /*x*/, int /*y*/)
{
	switch (key)
	{
	case 27:
		CleanupExit();
	case 'b':
		// Draw background?
		g_bDrawBackground = !g_bDrawBackground;
		break;
	case 'x':
		// Draw pixels at all?
		g_bDrawPixels = !g_bDrawPixels;
		break;
	case 's':
		// Draw Skeleton?
		g_bDrawSkeleton = !g_bDrawSkeleton;
		break;
	case 'i':
		// Print label?
		g_bPrintID = !g_bPrintID;
		break;
	case 'l':
		// Print ID & state as label, or only ID?
		g_bPrintState = !g_bPrintState;
		break;
	case 'f':
		// Print FrameID
		g_bPrintFrameID = !g_bPrintFrameID;
		break;
	case 'j':
		// Mark joints
		g_bMarkJoints = !g_bMarkJoints;
		break;
	case 'p':
		g_bPause = !g_bPause;
		break;
	case 'u':
		if(g_motor.Move(g_motor.GetAngle()+1)){
			printf("Move up to degree %d\n", g_motor.GetAngle()/2);
		}else{
			printf("Fail to Move up!\n");
		}
		break;
	case 'd':
		if(g_motor.Move(g_motor.GetAngle()-1)){
			printf("Move down to degree %d\n", g_motor.GetAngle()/2);
		}else{
			printf("Fail to Move down!\n");
		}
		break;
	case 'z':
		g_motor.ChangeLED((KinectDevice::LED_OPTION)((g_motor.GetLEDColor()+1)%7));
		break;
	}
}
void glInit (int * pargc, char ** argv)
{
	glutInit(pargc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(GL_WIN_SIZE_X, GL_WIN_SIZE_Y);
	glutCreateWindow ("User Tracker Viewer");
	//glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);

	glutKeyboardFunc(glutKeyboard);
	glutDisplayFunc(glutDisplay);
	glutIdleFunc(glutIdle);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void glutMain(int argc, char **argv){
	glInit(&argc, argv);
	glutMainLoop();
}

#else

void cmdMain(){
	while(1){
		updateAllData();
	}
}

#endif


static void setDepthEvents(){
	assertOK("Find Depth", context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_depth));
}