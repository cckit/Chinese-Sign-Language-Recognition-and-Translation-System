#include <XnCppWrapper.h>
#include <XnVNite.h>
using namespace xn;

#define FOCUS_GESTURE "Click"

extern XnVSessionManager *sessionManager;
extern GestureGenerator g_gesture;
extern void performMouseClick(bool isLeft);
static XnVSwipeDetector *swipeDetector;

static bool isInSession = false;

// Callback for when the focus is in progress
void XN_CALLBACK_TYPE FocusProgress(const XnChar* strFocus, const XnPoint3D& ptPosition, XnFloat fProgress, void* UserCxt)
{
	//printf("Focus progress: %s @(%f,%f,%f): %f\n", strFocus, ptPosition.X, ptPosition.Y, ptPosition.Z, fProgress);
	
	if(!isInSession){
		sessionManager->ForceSession(ptPosition);
	}else{
		printf("Multi Session\n");
	}	
}
// callback for session start
void XN_CALLBACK_TYPE SessionStarting(const XnPoint3D& ptPosition, void* UserCxt)
{
	isInSession = true;
	printf("Session start: (%f,%f,%f)\n", ptPosition.X, ptPosition.Y, ptPosition.Z);
	g_gesture.RemoveGesture(FOCUS_GESTURE);
}
// Callback for session end
void XN_CALLBACK_TYPE SessionEnding(void* UserCxt)
{
	isInSession = false;
	printf("Session end\n");
	g_gesture.AddGesture(FOCUS_GESTURE, nullptr);
}

void XN_CALLBACK_TYPE OnSwipeLeft(XnFloat fVelocity, XnFloat fAngle, void* pUserCxt){
	printf("Swipe Left!\n");
	performMouseClick(true);
	sessionManager->EndSession();
}

void XN_CALLBACK_TYPE OnSwipeRight(XnFloat fVelocity, XnFloat fAngle, void* pUserCxt){
	printf("Swipe Right!\n");
	performMouseClick(false);
	sessionManager->EndSession();
}

void configSwipeDetector(){
	swipeDetector = new XnVSwipeDetector();

	swipeDetector->RegisterSwipeLeft(nullptr, OnSwipeLeft);
	swipeDetector->RegisterSwipeRight(nullptr, OnSwipeRight);

	swipeDetector->SetUseSteady(false);
	//swipeDetector->SetSteadyDuration(500);
	//swipeDetector->SetSteadyMaxStdDev(0);
	//swipeDetector->SetSteadyMaxVelocity(0);

	swipeDetector->SetMotionSpeedThreshold(0.15);
	swipeDetector->SetMotionTime(100);
	//swipeDetector->SetXAngleThreshold(45);

	sessionManager->AddListener(swipeDetector);
}

void configNITE(Context &context){
	sessionManager = new XnVSessionManager();
	
	sessionManager->Initialize(&context, FOCUS_GESTURE, FOCUS_GESTURE);
	sessionManager->SetQuickRefocusTimeout(0);
	sessionManager->RegisterSession(NULL, SessionStarting, SessionEnding, FocusProgress);
	configSwipeDetector();

	XnVWaveDetector wave;
}