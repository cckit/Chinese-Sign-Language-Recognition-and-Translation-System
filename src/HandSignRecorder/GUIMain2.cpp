/*#include "Common.h"
#include "KinectDevice.h"
#include "SceneDrawer.h"
#include "glut.h"

#define GL_WIN_SIZE_X 720
#define GL_WIN_SIZE_Y 480

extern Context context;
extern DepthGenerator g_depth;
extern UserGenerator g_user;
extern KinectDevice g_motor;
extern bool isExit;
static XnUInt64 lastTimeStamp = 0;

extern bool updateDepthData(Context &context);
extern void updateRecord();

void CleanupExit()
{
	exit (1);
}

static void glutDisplay(){
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

	if(updateDepthData(context)){
		//updateRecord();
	}

	g_depth.GetMetaData(depthMD);
	g_user.GetUserPixels(0, sceneMD);

	DrawDepthMap(depthMD, sceneMD);
	glutSwapBuffers();

	/*if(updateDepthData(context)){
		//updateRecord();
	}

	if(lastTimeStamp != g_depth.GetTimestamp()){
		lastTimeStamp = g_depth.GetTimestamp();

		g_depth.GetMetaData(depthMD);
		g_user.GetUserPixels(0, sceneMD);

		DrawDepthMap(depthMD, sceneMD);

		glutSwapBuffers();
	}*/
/*}

static void glutIdle (void){
	// Display the frame
	glutPostRedisplay();
}

static void glutKeyboard (unsigned char key, int /*x*//*, int /*y*//*){
	switch(key){
	case 27:
		isExit = true;
		CleanupExit();
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
	}
}

static void glInit (int * pargc, char ** argv)
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

*/