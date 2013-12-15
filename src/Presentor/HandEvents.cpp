#include <XnCppWrapper.h>
using namespace xn;

HandsGenerator g_hand;

extern void assertOK(const XnChar* place, const XnStatus status);
/*
extern UserGenerator g_user;
extern XnUserID g_userID;




void notifyNewUser(XnUserID newUserID){
	XnSkeletonJointPosition posLeft, posRight;

	assertOK("Stop Hand Tracing", g_hand.StopTrackingAll());

	g_user.GetSkeletonCap().GetSkeletonJointPosition(newUserID, XN_SKEL_LEFT_HAND, posLeft);
	g_user.GetSkeletonCap().GetSkeletonJointPosition(newUserID, XN_SKEL_RIGHT_HAND, posRight);

	assertOK("Start Left Hand Tracing", g_hand.StartTracking(posLeft.position));
	assertOK("Start Right Hand Tracing", g_hand.StartTracking(posRight.position));
}
*/
void setHandEvents(Context &context){
	assertOK("Create Hand", g_hand.Create(context));
	//g_hand.RegisterHandCallbacks();
}