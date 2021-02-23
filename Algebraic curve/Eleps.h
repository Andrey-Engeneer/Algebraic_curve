#pragma once

#include "Curve_second_order.h"


class Eleps : public Curve_second_order
{
public:
	Eleps()
	{
		name_curve = "Eleps";
		a_half_axis = 2;
		b_half_axis = 1;
	}

	Eleps(set_coord in_plot) :Curve_second_order(in_plot)
	{
		name_curve = "Eleps";
		calc_coef();
	};
	~Eleps()
	{};

	coordinate calc_coord(float param) override;

	set_coord calc_tangent_vector(float param) override;

	bool closure_curve() override
	{
		return true;
	}
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