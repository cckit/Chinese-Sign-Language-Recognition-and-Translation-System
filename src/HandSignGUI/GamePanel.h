#pragma once

#include "SubMenu.h"
#include "CommonGUI.h"
#include "ProgramResources.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Media;

extern CONTROL_MODE controlMode;
extern void switchPanel(GUI_PAGE newPanel);

#define EASY_DETECT 7

namespace HandSignGUI {

	/// <summary>
	/// Summary for GamePanel
	/// </summary>
	public ref class GamePanel : public System::Windows::Forms::UserControl
	{
	public:
		static GamePanel ^instance;

	private: System::Windows::Forms::PictureBox^  picSign;
	public: 





	private: System::Windows::Forms::Label^  lblState;
	private: System::Windows::Forms::Label^  lblName;
	private: System::Windows::Forms::Label^  lblIntro;
	private: System::Windows::Forms::Label^  lblScore;
	private: System::Windows::Forms::Label^  lblMax;







	private:
		SubMenu ^subMenu;

	public:
		GamePanel(void)
		{
			menuCount = 4;
			instance = this;
			this->Controls->Add(subMenu = gcnew SubMenu(4, L"Images/GameBack01", L"Images/GameMenuItem"));
			gameSignIndex = gcnew array<int>(VOCAB_COUNT);
			srand(time(NULL));
			
			this->Visible = false;
			InitializeComponent();
			this->BackgroundImage = ProgramResources::gameBackground;
			//tableLayoutPanel1->BackgroundImage = ProgramResources::gameBackground;
			lblMax->Text = GAME_MAX+"";
			
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GamePanel()
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
			System::Windows::Forms::Label^  label10;
			System::Windows::Forms::Label^  label1;
			System::Windows::Forms::Label^  label2;
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(GamePanel::typeid));
			this->lblState = (gcnew System::Windows::Forms::Label());
			this->picSign = (gcnew System::Windows::Forms::PictureBox());
			this->lblName = (gcnew System::Windows::Forms::Label());
			this->lblIntro = (gcnew System::Windows::Forms::Label());
			this->lblScore = (gcnew System::Windows::Forms::Label());
			this->lblMax = (gcnew System::Windows::Forms::Label());
			label10 = (gcnew System::Windows::Forms::Label());
			label1 = (gcnew System::Windows::Forms::Label());
			label2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picSign))->BeginInit();
			this->SuspendLayout();
			// 
			// label10
			// 
			label10->BackColor = System::Drawing::Color::Transparent;
			label10->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			label10->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(9)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
				static_cast<System::Int32>(static_cast<System::Byte>(126)));
			label10->Location = System::Drawing::Point(661, 558);
			label10->Name = L"label10";
			label10->Size = System::Drawing::Size(64, 40);
			label10->TabIndex = 3;
			label10->Text = L"成績";
			label10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label1
			// 
			label1->BackColor = System::Drawing::Color::Transparent;
			label1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(9)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
				static_cast<System::Int32>(static_cast<System::Byte>(126)));
			label1->Location = System::Drawing::Point(751, 558);
			label1->Name = L"label1";
			label1->Size = System::Drawing::Size(65, 40);
			label1->TabIndex = 4;
			label1->Text = L"目標";
			label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			label2->BackColor = System::Drawing::Color::Transparent;
			label2->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(9)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
				static_cast<System::Int32>(static_cast<System::Byte>(126)));
			label2->Location = System::Drawing::Point(731, 598);
			label2->Name = L"label2";
			label2->Size = System::Drawing::Size(14, 40);
			label2->TabIndex = 7;
			label2->Text = L"/";
			label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblState
			// 
			this->lblState->BackColor = System::Drawing::Color::Transparent;
			this->lblState->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblState->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(9)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
				static_cast<System::Int32>(static_cast<System::Byte>(126)));
			this->lblState->Location = System::Drawing::Point(178, 558);
			this->lblState->Name = L"lblState";
			this->lblState->Size = System::Drawing::Size(346, 80);
			this->lblState->TabIndex = 8;
			this->lblState->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// picSign
			// 
			this->picSign->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->picSign->BackColor = System::Drawing::Color::White;
			this->picSign->Location = System::Drawing::Point(198, 241);
			this->picSign->Name = L"picSign";
			this->picSign->Size = System::Drawing::Size(307, 298);
			this->picSign->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picSign->TabIndex = 0;
			this->picSign->TabStop = false;
			// 
			// lblName
			// 
			this->lblName->BackColor = System::Drawing::Color::Transparent;
			this->lblName->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblName->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(9)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
				static_cast<System::Int32>(static_cast<System::Byte>(126)));
			this->lblName->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->lblName->Location = System::Drawing::Point(556, 257);
			this->lblName->Name = L"lblName";
			this->lblName->Size = System::Drawing::Size(366, 80);
			this->lblName->TabIndex = 10;
			this->lblName->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblIntro
			// 
			this->lblIntro->BackColor = System::Drawing::Color::Transparent;
			this->lblIntro->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblIntro->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(9)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
				static_cast<System::Int32>(static_cast<System::Byte>(126)));
			this->lblIntro->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->lblIntro->Location = System::Drawing::Point(556, 337);
			this->lblIntro->Name = L"lblIntro";
			this->lblIntro->Padding = System::Windows::Forms::Padding(50, 30, 0, 0);
			this->lblIntro->Size = System::Drawing::Size(366, 204);
			this->lblIntro->TabIndex = 9;
			// 
			// lblScore
			// 
			this->lblScore->BackColor = System::Drawing::Color::Transparent;
			this->lblScore->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->lblScore->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(9)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
				static_cast<System::Int32>(static_cast<System::Byte>(126)));
			this->lblScore->Location = System::Drawing::Point(661, 598);
			this->lblScore->Name = L"lblScore";
			this->lblScore->Size = System::Drawing::Size(64, 40);
			this->lblScore->TabIndex = 5;
			this->lblScore->Text = L"0";
			this->lblScore->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblMax
			// 
			this->lblMax->BackColor = System::Drawing::Color::Transparent;
			this->lblMax->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->lblMax->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(9)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
				static_cast<System::Int32>(static_cast<System::Byte>(126)));
			this->lblMax->Location = System::Drawing::Point(751, 598);
			this->lblMax->Name = L"lblMax";
			this->lblMax->Size = System::Drawing::Size(65, 40);
			this->lblMax->TabIndex = 6;
			this->lblMax->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// GamePanel
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->Controls->Add(this->lblMax);
			this->Controls->Add(label2);
			this->Controls->Add(this->lblState);
			this->Controls->Add(this->lblScore);
			this->Controls->Add(this->picSign);
			this->Controls->Add(label1);
			this->Controls->Add(this->lblName);
			this->Controls->Add(label10);
			this->Controls->Add(this->lblIntro);
			this->DoubleBuffered = true;
			this->Margin = System::Windows::Forms::Padding(0);
			this->Name = L"GamePanel";
			this->Size = System::Drawing::Size(1024, 768);
			this->VisibleChanged += gcnew System::EventHandler(this, &GamePanel::VocabPanel_VisibleChanged);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picSign))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		int gameProgress;
		int recognizedSignIndex;

		int selectedIndex;
		int menuCount;
		array<int> ^gameSignIndex;

	public:
		void initializeData(){

		}

	private:
		delegate void d_function();

	public:
		void setStateText(){
			if(gameProgress < GAME_MAX){
				if(recognizedSignIndex == gameSignIndex[gameProgress]){
					lblState->Text = L"您的動作很標準！\n做得很好！";
					gameProgress++;

					if(gameProgress == GAME_MAX){
						lblState->Text = L"恭喜你！\n你已经通過了測試了！";
						SoundPlayer ^player = gcnew SoundPlayer("Sound/Finish.wav");
						player->Play();
						delete player;
					}else{
						SoundPlayer ^player = gcnew SoundPlayer("Sound/Sucess.wav");
						player->Play();
						delete player;
					}
					updateGame();

				}else{
					lblState->Text = L"您的動作有點不同。。。\n再嘗試一遍吧！";
				}
			}
		}

		void notifySignRecognized(int index, double probability){
			recognizedSignIndex = index;

			if(this->InvokeRequired){
				this->BeginInvoke(gcnew d_function(this, &GamePanel::setStateText));
			}else{
				setStateText();
			}
		}

		void handleHandReleased(){
			subMenu->Visible = true;
			//menuVisible = true;
			this->Invalidate();
			controlMode = NI_MODE;
		}

		void notifyHandReleased(){
			if(this->InvokeRequired){
				this->BeginInvoke(gcnew d_function(this, &GamePanel::handleHandReleased));
			}else{
				handleHandReleased();
			}
		}

		void notifyItemSelected(int changedIndex){
			selectedIndex = subMenu->notifyItemSelected(changedIndex);
		}

		void handleItemClicked(){
			if(controlMode == NI_MODE){
				switch(selectedIndex){
				case 0: // Restart
					startGame();
					subMenu->Visible = false;
					//menuVisible = false;
					controlMode = CONTENT_MODE;
					break;
				case 1: // Sound
					isSoundOn = !isSoundOn;
					subMenu->Invalidate();
					//this->Invalidate();
					break;
				case 2: // Menu

					switchPanel(MAIN_MENU_PAGE);
					controlMode = NI_MODE;
					break;
				case 3: // Back
					subMenu->Visible = false;
					//menuVisible = false;
					controlMode = CONTENT_MODE;
					break;
				}
			}
		}

		void notifyItemClicked(){
			if(this->InvokeRequired){
				this->BeginInvoke(gcnew d_function(this, &GamePanel::handleItemClicked));
			}else{
				handleItemClicked();
			}
		}

	private: 
		void startGame(){
			gameProgress = 0;
			
			int currentA = 0, currentB = 0;
			static int list[EASY_DETECT] = {1, 3, 4, 13, 15, 28, 29};
			for(int i=0; i<EASY_DETECT; i++){
				gameSignIndex[i] = list[i];
			}

			for(int i=EASY_DETECT; i<VOCAB_COUNT; currentB++){
				if(!binary_search(list, list+EASY_DETECT, currentB)){
					gameSignIndex[i++] = currentB;
				}
			}

			int a, b, temp;
			for(int i=0; i<EASY_DETECT; i++){
				a = rand()%EASY_DETECT;
				b = rand()%EASY_DETECT;

				temp = gameSignIndex[a];
				gameSignIndex[a] = gameSignIndex[b];
				gameSignIndex[b] = temp;
			}

			for(int i=0; i<VOCAB_COUNT; i++){
				a = (rand()%(VOCAB_COUNT-EASY_DETECT)) + EASY_DETECT;
				b = (rand()%(VOCAB_COUNT-EASY_DETECT)) + EASY_DETECT;

				temp = gameSignIndex[a];
				gameSignIndex[a] = gameSignIndex[b];
				gameSignIndex[b] = temp;
			}

			lblState->Text = L"遊戲開始了！不懂的話\n可以看看右方的提示阿！！";
			lblScore->Text = ("0");
			updateGame();
		}

		void updateGame(){
			lblScore->Text = gameProgress+"";

			if(gameProgress != GAME_MAX){
				picSign->Image = ProgramResources::getSignImage(gameSignIndex[gameProgress]);
				lblName->Text = ProgramResources::getSignName(gameSignIndex[gameProgress]);
				lblIntro->Text = ProgramResources::getSignIntro(gameSignIndex[gameProgress]);
			}
		}

		System::Void VocabPanel_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(this->Visible){

					 subMenu->Visible = false;
					 subMenu->Invalidate();
					 controlMode = CONTENT_MODE;
					 selectedIndex = menuCount-1;
					 
					 startGame();
				 }
			 }
};
}
