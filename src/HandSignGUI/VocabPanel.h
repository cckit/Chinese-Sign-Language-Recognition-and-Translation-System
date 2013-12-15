#pragma once

#include "SubMenu.h"
#include "CommonGUI.h"
#include "ProgramResources.h"
#include <vector>
#include <process.h>
using namespace std;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;

extern CONTROL_MODE controlMode;
extern void switchPanel(GUI_PAGE newPanel);
extern int currentResultCount;


extern chosenCombination sentenceResult[SELECTION_CHOICE];
extern possible_choice possibleList;
extern vector<rawData> allInputs;
//extern int updateSentenceSelection(bool highestOnly);
extern void updateSentenceStat();
extern bool isSentenceModeOn;
extern bool isFocusSelectWord;

namespace HandSignGUI {

	/// <summary>
	/// Summary for VocabPanel
	/// </summary>
	public ref class VocabPanel : public System::Windows::Forms::UserControl
	{
	public:
		static VocabPanel ^instance;
	private:
		SubMenu ^subMenu;

	private: System::Windows::Forms::RichTextBox^  txtHistory;

	private: System::Windows::Forms::PictureBox^  picSign;


	private: System::Windows::Forms::Label^  lblName;
	private: System::Windows::Forms::PictureBox^  picStatus;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::ComponentModel::BackgroundWorker^  soundWorker;




















			 int menuCount;

	public:
		VocabPanel(void)
		{
			menuCount = 4;
			//isLastNewLine = true;
			wordList = gcnew System::Collections::Generic::List<int>();

			instance = this;
			isFocusSelectWord = false;
			this->Controls->Add(subMenu = gcnew SubMenu(menuCount, L"Images/VocabBack01", L"Images/VocabMenuItemClose"));
			subMenu->TabIndex = 20;
			subMenu->Dock = System::Windows::Forms::DockStyle::Fill;
			InitializeComponent();
			this->BackgroundImage = ProgramResources::vocabBackground;
			this->Visible = false;

			subMenu->BringToFront();
			initializeData();

			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~VocabPanel()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 

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
			this->txtHistory = (gcnew System::Windows::Forms::RichTextBox());
			this->picSign = (gcnew System::Windows::Forms::PictureBox());
			this->lblName = (gcnew System::Windows::Forms::Label());
			this->picStatus = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->soundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picSign))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picStatus))->BeginInit();
			this->SuspendLayout();
			// 
			// txtHistory
			// 
			this->txtHistory->BackColor = System::Drawing::Color::White;
			this->txtHistory->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txtHistory->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->txtHistory->DetectUrls = false;
			this->txtHistory->Font = (gcnew System::Drawing::Font(L"STCaiyun", 26.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->txtHistory->Location = System::Drawing::Point(526, 202);
			this->txtHistory->Margin = System::Windows::Forms::Padding(3, 50, 3, 50);
			this->txtHistory->Name = L"txtHistory";
			this->txtHistory->ReadOnly = true;
			this->txtHistory->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
			this->txtHistory->Size = System::Drawing::Size(356, 300);
			this->txtHistory->TabIndex = 0;
			this->txtHistory->TabStop = false;
			this->txtHistory->Text = L"";
			// 
			// picSign
			// 
			this->picSign->BackColor = System::Drawing::Color::White;
			this->picSign->Location = System::Drawing::Point(97, 254);
			this->picSign->Margin = System::Windows::Forms::Padding(3, 25, 3, 3);
			this->picSign->Name = L"picSign";
			this->picSign->Size = System::Drawing::Size(356, 272);
			this->picSign->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picSign->TabIndex = 1;
			this->picSign->TabStop = false;
			// 
			// lblName
			// 
			this->lblName->BackColor = System::Drawing::Color::Transparent;
			this->lblName->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->lblName->Font = (gcnew System::Drawing::Font(L"STHupo", 47.99999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->lblName->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(9)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
				static_cast<System::Int32>(static_cast<System::Byte>(126)));
			this->lblName->Location = System::Drawing::Point(91, 540);
			this->lblName->Margin = System::Windows::Forms::Padding(0);
			this->lblName->Name = L"lblName";
			this->lblName->Padding = System::Windows::Forms::Padding(0, 25, 0, 0);
			this->lblName->Size = System::Drawing::Size(362, 91);
			this->lblName->TabIndex = 3;
			this->lblName->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// picStatus
			// 
			this->picStatus->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->picStatus->BackColor = System::Drawing::Color::Transparent;
			this->picStatus->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->picStatus->Location = System::Drawing::Point(25, 180);
			this->picStatus->Name = L"picStatus";
			this->picStatus->Size = System::Drawing::Size(190, 65);
			this->picStatus->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picStatus->TabIndex = 4;
			this->picStatus->TabStop = false;
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(9)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
				static_cast<System::Int32>(static_cast<System::Byte>(126)));
			this->label1->Location = System::Drawing::Point(273, 202);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(285, 50);
			this->label1->TabIndex = 4;
			this->label1->Text = L"我";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->label1->Visible = false;
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(9)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
				static_cast<System::Int32>(static_cast<System::Byte>(126)));
			this->label2->Location = System::Drawing::Point(273, 346);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(285, 50);
			this->label2->TabIndex = 5;
			this->label2->Text = L"我";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->label2->Visible = false;
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(9)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
				static_cast<System::Int32>(static_cast<System::Byte>(126)));
			this->label3->Location = System::Drawing::Point(273, 490);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(285, 50);
			this->label3->TabIndex = 6;
			this->label3->Text = L"我";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->label3->Visible = false;
			// 
			// label4
			// 
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(9)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
				static_cast<System::Int32>(static_cast<System::Byte>(126)));
			this->label4->Location = System::Drawing::Point(273, 634);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(285, 50);
			this->label4->TabIndex = 7;
			this->label4->Text = L"我";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->label4->Visible = false;
			// 
			// soundWorker
			// 
			this->soundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &VocabPanel::soundWorker_DoWork);
			// 
			// VocabPanel
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::Disable;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->CausesValidation = false;
			this->Controls->Add(this->txtHistory);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->lblName);
			this->Controls->Add(this->picSign);
			this->Controls->Add(this->picStatus);
			this->DoubleBuffered = true;
			this->Margin = System::Windows::Forms::Padding(0);
			this->Name = L"VocabPanel";
			this->Size = System::Drawing::Size(1024, 768);
			this->VisibleChanged += gcnew System::EventHandler(this, &VocabPanel::VocabPanel_VisibleChanged);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &VocabPanel::VocabPanel_Paint);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picSign))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picStatus))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		bool isLastNewLine;
		static Image ^statusRecording = Image::FromFile("Images/StatusRecording.png");
		static Image ^statusReady = Image::FromFile("Images/StatusReady.png");
		static Image ^checkBox = Image::FromFile("Images/checkBox.png");
		static Image ^checkBoxS = Image::FromFile("Images/checkBoxS.png");
		static Image ^sentenceOpen = Image::FromFile("Images/VocabMenuItemOpen.png");
		static Image ^sentenceOpenS = Image::FromFile("Images/VocabMenuItemOpenS.png");
		static Image ^sentenceClose = Image::FromFile("Images/VocabMenuItemClose.png");
		static Image ^sentenceCloseS = Image::FromFile("Images/VocabMenuItemCloseS.png");
		System::Collections::Generic::List<int> ^wordList;
		array<double> ^rank;
		array<System::Collections::Generic::List<int> ^> ^combination;
		//RECORD_STATE newState;
		int recognizedSignIndex;
		double probability;
		int selectedIndex;
		System::Media::SoundPlayer ^player;

	private:
		void handleInitData(){
			isLastNewLine = true;
			recognizedSignIndex = -1;
			probability = 0;
			selectedIndex = 0;
			isSentenceModeOn = false;
			wordList->Clear();

			picStatus->Image = statusReady;
			picSign->Image = nullptr;
			lblName->Text = "";
			txtHistory->Clear();

			player = gcnew System::Media::SoundPlayer();
			subMenu->initializeData();
		}

	public:
		void initializeData(){
			if(this->InvokeRequired){
				this->BeginInvoke(gcnew d_function(this, &VocabPanel::handleInitData));
			}else{
				handleInitData();
			}
		}

		void showSelection(bool isOn){

			selectedIndex = 0;

			picStatus->Visible = !isOn;
			picSign->Visible = !isOn;
			lblName->Visible = !isOn;
			txtHistory->Visible = !isOn;

			label1->Visible = isOn;
			label2->Visible = isOn;
			label3->Visible = isOn;
			label4->Visible = isOn;

			if(isOn){
				controlMode = NI_MODE;
				this->BackgroundImage = ProgramResources::vocabBackgroundS;
			}else{
				controlMode = CONTENT_MODE;
				this->BackgroundImage = ProgramResources::vocabBackground;
			}

			this->Invalidate();
		}

	private:
		void saveToFile(){
			StreamWriter^ pwriter = gcnew StreamWriter(L"talkRecord.txt", false, System::Text::Encoding::UTF8);
			array<String ^> ^lines = txtHistory->Lines;

			for(int i=0; i<lines->Length; i++){
				pwriter->WriteLine(lines[i]);
			}
			pwriter->Close();
		}

		delegate void d_function();

	public:

		void notifyStateChanged(RECORD_STATE state){
			if(state == WAIT_READY){
				picStatus->Image = statusReady;
			}else{
				picStatus->Image = statusRecording;
			}
		}

		void updateLayout(int recognizedSignIndex){

			picSign->Image = ProgramResources::getSignImage(recognizedSignIndex);
			lblName->Text = ProgramResources::getSignName(recognizedSignIndex);

			if(multiWord.find(recognizedSignIndex) != multiWord.end()){
				lblName->Text += "／";
				lblName->Text += ProgramResources::getSignName(multiWord[recognizedSignIndex]);
			}

			txtHistory->AppendText(ProgramResources::getSignName(recognizedSignIndex));
			//txtHistory->AppendText(possibleList.choice[0].prob+"");
			txtHistory->Text += Environment::NewLine;

			if(isSoundOn){
				player->SoundLocation = "Sound/"+recognizedSignIndex+".wav";
				player->LoadAsync();
				player->Play();
			}

			isLastNewLine = false;

			wordList->Add(recognizedSignIndex);

			txtHistory->SelectionStart = txtHistory->Text->Length;
			txtHistory->ScrollToCaret();
		}

		void handleSignRecognized(){
			if(!isSentenceModeOn){
				if(isFocusSelectWord){
					label1->Text = ProgramResources::getSignName(possibleList.choice[0].wordIndex);
					label2->Text = ProgramResources::getSignName(possibleList.choice[1].wordIndex);
					label3->Text = ProgramResources::getSignName(possibleList.choice[2].wordIndex);
					label4->Text = ProgramResources::getSignName(possibleList.choice[3].wordIndex);
					this->BackgroundImage = ProgramResources::vocabBackgroundS;
					showSelection(true);
				}else{
					updateLayout(recognizedSignIndex);
				}
			}else{
				int a = recognizedSignIndex;

				picSign->Image = ProgramResources::getSignImage(recognizedSignIndex);
				lblName->Text = ProgramResources::getSignName(recognizedSignIndex);
				if(multiWord.end() != multiWord.find(a)){
					lblName->Text += L"／";
					lblName->Text += ProgramResources::getSignName(multiWord[a]);
				}
			}
		}


		void notifySignRecognized(int index, double probability){
			recognizedSignIndex = index;
			this->probability = probability;

			if(this->InvokeRequired){
				this->BeginInvoke(gcnew d_function(this, &VocabPanel::handleSignRecognized));
			}else{
				handleSignRecognized();
			}
		}

		void updateText(Control ^dest, vector<int> &source){
			for(int i=0; i<source.size(); i++){
				dest->Text += ProgramResources::getSignName(source[i]);
			}
		}

		void handleSentenceCompleted(){

			if(isSentenceModeOn){
				//int count = updateSentenceSelection(false);
				updateSentenceStat();
				if(currentResultCount == 0){
					return;
				}

				label1->Text = "";
				//if(count >= 1)
					updateText(label1, sentenceResult[0].words);

				label2->Text = "";
				//if(count >= 2)
					updateText(label2, sentenceResult[1].words);

				label3->Text = "";
				//if(count >= 3)
					updateText(label3, sentenceResult[2].words);

				label4->Text = "";
				//if(count >= 4)
					updateText(label4, sentenceResult[3].words);

				//if(count >= 1)
					showSelection(true);
			}
		}

		void notifySentenceCompleted(){
			if(this->InvokeRequired){
				this->BeginInvoke(gcnew d_function(this, &VocabPanel::handleSentenceCompleted));
			}else{
				handleSentenceCompleted();
			}
		}


		void handleHandReleased(){
			subMenu->Visible = true;
			picStatus->Image = statusReady;
			picSign->Image = nullptr;
			lblName->Text = "";
			txtHistory->Clear();
			controlMode = NI_MODE;
		}

		void notifyHandReleased(){

			if(this->InvokeRequired){
				this->BeginInvoke(gcnew d_function(this, &VocabPanel::handleHandReleased));
			}else{
				handleHandReleased();
			}
		}

		void notifyItemSelected(int changedIndex){
			if(subMenu->Visible){
				subMenu->notifyItemSelected(changedIndex);
			}else if(label1->Visible){

				int newIndex;

				if(!isSentenceModeOn){
					newIndex = ((selectedIndex+SENTENCE_CHOICE-changedIndex)%SENTENCE_CHOICE);
				}else{
					newIndex = ((selectedIndex+currentResultCount-changedIndex)%currentResultCount);
				}

				if(selectedIndex != newIndex){
					selectedIndex = newIndex;
					this->Invalidate();
				}
			}
		}

		void handleItemClicked(){
			if(label1->Visible){
				if(isSentenceModeOn){
					if(isSoundOn){
						soundWorker->RunWorkerAsync(selectedIndex);
					}					
					switch(selectedIndex){
					case 0:
						txtHistory->Text += label1->Text;
						break;
					case 1:
						txtHistory->Text += label2->Text;
						break;
					case 2:
						txtHistory->Text += label3->Text;
						break;
					case 3:
						txtHistory->Text += label4->Text;
						break;
					}

					label1->Text = "";
					label2->Text = "";
					label3->Text = "";
					label4->Text = "";


					txtHistory->Text += "。";
					txtHistory->Text += Environment::NewLine;
					txtHistory->SelectionStart = txtHistory->Text->Length;
					txtHistory->ScrollToCaret();
				}else{
					updateLayout(possibleList.choice[selectedIndex].wordIndex);
				}

				showSelection(false);

			}else if(controlMode == NI_MODE){
				switch(subMenu->selectedIndex){
				case 0: // Save
					if(isSentenceModeOn){
						//int count = updateSentenceSelection(true);
						updateSentenceStat();
						selectedIndex = 0;
						//if(sentenceResult[0].score > 0){
						//if(count > 0)
							updateText(txtHistory, sentenceResult[0].words);
						//}
					}
					isSentenceModeOn = !isSentenceModeOn;
					subMenu->item1 = isSentenceModeOn ? sentenceOpen : sentenceClose;
					subMenu->item1s = isSentenceModeOn ? sentenceOpenS : sentenceCloseS;

					//saveToFile();
				case 3: // Back
					subMenu->Visible = false;
					controlMode = CONTENT_MODE;
					picStatus->Image = statusReady;
					this->Invalidate();
					break;
				case 1: // Sound
					isSoundOn = !isSoundOn;
					subMenu->Invalidate();
					break;
				case 2: // Menu
					switchPanel(MAIN_MENU_PAGE);
					controlMode = NI_MODE;
					break;

				}
			}
		}

		void notifyItemClicked(){
			if(this->InvokeRequired){
				this->BeginInvoke(gcnew d_function(this, &VocabPanel::handleItemClicked));
			}else{
				handleItemClicked();
			}
		}

	private: System::Void VocabPanel_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(this->Visible){
					 isSentenceModeOn = false;
					 subMenu->item1 = sentenceClose;
					 subMenu->item1s = sentenceCloseS;
					 subMenu->Visible = false;
					 subMenu->Invalidate();
					 controlMode = CONTENT_MODE;
					 picStatus->Image = statusReady;
				 }
			 }
	private: System::Void VocabPanel_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 if(label1->Visible){
					 for(int i=0; i<SENTENCE_CHOICE; i++){
						 if((currentResultCount > i) || (!isSentenceModeOn))
							 e->Graphics->DrawImage(selectedIndex==i ? checkBoxS : checkBox, 167, 177+144*i, 100, 100);
					 }
				 }
			 }
	private: System::Void soundWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				 vector<int> words = sentenceResult[(int)e->Argument].words;
				 System::Media::SoundPlayer ^player = gcnew  System::Media::SoundPlayer();
				 
				 for(int i=0; i<words.size(); i++){
					 player->SoundLocation = "Sound/"+words[i]+".wav";
					 player->PlaySync();
				 }

				 player->Stop();
			 }
	};
}
