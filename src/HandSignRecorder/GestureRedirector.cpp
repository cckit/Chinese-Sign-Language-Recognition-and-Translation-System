#include "Common.h"
#include "CommonGUI.h"
using namespace xn;

extern CONTROL_MODE controlMode;
extern UserGenerator g_user;
extern XnUserID g_userID;
extern RECORD_STATE recordState;

extern void endRecord();
extern void updateNI(int changedIndex, bool isClicked);
extern void updateRecognizeRecord();
extern bool isNewUserEnter();

extern void notifyHandReleased();
extern void notifyUserEnter();
extern void notifySwipeLeft(unsigned long long timestamp);
extern void notifySwipeRight(unsigned long long timestamp);

#define HAND_RELEASE_THRESHOLD 100
#define MOVE_INDEX_DIST 500

static void checkIfHandReleased(){
	static int time = 0;
	XnSkeletonJointPosition posLeftHand, posRightHand, posHip;

	g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_LEFT_HAND, posLeftHand);
	g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_RIGHT_HAND, posRightHand);
	g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_RIGHT_HIP, posHip);

	if(posLeftHand.position.Y+HAND_RELEASE_THRESHOLD < posHip.position.Y
		&& posRightHand.position.Y+HAND_RELEASE_THRESHOLD < posHip.position.Y){
			//endRecord();
			//notifyHandReleased();
			time++;
	}else{
		time = 0;
	}

	if(time > 15){
		time = 0;
		endRecord();
		notifyHandReleased();
	}
}

void updateRecord(){
	/* New Code Start */
	/*if(centerChecking()){
		return;
	}
	/* New Code End */

	switch(controlMode){

	case NI_MODE:
		{
			static bool isClicked = false;
			static XnFloat currentY = 0.0F;
			static XnFloat lastDown = 0.0F;
			int changedIndex = 0;
			XnSkeletonJointPosition posLeftHand, posRightHand, posHead, posHip;

			g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_LEFT_HAND, posLeftHand);
			g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_RIGHT_HAND, posRightHand);
			g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_HEAD, posHead);
			g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_TORSO, posHip);

			//rightHandPositionRatio = (posHead.position.Y-posRightHand.position.Y)/(posHead.position.Y-posHip.position.Y);
			currentY = posRightHand.position.Y;

			printf("CurrentY: %f, LastDown: %f, Dist: %f\n", currentY, lastDown, currentY - lastDown);
			if(lastDown == 0 || currentY - lastDown < 0){
				lastDown = posRightHand.position.Y;
			}else{
				/*while*/if(currentY - lastDown > MOVE_INDEX_DIST){
					changedIndex = 1; //++;
					//lastDown += MOVE_INDEX_DIST;
				}
				if(changedIndex > 0)
					lastDown = currentY;
			}
			
			if(!isClicked){
				if(posLeftHand.position.Y > posHip.position.Y){
					updateNI(changedIndex, isClicked = true);
				}else{
					updateNI(changedIndex, false);
				}
			}else{
				if(posLeftHand.position.Y < posHip.position.Y){
					updateNI(changedIndex, isClicked = false);
				}else{
					updateNI(changedIndex, false);
				}
			}

			break;
		}

	case CONTENT_MODE:
		{
			updateRecognizeRecord();
			checkIfHandReleased();
			break;
		}

	case SWIPE_MODE:
		{
			XnSkeletonJointPosition posLeftHand, posRightHand, posNeck;
			g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_LEFT_HAND, posLeftHand);
			g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_RIGHT_HAND, posRightHand);
			g_user.GetSkeletonCap().GetSkeletonJointPosition(g_userID, XN_SKEL_NECK, posNeck);

			if(posLeftHand.position.Y > posNeck.position.Y){
				notifySwipeLeft(g_user.GetTimestamp());
			}else if(posRightHand.position.Y > posNeck.position.Y){
				notifySwipeRight(g_user.GetTimestamp());
			}

			checkIfHandReleased();

			break;
		}
	}
}