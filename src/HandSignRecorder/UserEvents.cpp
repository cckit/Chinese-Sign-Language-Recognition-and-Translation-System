#include "Common.h"
#include "KinectDevice.h"
#include <stdio.h>
using namespace xn;

UserGenerator g_user;
XnUserID g_userID = 1<<31;

static XnCallbackHandle hCallbacks;
static XnUInt16 width, height;
static FILE *output;

extern DepthGenerator g_depth;
extern Query mockDepthQuery;
extern KinectDevice g_motor;
extern RECORD_STATE recordState;
extern void setState(int index);
extern void notifyUserEnter();
extern void notifyUserExit();
extern void endRecord();


static void kickOutUser(XnUserID userID){
	printf("User %u Kicked out\n", userID);
	g_motor.ChangeLED(KinectDevice::LED_RED);
	endRecord();
	g_user.GetSkeletonCap().StopTracking(userID);
	setState(recordState = WAIT_TRACING);
	notifyUserExit();
}

// Rerturn true = change
bool isNewUserEnter(UserGenerator &generator, XnUserID newUserID){

	if(generator.GetNumberOfUsers()<=1){
		return g_userID != newUserID;
	}else if(g_userID != newUserID){
		static XnUInt32 targetDis, tempDis;
		static XnPoint3D temp;
		static XnUInt16 w = 400;

		assertOK("Get User CoM", g_user.GetCoM(g_userID, temp));
		targetDis = (temp.X-w)*(temp.X-w);
		assertOK("Get User CoM", g_user.GetCoM(newUserID, temp));
		tempDis = (temp.X-w)*(temp.X-w);

		return targetDis < tempDis;
	}

	return false;

	/*static XnUInt32 targetDis, tempDis;
	static XnPoint3D temp;
	static XnUserID targetID, userIDs[100];
	static XnUInt16 nUsers;
	static XnUInt16 w = 400, h = 300;

	assertOK("Get Users", g_user.GetUsers(userIDs, nUsers));

	if(nUsers <= 0){
		return false;
	}else{
		targetID = userIDs[0];
		g_user.GetCoM(userIDs[0], temp);
		targetDis = (temp.X-w)*(temp.X-w);
	}
	
	for(XnUInt16 i=1; i<nUsers; i++){
		g_user.GetCoM(userIDs[i], temp);
		tempDis = (temp.X-w)*(temp.X-w);
		if(tempDis < targetDis){
			targetID = userIDs[i];
			targetDis = tempDis;
		}
	}

	g_user.GetCoM(targetID, temp);
	fprintf(output, "Target ID: %d, Z: %f\n", targetID, temp.Z);
	fflush(output);
	if(temp.Z == 0){
		return false;
	}else if(targetID == g_userID){
		return false;
	}else{
		if(g_user.GetSkeletonCap().IsTracking(g_userID)){
			kickOutUser(g_userID);
		}
		g_userID = targetID;
		setState(USER_ENTER);
		g_user.GetSkeletonCap().RequestCalibration(targetID, TRUE);
		return true;
	}
	return false;*/
}

static void XN_CALLBACK_TYPE UserFind(UserGenerator &generator, XnUserID userID, void *pCookie){
	printf("User %u Find\n", userID);
	
	if(isNewUserEnter(generator, userID)){
		if(generator.GetSkeletonCap().IsTracking(g_userID)){
			kickOutUser(g_userID);
		}
		
		g_userID = userID;
		setState(USER_ENTER);
		generator.GetSkeletonCap().RequestCalibration(userID, TRUE);
	}

	/*if(generator.GetSkeletonCap().IsTracking(g_userID)){
		kickOutUser(g_userID);
	}
	
	g_userID = userID;
	setState(USER_ENTER);
	generator.GetSkeletonCap().RequestCalibration(userID, TRUE);*/
}

static void XN_CALLBACK_TYPE UserLost(UserGenerator &generator, XnUserID userID, void *pCookie){
	printf("User %u Lost\n", userID);

	if(g_userID == userID){
		kickOutUser(g_userID);
	}
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
	g_motor.ChangeLED(KinectDevice::LED_YELLOW);
	setState(CALIBRATION_START);
}

static void XN_CALLBACK_TYPE SkeletonCalibrationCompleted(SkeletonCapability &skeleton, XnUserID userID, XnCalibrationStatus calibrationError, void *pCookie){
	if(calibrationError == XN_CALIBRATION_STATUS_OK){
		printf("User %u Calibration Complete and Start Skeleton\n", userID);
		assertOK("Skeleton Trace", skeleton.StartTracking(userID));
		g_motor.ChangeLED(KinectDevice::LED_GREEN);
		notifyUserEnter();
	}else{
		skeleton.RequestCalibration(userID, TRUE);
	}
}

void setUserEvents(Context &context){
	assertOK("Create User", g_user.Create(context, &mockDepthQuery));
	assertOK("User Callbacks", g_user.RegisterUserCallbacks(UserFind, UserLost, NULL, hCallbacks));
	assertOK("User Exit", g_user.RegisterToUserExit(UserExit, NULL, hCallbacks));
	assertOK("User ReEnter", g_user.RegisterToUserReEnter(UserReEnter, NULL, hCallbacks));

	if(g_user.IsCapabilitySupported(XN_CAPABILITY_SKELETON)){
		g_user.GetSkeletonCap().SetSmoothing(SMOOTH_FACTOR);
		assertOK("Calibration Start", g_user.GetSkeletonCap().RegisterToCalibrationStart(SkeletonCalibrationStart, NULL, hCallbacks));
		assertOK("Calibration Completed", g_user.GetSkeletonCap().RegisterToCalibrationComplete(SkeletonCalibrationCompleted, NULL, hCallbacks));
		g_user.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_UPPER);
		g_user.GetSkeletonCap().SetJointActive(XN_SKEL_RIGHT_HIP, TRUE);
		g_user.GetSkeletonCap().SetJointActive(XN_SKEL_LEFT_HIP, TRUE);
	}

	g_motor.ChangeLED(KinectDevice::LED_RED);
	//g_userID = -2;
	//output = fopen("output.txt", "w");
}