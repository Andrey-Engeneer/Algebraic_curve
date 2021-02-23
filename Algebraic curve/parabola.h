#pragma once
#include "Curve_second_order.h"

class Parabola : public Curve_second_order
{
public:
	Parabola()
	{
		name_curve = "Parabola";
		coeff_curve.a11 = 1;
	}

	Parabola(set_coord in_plot) :Curve_second_order(in_plot)
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
