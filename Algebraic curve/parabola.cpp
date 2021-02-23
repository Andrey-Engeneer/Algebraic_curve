#include "stdafx.h"
#include "parabola.h"
void Parabola::calc_coef()
{
	if (Identical_point())
	{
		error_Identical_point();
		calc_coef();
		return;
	}
	float x1 = points_plot.coord[0].x;
	float y1 = points_plot.coord[0].y;
	float x2 = points_plot.coord[1].x;
	float y2 = points_plot.coord[1].y;
	float x3 = points_plot.coord[2].x;
	float y3 = points_plot.coord[2].y;
	float ch3 = (x2 - x1);
	float ch2 = x3*(x3 - x1 - x2) + x1*x2;
	float ch1 = (x3*(y2 - y1) + x2*y1 - x1*x2) / ch3;

	if (ch3 == 0 || ch2 == 0)
	{
		error_construction_curve(name_curve);
		calc_coef();
		return;
	}
	coeff_curve.a11 = (y3 - ch1) / ch2;
	coeff_curve.a13 = (y2 - y1) / (x2 - x1) - coeff_curve.a11 * (x1 + x2);
	coeff_curve.a33 = (x2 * y1 - x1 * y2) / (x2 - x1) + coeff_curve.a11 * x1 * x2;
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
	second_point.y = (2 * coeff_curve.a11*point.x + coeff_curve.a13)*second_point.x + coeff_curve.a33 - coeff_curve.a11*pow(point.x, 2);
	return second_point;
}