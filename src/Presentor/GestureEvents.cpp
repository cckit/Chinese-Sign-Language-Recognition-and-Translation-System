#include <XnCppWrapper.h>
using namespace xn;

extern HandsGenerator hand;
extern GestureGenerator g_gesture;
extern void assertOK(const XnChar* place, const XnStatus status);

static void XN_CALLBACK_TYPE GestureRecognizedHandler(GestureGenerator &generator, const XnChar *strGesture, const XnPoint3D *pIDPosition, const XnPoint3D *pEndPosition, void *pCookie){ 
	printf("Gesture %s: Gesture Recognized (%f,%f,%f -> )\n", strGesture, pIDPosition->X, pIDPosition->Y, pIDPosition->Z, pEndPosition->X, pEndPosition->Y, pEndPosition->Z);
}


static void XN_CALLBACK_TYPE GestureIntermediateStageCompletedHandler(xn::GestureGenerator& generator, const XnChar* strGesture, const XnPoint3D* pPosition, void* pCookie){
	printf("Gesture %s: Intermediate stage complete (%f,%f,%f)\n", strGesture, pPosition->X, pPosition->Y, pPosition->Z);
}

static void XN_CALLBACK_TYPE GestureReadyForNextIntermediateStageHandler(xn::GestureGenerator& generator, const XnChar* strGesture, const XnPoint3D* pPosition, void* pCookie){
	printf("Gesture %s: Ready for next intermediate stage (%f,%f,%f)\n", strGesture, pPosition->X, pPosition->Y, pPosition->Z);
}

static void XN_CALLBACK_TYPE GestureProgressHandler(xn::GestureGenerator& generator, const XnChar* strGesture, const XnPoint3D* pPosition, XnFloat fProgress, void* pCookie){
	printf("Gesture %s progress: %f (%f,%f,%f)\n", strGesture, fProgress, pPosition->X, pPosition->Y, pPosition->Z);
}

void configGesture(Context &context){
	XnCallbackHandle hGestureIntermediateStageCompleted, hGestureProgress, hGestureReadyForNextIntermediateStage;

	g_gesture.RegisterToGestureIntermediateStageCompleted(GestureIntermediateStageCompletedHandler, NULL, hGestureIntermediateStageCompleted);
	g_gesture.RegisterToGestureReadyForNextIntermediateStage(GestureReadyForNextIntermediateStageHandler, NULL, hGestureReadyForNextIntermediateStage);
	g_gesture.RegisterGestureCallbacks(GestureRecognizedHandler, GestureProgressHandler, NULL, hGestureProgress);

}