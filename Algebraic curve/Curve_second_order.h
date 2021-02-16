#pragma once

#define COORDINATE_MAXCOUNT 3
#include <iostream>
#include <string>

struct coordinate
{
	float x;
	float y;
};

struct set_coord
{
	coordinate coord[COORDINATE_MAXCOUNT];
};


class Curve_second_order
{
public:
	Curve_second_order()
	{
		coeff_curve.a11 = 0;
		coeff_curve.a22 = 0;
		coeff_curve.a12 = 0;
		coeff_curve.a13 = 0;
		coeff_curve.a23 = 0;
		coeff_curve.a33 = 0;
	}
	Curve_second_order(set_coord in_plot):points_plot(in_plot)
	{
		coeff_curve.a11 = 0;
		coeff_curve.a22 = 0;
		coeff_curve.a12 = 0;
		coeff_curve.a13 = 0;
		coeff_curve.a23 = 0;
		coeff_curve.a33 = 0;
	}
	~Curve_second_order(){}
	
	virtual coordinate calc_coord(float param) = 0; //вычисление координат точки на кривой по заданному параметру;
	virtual set_coord calc_tangent_vector(float param) = 0;//вычисление точек касательного вектора к кривой для заданному параметру;
	virtual bool closure_curve() = 0;// выдача информации, является ли данная кривая замкнутой.

protected:
	bool Identical_point() //проверка на совпадение исходных точек
	{
		if (points_plot.coord[0] == points_plot.coord[1] || points_plot.coord[1] == points_plot.coord[2] ||
			points_plot.coord[0] == points_plot.coord[2])
			return true;
		return false;
	}
	virtual void calc_coef()=0; // расчёт коэффициентов уравнения
	friend bool operator == (const coordinate &point1, const coordinate &point2);

	void input_points_plot()// запрос новых точек
	{
		for (int i = 0; i < COORDINATE_MAXCOUNT; i++)
		{
			std::cout << "Введите х" <<i+1<< std::endl;

			while (!(std::cin >> points_plot.coord[i].x) || (std::cin.peek() != '\n'))
			{
				std::cin.clear();
				while (std::cin.get() != '\n');
				std::cout << "Input error! Repeat please...\n";
			}

			std::cout << std::endl << "Введите y" <<i+1<< std::endl;

			while (!(std::cin >> points_plot.coord[i].y) || (std::cin.peek() != '\n'))
			{
				std::cin.clear();
				while (std::cin.get() != '\n');
				std::cout << "Input error! Repeat please...\n";
			}
			std::cout << std::endl;
		}
	}

	void error_Identical_point()// обработка случая одинаковых точек
	{
		std::cout << "Введены одинаковые точки. Введите новые"<< std::endl;
		input_points_plot();
	}
	void error_construction_curve(std::string curve)// обработка случая несоответствия точек заданной кривой
	{
		std::cout << "По данным точкам невозможо построить "<< curve<<", введите другие точки"<<std::endl;
		input_points_plot();
	}
	float error_parametr_curve(float min, float max)// обработка случая выхода параметра за пределы
	{
		float result;
		std::cout << "Выход параметра за пределы от" << min << " до " << max <<". Введите параметр в заданных пределах"<< std::endl;
		while (!(std::cin >> result) || (std::cin.peek() != '\n'))
		{
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "Input error! Repeat please...\n";
		}
		return result;
	}
protected:
	struct  Coeff_curve
	{
		float a11, a22, a12, a13, a23, a33;
	}coeff_curve;//коэффициены уравнения
	set_coord points_plot;//заданныe точки
	std::string name_curve = "Curve_second_order";
	float const pi = 3.1415926535;
};


class Parabola : public Curve_second_order
{
public:
	Parabola()
	{
		name_curve = "Parabola";
		coeff_curve.a11 = 1;
	}

	Parabola(set_coord in_plot):Curve_second_order(in_plot)
	{ 
		name_curve = "Parabola";
		calc_coef();
	}
	~Parabola() {}
	
	
	coordinate calc_coord(float param) override;
	set_coord calc_tangent_vector(float param) override;
	bool closure_curve() override
	{
		return false;
	}

protected:
	
	 void calc_coef() override;
private:
	coordinate point_tangent(coordinate point);//рассчёт точки касательного вектора
};



class Eleps : public Curve_second_order
{
public:
	Eleps() 
	{
		name_curve = "Eleps";
		a_half_axis = 2;
		b_half_axis = 1;
	}

	Eleps(set_coord in_plot):Curve_second_order(in_plot)
	{
		name_curve = "Eleps";
		calc_coef();
	};
	~Eleps() 
	{};

	 coordinate calc_coord(float param) override;

	 set_coord calc_tangent_vector(float param) override;

	 bool closure_curve() override 
	{ return true; }
protected:
	 void calc_coef() override;
	coordinate point_tangent(coordinate point);
	float a_half_axis;
	float b_half_axis;

	
};


class Circle : public Eleps
{
public:
	Circle()
	{

		name_curve = "Circle";
		a_half_axis = 1;
		b_half_axis = a_half_axis;

	}
	Circle(set_coord in_plot)
	{
		points_plot = in_plot;
		name_curve = "Circle";
		bool flag;
		do
		{
			calc_coef();
			if (a_half_axis != b_half_axis)
			{
				error_construction_curve(name_curve);
				flag = true;
			}
			else
			{
				flag = false;
			}
		} while (flag);
	}
	~Circle() 
	{}
	 
};



