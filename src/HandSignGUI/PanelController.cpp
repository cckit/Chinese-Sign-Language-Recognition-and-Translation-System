#include "stdafx.h"
#include "Form1.h"
#include "WelcomePanel.h"
#include "MainMenuPanel.h"
#include "CommonGUI.h"
#include <cstdio>
#include <vector>
using namespace std;

using namespace HandSignGUI;
using namespace System::Media;


GUI_PAGE guiPage = WELCOME_PAGE;
GUI_PAGE newGUIPage = WELCOME_PAGE;
CONTROL_MODE controlMode = WELCOME_MODE;

bool isSoundOn = true;

void switchPanel(GUI_PAGE newPanel);
void notifyStateChanged(RECORD_STATE state);
void notifyUserEnter();
void notifyUserExit();
void notifyItemSelected(int changedIndex);
void notifyItemClicked();
void notifyHandReleased();
void updateNI(int changedIndex, bool isClicked);
void notifySignRecognized(int index);
void notifySentenceCompleted();
void notifySwipeLeft(unsigned long long timestamp);
void notifySwipeRight(unsigned long long timestamp);

double label_probability = 0.0;
extern possible_choice possibleList;
extern int inputSize;

void switchPanel2(){
	Form1::instance->Controls[(int)newGUIPage]->Visible = true;
	Form1::instance->Controls[(int)guiPage]->Visible = false;
	guiPage = newGUIPage;
}

delegate void d_switchPanel();

void switchPanel(GUI_PAGE newPanel){
	if(guiPage==newPanel)
		return;
	newGUIPage = newPanel;

	if(Form1::instance->InvokeRequired){
		Form1::instance->BeginInvoke(gcnew d_switchPanel(switchPanel2));
	}else{
		switchPanel2();
	}
}

void notifyStateChanged(RECORD_STATE state){
	switch(guiPage){
	case VOCAB_PAGE:
		VocabPanel::instance->notifyStateChanged(state);
		break;
	}
}

void notifyUserEnter(){
	isSoundOn = true;

	if(guiPage == WELCOME_PAGE){
		switchPanel(MAIN_MENU_PAGE);
		controlMode = NI_MODE;
	}
}

void notifyUserExit(){
	switchPanel(WELCOME_PAGE);
	controlMode = WELCOME_MODE;

	MainMenuPanel::instance->initializeData();
	VocabPanel::instance->initializeData();
	WordListPanel::instance->initializeData();
}

void notifyItemSelected(int changedIndex){
	switch(guiPage){
	case MAIN_MENU_PAGE:
		MainMenuPanel::instance->notifyItemSelected(changedIndex);
		break;
	case VOCAB_PAGE:
		VocabPanel::instance->notifyItemSelected(changedIndex);
		break;
	case WORD_LIST_PAGE:
		WordListPanel::instance->notifyItemSelected(changedIndex);
		break;
	case GAME_PAGE:
		GamePanel::instance->notifyItemSelected(changedIndex);
		break;
	}
}

void notifyItemClicked(){
	switch(guiPage){
	case MAIN_MENU_PAGE:
		MainMenuPanel::instance->notifyItemClicked();
		break;
	case VOCAB_PAGE:
		VocabPanel::instance->notifyItemClicked();
		break;
	case WORD_LIST_PAGE:
		WordListPanel::instance->notifyItemClicked();
		break;
	case GAME_PAGE:
		GamePanel::instance->notifyItemClicked();
		break;
	}
}

void notifyHandReleased(){
	switch(guiPage){
	case VOCAB_PAGE:
		VocabPanel::instance->notifyHandReleased();
		break;
	case WORD_LIST_PAGE:
		WordListPanel::instance->notifyHandReleased();
		break;
	case GAME_PAGE:
		GamePanel::instance->notifyHandReleased();
		break;
	}
}

void updateNI(int changedIndex, bool isClicked){
	notifyItemSelected(changedIndex);

	if(isClicked){
		notifyItemClicked();
	}
}

void notifySignRecognized(int index){

	if(guiPage == VOCAB_PAGE)
		VocabPanel::instance->notifySignRecognized(index, label_probability);
	else if(guiPage == GAME_PAGE)
		GamePanel::instance->notifySignRecognized(index, label_probability);
}

void notifySentenceCompleted(){
	if(guiPage == VOCAB_PAGE && inputSize > 0){
		VocabPanel::instance->notifySentenceCompleted();
	}
}

void notifySwipeLeft(unsigned long long timestamp){
	if(guiPage == WORD_LIST_PAGE){
		WordListPanel::instance->notifySwipeLeft(timestamp);
	}
}

void notifySwipeRight(unsigned long long timestamp){
	if(guiPage == WORD_LIST_PAGE){
		WordListPanel::instance->notifySwipeRight(timestamp);
	}
}