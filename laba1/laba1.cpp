#include <iostream>
#include <SFML/Graphics.hpp>

class AnimatedText
{
private:
	std::string a_text;
	std::string a_current_text = "";
	float a_duration;
	int a_length;
	float a_frequency;
	int a_count = 0;
	float a_clock;

public:
	AnimatedText(std::string text, float duration)
	{
		a_text = text;
		a_duration = duration;
		a_length = text.size();
		a_frequency = a_duration / a_length;
	}

	//float getFrequency()
	//{
	//	return a_frequency;
	//}

	//int getCount()
	//{
	//	return a_count;
	//}

	void printText()
	{
		if (a_count != a_length)
		{
			if (a_clock = a_frequency)
			{
				a_count++;
				a_clock = 0;
				a_current_text = a_text.substr(0, a_count);

			}
		}
	}

};