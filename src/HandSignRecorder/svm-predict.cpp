#include "Common.h"
#include <vector>
#include <map>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <errno.h>
#include "svm.h"
#include "CommonGUI.h"
using namespace std;

#define TRAINING_MODEL_FILE "TrainingData/train.model"
#define DATA_SIZE STANARD_FRAME*VECTOR_SIZE
#define VOCAB_COUNT 48

struct svm_node nodeX[DATA_SIZE+1];
int max_nr_attr = 64;

struct svm_model* model;
int predict_probability=1;

extern double label_probability;
extern map<int, int> multiWord;
//extern void addWord(int choice1, double prob1, int choice2, double prob2);

static rawData detectedList[VOCAB_COUNT+SENTENCE_CHOICE];
static int totalDetected;
possible_choice possibleList;
vector<possible_choice> allInputs;
int inputSize = 0;

bool isSentenceModeOn;
bool isFocusSelectWord;

static char *line = NULL;

static bool sortByDesc (rawData i,rawData j) { 
	return (i.prob > j.prob); 
}

inline void putFrameToNode(Frame &frame, int &i){
	nodeX[i++].value = frame.vector_left_shoulder_hand.X;
	nodeX[i++].value = frame.vector_left_shoulder_hand.Y;
	nodeX[i++].value = frame.vector_left_shoulder_hand.Z;
	nodeX[i++].value = frame.vector_right_shoulder_hand.X;
	nodeX[i++].value = frame.vector_right_shoulder_hand.Y;
	nodeX[i++].value = frame.vector_right_shoulder_hand.Z;
	nodeX[i++].value = frame.vector_right_hand_left.X;
	nodeX[i++].value = frame.vector_right_hand_left.Y;
	nodeX[i++].value = frame.vector_right_hand_left.Z;
	nodeX[i++].value = frame.angle_left_hand_elbow_shoulder;
	nodeX[i++].value = frame.angle_left_elbow_shoulder_body;
	nodeX[i++].value = frame.angle_right_hand_elbow_shoulder;
	nodeX[i++].value = frame.angle_right_elbow_shoulder_body;
	nodeX[i++].value = frame.distance_hands;
}

inline void putActionToNode(vector<Frame> &action){
	for(int count=0, j=0; j<STANARD_FRAME;j++){
		putFrameToNode(action[j], count);
	}

	for(int i=0; i<DATA_SIZE; i++){
		nodeX[i].index = i+1;
	}
	nodeX[DATA_SIZE].index = -1;
}

void updateMultiWord(int *label, double *prob, int nClass){

	isFocusSelectWord = false;
	memset(detectedList, -1, sizeof(detectedList));

	totalDetected = nClass;
	for(int i=0; i<nClass; i++){
		detectedList[i].wordIndex = label[i]-1;
		detectedList[i].prob = prob[i];
	}
	
	sort(detectedList, detectedList+totalDetected, sortByDesc);
	for(int i=0; i<SENTENCE_CHOICE; i++){
		if(multiWord.find(detectedList[i].wordIndex) != multiWord.end()){
			detectedList[totalDetected].wordIndex = multiWord[detectedList[i].wordIndex];
			detectedList[totalDetected].prob = detectedList[i].prob;
			totalDetected++;
			//isFocusSelectWord = true;
		}
	}
	sort(detectedList, detectedList+totalDetected, sortByDesc);

	memset(&possibleList, 0, sizeof(possible_choice));
	for(int i=0; i<SENTENCE_CHOICE; i++){
		possibleList.choice[i].wordIndex = detectedList[i].wordIndex;
		possibleList.choice[i].prob = detectedList[i].prob;
	}
}

void updatePossibleChoiceList(int *label, double *prob, int nClass){
	int currentPossibleSize = 0;

	if(allInputs.size()==0){
		//initialize();
	}

	updateMultiWord(label, prob, nClass);
	if(label_probability < 0.2){
		isFocusSelectWord = true;
	}

	if(isSentenceModeOn){
		isFocusSelectWord = false;
		allInputs.push_back(possibleList);
		inputSize++;
	}
}

double predict(vector<Frame> &action){
	int correct = 0;
	int total = 0;
	double error = 0;
	double sump = 0, sumt = 0, sumpp = 0, sumtt = 0, sumpt = 0;

	int svm_type=svm_get_svm_type(model);
	int nr_class=svm_get_nr_class(model);
	double *prob_estimates=NULL;

	if(predict_probability){
		if (svm_type==NU_SVR || svm_type==EPSILON_SVR){
			printf("Prob. model for test data: target value = predicted value + z,\nz: Laplace distribution e^(-|z|/sigma)/(2sigma),sigma=%g\n",svm_get_svr_probability(model));
		}else{
			int *labels=(int *) malloc(nr_class*sizeof(int));
			svm_get_labels(model,labels);
			prob_estimates = (double *) malloc(nr_class*sizeof(double));
			free(labels);
		}
	}

	double predict_label;
	putActionToNode(action);

	if (predict_probability && (svm_type==C_SVC || svm_type==NU_SVC)){
		//int secondHighIndex = -1;
		//double secondHighProb = 0.0;

		predict_label = svm_predict_probability(model,nodeX,prob_estimates);
		for(int i=0; i<nr_class; i++){
			//printf("Class %d: %lf\n", model->label[i], prob_estimates[i]);

			if(model->label[i] == predict_label){
				label_probability = prob_estimates[i];
			}
		}

		updatePossibleChoiceList(model->label, prob_estimates, nr_class);
		

	}else{
		predict_label = svm_predict(model,nodeX);
		printf("%g\n",predict_label);
	}

	if(predict_probability)
		free(prob_estimates);

	return predict_label;
}

void svmInit(){
	if((model=svm_load_model(TRAINING_MODEL_FILE))==0){
		fprintf(stderr,"can't open model file %s\n",TRAINING_MODEL_FILE);
		getchar();
		exit(1);
	}

	if(predict_probability){
		if(svm_check_probability_model(model)==0){
			fprintf(stderr,"Model does not support probabiliy estimates\n");
			getchar();
			exit(1);
		}
	}
	else if(svm_check_probability_model(model)!=0){
			printf("Model supports probability estimates, but disabled in prediction.\n");
	}
}

void svmFree(){
	svm_free_and_destroy_model(&model);
	free(line);
}