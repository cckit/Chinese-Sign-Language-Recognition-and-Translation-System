#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

extern bool isSoundOn;

namespace HandSignGUI {

	/// <summary>
	/// Summary for SubMenu
	/// </summary>
	public ref class SubMenu : public System::Windows::Forms::UserControl
	{
	private:
		static Image ^soundOff = Image::FromFile("Images/SubMenuSoundOff.png");
		static Image ^soundOffS = Image::FromFile("Images/SubMenuSoundOffS.png");
		static Image ^soundOn = Image::FromFile("Images/SubMenuSoundOn.png");
		static Image ^soundOnS = Image::FromFile("Images/SubMenuSoundOnS.png");
		static Image ^menuImage = Image::FromFile("Images/SubMenuMenu.png");
		static Image ^menuImageS = Image::FromFile("Images/SubMenuMenuS.png");
		static Image ^closeImage = Image::FromFile("Images/SubMenuClose.png");
		static Image ^closeImageS = Image::FromFile("Images/SubMenuCloseS.png");
		//static Image ^backImage = Image::FromFile("Images/SubMenu.png");
		
	public:
		Image /*^title, */^item1, ^item1s;

	public:
		int selectedIndex;

	public:

		SubMenu(int menuCount, String ^name, String ^item1)
		{
			this->menuCount = menuCount;
			InitializeComponent();
			//this->title = Image::FromFile(name+".png");
			this->BackgroundImage = Image::FromFile(name+".png");//backImage;
			this->item1 = Image::FromFile(item1+".png");
			this->item1s = Image::FromFile(item1+"S.png");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SubMenu()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 

	protected: 

	protected: 

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
			// SubMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::Disable;
			this->BackColor = System::Drawing::Color::Transparent;
			this->CausesValidation = false;
			this->DoubleBuffered = true;
			this->Name = L"SubMenu";
			this->Size = System::Drawing::Size(1024, 768);
			this->VisibleChanged += gcnew System::EventHandler(this, &SubMenu::SubMenu_VisibleChanged);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &SubMenu::SubMenu_Paint);
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		int menuCount;

	public:
		int notifyItemSelected(int changedIndex){
			selectedIndex = ((selectedIndex+menuCount*2-changedIndex)%menuCount);

			this->Invalidate();
			return selectedIndex;
		}

		void initializeData(){
			selectedIndex = menuCount-1;
			this->Visible = false;
		}

	private: System::Void SubMenu_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(!this->Visible){
					 initializeData();
				 }
			 }

	private: System::Void SubMenu_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 
				 e->Graphics->DrawImage(selectedIndex == 0 ? item1s : item1, 270, 260, 200, 50);//80, 190, 200, 50);

				 if(isSoundOn)
					 e->Graphics->DrawImage(selectedIndex == 1 ? soundOnS : soundOn, 270, 340, 200, 50);//120, 330, 200, 50);
				 else
					 e->Graphics->DrawImage(selectedIndex == 1 ? soundOffS : soundOff, 270, 340, 200, 50);//120, 330, 200, 50);

				 e->Graphics->DrawImage(selectedIndex == 2 ? menuImageS : menuImage, 270, 420, 200, 50);//90, 480, 200, 50);
				 e->Graphics->DrawImage(selectedIndex == 3 ? closeImageS : closeImage, 270, 500, 200, 50);//35, 625, 200, 50);
			 }
	};
}
