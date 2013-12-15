#pragma once

#include "SubMenu.h"
#include "CommonGUI.h"
#include "ProgramResources.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

extern CONTROL_MODE controlMode;
extern void switchPanel(GUI_PAGE newPanel);

namespace HandSignGUI {

	/// <summary>
	/// Summary for WordListPanel
	/// </summary>
	public ref class WordListPanel : public System::Windows::Forms::UserControl
	{
	public:
		static WordListPanel ^instance;

	private: System::Windows::Forms::Label^  lblIntro;

	private: System::Windows::Forms::PictureBox^  picCurrent;

	private: System::Windows::Forms::PictureBox^  picRight;




	private: System::Windows::Forms::PictureBox^  picLeft;
	private: System::Windows::Forms::Timer^  autoPlayTimer;
	private: System::Windows::Forms::Label^  lblName;




	public: 
	private:
		SubMenu ^subMenu;

	public:
		WordListPanel(void)
		{
			menuCount = 4;
			instance = this;
			this->Controls->Add(subMenu = gcnew SubMenu(4, L"Images/WordListBack01", L"Images/WordListMenuItem"));
			InitializeComponent();
			this->BackgroundImage = ProgramResources::wordListBackground;

			autoPlayTimer->Interval = AUTO_PLAY_SPEED/1000;
			initializeData();

			this->Visible = false;			
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~WordListPanel()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^  components;
	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(WordListPanel::typeid));
			this->picRight = (gcnew System::Windows::Forms::PictureBox());
			this->lblIntro = (gcnew System::Windows::Forms::Label());
			this->picCurrent = (gcnew System::Windows::Forms::PictureBox());
			this->picLeft = (gcnew System::Windows::Forms::PictureBox());
			this->autoPlayTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->lblName = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picRight))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picCurrent))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picLeft))->BeginInit();
			this->SuspendLayout();
			// 
			// picRight
			// 
			this->picRight->BackColor = System::Drawing::Color::Transparent;
			this->picRight->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->picRight->Location = System::Drawing::Point(940, 395);
			this->picRight->Name = L"picRight";
			this->picRight->Size = System::Drawing::Size(70, 70);
			this->picRight->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picRight->TabIndex = 4;
			this->picRight->TabStop = false;
			// 
			// lblIntro
			// 
			this->lblIntro->BackColor = System::Drawing::Color::Transparent;
			this->lblIntro->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->lblIntro->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(9)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
				static_cast<System::Int32>(static_cast<System::Byte>(126)));
			this->lblIntro->Location = System::Drawing::Point(199, 315);
			this->lblIntro->Name = L"lblIntro";
			this->lblIntro->Padding = System::Windows::Forms::Padding(0, 50, 0, 50);
			this->lblIntro->Size = System::Drawing::Size(306, 390);
			this->lblIntro->TabIndex = 0;
			this->lblIntro->Text = L"label1";
			// 
			// picCurrent
			// 
			this->picCurrent->BackColor = System::Drawing::Color::Transparent;
			this->picCurrent->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"picCurrent.Image")));
			this->picCurrent->Location = System::Drawing::Point(578, 237);
			this->picCurrent->Name = L"picCurrent";
			this->picCurrent->Size = System::Drawing::Size(278, 410);
			this->picCurrent->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picCurrent->TabIndex = 1;
			this->picCurrent->TabStop = false;
			// 
			// picLeft
			// 
			this->picLeft->BackColor = System::Drawing::Color::Transparent;
			this->picLeft->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->picLeft->Location = System::Drawing::Point(15, 395);
			this->picLeft->Name = L"picLeft";
			this->picLeft->Size = System::Drawing::Size(70, 70);
			this->picLeft->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picLeft->TabIndex = 2;
			this->picLeft->TabStop = false;
			// 
			// autoPlayTimer
			// 
			this->autoPlayTimer->Tick += gcnew System::EventHandler(this, &WordListPanel::autoPlayTimer_Tick);
			// 
			// lblName
			// 
			this->lblName->BackColor = System::Drawing::Color::Transparent;
			this->lblName->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->lblName->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(9)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
				static_cast<System::Int32>(static_cast<System::Byte>(126)));
			this->lblName->Location = System::Drawing::Point(199, 237);
			this->lblName->Name = L"lblName";
			this->lblName->Size = System::Drawing::Size(306, 67);
			this->lblName->TabIndex = 5;
			this->lblName->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// WordListPanel
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::Disable;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->Controls->Add(this->lblName);
			this->Controls->Add(this->picRight);
			this->Controls->Add(this->lblIntro);
			this->Controls->Add(this->picLeft);
			this->Controls->Add(this->picCurrent);
			this->DoubleBuffered = true;
			this->Margin = System::Windows::Forms::Padding(0);
			this->Name = L"WordListPanel";
			this->Size = System::Drawing::Size(1024, 768);
			this->VisibleChanged += gcnew System::EventHandler(this, &WordListPanel::WordListPanel_VisibleChanged);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picRight))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picCurrent))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picLeft))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		int currentSignIndex;
		int menuCount;
		static Image ^arrowLeft = Image::FromFile("Images/ArrowLeft.png");
		static Image ^arrowLeftD = Image::FromFile("Images/ArrowLeftD.png");
		static Image ^arrowRight = Image::FromFile("Images/ArrowRight.png");
		static Image ^arrowRightD = Image::FromFile("Images/ArrowRightD.png");

		delegate void d_function();

	private:
		void handleInitData(){
			currentSignIndex = 0;
			autoPlayTimer->Enabled = false;
			updateSign(0);
			subMenu->initializeData();
		}

	public:
		void initializeData(){
			if(this->InvokeRequired){
				this->BeginInvoke(gcnew d_function(this, &WordListPanel::handleInitData));
			}else{
				handleInitData();
			}
		}

	public:

		void updateSign(int index){
			if(index >= 0 && index < VOCAB_COUNT){
				currentSignIndex = index;

				picCurrent->Image = ProgramResources::getSignImage(index);
				lblName->Text = ProgramResources::getSignName(index);
				lblIntro->Text = ProgramResources::getSignIntro(index);

				if(index > 0){
					//picLeft->BackgroundImage = ProgramResources::getSignImage(index-1);
					picLeft->Image = arrowLeft;
				}else{
					//picLeft->BackgroundImage = nullptr;
					picLeft->Image = arrowLeftD;
				}

				if(index != VOCAB_COUNT-1){
					//picRight->BackgroundImage = ProgramResources::getSignImage(index+1);
					picRight->Image = arrowRight;
				}else{
					//picRight->BackgroundImage = nullptr;
					picRight->Image = arrowRightD;
				}
			}
		}

		void notifySwipeLeft(unsigned long long timestamp){
			static unsigned long long lastTime = 0;

			if(!autoPlayTimer->Enabled && timestamp - lastTime > SWIPE_INTERVAL){
				updateSign(currentSignIndex-1);
				lastTime = timestamp;
			}
		}

		void notifySwipeRight(unsigned long long timestamp){
			static unsigned long long lastTime = 0;

			if(!autoPlayTimer->Enabled && timestamp - lastTime > SWIPE_INTERVAL){
				updateSign(currentSignIndex+1);
				lastTime = timestamp;
			}
		}

		void handleHandReleased(){
			subMenu->Visible = true;
			autoPlayTimer->Stop();
			controlMode = NI_MODE;
		}

		void notifyHandReleased(){
			if(this->InvokeRequired){
				this->BeginInvoke(gcnew d_function(this, &WordListPanel::handleHandReleased));
			}else{
				handleHandReleased();
			}
		}

		void notifyItemSelected(int changedIndex){
			//selectedIndex = subMenu->notifyItemSelected(rightHandPositionRatio);
			subMenu->notifyItemSelected(changedIndex);
		} 

		void handleItemClicked(){
			if(controlMode == NI_MODE){
				switch(subMenu->selectedIndex){
				case 0: // Auto Play
					subMenu->Visible = false;
					autoPlayTimer->Start();
					controlMode = SWIPE_MODE;
					break;
				case 1: // Sound
					isSoundOn = !isSoundOn;
					subMenu->Invalidate();
					break;
				case 2: // Menu
					autoPlayTimer->Enabled = false;
					switchPanel(MAIN_MENU_PAGE);
					controlMode = NI_MODE;
					break;
				case 3: // Back
					subMenu->Visible = false;
					controlMode = SWIPE_MODE;
					break;
				}
			}
		}

		void notifyItemClicked(){
			if(this->InvokeRequired){
				this->BeginInvoke(gcnew d_function(this, &WordListPanel::handleItemClicked));
			}else{
				handleItemClicked();
			}
		}

	private: System::Void WordListPanel_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(this->Visible){
					 subMenu->Visible = false;
					 subMenu->Invalidate();
					 controlMode = SWIPE_MODE;
				 }
			 }
	private: System::Void autoPlayTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
				 updateSign((currentSignIndex+1)%VOCAB_COUNT);
			 }
};
}
