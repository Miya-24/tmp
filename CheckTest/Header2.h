#pragma once

// �ȉ��̃f�[�^���R�s�y����
/*

[WEATHER1]
CityName="�D�y"
Condition="��"
Temperature=-5

[WEATHER2]
CityName="����"
Condition="�܂�"
Temperature=8

[WEATHER3]
CityName="���"
Condition="�܂�"
Temperature=9

[WEATHER4]
CityName="���s"
Condition="�܂�"
Temperature=8

[WEATHER5]
CityName="����"
Condition="����"
Temperature=10

[WEATHER6]
CityName="�ߔe"
Condition="����"
Temperature=15

*/

// �e�X�g�֐��͕ύX���Ȃ��ł�������
//------------------------
void Test1(const std::string& cityName, const std::string& condition, int tempurature, int index)
{
	if (index == 0)
	{
		assert(cityName == "�D�y");
		assert(condition == "��");
		assert(tempurature == -5);
	}
	else if (index == 1)
	{
		assert(cityName == "����");
		assert(condition == "�܂�");
		assert(tempurature == 8);
	}
	else if (index == 2)
	{
		assert(cityName == "���");
		assert(condition == "�܂�");
		assert(tempurature == 9);
	}
	else if (index == 3)
	{
		assert(cityName == "���s");
		assert(condition == "�܂�");
		assert(tempurature == 8);
	}
	else if (index == 4)
	{
		assert(cityName == "����");
		assert(condition == "����");
		assert(tempurature == 10);
	}
	else if (index == 5)
	{
		assert(cityName == "�ߔe");
		assert(condition == "����");
		assert(tempurature == 15);
	}
	else
	{
		assert(false);
	}
}

void Test2(const std::string cityName)
{
	assert(cityName == "�ߔe");
}
//------------------------
