#include "stdafx.h"
#include "Curve_second_order.h"
#include <math.h>
#include <iostream>



bool operator == (const coordinate & point1, const coordinate & point2)
{
	return point1.x == point2.x && point1.y == point2.y;
}


void Parabola::calc_coef()
{
	if (Identical_point())
	{
		error_Identical_point();
		calc_coef();
		return;
	}
	float ch3 = (points_plot.coord[1].x - points_plot.coord[0].x);
	float ch2 = points_plot.coord[2].x*(points_plot.coord[2].x - points_plot.coord[0].x - points_plot.coord[1].x) + points_plot.coord[0].x*points_plot.coord[1].x;
	float ch1 = (points_plot.coord[2].x*(points_plot.coord[1].y - points_plot.coord[0].y) + points_plot.coord[1].x*points_plot.coord[0].y - points_plot.coord[0].x*points_plot.coord[1].y) / ch3;
	
	if (ch3 == 0 || ch2 == 0)
	{
		error_construction_curve("Parabola");
		calc_coef();
		return;
	}
	coeff_curve.a11 = (points_plot.coord[2].y - ch1) / ch2;
	coeff_curve.a13 = (points_plot.coord[1].y - points_plot.coord[0].y) / (points_plot.coord[1].x - points_plot.coord[0].x) - coeff_curve.a11*(points_plot.coord[0].x + points_plot.coord[1].x);
	coeff_curve.a33 = (points_plot.coord[1].x*points_plot.coord[0].y-points_plot.coord[0].x*points_plot.coord[1].y)/(points_plot.coord[1].x-points_plot.coord[0].x)+coeff_curve.a11*points_plot.coord[0].x*points_plot.coord[1].x;
}

coordinate Parabola::calc_coord(float param)// проверить на все параметры
{
	coordinate result;
	result.y = pow(param, 2) * coeff_curve.a11 + coeff_curve.a13 * param + coeff_curve.a33;
	result.x = param;
	return result;
}

set_coord Parabola::calc_tangent_vector(float param)
{
	coordinate point = calc_coord(param);
	set_coord vector;
	vector.coord[0] = point;
	vector.coord[1] = point_tangent(point);
	return vector;
}

coordinate Parabola::point_tangent(coordinate point)
{
	coordinate second_point;
	if (point.x != 0)
		second_point.x = 0;
	else
		second_point.x = 1;
	second_point.y = (2* coeff_curve.a11*point.x+ coeff_curve.a13)*second_point.x+ coeff_curve.a33- coeff_curve.a11*pow(point.x,2);
	return second_point;
}




coordinate Eleps::calc_coord(float param)
{
	while (param < 0 || param > 2 * pi)
		param=error_parametr_curve(0, 2 * pi);
	coordinate result;
	result.x = a_half_axis*cos(param);
	result.y = b_half_axis*sin(param);
	return result;
}

set_coord Eleps::calc_tangent_vector(float param)
{
	coordinate point = calc_coord(param);
	set_coord vector;
	
	vector.coord[0] = point;
	if (point.y != 0)
	vector.coord[1] = point_tangent(point);
	else
	{
		vector.coord[1].x = vector.coord[0].x + 1;
		vector.coord[1].y = 0;
	}
	return vector;
}

coordinate Eleps::point_tangent(coordinate point)
{
	coordinate second_point;
	if (point.x != 0)
		second_point.x = 0;
	else
		second_point.x = 1;

	second_point.y = pow(b_half_axis, 2)*point.x*(second_point.x - point.x) / (pow(a_half_axis, 2)*point.y) + point.y;
	return second_point;
}

void Eleps::calc_coef()
{
	int num = 1;
	int mir = 2;
	float brige;
	if (Identical_point())
	{
		error_Identical_point();
		calc_coef();
		return;
	}
	if (abs(points_plot.coord[0].x) == abs(points_plot.coord[1].x) && abs(points_plot.coord[0].y) == abs(points_plot.coord[1].y))
	{
		num = 2;
		mir = 1;
	}
	float d, d1, d2;
	d = points_plot.coord[0].x * points_plot.coord[num].y - points_plot.coord[num].x * points_plot.coord[0].y;
	d1 = points_plot.coord[num].y - points_plot.coord[0].y;
	d2 = points_plot.coord[0].x - points_plot.coord[num].x;
	if (d1 == 0 && d2 == 0 || d == 0)
	{
		error_construction_curve(name_curve);
		calc_coef();
		return;
	}

	a_half_axis = d /d1;
	b_half_axis = d / d2;
	
	if (abs(pow(points_plot.coord[mir].x, 2) / pow(a_half_axis, 2) + pow(points_plot.coord[mir].y, 2) / pow(b_half_axis, 2) - 1)>0.0001)
	{
			error_construction_curve(name_curve);
			calc_coef();
			return;
	}


}

