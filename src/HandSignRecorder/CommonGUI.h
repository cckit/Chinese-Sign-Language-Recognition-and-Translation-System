/*#include "MainPanel.h"
#include "WelcomePanel.h"
#include "MainMenuPanel.h"
#include "DetectionPanel.h"
#include "WordListPanel.h"
#include "GamePanel.h"*/

#ifndef __COMMON_GUI_H
#define __COMMON_GUI_H

#define SENTENCE_CHOICE 4
#define VOCAB_COUNT 48

typedef enum { WELCOME_PAGE, MAIN_MENU_PAGE, DETECTION_PAGE, WORD_LIST_PAGE, GAME_PAGE} GUI_PAGE;
typedef enum { WELCOME_MODE, NI_MODE, CONTENT_MODE, SWIPE_MODE} CONTROL_MODE;

typedef struct{
	int wordIndex;
	double prob;
} rawData;

typedef struct{
	rawData choice[SENTENCE_CHOICE];
} possible_choice;

#endif