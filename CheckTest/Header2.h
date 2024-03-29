#pragma once

// 以下のデータをコピペする
/*

[WEATHER1]
CityName="札幌"
Condition="雪"
Temperature=-5

[WEATHER2]
CityName="東京"
Condition="曇り"
Temperature=8

[WEATHER3]
CityName="大阪"
Condition="曇り"
Temperature=9

[WEATHER4]
CityName="京都"
Condition="曇り"
Temperature=8

[WEATHER5]
CityName="福岡"
Condition="晴れ"
Temperature=10

[WEATHER6]
CityName="那覇"
Condition="晴れ"
Temperature=15

*/

// テスト関数は変更しないでください
//------------------------
void Test1(const std::string& cityName, const std::string& condition, int tempurature, int index)
{
	if (index == 0)
	{
		assert(cityName == "札幌");
		assert(condition == "雪");
		assert(tempurature == -5);
	}
	else if (index == 1)
	{
		assert(cityName == "東京");
		assert(condition == "曇り");
		assert(tempurature == 8);
	}
	else if (index == 2)
	{
		assert(cityName == "大阪");
		assert(condition == "曇り");
		assert(tempurature == 9);
	}
	else if (index == 3)
	{
		assert(cityName == "京都");
		assert(condition == "曇り");
		assert(tempurature == 8);
	}
	else if (index == 4)
	{
		assert(cityName == "福岡");
		assert(condition == "晴れ");
		assert(tempurature == 10);
	}
	else if (index == 5)
	{
		assert(cityName == "那覇");
		assert(condition == "晴れ");
		assert(tempurature == 15);
	}
	else
	{
		assert(false);
	}
}

void Test2(const std::string cityName)
{
	assert(cityName == "那覇");
}
//------------------------
