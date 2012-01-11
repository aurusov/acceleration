#include <iostream>

typedef double Speed;
typedef double Length;
typedef double Acceleration;
typedef double TimeStep;

static const TimeStep     dT   = 1.0;
static const Length       Xs   = 1000.0;
static const Speed        Vmax = 30.5;
static const Acceleration Amax = 6.0;

static Length       Xm = 0.0;
static Speed        Vm = 0.0;
static Acceleration Am = 0.0;

Acceleration AccelerationNext(Length Li, Speed Vi, Acceleration Ai)
{
	//! ������ � ���� ��� ����� ���������� �� �����
	if (Vi == 0.0 && Ai == 0.0)
		return Amax;

	double dT = 100;
	Acceleration Anext = (2 * Li - 2 * Vi * dT) / dT / dT;

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
		Vnext = Vmax;

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
	while (Vm >= 0.0)
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
