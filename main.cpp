#include <iostream>
#include <math.h>

typedef double Speed;
typedef double Length;
typedef double Acceleration;
typedef double TimeStep;

static const TimeStep     dT   = 1.0;
static const Length       Xs   = 1000.0;
static const Speed        Vmax = 30.5;
static const Speed        Vmin = 0.0;
static const Acceleration Amax = 6.0;

static Length       Xm = 0.0;
static Speed        Vm = 0.0;
static Acceleration Am = 0.0;

//! Тормозной путь
//! param  V - текущая скросроть автомобиля
//! result     величина тормозного пути
Length brakingDistance(Speed V)
{
	return (V * V) / (2 * Amax);
}

Acceleration AccelerationNext(Length Li, Speed Vi, Acceleration Ai)
{
	Length Lb = brakingDistance(Vi);

	Acceleration Anext;

	Length delta        = Li - Lb;
	Length deltaAbs     = fabs(delta);
	Length minPrecision = Vi * dT;

	if (delta <= 0.0)
	{
		Anext = -Amax;
	}
	else if (delta > 0.0)
	{
		Anext = Amax;
	}
	else
	{
		Anext = Ai;
	}

	if (Anext > Amax)
		Anext = Amax;

	if (Anext < -Amax)
		Anext = -Amax;

	return Anext;
}

Speed SpeedNext(Length Li, Speed Vi, Acceleration Ai)
{
	Speed Vnext = Ai * dT + Vi;
	if (Vnext > Vmax)
	{
		Vnext = Vmax;
	}
	else if (Vnext < -Vmin)
	{
		Vnext = -Vmin;
	}
	else if (fabs(Vnext) < 0.1)
	{
		Vnext = 0.0;
	}

	return Vnext;
}

Length LengthNext(Length Li, Speed Vi, Acceleration Ai)
{
	Length Lnext = Vi * dT + fabs(Ai) * dT * dT / 2;
	return Lnext;
}

void main()
{
	Length delta = Xs - Xm;
	while (true)
	{
		Acceleration Anext = AccelerationNext(delta, Vm, Am);
		Speed        Vnext = SpeedNext       (delta, Vm, Anext);
		Length       Lnext = delta - LengthNext(delta, Vnext, Anext);

		Am = AccelerationNext(Lnext, Vnext, Anext);
		Vm = SpeedNext       (delta, Vm, Am);
		if (Vm >= Vmax)
		{
			Am = 0.0;
		}
		else if (Vm <= -Vmin)
		{
			Am = 0.0;
		}
		Xm += LengthNext(delta, Vm, Am);

		std::cout << "Am = " << Am << "   "
		          << "Vm = " << Vm << "   "
		          << "Xm = " << Xm << "   "
		          << std::endl;

		delta = Xs - Xm;

		if (fabs(Vm) == 0.0)
			break;
	}
}
