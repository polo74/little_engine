#include "fourrier.hpp"

#define PRECISION 10

void Fourrier::getFrequency(Coord coord[])
{
	int taille = sizeof(coord) / sizeof(coord[0]);
	double a0;
	double an[PRECISION];
	double bn[PRECISION];
	double T;

	T = coord[taille].x - coord[0].x;

	// Calcul de a0 :

	a0 = 0;

	for (int i = 1; i < taille; i++)
	{
		double xa = coord[i-1].x;
		double ya = coord[i-1].y;
		double xb = coord[i].x;
		double yb = coord[i].y;

		double a = (xb - xa) / (yb - ya);
		double b = ya - (a * xa);

		a0 += ((a * b * b) / 2) - ((a * a * a) / 2) + (b * b) - a * b;
	}

	a0 = (1 / T) * a0;

	// Calcul de an
	


}
