//Лабораторная работа №2
//«Самодельный string»
//
//Реализуйте класс String для работы со строками.
//Понятное дело, что std::string для реализации использовать нельзя, только char.
//
//У вас должны быть реализованы :
//1.	Базовый конструктор
//2.	Конструктор копирования(правило 3 - х)
//3.	Оператор присваивания копированием(правило 3 - х)
//4.	Деструктор(правило 3 - х)
//5.	Операторы + и +=
//6.	Оператор[] – чтение и изменение элемента
//7.	Операторы <, >, ==
//8.	Операторы ввода и вывода в поток
//9.	Метод find – поиск первого вхождения символа в строку слева
//10.	 Метод length – длина строки
//11.	 Метод c_str – получить массив char
//12.	 Метод at для получения доступа(чтение и изменение) к элементу строки с проверкой на выход за пределы строки
//
//Продемонстрируйте работу вашего класса.Будьте готовы объяснить написанное.

#include <iostream>

class String
{
private:
	size_t s_size = 0;
	char* s_str = nullptr; //why * ? because of dynamic memory

public:
	friend std::ostream& operator << (std::ostream& out, const String& str); //output using a friend method
	friend std::istream& operator >> (std::istream& in, String& str); //input

	String(const char* str) : s_size(strlen(str)), s_str(new char[s_size + 1])		//base costructor
	{
		/*std::cout << "Constructor 1\n";*/
		std::copy(str, str + s_size + 1, s_str); // +1 for terminating symbol 
	}

	String(char symbol, size_t size) : s_size(size), s_str(new char[size + 1])
	{
		/*std::cout << "Constructor 2\n";*/
		std::fill(s_str, s_str + s_size, symbol);		//assign the value in the range
		s_str[size] = '\0';	//add the terminating symbol at the end
	}

	String(const String& other) : String(other.s_str)		//copy constructor + delegating constructor
	{
		/*std::cout << "Constructor copy\n";*/
	}

	~String()		//destructor
	{
		/*std::cout << "Destructor\n";*/
		if (s_str != nullptr)
			delete[] s_str;
	}

	String& operator = (String temp)		//copy assignment operator
	{
		std::swap(s_size, temp.s_size);
		std::swap(s_str, temp.s_str);
		return *this;
	}

	String& operator += (const String& other)
	{
		size_t size = this->s_size + other.s_size;
		String temp('a', size);
		for (int i = 0; i < this->s_size; i++)
		{
			temp.s_str[i] = this->s_str[i];
		}

		for (int i = 0; i < other.s_size; i++)
		{
			temp.s_str[i + this->s_size] = other.s_str[i];
		}

		std::swap(this->s_size, temp.s_size);
		std::swap(this->s_str, temp.s_str);
		return *this;
	}

	String operator + (const String& other) const		//const method doesn't change the elements
	{
		String temp = *this;
		temp += other;
		return temp;
	}

	String operator + (const char* other) const
	{
		String temp1 = *this;
		String temp2(other);
		temp1 += temp2;
		return temp1;
	}

	char& operator [] (size_t element)
	{
		return this->s_str[element];
	}

	bool operator > (const String& other)
	{
		if (this->s_size > other.s_size) { return true; }
		else if (this->s_size < other.s_size) { return false; }
		else if (this->s_size == other.s_size)
		{
			for (int i = 0; i < this->s_size; i++)
			{
				if (int(this->s_str[i]) > int(other.s_str[i])) { return true; }
				if (int(this->s_str[i]) < int(other.s_str[i])) { return false; }
				if (int(this->s_str[i]) == int(other.s_str[i])) { continue; }
			}
			return false;
		}
	}

	bool operator < (const String& other)
	{
		if (this->s_size < other.s_size) { return true; }
		else if (this->s_size > other.s_size) { return false; }
		else if (this->s_size == other.s_size)
		{
			for (int i = 0; i < this->s_size; i++)
			{
				if (int(this->s_str[i]) < int(other.s_str[i])) { return true; }
				if (int(this->s_str[i]) > int(other.s_str[i])) { return false; }
				if (int(this->s_str[i]) == int(other.s_str[i])) { continue; }
			}
			return false;
		}
	}

	bool operator == (const String& other)
	{
		if (this->s_size != this->s_size) { return false; }
		for (int i = 0; i < this->s_size; i++)
		{
			if (this->s_str[i] != other.s_str[i]) { return false; }
		}
		return true;
	}

	size_t length()
	{
		return s_size;
	}

	char* c_str()
	{
		return s_str;
	}

	size_t at(char temp)
	{
		for (int i = 0; i < this->s_size; i++)
		{
			if (this->s_str[i] == temp)
			{
				return i;
			}
		}
		return -1; //if wasn't found
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
	String s1("Hello world!");
	String s2 = s1;
	String s3('a', 5);
	std::cout << s1 << " " << s2 << " " << s3 << "\n";
	s2 = s3 + "!!!";
	std::cout << s2 << "\n";
	std::cout << (s2 == s3) << "\n";
	std::cout << s1.at('w') << "\n";
	std::cin >> s3;
	std::cout << s3;
	return 0;
}