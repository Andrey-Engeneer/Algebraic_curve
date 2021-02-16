// Algebraic curve.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

#include <iostream>
#include <locale.h>

#include "Curve_second_order.h"

using namespace std;
template <typename T>
T input_meaning(T in)// ������ ��������
{ 
	T choice;
	while (!(std::cin >> choice) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Input error! Repeat please...\n";
	}
	return choice;
}

set_coord input_points_plot()// ������ ����� �����
{
	set_coord points_plot;
	for (int i = 0; i < COORDINATE_MAXCOUNT; i++)
	{
		std::cout << "������� �" << i + 1 << std::endl;

		while (!(std::cin >> points_plot.coord[i].x) || (std::cin.peek() != '\n'))
		{
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "Input error! Repeat please...\n";
		}

		std::cout << std::endl << "������� y" << i + 1 << std::endl;

		while (!(std::cin >> points_plot.coord[i].y) || (std::cin.peek() != '\n'))
		{
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "Input error! Repeat please...\n";
		}
		std::cout << std::endl;
	}
	return points_plot;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	set_coord input_points;
	cout << "�������� 3 ����� ��� ���������� ��������" << endl;
	input_points = input_points_plot();
	Parabola parab(input_points);
	cout << "�������� 3 ����� ��� ���������� �������" << endl;
	input_points = input_points_plot();
	Eleps eleps(input_points);
	cout << "�������� 3 ����� ��� ���������� �����" << endl;
	input_points = input_points_plot();
	Circle circle(input_points);
	Curve_second_order *Curve[] = { &parab ,&eleps, &circle };
	
	coordinate out_coord;
	set_coord out_set;

	unsigned int method = 0;
	int i = 0;
	while (i != -1)
	{
		
		do
		{
			cout << "�������� ������" << endl;
			cout << "1-��������" << endl << "2-������" << endl << "3-����" << endl << "0-�����" << endl;
			i = input_meaning(i) - 1;
		} while (i > 2 || i < -1);

		cout << "�������� �����" << endl;
		cout << "1-���������� ��������� ����� �� ������ �� ��������� ���������;" << endl << "2-���������� ������������ ������� � ������ �� ��������� ���������" << endl << "3-������ ����������, �������� �� ������ ������ ���������" << endl;

		method = input_meaning(method);
		float param = 0;
		switch (method)
		{
		case(1): {
			cout << "������� ��������" << endl;
			param = input_meaning(param);
			out_coord = Curve[i]->calc_coord(param);
			cout << "x = " << out_coord.x << "; y  = " << out_coord.y << endl;
			break;
		}
		case(2):
		{
			cout << "������� ��������" << endl;
			param = input_meaning(param);
			out_set = Curve[i]->calc_tangent_vector(param);
			cout <<"x1 = "<< out_set.coord[0].x << " : y1 = " << out_set.coord[0].y << endl <<"x2 = "<< out_set.coord[1].x << " : y2 =" << out_set.coord[1].y << endl;
			break;
		}
		case(3): {
			if (Curve[i]->closure_curve())
				cout << "��������" << endl;
			else
				cout << "�� ��������"<<endl;
			break;
		}
		default:
			break;
		}
	}

    return 0;
}

