#include <iostream>
#include <cassert>
#include <vector>
#include <Windows.h>
#include "CheckIF.h"
#include "Header2.h"

/*

Header2.h�̃R�����g���R�s�y����Test.ini���쐬���z�u���Ă��������B
CheckTest2()�֐��ɏ������ׂ��������Ă��܂��B
���t�@�N�^�����O�� �����Ă��������B

�� �v���O�����̊O�����猩�������ς����Ƀ\�[�X�R�[�h�̓����\���𐮗����邱��

*/

void CheckTest2()
{
	std::vector<std::string> cityNames;
	std::vector<std::string> conditions;
	std::vector<int> tempuratures;

	//�V�C�f�[�^��ǂݍ���

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


	//�o��
	int highest = INT_MIN;
	int highestIndex = 0;
	
	std::cout << "�����̓V�C" << std::endl;

	for (int i = 0; i < dataSize; i++)
	{
		Test1(cityNames[i], conditions[i], tempuratures[i], i);

		printf_s("%s\t%s\t%d��\n",
			cityNames[i].c_str(),
			conditions[i].c_str(),
			tempuratures[i]);

		if (highest < tempuratures[i]) {
			highestIndex = i;
		}
	}

	Test2(cityNames[highestIndex]);

	printf_s("�ł��C���������ꏊ�� %s �ł�\n", cityNames[highestIndex].c_str());
}
