#include <iostream>
#include <cassert>
#include <vector>
#include <Windows.h>
#include "CheckIF.h"
#include "Header2.h"

/*

Header2.hのコメントをコピペしてTest.iniを作成し配置してください。
CheckTest2()関数に処理をべた書きしています。
リファクタリング※ をしてください。

※ プログラムの外部から見た動作を変えずにソースコードの内部構造を整理すること

*/

void CheckTest2()
{
	std::vector<std::string> cityNames;
	std::vector<std::string> conditions;
	std::vector<int> tempuratures;

	//天気データを読み込む

	char sections[1024];
	::GetPrivateProfileSectionNamesA(sections, sizeof(sections), "./Debug/Test.ini");

	int dataSize = 0;
	for (char* section = sections; *section != '\0'; section += strlen(section) + 1)
	{
		char cityName[255];
		char conditon[255];
		int tempurature;

		::GetPrivateProfileStringA(section, "CityName", "", cityName, sizeof(cityName), "./Debug/Test.ini");
		::GetPrivateProfileStringA(section, "Condition", "", conditon, sizeof(conditon), "./Debug/Test.ini");
		tempurature = ::GetPrivateProfileIntA(section, "Temperature", 0, "./Debug/Test.ini");

		cityNames.push_back(cityName);
		conditions.push_back(conditon);
		tempuratures.push_back(tempurature);
		dataSize++;
	}


	//出力
	int highest = INT_MIN;
	int highestIndex = 0;
	
	std::cout << "今日の天気" << std::endl;

	for (int i = 0; i < dataSize; i++)
	{
		Test1(cityNames[i], conditions[i], tempuratures[i], i);

		printf_s("%s\t%s\t%d℃\n",
			cityNames[i].c_str(),
			conditions[i].c_str(),
			tempuratures[i]);

		if (highest < tempuratures[i]) {
			highestIndex = i;
		}
	}

	Test2(cityNames[highestIndex]);

	printf_s("最も気温が高い場所は %s です\n", cityNames[highestIndex].c_str());
}
