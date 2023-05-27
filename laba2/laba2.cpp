//������������ ������ �2
//������������ string�
//
//���������� ����� String ��� ������ �� ��������.
//�������� ����, ��� std::string ��� ���������� ������������ ������, ������ char.
//
//� ��� ������ ���� ����������� :
//1.	������� �����������
//2.	����������� �����������(������� 3 - �)
//3.	�������� ������������ ������������(������� 3 - �)
//4.	����������(������� 3 - �)
//5.	��������� + � +=
//6.	��������[] � ������ � ��������� ��������
//7.	��������� <, >, ==
//8.	��������� ����� � ������ � �����
//9.	����� find � ����� ������� ��������� ������� � ������ �����
//10.	 ����� length � ����� ������
//11.	 ����� c_str � �������� ������ char
//12.	 ����� at ��� ��������� �������(������ � ���������) � �������� ������ � ��������� �� ����� �� ������� ������
//
//����������������� ������ ������ ������.������ ������ ��������� ����������.

#include <iostream>

class String
{
private:
	size_t s_size = 0;
	char* s_str = nullptr; //why * ?
public:
	friend std::ostream& operator << (std::ostream& out, const String& str); //output using a friend method
	friend std::istream& operator >> (std::istream& in, String& str); //input

	String(const char* str) : s_size(strlen(str)), s_str(new char[s_size + 1]) //base costructor
	{
		std::copy(str, str + s_size + 1, s_str); // +1 for terminating symbol 
	}

	String(char )

	~String() //destructor
	{
		if (s_str != nullptr)
			delete[] s_str;
	}



};

std::ostream& operator << (std::ostream& out, const String & str)
{
	for (int i = 0; i < str.s_size; i++)
	{
		out << str.s_str[i];
	}
	return out;
}

std::istream& operator >> (std::istream& in, String& str)
{
	char* tmp = new char[10000];
	in >> tmp;
	int index = -1;
	for (int i = 0; i < 10000; i++)
	{
		if (tmp[i] == '\0') //entering until a terminating symbol
		{
			index = i;
			break;
		}
	}
	str.s_size = index + 1;
	delete[] str.s_str;
	str.s_str = new char[str.s_size + 1];
	std::copy(tmp, tmp + index + 1, str.s_str);
	delete[] tmp;

	return in;
}

int main()
{


	String string("Hello!");

}