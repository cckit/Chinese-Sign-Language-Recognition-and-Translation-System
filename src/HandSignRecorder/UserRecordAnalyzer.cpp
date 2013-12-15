#include "Common.h"
#include <vector>
using namespace xn;
using namespace std;

#define dotProduct(a, b, o) ((a.X-o.X)*(b.X-o.X) + (a.Y-o.Y)*(b.Y-o.Y) + (a.Z-o.Z)*(b.Z-o.Z))
#define magnitudeSq(a, o) dotProduct(a, a, o)
#define vectorLength(a,o) sqrt(magnitudeSq(a,o))
#define VECTOR_NORMALIZE(des, a, o, l) l = vectorLength(a, o); des.X = (a.X-o.X)/l; des.Y = (a.Y-o.Y)/l; des.Z = (a.Z-o.Z)/l;
#define radianAngle3D(a, b, o) (acos(dotProduct(a, b, o)/sqrt(magnitudeSq(a, o)*magnitudeSq(b, o))))
#define radianAngleVericalPlan(a,o) (acos((a.Y-o.Y)/-vectorLength(a,o)))

#define INTERPOLATE_4(fx, x, x0, x1, x2, fx0, fx1, fx2) \
	fx = (x-x1)*(x-x2)*fx0/2 - (x-x0)*(x-x2)*fx1 + (x-x0)*(x-x1)*fx2/2;

#define INTERPOLATE_3(dest, src, mid, place, dim, num, srcSize) \
	INTERPOLATE_4(dest.place.dim, num, mid-1, mid, mid+1, src[mid-1].place.dim, src[mid].place.dim, src[mid+1].place.dim);

#define INTERPOLATE_2(dest, src, mid, place, num, srcSize) \
	INTERPOLATE_3(dest, src, mid, place, X, num, srcSize) \
	INTERPOLATE_3(dest, src, mid, place, Y, num, srcSize) \
	INTERPOLATE_3(dest, src, mid, place, Z, num, srcSize)

#define INTERPOLATE(dest, src, mid, num, srcSize) \
	INTERPOLATE_2(dest, src, mid, leftHand, num, srcSize) \
	INTERPOLATE_2(dest, src, mid, leftElbow, num, srcSize) \
	INTERPOLATE_2(dest, src, mid, leftShoulder, num, srcSize) \
	INTERPOLATE_2(dest, src, mid, rightHand, num, srcSize) \
	INTERPOLATE_2(dest, src, mid, rightElbow, num, srcSize) \
	INTERPOLATE_2(dest, src, mid, rightShoulder, num, srcSize)

static void getNormalizedRawData(vector<SkeletonRawData> &normalizedDatas, vector<SkeletonRawData> &rawDatas){
	SkeletonRawData newRawData;
	int dataSize = rawDatas.size();
	double num;
	int middle;

	normalizedDatas.clear();
	for(int i=0; i<STANARD_FRAME; i++){
		memset(&newRawData, 0, sizeof(SkeletonRawData));

		if((i*(dataSize-1)) % (STANARD_FRAME-1) == 0){
			normalizedDatas.push_back(rawDatas[i*(dataSize-1)/(STANARD_FRAME-1)]);
		}else{
			num = 1.0*i*(dataSize-1)/(STANARD_FRAME-1);
			middle = (int)(num+0.5);

			if(middle <= 1){
				middle = 1;
			}else if(middle >= dataSize-2){
				middle = dataSize-2;
			}

			INTERPOLATE(newRawData, rawDatas, middle, num, dataSize);
			normalizedDatas.push_back(newRawData);
		}
	}
}

void getNormalizedAction(vector<Frame> &actionResult, vector<SkeletonRawData> &rawDatas){
	Frame cuFrame;
	double leftArmLength, rightArmLength;
	double length;
	vector<SkeletonRawData> normalizedDatas;

	getNormalizedRawData(normalizedDatas, rawDatas);

	actionResult.clear();
	for(unsigned int i=0; i<normalizedDatas.size(); i++){
		SkeletonRawData data = normalizedDatas[i];

		VECTOR_NORMALIZE(cuFrame.vector_left_shoulder_hand, data.leftShoulder, data.leftHand, length);
		VECTOR_NORMALIZE(cuFrame.vector_right_shoulder_hand, data.rightShoulder, data.rightHand, length);
		VECTOR_NORMALIZE(cuFrame.vector_right_hand_left, data.rightHand, data.leftHand, length);

		leftArmLength = vectorLength(data.leftHand, data.leftElbow);
		rightArmLength = vectorLength(data.rightHand, data.rightElbow);
		cuFrame.distance_hands = vectorLength(data.rightHand, data.leftHand) * 2 / (leftArmLength + rightArmLength);
		cuFrame.angle_left_hand_elbow_shoulder = radianAngle3D(data.leftHand, data.leftShoulder, data.leftElbow);
		cuFrame.angle_right_hand_elbow_shoulder = radianAngle3D(data.rightHand, data.rightShoulder, data.rightElbow);
		cuFrame.angle_left_elbow_shoulder_body = radianAngleVericalPlan(data.leftElbow, data.leftShoulder);
		cuFrame.angle_right_elbow_shoulder_body = radianAngleVericalPlan(data.rightElbow, data.rightShoulder);

		actionResult.push_back(cuFrame);
	}
}