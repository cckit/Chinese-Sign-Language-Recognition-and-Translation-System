#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
#include "CommonGUI.h"
using namespace std;

#define SELECTION_CHOICE 4

typedef struct{
	vector<int> words;
	int score;
} chosenCombination;

typedef struct{
	double ratio;
	int Data_No;
	int choice2;
} proRatio;

static bool myfunction(proRatio i, proRatio j){ 
	return (i.ratio < j.ratio);
}



extern vector<possible_choice> allInputs;
extern int inputSize;

static int possCombin[51][51];
static vector<proRatio> allRatios;
static vector<int> currentSelected;
map<int, int> multiWord;

typedef struct{
	int left;
	int right;
	int score;
} tempChoice;

tempChoice tempScore[SELECTION_CHOICE * SELECTION_CHOICE];

static bool compareTempChoice(tempChoice a, tempChoice b){
	return a.score > b.score;
}

chosenCombination sentenceResult[SELECTION_CHOICE];
int currentResultCount = 0;


static void initialize(){	

	allRatios.clear();
	currentSelected.clear();

	currentResultCount = 0;

	for(int i=0; i<SELECTION_CHOICE; i++){
		sentenceResult[i].words.clear();
		sentenceResult[i].score = 1;
	}
}

void sentenceInit(){
	static bool inited = false;

	if(!inited){
		inited = true;

		for(int i=0; i<50; i++){
			for(int j=0; j<50; j++){
				possCombin[i][j] = 1;
			}
		}

		multiWord[5] = 48;
		multiWord[8] = 49;
		multiWord[12] = 50;
		multiWord[15] = 51;
		multiWord[20] = 52;
		multiWord[36] = 53;
		multiWord[40] = 54;

		multiWord[48] = 5;
		multiWord[49] = 8;
		multiWord[50] = 12;
		multiWord[51] = 15;
		multiWord[52] = 20;
		multiWord[53] = 36;
		multiWord[54] = 40;

		possCombin[0][13] = 6;
		possCombin[0][16] = 3;
		possCombin[0][18] = 8;
		possCombin[0][21] = 4;
		possCombin[0][23] = 4;
		possCombin[0][30] = 5;
		possCombin[0][32] = 6;
		possCombin[0][34] = 4;
		possCombin[0][35] = 5;
		possCombin[0][38] = 5;
		possCombin[0][41] = 5;
		possCombin[0][43] = 5;
		possCombin[0][44] = 5;
		possCombin[0][45] = 5;
		possCombin[0][51] = 9;

		possCombin[2][0] = 4;
		possCombin[7][28] = 4;
		possCombin[7][29] = 4; 
		possCombin[9][28] = 4;
		possCombin[9][29] = 4;
		possCombin[11][28] = 7;
		possCombin[11][29] = 7;
		possCombin[14][28] = 4;
		possCombin[14][29] = 4;
		possCombin[15][28] = 7;
		possCombin[15][29] = 7;
		possCombin[15][0] = 5;
		possCombin[17][0] = 5;
		possCombin[17][28] = 7;
		possCombin[17][29] = 7;
		possCombin[18][5] = 5;
		possCombin[18][8] = 5;
		possCombin[18][12] = 5;
		possCombin[18][14] = 3;
		possCombin[18][28] = 8;
		possCombin[18][29] = 8;
		possCombin[18][33] = 5;
		possCombin[18][36] = 6;
		possCombin[18][39] = 4;
		possCombin[18][49] = 7;

		possCombin[20][28] = 9;
		possCombin[20][29] = 9;
		possCombin[21][28] = 5;
		possCombin[21][29] = 5;

		possCombin[28][0] = 9;
		possCombin[28][5] = 3;
		possCombin[28][7] = 3;
		possCombin[28][9] = 3;
		possCombin[28][10] = 3;
		possCombin[28][12] = 5;
		possCombin[28][14] = 4;
		possCombin[28][15] = 7;
		possCombin[28][18] = 6;
		possCombin[28][20] = 7;
		possCombin[28][30] = 5;
		possCombin[28][48] = 5;
		possCombin[28][53] = 5;

		possCombin[29][0] = 9;
		possCombin[29][5] = 3;
		possCombin[29][7] = 3;
		possCombin[29][9] = 3;
		possCombin[29][10] = 3;
		possCombin[29][12] = 5;
		possCombin[29][14] = 4;
		possCombin[29][15] = 7;
		possCombin[29][18] = 6;
		possCombin[29][20] = 7;
		possCombin[29][30] = 5;
		possCombin[29][48] = 5;
		possCombin[29][53] = 5;

		possCombin[30][28] = 5;
		possCombin[30][29] = 5;

		possCombin[33][25] = 5;

		possCombin[48][28] = 7;
		possCombin[50][28] = 5;
		possCombin[54][28] = 8;

		possCombin[48][29] = 7;
		possCombin[50][29] = 5;
		possCombin[54][29] = 8;

		initialize();
	}	
}

void insert(int score){
	if(score > sentenceResult[currentResultCount-1].score){
		if(currentResultCount == 4){
			sentenceResult[currentResultCount-1].score = score;
			sentenceResult[currentResultCount-1].words.clear();

			sentenceResult[currentResultCount-1].words.assign(currentSelected.begin(), currentSelected.end());
		}else if(score > 0){
			sentenceResult[currentResultCount].score = score;
			sentenceResult[currentResultCount].words.clear();

			sentenceResult[currentResultCount].words.assign(currentSelected.begin(), currentSelected.end());
			currentResultCount++;
		}

		if(score > sentenceResult[2].score){
			sentenceResult[3].score = sentenceResult[2].score;
			sentenceResult[3].words.assign(sentenceResult[2].words.begin(), sentenceResult[2].words.end());
		}
	}
}

void updateSentenceStat(){
	chosenCombination combinationCopy[4];

	initialize();

	if(allInputs.size() == 0){
		currentResultCount = 0;
		return;
	}

	for(int i=0; i<SELECTION_CHOICE; i++){
		sentenceResult[i].words.push_back(allInputs[0].choice[i].wordIndex);
		sentenceResult[i].score = 1;
	}

	if(allInputs.size() > 1){
		memset(tempScore, 0, sizeof(tempScore));

		for(int ia=1; ia<allInputs.size(); ia++){


			for(int j=0; j<SELECTION_CHOICE; j++){
				int lastIndex = sentenceResult[j].words[ia-1];
				int oldScore = sentenceResult[j].score;
				combinationCopy[j].words = sentenceResult[j].words;

				for(int l=0; l<SELECTION_CHOICE; l++){
					int newIndex = allInputs[ia].choice[l].wordIndex;
					tempScore[j*4 + l].left = j;
					tempScore[j*4 + l].right = l;
					tempScore[j*4 + l].score = oldScore*possCombin[lastIndex][newIndex];
				}
			}

			sort(tempScore, tempScore+(SELECTION_CHOICE*SELECTION_CHOICE), compareTempChoice);

			for(int j=0; j<SELECTION_CHOICE; j++){
				sentenceResult[j].words = combinationCopy[tempScore[j].left].words;
				sentenceResult[j].words.push_back(allInputs[ia].choice[tempScore[j].right].wordIndex);
				sentenceResult[j].score = tempScore[j].score;
			}
		}

		bool isContained = true;
		for(int i=0; i<SELECTION_CHOICE; i++){
			isContained = true;
			for(int j=0; j<allInputs.size(); j++){
				if(allInputs[j].choice[0].wordIndex != sentenceResult[i].words[j]){
					isContained = false;
				}
			}

			if(isContained == true){
				break;
			}
		}

		if(!isContained){
			for(int i=0; i<allInputs.size(); i++){
				sentenceResult[SELECTION_CHOICE-1].words[i] = allInputs[i].choice[0].wordIndex;
			}
		}
	}

	currentResultCount = SELECTION_CHOICE;
	allInputs.clear();
	inputSize = 0;
}

/*void dfs(int step, int index, int score){
if(step == allInputs.size()-1){
insert(score);
}else{
if(score >= sentenceResult[currentPossibleCount-1].score){


for(int i=0; i<VOCAB_COUNT; i++){
currentSelected.push_back(i);
dfs(step+1, i, score*possCombin[allInputs[step][i].wordIndex]);
currentSelected.pop_back(i);
}
}
}
}*/

/*int updateSentenceSelection(bool highestOnly){

if(allInputs.size() == 0)
return 0;

if(highestOnly){
for(int i=0; i<allInputs.size(); i++){
sentenceResult[0].words.push_back(allInputs[i].choice[0].wordIndex);
}

allInputs.clear();
return 1;
}else{
currentResultCount = 0;
currentSelected.clear();


//dfs(0, 0, 1);

if(currentResultCount == 4){
sentenceResult[3].words.clear();
for(int i=0; i<allInputs.size(); i++){
sentenceResult[3].words.push_back(allInputs[i].choice[0].wordIndex);
}
}else{
sentenceResult[currentResultCount].words.clear();
for(int i=0; i<allInputs.size(); i++){
sentenceResult[currentResultCount].words.push_back(allInputs[i].choice[0].wordIndex);
}
currentResultCount++;
}

allInputs.clear();
return currentResultCount;
}


else{
for(int i = 0; i < allInputs.size(); i++){
proRatio data;
data.ratio = allInputs[i].prob1/allInputs[i].prob2;
data.Data_No = i;
data.choice2 = allInputs[i].choice2;
allRatios.push_back(data);
}

sort(allRatios.begin(),allRatios.end(),myfunction);

for(int i = 0; i < SELECTION_CHOICE; i++)
for( int j = 0; j < allInputs.size(); j++)
//sentenceResult[i].words[j] = allInputs[j].choice1;
sentenceResult[i].words.push_back(allInputs[j].choice1);

for(int i = 1; i < SELECTION_CHOICE; i++)
sentenceResult[i].words[allRatios[i-1].Data_No] = allRatios[i-1].choice2;

allInputs.clear();
return 4;
}
}*/

/*#include <string.h>

#define MAX_WORD_COUNT 10
#define CHOICE 3
#define SELECTION_CHOICE 4

typedef struct{
int words[MAX_WORD_COUNT];
double prob;
} chosenCombination;

typedef struct{
int words;
double prob;
} rawData;

chosenCombination chooseResult[SELECTION_CHOICE];
int chooseResultCount;

static rawData words[MAX_WORD_COUNT][CHOICE];
static int startWord, endNextWord;
static bool isWordEmpty = false;
static int buffer[MAX_WORD_COUNT];

static void dfs(int step, int choice){

if(step == (endNextWord-startWord)%MAX_WORD_COUNT){
double prob = 1.0;
for(int i=0; i<wordCount; i++){
prob *= words[i][buffer[i]].prob;
}

if(chooseResultCount < SELECTION_CHOICE){
memcpy(chooseResult[chooseResultCount].words, buffer, sizeof(buffer));
chooseResult[chooseResultCount].prob = prob;
chooseResultCount++;
}else{
int insertIndex = -1;

if(prob > chooseResult[chooseResultCount-1].prob){
insertIndex = chooseResultCount-1;
}

for(int i=chooseResultCount-2; i>=1; i--){
if(prob > chooseResult[i].prob){
insertIndex = i;
}else{
break;
}
}

if(insertIndex > 0){
for(int i=chooseResultCount-1; i>insertIndex; i--){
memcpy(&chooseResult[i], &chooseResult[i-1], sizeof(chosenCombination));
}
memcpy(chooseResult[insertIndex].words, buffer, sizeof(buffer));
chooseResult[insertIndex].prob = prob;
}			
}
}

for(int i=0; i<CHOICE; i++){
buffer[step+1] = i;
dfs(step+1, i);
}
buffer[step] = -1;
}

void addWord(int vocabIndex[CHOICE], double prob[CHOICE]){
isWordEmpty = true;


}

void updateSelection(){
memset(chooseResult, -1, sizeof(chooseResult));
chooseResultCount = 0;
memset(buffer, -1, sizeof(buffer));

dfs(0, 0);

memset(words, -1, sizeof(words));
isWordEmpty = true;
}*/