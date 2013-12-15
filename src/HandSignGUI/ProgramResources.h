#pragma once
#include <map>
#include "stdafx.h"
#include "CommonGUI.h"
using namespace std;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;

extern map<int, int> multiWord;

namespace HandSignGUI{

	public ref class ProgramResources{
	public:

		static Image ^welcomeBackground;
		static Image ^mainMenuBackground;
		static Image ^vocabBackground;
		static Image ^vocabBackgroundS;
		static Image ^wordListBackground;
		static Image ^gameBackground;
		static Image ^subMenuBackground;

		static array<Image ^> ^imageList;
		static array<String ^> ^introList;
		static array<String ^> ^nameList = {
			L"很", L"東", L"家", L"右", L"左", L"請假", L"飛", L"看", L"體育", L"叫", L"聽", L"現在", L"做夢", L"光亮", L"報復", L"今天", L"滿", L"早上", L"愛", L"比較", L"和", L"對不起", L"操心", L"費力", L"當面", L"斗篷", L"丟", L"堆積", L"我", L"你", L"關照", L"對面", L"恭敬", L"戴", L"封閉", L"崇高", L"讀書", L"貢獻", L"高", L"和平", L"後", L"不幸", L"回家", L"熱", L"倔強", L"健康", L"過渡", L"開", L"聘請", L"運動", L"幻想", L"高興", L"閉合", L"學", L"過去"
		};

		static void initialize(){
			static bool completed = false;

			if(!completed){
				completed = true;

				welcomeBackground = Image::FromFile("Images/WelcomeBack.png");
				mainMenuBackground = Image::FromFile("Images/MainMenuBack.png");
				vocabBackground = Image::FromFile("Images/VocabBack.png");
				vocabBackgroundS = Image::FromFile("Images/VocabBack02.png");
				wordListBackground = Image::FromFile("Images/WordListBack.png");
				gameBackground = Image::FromFile("Images/GameBack.png");
				subMenuBackground = Image::FromFile("Images/SubMenu.png");

				imageList = gcnew array<Image ^>(VOCAB_COUNT);
				for(int i=1; i<=VOCAB_COUNT; i++){
					imageList[i-1] = Image::FromFile("Images/Vocab/"+i+".png");
				}

				StreamReader ^sr = gcnew StreamReader(L"Images/Vocab/Intro.txt");
				introList = gcnew array<String ^>(VOCAB_COUNT);
				for(int i=0; i<VOCAB_COUNT; i++){
					introList[i] = sr->ReadLine();
				}
				sr->Close();
			}
		}

		static Image ^getSignImage(int index){
			if(index >= VOCAB_COUNT)
				return imageList[multiWord[index]];
			return imageList[index];
		}

		static String ^getSignName(int index){
			if(index >= 0){
				return nameList[index];
			}else{
				return "";
			}
		}

		static String ^getSignIntro(int index){
			return introList[index];
		}

		//static int getSentence(int sentenceID, int index){
		//	return sentence_base[sentenceID, index];
		//}
	};


}