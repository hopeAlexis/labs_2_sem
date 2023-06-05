//Лабораторная работа №3
//«Комплексные числа»
//
//Реализуйте класс Complex для работы с комплексными числами.Он должен включать :
//
//1.	Базовый конструктор
//2.	Конструктор копирования
//3.	Оператор присваивания копированием
//4.	Деструктор
//5.	Операторы += и + , *= и *
//6.	Оператор ++ префиксный и постфиксный(увеличение действительной части числа на 1)
//7.	Операторы ввода и вывода
//
//Продемонстрируйте работу с классом.

#include <iostream>

class Complex
{
private:

	long long c_re = 0;	
	long long c_im = 0;	

public:

	friend std::ostream& operator << (std::ostream& out, const Complex& c); //output using a friend method
	friend std::istream& operator >> (std::istream& in, Complex& c); //input

	Complex() : c_re(0), c_im(0) { }		// default constructor (complex number zero)

	Complex(long long re, long long im) : c_re(re), c_im(im) { }

	Complex(long long re) : c_re(re), c_im(0) { } //real number constructor

	~Complex() { }		// default destructor

	Complex(const Complex& other) : Complex(other.c_re, other.c_im) {}		// copy constructor

	Complex& operator = (const Complex& other)		// copy assignment operator
	{
		Complex temp = other;
		std::swap(this->c_re, temp.c_re);
		std::swap(this->c_im, temp.c_im);
		return *this;
	}

	Complex& operator += (const Complex& other)
	{
		long long re = this->c_re + other.c_re;
		long long im = this->c_im + other.c_im;
		Complex temp(re, im);
		std::swap(this->c_re, temp.c_re);
		std::swap(this->c_im, temp.c_im);
		return *this;
	}

	Complex operator + (const Complex& other) const
	{
		Complex temp = *this;
		temp += other;
		return temp;

	}

	Complex& operator *= (const Complex& other)		// (a + Ai)*(b + Bi) = a*b + (a*B + b*A)*i - A*B, i*i = 1
	{
		long long re = this->c_re * other.c_re - this->c_im * other.c_im; // a*b - A*B
		long long im = this->c_im * other.c_re + this->c_re * other.c_im; // a*B*i + A*b*i
		Complex tmp(re, im);
		std::swap(this->c_re, tmp.c_re);
		std::swap(this->c_im, tmp.c_im);
		return *this;
	}

	Complex operator * (const Complex& other) const
	{
		Complex temp = *this;
		temp *= other;
		return temp;
	}

	Complex& operator ++ ()		// префикс, сначала прибавляем к значению m_re 1, затем возвращаем ссылку на объект
	{
		this->c_re++;
		return *this;
	}

	Complex operator ++ (int)	// постфикс, сначала присваиваем новому объекту значение m_re, затем прибавляем 1
	{
		Complex temp = *this;
		++this->c_re;
		return temp;
	}
};

std::ostream& operator << (std::ostream& out, const Complex& complex)
{
	if (complex.c_im < 0)
	{
		out << complex.c_re << " - " << complex.c_im * (-1) << "i";
	}
	else
	{
		out << complex.c_re << " + " << complex.c_im << "i";
	}
	return out;
}

std::istream& operator >> (std::istream& in, Complex& c)
{
	in >> c.c_re;
	in >> c.c_im;
	return in;
}


int main()
{
	Complex c1(1, 2);
	Complex c2(3, 4);
	Complex c3 = c1 + c2;
	std::cout << "c3: " << c3 << std::endl;
	c1 *= c2;
	std::cout << "c: " << c1 << std::endl;
	Complex plusC = ++c1;
	std::cout << "++c: " << plusC << std::endl;
	Complex Cplus = c1++;
	std::cout << "c++: " << Cplus << std::endl;
}
