#include <XnCppWrapper.h>

#define SMOOTH_FACTOR 0.3F
#define FRAME_PER_READ 2
#define STANARD_FRAME 121
#define VECTOR_SIZE 14

void assertOK(const XnChar* place, const XnStatus status);

typedef enum {WAIT_TRACING, USER_ENTER, CALIBRATION_START,
	WAIT_READY, WAIT_MOVING, TAKING_RECORD} RECORD_STATE;
//typedef enum {WAIT_TRACING, WAIT_READY, WAIT_MOVING, TAKING_RECORD} RECORD_STATE;

typedef struct{
	XnPoint3D leftHand;
	XnPoint3D leftElbow;
	XnPoint3D leftShoulder;
	XnPoint3D rightHand;
	XnPoint3D rightElbow;
	XnPoint3D rightShoulder;
} SkeletonRawData;

typedef struct{
	XnPoint3D vector_left_shoulder_hand;
	XnPoint3D vector_right_shoulder_hand;
	XnDouble angle_left_hand_elbow_shoulder;
	XnDouble angle_right_hand_elbow_shoulder;
	XnDouble angle_left_elbow_shoulder_body;
	XnDouble angle_right_elbow_shoulder_body;
	XnPoint3D vector_right_hand_left;
	XnDouble distance_hands;
} Frame;