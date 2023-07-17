#pragma once

// ˆÈ‰º‚Ìƒf[ƒ^‚ğƒRƒsƒy‚·‚é
/*

[WEATHER1]
CityName="D–y"
Condition="á"
Temperature=-5

[WEATHER2]
CityName="“Œ‹"
Condition="“Ü‚è"
Temperature=8

[WEATHER3]
CityName="‘åã"
Condition="“Ü‚è"
Temperature=9

[WEATHER4]
CityName="‹“s"
Condition="“Ü‚è"
Temperature=8

[WEATHER5]
CityName="•Ÿ‰ª"
Condition="°‚ê"
Temperature=10

[WEATHER6]
CityName="“ß”e"
Condition="°‚ê"
Temperature=15

*/

// ƒeƒXƒgŠÖ”‚Í•ÏX‚µ‚È‚¢‚Å‚­‚¾‚³‚¢
//------------------------
void Test1(const std::string& cityName, const std::string& condition, int tempurature, int index)
{
	if (index == 0)
	{
		assert(cityName == "D–y");
		assert(condition == "á");
		assert(tempurature == -5);
	}
	else if (index == 1)
	{
		assert(cityName == "“Œ‹");
		assert(condition == "“Ü‚è");
		assert(tempurature == 8);
	}
	else if (index == 2)
	{
		assert(cityName == "‘åã");
		assert(condition == "“Ü‚è");
		assert(tempurature == 9);
	}
	else if (index == 3)
	{
		assert(cityName == "‹“s");
		assert(condition == "“Ü‚è");
		assert(tempurature == 8);
	}
	else if (index == 4)
	{
		assert(cityName == "•Ÿ‰ª");
		assert(condition == "°‚ê");
		assert(tempurature == 10);
	}
	else if (index == 5)
	{
		assert(cityName == "“ß”e");
		assert(condition == "°‚ê");
		assert(tempurature == 15);
	}
	else
	{
		assert(false);
	}
}

void Test2(const std::string cityName)
{
	assert(cityName == "“ß”e");
}
//------------------------
