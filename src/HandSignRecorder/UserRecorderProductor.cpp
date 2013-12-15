#include "Common.h"
#include "KinectDevice.h"
#include <cstdio>
#include <vector>
#include <process.h>
using namespace xn;
using namespace std;

#define MAX_STOP_FRAME 45
#define CONTINUE_MOVING_LIMIT 2
#define STEAD_DISTANCE_LIMIT 50.0

#define dotProduct(a, b, o) ((a.X-o.X)*(b.X-o.X) + (a.Y-o.Y)*(b.Y-o.Y) + (a.Z-o.Z)*(b.Z-o.Z))
#define magnitudeSq(a, o) dotProduct(a, a, o)

#define IS_BETWEEN(dest, smallerLimit, largerLimit, dim) ((dest.position.dim >= smallerLimit.position.dim)&&(dest.position.dim <= largerLimit.position.dim))
#define IS_RECORDING (recordedData.size()>0)
#define IS_HAND_MOVING(handI, handJ) magnitudeSq(handI, handJ)>(STEAD_DISTANCE_LIMIT*STEAD_DISTANCE_LIMIT)

extern UserGenerator g_user;
extern XnUserID g_userID;
extern KinectDevice g_motor;
extern void actionEndClearUp();
//extern void setState(int index);
extern void signStarted();

extern void notifyStateChanged(RECORD_STATE state);
extern void notifySentenceCompleted();

vector<SkeletonRawData> rawDatas;

RECORD_STATE recordState = WAIT_TRACING;
static XnUInt64 actionStartTime;
static XnSkeletonJointPosition leftHandPosition, rightHandPosition;


static inline void updateHandPosition(){
	g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_LEFT_HAND, leftHandPosition);
	g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_RIGHT_HAND, rightHandPosition);
}

// Detect if hand is moved
static bool isMoving(){
	if(rawDatas.size() >= CONTINUE_MOVING_LIMIT){
		int startData = rawDatas.size()-CONTINUE_MOVING_LIMIT;
		int endData = rawDatas.size()-1;

		// Search several data to confirm if any hand is moved with certain distance
		for(int i=startData; i<=endData; i++){
			for(int j=i+1; j<=endData; j++){
				if(IS_HAND_MOVING(rawDatas[i].leftHand, rawDatas[j].leftHand)
					|| IS_HAND_MOVING(rawDatas[i].rightHand, rawDatas[j].rightHand)){
						return TRUE;
				}
			}
		}
	}else{
		return recordState == TAKING_RECORD;
	}
	return FALSE;
}

// Detect if hands are forming "Ready Pose"
static bool isReadyPose(){
	XnSkeletonJointPosition torso, leftHip, rightHip;

	g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_TORSO, torso);
	g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_LEFT_HIP, leftHip);
	g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_RIGHT_HIP, rightHip);

	// Return if hands are within hips ad torso
	return IS_BETWEEN(leftHandPosition, leftHip, torso, Y) && IS_BETWEEN(rightHandPosition, rightHip, torso, Y)
		&& IS_BETWEEN(leftHandPosition, leftHip, rightHip, X) && IS_BETWEEN(rightHandPosition, leftHip, rightHip, X);
}

// Record one frame from data
static void takeFrame(){
	SkeletonRawData rawData;
	XnSkeletonJointPosition pos_left_elbow, pos_right_elbow, pos_left_shoulder, pos_right_shoulder;

	// Capture Data
	xnOSMemCopy(&(rawData.leftHand), &(leftHandPosition.position), sizeof(XnPoint3D));
	xnOSMemCopy(&(rawData.rightHand), &(rightHandPosition.position), sizeof(XnPoint3D));

	g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_LEFT_ELBOW, pos_left_elbow);
	xnOSMemCopy(&(rawData.leftElbow), &(pos_left_elbow.position), sizeof(XnPoint3D));
	g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_RIGHT_ELBOW, pos_right_elbow);
	xnOSMemCopy(&(rawData.rightElbow), &(pos_right_elbow.position), sizeof(XnPoint3D));

	g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_LEFT_SHOULDER, pos_left_shoulder);
	xnOSMemCopy(&(rawData.leftShoulder), &(pos_left_shoulder.position), sizeof(XnPoint3D));
	g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_RIGHT_SHOULDER, pos_right_shoulder);
	xnOSMemCopy(&(rawData.rightShoulder), &(pos_right_shoulder.position), sizeof(XnPoint3D));

	rawDatas.push_back(rawData);
}

static inline void startRecord(){
	actionStartTime = g_user.GetTimestamp();
	rawDatas.clear();
	takeFrame();
}

void endRecord(){
	rawDatas.clear();
	notifyStateChanged(recordState = WAIT_READY);
}

void updateRecognizeRecord(){
	//printf("2. Start Update Skeleton Thread\n");
	fflush(stdout);

	printf("State: %d, DataSize: %d\n", recordState, rawDatas.size());
	switch(recordState){
	case WAIT_TRACING:
		{
			if(g_user.GetSkeletonCap().IsTracking(g_userID)){
				notifyStateChanged(recordState = WAIT_READY);
				//printf("Current State : WAIT READY <- WAIT TRACING\n");
			}

			break;
		}
	case WAIT_READY:
		{
			g_motor.ChangeLED(KinectDevice::LED_BLINK_YELLOW);
			updateHandPosition();

			if(isReadyPose()){
				recordState = WAIT_MOVING;
				//printf("Current State : WAIT MOVING <- WAIT READY\n");
			}

			break;
		}
	case WAIT_MOVING:
		{
			static int stopFrame = 0;
			g_motor.ChangeLED(KinectDevice::LED_BLINK_RED_YELLOW);
			updateHandPosition();

			if(isMoving()){
				stopFrame = 0;
				notifyStateChanged(recordState = TAKING_RECORD);
				startRecord();

				printf("Current State : TAKING RECORD <- WAIT MOVING\n");				
			}else{
				stopFrame++;
				if(stopFrame > MAX_STOP_FRAME){
					stopFrame = 0;
					endRecord();
					notifySentenceCompleted();
				}else{
					takeFrame();
				}
			}
			break;
		}
	case TAKING_RECORD:
		{
			g_motor.ChangeLED(KinectDevice::LED_BLINK_GREEN);
			actionStartTime = 0;
			updateHandPosition();

			if(isReadyPose()){
				if(!isMoving()){
					//notifyStateChanged(recordState = WAIT_READY);
					recordState = WAIT_READY;

					printf("Frame Recorded: %u, Time used: %llu\n", rawDatas.size(), g_user.GetTimestamp()-actionStartTime);
					actionEndClearUp();
					actionStartTime = 0;
					printf("Current State : WAIT READY <- TAKING RECORD\n");					
				}else{
					takeFrame();

					printf("READY AND MOVING\n");
				}
			}else{
				takeFrame();

				if(!isMoving()){
					printf("NOT READY AND NOT MOVING\n");
				}		
			}
			break;
		}
	}

	//printf("2. End Update Skeleton Thread, User Frame: %llu\n", g_user.GetTimestamp());
	fflush(stdout);
}