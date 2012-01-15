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
//! param  A - ускорение, неизменяемая характеристика автомобиля, зависит от его мощности
//! param  V - текущая скросроть автомобиля
//! result     величина тормозного пути
Length brakingDistance(Acceleration A, Speed V)
{
	return (V * V) / (2 * A);
}

Acceleration AccelerationNext(Length Li, Speed Vi, Acceleration Ai)
{
	//if (Li < 0)
	//	return -Amax;

	Length Lb = brakingDistance(Amax, Vi);

	Acceleration Anext;

	Length delta        = Li - Lb;
	Length deltaAbs     = fabs(delta);
	Length minPrecision = Vi * dT;

	if (delta < minPrecision)
	{
		Anext = -Amax;
	}
	else if (delta > 2 * minPrecision)
	{
		Anext = Amax;
	}
	else
	{
		Anext = Ai;
	}

	if (Li > 0.0 && Li < 3.0)
	{
		Anext = -Amax;
	}

	if (Anext > Amax)
		Anext = Amax;

	if (Anext < -Amax)
		Anext = -Amax;

	return Anext;
}

Speed SpeedNext(Length Li, Speed Vi)
{
	Am = AccelerationNext(Li, Vi, Am);

	Speed Vnext = Am * dT + Vi;
	if (Vnext > Vmax)
	{
		Vnext = Vmax;
		Am    = 0.0;
	}
	else if (Vnext < -Vmin)
	{
		Vnext = -Vmin;
		Am    = 0.0;
	}
	else if (fabs(Vnext) < 0.1)
	{
		Vnext = 0.0;
	}

	return Vnext;
}

Length LengthNext(Length Li)
{
	Vm = SpeedNext(Li, Vm);

	Length Lnext = Vm * dT + Am * dT * dT / 2;
	return Lnext;
}

void main()
{
	Length delta = Xs - Xm;
	while (fabs(Vm) > 0.0 || fabs(delta) > 10.0)
	{
		Xm += LengthNext(delta);
		delta = Xs - Xm;

		std::cout << "Am = " << Am << "   "
		          << "Vm = " << Vm << "   "
		          << "Xm = " << Xm << "   "
		          << std::endl;
	}

	int i = 1;
}
