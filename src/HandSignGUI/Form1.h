#pragma once

#include "WelcomePanel.h"
#include "MainMenuPanel.h"
#include "VocabPanel.h"
#include "WordListPanel.h"
#include "GamePanel.h"
#include "ProgramResources.h"
#include <cstdlib>
#include <ctime>

extern void switchPanel(GUI_PAGE newPanel);
extern void notifyStateChanged(RECORD_STATE state);
extern void notifyUserEnter();
extern void notifyUserExit();
extern void notifyItemSelected(int changedIndex);
extern void notifyItemClicked();
extern void notifyHandReleased();
extern void notifySignRecognized(int index);
extern void notifySentenceCompleted();
extern void notifySwipeLeft(unsigned long long timestamp);
extern void notifySwipeRight(unsigned long long timestamp);


//extern void addWord(int choice1, double prob1, int choice2, double prob2);
extern possible_choice possibleList;
extern double label_probability;
extern void updatePossibleChoiceList(int *label, double *prob, int nClass);

namespace HandSignGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		static Form1 ^instance;
		WelcomePanel ^welcomePanel;
		MainMenuPanel ^mainMenuPanel;
		VocabPanel ^vocabPanel;
		WordListPanel ^wordListPanel;

	public: 
		GamePanel ^gamePanel;

	public:
		Form1(void)
		{
			instance = this;
			InitializeComponent();
		
			HandSignGUI::ProgramResources::initialize();
			System::Windows::Forms::Cursor::Hide();

			this->Controls->Add(welcomePanel = gcnew WelcomePanel());
			this->Controls->Add(mainMenuPanel = gcnew MainMenuPanel());
			this->Controls->Add(vocabPanel = gcnew VocabPanel());
			this->Controls->Add(wordListPanel = gcnew WordListPanel());
			this->Controls->Add(gamePanel = gcnew GamePanel);
			

			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(1024, 768);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->KeyPreview = true;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Form1";
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::Form1_KeyPress);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
			 {
				 static int i=0;
				 switch(e->KeyChar){
				 case 'a':
					 notifySignRecognized(rand()%VOCAB_COUNT);
					 break;
				 case 'e':
					 notifyUserEnter();
					 break;
				 case 'x':
					 notifyUserExit();
					 break;
				 case 'c':
					 notifyItemClicked();
					 break;
				 case 'r':
					 notifyHandReleased();
					 break;
				 case 'j':
					 notifyStateChanged(WAIT_READY);
					 break;
				 case 'k':
					 notifyStateChanged(WAIT_MOVING);
					 break;
				 case 's':
					 notifySentenceCompleted();
					 break;
				 case 'w':{
					 for(int j=0; j<SELECTION_CHOICE; j++){
						 possibleList.choice[j].wordIndex = rand()%VOCAB_COUNT;
						 possibleList.choice[j].prob = rand()*1.0/RAND_MAX;
					 }
					 //addWord(i=(rand()%VOCAB_COUNT), rand()*1.0/RAND_MAX, rand()%VOCAB_COUNT, rand()*1.0/RAND_MAX);
					 int word[4] = {rand()%(VOCAB_COUNT+5), rand()%(VOCAB_COUNT+5), rand()%(VOCAB_COUNT+5), rand()%(VOCAB_COUNT+5)};
					 double prob[4] = {rand()*1.0/RAND_MAX, rand()*1.0/RAND_MAX, rand()*1.0/RAND_MAX, rand()*1.0/RAND_MAX};
					 
					 updatePossibleChoiceList(word, prob, 4);
					 notifySignRecognized(possibleList.choice[0].wordIndex);
					 break;
						  }
				 case 'o':
					 notifySwipeLeft(time(NULL));
					 break;
				 case 'p':
					 notifySwipeRight(time(NULL));
					 break;
				 default:
					 if(e->KeyChar>='0' && e->KeyChar<='9'){
						 notifyItemSelected(e->KeyChar-'0');
					 }
				 }
			 }
	};
}

