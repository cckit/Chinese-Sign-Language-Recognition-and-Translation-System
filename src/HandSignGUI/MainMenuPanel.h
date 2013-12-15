#pragma once

#include "CommonGUI.h"

#define MENU_COUNT 4

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

extern GUI_PAGE guiPage;
extern CONTROL_MODE controlMode;
extern void switchPanel(GUI_PAGE newPanel);

namespace HandSignGUI {

	/// <summary>
	/// Summary for MainMenuPanel
	/// </summary>
	public ref class MainMenuPanel : public System::Windows::Forms::UserControl
	{
	public:
		static MainMenuPanel ^instance;


	public: 

	private:
		int menuCount;
		static Image ^item1 = Image::FromFile("Images/MainMenuItem1.png");
		static Image ^item1s = Image::FromFile("Images/MainMenuItem1s.png");
		static Image ^item2 = Image::FromFile("Images/MainMenuItem2.png");
		static Image ^item2s = Image::FromFile("Images/MainMenuItem2s.png");
		static Image ^item3 = Image::FromFile("Images/MainMenuItem3.png");
		static Image ^item3s = Image::FromFile("Images/MainMenuItem3s.png");
		static Image ^item4 = Image::FromFile("Images/MainMenuItem4.png");
		static Image ^item4s = Image::FromFile("Images/MainMenuItem4s.png");

	public:
		MainMenuPanel(void)
		{
			menuCount = 4;
			instance = this;
			InitializeComponent();
			this->BackgroundImage = Image::FromFile("Images/MainMenuBack.png");
			this->Visible = false;
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainMenuPanel()
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
			this->SuspendLayout();
			// 
			// MainMenuPanel
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoValidate = System::Windows::Forms::AutoValidate::Disable;
			this->DoubleBuffered = true;
			this->Margin = System::Windows::Forms::Padding(0);
			this->Name = L"MainMenuPanel";
			this->Size = System::Drawing::Size(1024, 768);
			this->VisibleChanged += gcnew System::EventHandler(this, &MainMenuPanel::MainMenuPanel_VisibleChanged);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainMenuPanel::MainMenuPanel_Paint);
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		GUI_PAGE selectedIndex;
		/*static array<Rectangle> ^area = {Rectangle(600, 85, 250, 60), 
			Rectangle(600, 255, 250, 60),
			Rectangle(600, 425, 250, 60),
			Rectangle(600, 595, 250, 60)
		};*/
		static Rectangle refreshArea = Rectangle(700, 240, 200, 655);

	public:

		void initializeData(){
			selectedIndex = VOCAB_PAGE;
			this->Invalidate(refreshArea, false);
		}

		void notifyItemSelected(int changedIndex){
			int newIndex = ((selectedIndex-VOCAB_PAGE+4-changedIndex)%4);

			if(selectedIndex != (GUI_PAGE)(newIndex + VOCAB_PAGE)){
				selectedIndex = (GUI_PAGE)(newIndex + VOCAB_PAGE);				
				this->Invalidate(refreshArea, false);		
			}
		}

		void notifyItemClicked(){
			if(selectedIndex == menuCount+VOCAB_PAGE-1){
				this->ParentForm->Close();
			}else if(selectedIndex >= VOCAB_PAGE){
				switchPanel(selectedIndex);
				if(guiPage == WORD_LIST_PAGE){
					controlMode = SWIPE_MODE;
				}else{
					controlMode = CONTENT_MODE;
				}
			}		
		}

	private: System::Void MainMenuPanel_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 /*e->Graphics->DrawImage(selectedIndex == VOCAB_PAGE?item1s:item1, 600, 85, 250, 60);
				 e->Graphics->DrawImage(selectedIndex == VOCAB_PAGE+1?item2s:item2, 600, 255, 250, 60);
				 e->Graphics->DrawImage(selectedIndex == VOCAB_PAGE+2?item3s:item3, 600, 425, 250, 60);
				 e->Graphics->DrawImage(selectedIndex == VOCAB_PAGE+3?item4s:item4, 600, 595, 250, 60);*/

				 e->Graphics->DrawImage(selectedIndex == VOCAB_PAGE?item1s:item1, 700, 240, 200, 50);
				 e->Graphics->DrawImage(selectedIndex == VOCAB_PAGE+1?item2s:item2, 700, 330, 200, 50);
				 e->Graphics->DrawImage(selectedIndex == VOCAB_PAGE+2?item3s:item3, 700, 420, 200, 50);
				 e->Graphics->DrawImage(selectedIndex == VOCAB_PAGE+3?item4s:item4, 700, 510, 200, 50);
				 
				 /*e->Graphics->DrawImage(selectedIndex == VOCAB_PAGE?item1s:item1, area[0]);
				 e->Graphics->DrawImage(selectedIndex == VOCAB_PAGE+1?item2s:item2, area[1]);
				 e->Graphics->DrawImage(selectedIndex == VOCAB_PAGE+2?item3s:item3, area[2]);
				 e->Graphics->DrawImage(selectedIndex == VOCAB_PAGE+3?item4s:item4, area[3]);*/
			 }
	private: System::Void MainMenuPanel_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(this->Visible){
					 selectedIndex = (VOCAB_PAGE);
				 }
			 }
	};
}
