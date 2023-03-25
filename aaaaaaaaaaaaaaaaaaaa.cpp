#include <iostream>
#include <string>

class Cipher
{
private:
	int c_fibonacci[30] = { 1,2 };
	int c_wordAmount = 0;
	std::string c_message = "";
	std::string c_words[30];
	int c_code[30];

	void fiboFinder()
	{
		for (size_t i = 2; i <= c_wordAmount; i++)
		{
			c_fibonacci[i] = c_fibonacci[i - 1] + c_fibonacci[i - 2];
		}
	}

	void wordCount(const std::string& message)
	{
		for (size_t i = 0; i < message.length(); i++)
		{
			if (message[i] == ' ')
			{
				c_wordAmount++;
			}
		}
	}


public:
	Cipher(std::string str)
	{
		c_message = str;
		wordCount(str);
		fiboFinder();

		int count = -1;

		for (size_t i = 0; i < c_wordAmount; i++) //input into c_words array
		{
			count++;
			while (str[count] != ' ')
			{
				if (count >= str.length())
				{
					break;
				}
				c_words[i] += str[count];
				count++;
			}
		}
	}

	void encode()
	{

	}

	void decode()
	{

	}



};




int main()
{
	std::string str;
	std::getline(std::cin, str);
}
