#pragma once

#include "ProgramResources.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace HandSignGUI {

	/// <summary>
	/// Summary for WelcomePanel
	/// </summary>
	public ref class WelcomePanel : public System::Windows::Forms::UserControl
	{
	public:
		static WelcomePanel ^instance;
	public:
		WelcomePanel(void)
		{
			instance = this;
			InitializeComponent();
			this->BackgroundImage = ProgramResources::welcomeBackground;
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~WelcomePanel()
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
			// WelcomePanel
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->Margin = System::Windows::Forms::Padding(0);
			this->Name = L"WelcomePanel";
			this->Size = System::Drawing::Size(1024, 768);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &WelcomePanel::WelcomePanel_Paint);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void WelcomePanel_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 
				// e->Graphics->DrawImage(a, 0, 0, 1024, 768);
				// a->RotateFlip(RotateFlipType::Rotate180FlipNone);
				// e->Graphics->DrawImage(a, 200, 0, 824, 768);
			 }
	};
}
