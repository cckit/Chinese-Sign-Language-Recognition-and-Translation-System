#include "Common.h"
#include <process.h>
#include <windows.h>
#include <vector>
using namespace xn;
using namespace std;

#define DO_CLASSIFY
#define DO_ANALYSIS
#define DO_FILE_IO
#define MIN_RAW_DATA_SIZE 15
#define PRINT_VECTOR(v) "%f %f %f ", v.X, v.Y, v.Z

static FILE *recordFile;
static vector<Frame> actionResult;
extern vector<SkeletonRawData> rawDatas;
extern void getNormalizedAction(vector<Frame> &result, vector<SkeletonRawData> &rawDatas);
extern double predict(vector<Frame> &action);
//extern void signRecognized(int index);
extern void notifySignRecognized(int index);

// Thing done before starting trace
static inline void createRecordFile(){
	if(recordFile == NULL){
		char fileName[100];

		sprintf(fileName, "Record/%ld.txt", time(NULL)*1);
		recordFile = fopen(fileName, "w");

		printf("Created File for Recording\n");
	}
}

// Save Record to Files
static void saveToFile(){

#ifdef DO_FILE_IO
	for(unsigned int j=0; j<actionResult.size(); j++){
		fprintf(recordFile, PRINT_VECTOR(actionResult[j].vector_left_shoulder_hand));
		fprintf(recordFile, PRINT_VECTOR(actionResult[j].vector_right_shoulder_hand));
		fprintf(recordFile, PRINT_VECTOR(actionResult[j].vector_right_hand_left));
		fprintf(recordFile, "%f %f ", actionResult[j].angle_left_hand_elbow_shoulder, actionResult[j].angle_left_elbow_shoulder_body);
		fprintf(recordFile, "%f %f ", actionResult[j].angle_right_hand_elbow_shoulder, actionResult[j].angle_right_elbow_shoulder_body);
		fprintf(recordFile, "%f ", actionResult[j].distance_hands);
	}
	fprintf(recordFile, "\n");
	fflush(recordFile);
#endif

}

static unsigned int __stdcall runAnalysisThread(void *dummy){
	printf("4A. Start Analysis Thread\n");
	fflush(stdout);

#ifdef DO_CLASSIFY
	double result = predict(actionResult);
	printf("SVM result: %g\n", result);
	notifySignRecognized((int)(result-1));
#endif

	printf("4A. End Analysis Thread\n");
	fflush(stdout);
	return 0;
}

static unsigned int __stdcall runSaveFileThread(void *dummy){
	printf("4B. Start Save File Thread\n");
	fflush(stdout);

	createRecordFile();
	saveToFile();

	printf("4B. End Save File Thread\n");
	fflush(stdout);
	return 0;
}

static unsigned int __stdcall runNormalizationThread(void *dummy){
	printf("3. Start Normalization\n");
	fflush(stdout);
#ifdef DO_ANALYSIS
	getNormalizedAction(actionResult, rawDatas);
	//runAnalysisThread(NULL);
	//runSaveFileThread(NULL);
	rawDatas.clear();
	_beginthreadex(NULL, 0, runAnalysisThread, NULL, 0, NULL);
	_beginthreadex(NULL, 0, runSaveFileThread, NULL, 0, NULL);
#endif
	printf("3. End Normalization\n");
	fflush(stdout);

	return 0;
} 

void actionEndClearUp(){
	if(rawDatas.size()>=MIN_RAW_DATA_SIZE){
		_beginthreadex(NULL, 0, runNormalizationThread, NULL, 0, NULL);
	}else{
		printf("Action rejected: too few raw data (%d)\n", rawDatas.size());
	}
}