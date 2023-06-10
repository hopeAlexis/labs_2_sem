//Лабораторная работа №7
//«Геометрические фигуры»
//
//Используя наследование и полиморфизм, напишите программу, которая работает с геометрическими фигурами :
//1.	Треугольник
//2.	Прямоугольник
//3.	Круг
//
//Программа должна хранить координаты и размеры фигуры, цвет, уметь вычислять площадь фигуры.
//
//Продемонстрируйте, как ваша программа будет выводить на экран площади всех фигур.

#include <iostream>
#define PI 3.14159265359

class GeomShape
{
private:
	float x, y;
	std::string color;
public:
	GeomShape (float x, float y, std::string color) : x(x), y(y), color(color){}
	virtual ~GeomShape()
	{
		std::cout << "Shape destructor";
	}
	virtual float getArea()		//using keyword virtual so that we can alter it in an heir class
	{
		std::cout << "The area of the shape is ";
		return 0;
	}
};

class Triangle : public GeomShape
{
private:
	float sideA, sideB, sideC;
public: 
	Triangle(float x, float y, std::string color, float a, float b, float c) : GeomShape(x, y, color), sideA(a), sideB(b), sideC(c) {};
	~Triangle() override
	{
		std::cout << "Triangle destructor";
	}
	float getArea() override
	{
		std::cout << "The area of the triangle is ";
		float p = (sideA + sideB + sideC) / 2;
		return sqrt(p * (p - sideA) * (p - sideB) * (p - sideC));
	}
};

class Rectangle : public GeomShape
{
private:
	float sideA, sideB;
public:
	Rectangle(float x, float y, std::string color, float a, float b) : GeomShape(x, y, color), sideA(a), sideB(b) {};
	~Rectangle() override
	{
		std::cout << "Rectangle destructor";
	}
	float getArea() override
	{
		std::cout << "The area of the rectangle is ";
		return sideA * sideB;
	}
};

class Circle : public GeomShape
{
private:
	float radius;
public:
	Circle(float x, float y, std::string color, float r) : GeomShape(x, y, color), radius(r) {};
	~Circle() override
	{
		std::cout << "Circle destructor";
	}
	float getArea() override
	{
		std::cout << "The area of the circle is ";
		return PI*radius*radius;
	}
};


int main()
{
	GeomShape* geomShapes[3] = {};	
	geomShapes[0] = new Triangle(0, 0, "violet", 3, 4, 5);
	geomShapes[1] = new Rectangle(0, 0, "aqua", 5.6, 7.123);
	geomShapes[2] = new Circle(0, 0, "turquoise", 1);


	for (int i = 0; i < 3; i++)
	{
		std::cout << geomShapes[i]->getArea() << "\n";
	}

	for (int i = 0; i < 3; i++)
	{
		delete geomShapes[i];
	}

	return 0;
}