#include <iostream>
#include <SFML/Graphics.hpp>

class AnimatedText
{
private:
	sf::Text a_text;
	sf::Font a_font;
	std::string a_full_text;
	std::string a_current_text = "";
	float a_duration;
	int a_length;
	sf::Time a_frequency;
	int a_count = 0;
	sf::Clock a_clock;

public:
	AnimatedText(std::string text, float duration)
	{
		a_full_text = text;
		a_duration = duration;
		a_length = text.size();
		a_frequency = sf::milliseconds(a_duration / a_length);
		a_font.loadFromFile("BebasNeue-Regular.ttf");
		a_text.setFont(a_font);
		a_text.setString(a_current_text);
		a_text.setCharacterSize(24);
		a_text.setFillColor(sf::Color::Blue);
	}

	void changeText()
	{
		if (a_count != a_length)
		{
			if (a_clock.getElapsedTime() == a_frequency)
			{
				a_count++;
				a_clock.restart();
				a_current_text = a_full_text.substr(0, a_count);
				std::cout << a_current_text << ".";
			}
		}
	}

	sf::Text getText()
	{
		return a_text;
	}

	//void drawText()
	//{
	//	
	//}

};

int main()
{
    unsigned int w_width = 800, w_height = 500;
	sf::RenderWindow window(sf::VideoMode(w_width, w_height), "laba1");
	AnimatedText text("Hello world!", 13);
    while (window.isOpen())
    {
        sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		text.changeText();
        window.draw(text.getText());
        window.display();
    }

    return 0;
}