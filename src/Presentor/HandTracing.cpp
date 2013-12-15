#include <XnCppWrapper.h>
#include <XnVNite.h>
using namespace xn;

static Context context;
static DepthGenerator depth;
static HandsGenerator hand;
GestureGenerator g_gesture;
XnVSessionManager *sessionManager;

extern void configGesture(Context &context);
extern void configNITE(Context &context);

void assertOK(const XnChar* place, const XnStatus status){
	if(status != XN_STATUS_OK){
		printf("Failed while %s: %s\n", place, xnGetStatusString(status));
		exit(1);
	}else{
		//printf("Success for %s\n", place);
	}
}

static void configOpenNI(){
	xn::ScriptNode g_ScriptNode;
	xn::EnumerationErrors errors;

	assertOK("OpenNI Init", context.InitFromXmlFile("Config.xml", g_ScriptNode, &errors));
	assertOK("Find Depth", context.FindExistingNode(XN_NODE_TYPE_DEPTH, depth));
	assertOK("Find Hand", context.FindExistingNode(XN_NODE_TYPE_HANDS, hand));
	assertOK("Find Gesture", context.FindExistingNode(XN_NODE_TYPE_GESTURE, g_gesture));
}

int main(void){
	
	configOpenNI();
	configGesture(context);
	configNITE(context);

	g_gesture.StartGenerating();
	context.StartGeneratingAll();

	while(1){
		context.WaitOneUpdateAll(depth);
		sessionManager->Update(&context);
	}
}