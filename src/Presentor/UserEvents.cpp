#include <XnCppWrapper.h>
using namespace xn;

UserGenerator g_user;
XnUserID g_userID;
static XnCallbackHandle hCallbacks;
extern void assertOK(const XnChar* place, const XnStatus status);

static void kickOutUser(XnUserID userID){
	printf("User %u Kicked out\n", userID);
	g_user.GetSkeletonCap().StopTracking(userID);
}

static void XN_CALLBACK_TYPE UserFind(UserGenerator &generator, XnUserID userID, void *pCookie){
	printf("User %u Find\n", userID);

	if(generator.GetSkeletonCap().IsTracking(g_userID)){
		kickOutUser(g_userID);
	}

	g_userID = userID;
	generator.GetSkeletonCap().RequestCalibration(userID, TRUE);
}

static void XN_CALLBACK_TYPE UserLost(UserGenerator &generator, XnUserID userID, void *pCookie){
	printf("User %u Lost\n", userID);
}

static void XN_CALLBACK_TYPE UserReEnter(UserGenerator &generator, XnUserID userID, void *pCookie){
	printf("User %u Re-enter\n", userID);
	
	if(g_userID != userID){
		kickOutUser(g_userID);
	}
	generator.GetSkeletonCap().RequestCalibration(userID, TRUE);
}

static void XN_CALLBACK_TYPE UserExit(UserGenerator &generator, XnUserID userID, void *pCookie){
	printf("User %u Exit\n", userID);
	
	if(g_userID == userID){
		kickOutUser(userID);
	}
}

static void XN_CALLBACK_TYPE SkeletonCalibrationStart(SkeletonCapability &skeleton, XnUserID userID, void *pCookie){
	printf("User %u Calibration Start\n", userID);
}

static void XN_CALLBACK_TYPE SkeletonCalibrationCompleted(SkeletonCapability &skeleton, XnUserID userID, XnCalibrationStatus calibrationError, void *pCookie){
	if(calibrationError == XN_CALIBRATION_STATUS_OK){
		printf("User %u Calibration Complete and Start Skeleton\n", userID);
		assertOK("Skeleton Trace", skeleton.StartTracking(userID));
	}else{
		skeleton.RequestCalibration(userID, TRUE);
	}
}

void setUserEvents(Context &context){
	assertOK("Create User", g_user.Create(context));
	assertOK("User Callbacks", g_user.RegisterUserCallbacks(UserFind, UserLost, NULL, hCallbacks));
	assertOK("User Exit", g_user.RegisterToUserExit(UserExit, NULL, hCallbacks));
	assertOK("User ReEnter", g_user.RegisterToUserReEnter(UserReEnter, NULL, hCallbacks));

	if(g_user.IsCapabilitySupported(XN_CAPABILITY_SKELETON)){
		g_user.GetSkeletonCap().SetSmoothing(0.1F);
		assertOK("Calibration Start", g_user.GetSkeletonCap().RegisterToCalibrationStart(SkeletonCalibrationStart, NULL, hCallbacks));
		assertOK("Calibration Completed", g_user.GetSkeletonCap().RegisterToCalibrationComplete(SkeletonCalibrationCompleted, NULL, hCallbacks));
		g_user.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_UPPER);
		g_user.GetSkeletonCap().SetJointActive(XN_SKEL_RIGHT_HIP, TRUE);
		g_user.GetSkeletonCap().SetJointActive(XN_SKEL_LEFT_HIP, TRUE);
	}
}

