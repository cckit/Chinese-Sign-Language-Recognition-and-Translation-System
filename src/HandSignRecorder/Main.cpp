#include "Main.h"
#include "Common.h"
#include "KinectDevice.h"
#include <cstdio>
#include <process.h>
using namespace xn;

#define DEFAULT_MOTOR_HEIGHT 23

Context context;
KinectDevice g_motor;
bool isExit = false;
bool isKinectError = false;
static FILE *record;

extern DepthGenerator g_depth;
extern MockDepthGenerator g_mockDepth;
extern UserGenerator g_user;
extern void setDepthEvents(Context &context);
extern void setUserEvents(Context &context);
extern bool updateDepthData(Context &context);
extern void updateRecognizeRecord();
extern void updateGUI();
extern void svmInit();
extern void sentenceInit();
extern void glutMain(int argc, char **argv);
extern void svmFree();
extern void updateRecord();

//extern void startGUI();

void assertOK(const XnChar* place, const XnStatus status){
	if(status != XN_STATUS_OK){
		printf("Failed while %s: %s\n", place, xnGetStatusString(status));
		isKinectError = true;
		//_endthreadex(0);
		exit(0);
	}else{
		//printf("Success for %s\n", place);
	}
}

static void startDeviceMotor(){    
	//FILE *setting  = fopen("setting.txt", "r");
	//int motorHeight = 0;

	if(g_motor.Open()){
		printf("Open Motor\n");

		//if(fscanf(setting, "%d", &motorHeight) > 0){
		//	g_motor.Move(motorHeight);
		//}else{
			g_motor.Move(DEFAULT_MOTOR_HEIGHT);
		//}
		
		g_motor.ChangeLED(KinectDevice::LED_RED);
	}else{
		printf("Failed to Open Motor\n");
	}

	//fclose(setting);
}

static void configGenerator(){
	assertOK("Context Init", context.Init());

	setDepthEvents(context);
	setUserEvents(context);

	assertOK("Start Generating All", context.StartGeneratingAll());
}

static void cleanUp(){
	g_motor.ChangeLED(KinectDevice::LED_RED);

	svmFree();	
	g_motor.Close();
	context.StopGeneratingAll();
	g_depth.Release();
	g_mockDepth.Release();
	g_user.Release();
	context.Release();

	printf("Program end without errors\n");
	fflush(stdout);
	fclose(record);
}

static unsigned int __stdcall mainLoop(void *dummy){
	record = freopen("Record.txt", "w", stdout);

	startDeviceMotor();
	svmInit();
	configGenerator();

	while(!isExit){
		if(updateDepthData(context)){
			updateRecord();
		}
	}

	cleanUp();

	return 0;
}

void startKinect(){
//int main(int argv, char *args[]){
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, mainLoop, NULL, 0, NULL);
	//WaitForSingleObject( hThread, INFINITE );
	//CloseHandle(hThread);
}

