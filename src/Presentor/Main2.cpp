/*#include <stdlib.h>
#include <string.h>
#include <iostream>

#include <XnCppWrapper.h>
#include <XnVSwipeDetector.h>
#include <XnVSessionManager.h>

using namespace xn;
using namespace std;

void XN_CALLBACK_TYPE OnSwipeLeft(XnFloat fVelocity, XnFloat fAngle, void* pUserCxt){
	printf("Swipe Left!\n");
}

void XN_CALLBACK_TYPE OnSwipeRight(XnFloat fVelocity, XnFloat fAngle, void* pUserCxt){
	printf("Swipe Right!\n");
}

void configOpenNI(){
	
}

void configNITE(){

}

int main(int argc, char **argv){
	Context context;
	ScriptNode scriptNode;
	XnVSessionGenerator *pSessionGenerator;

	context.InitFromXmlFile("Sample-Tracking.xml");
	pSessionGenerator = new XnVSessionManager();
	((XnVSessionManager*)pSessionGenerator)->Initialize(&context, "Wave", "RaiseHand");
	context.StartGeneratingAll();

	XnVSwipeDetector *swipeDetector = new XnVSwipeDetector();
	
	swipeDetector->RegisterSwipeLeft(nullptr, OnSwipeLeft);
	swipeDetector->RegisterSwipeRight(nullptr, OnSwipeRight);
	pSessionGenerator->AddListener(swipeDetector);

	while(1){
		context.WaitAnyUpdateAll();
		((XnVSessionManager*)pSessionGenerator)->Update(&context);
	}

	return 0;
}*/