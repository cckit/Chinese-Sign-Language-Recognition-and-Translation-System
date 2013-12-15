#include <XnCppWrapper.h>
#include <XnVNite.h>

using namespace xn;

static Context context;
static GestureGenerator gesture;
static XnVSessionManager *sessionManager;
static XnVSwipeDetector *swipeDetector;


#pragma region GestureCallbacks
void XN_CALLBACK_TYPE GestureIntermediateStageCompletedHandler(xn::GestureGenerator& generator, const XnChar* strGesture, const XnPoint3D* pPosition, void* pCookie){
	printf("Gesture %s: Intermediate stage complete (%f,%f,%f)\n", strGesture, pPosition->X, pPosition->Y, pPosition->Z);
}
void XN_CALLBACK_TYPE GestureReadyForNextIntermediateStageHandler(xn::GestureGenerator& generator, const XnChar* strGesture, const XnPoint3D* pPosition, void* pCookie){
	printf("Gesture %s: Ready for next intermediate stage (%f,%f,%f)\n", strGesture, pPosition->X, pPosition->Y, pPosition->Z);
}
void XN_CALLBACK_TYPE GestureProgressHandler(xn::GestureGenerator& generator, const XnChar* strGesture, const XnPoint3D* pPosition, XnFloat fProgress, void* pCookie){
	printf("Gesture %s progress: %f (%f,%f,%f)\n", strGesture, fProgress, pPosition->X, pPosition->Y, pPosition->Z);
}

static void configGestureCallbacks(){

	XnCallbackHandle hGestureIntermediateStageCompleted, hGestureProgress, hGestureReadyForNextIntermediateStage;
	gesture.RegisterToGestureIntermediateStageCompleted(GestureIntermediateStageCompletedHandler, NULL, hGestureIntermediateStageCompleted);
	gesture.RegisterToGestureReadyForNextIntermediateStage(GestureReadyForNextIntermediateStageHandler, NULL, hGestureReadyForNextIntermediateStage);
	gesture.RegisterGestureCallbacks(NULL, GestureProgressHandler, NULL, hGestureProgress);

}
#pragma endregion

#pragma region SwipeCallbacks
void XN_CALLBACK_TYPE OnSwipeLeft(XnFloat fVelocity, XnFloat fAngle, void* pUserCxt){
	printf("Swipe Left!\n");
}

void XN_CALLBACK_TYPE OnSwipeRight(XnFloat fVelocity, XnFloat fAngle, void* pUserCxt){
	printf("Swipe Right!\n");
}
#pragma endregion

static void configOpenNI(){
	DepthGenerator depth;
	HandsGenerator hand;

	context.InitFromXmlFile("Sample-Tracking.xml");
	context.FindExistingNode(XN_NODE_TYPE_GESTURE, gesture);
}

static void configNITE(){
	sessionManager = new XnVSessionManager();
	sessionManager->Initialize(&context, "Wave", "RaiseHand");

	swipeDetector->RegisterSwipeLeft(nullptr, OnSwipeLeft);
	swipeDetector->RegisterSwipeRight(nullptr, OnSwipeRight);
	sessionManager->AddListener(swipeDetector);
}

int main(void){
	configOpenNI();
	configGestureCallbacks();
	configNITE();

	context.StartGeneratingAll();
	while(1){
		context.WaitAnyUpdateAll();
		((XnVSessionManager*)sessionManager)->Update(&context);
	}

	return 0;
}