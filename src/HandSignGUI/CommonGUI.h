#pragma once

#include <vector>

//#define NO_KINECT

#define VOCAB_COUNT 48
#define SWIPE_INTERVAL 1000000
#define AUTO_PLAY_SPEED 1500000
#define GAME_MAX 3
#define SENTENCE_CHOICE 4
#define SENTENCE_COUNT 20
#define MIN_PROB 0.2

#define MAX_WORD_COUNT 10
#define SELECTION_CHOICE 4

typedef enum { WELCOME_PAGE, MAIN_MENU_PAGE, VOCAB_PAGE, WORD_LIST_PAGE, GAME_PAGE} GUI_PAGE;
typedef enum { WELCOME_MODE, NI_MODE, CONTENT_MODE, SWIPE_MODE, SENTENCE_MODE} CONTROL_MODE;
typedef enum {WAIT_TRACING, USER_ENTER, CALIBRATION_START,
	WAIT_READY, WAIT_MOVING, TAKING_RECORD} RECORD_STATE;

typedef struct{
	std::vector<int> words;
	int score;
} chosenCombination;

typedef struct{
	int wordIndex;
	double prob;
} rawData;

typedef struct{
	rawData choice[4];
} possible_choice;