#include "Instancia.h"

Instancia::Instancia()
{
	float tx, ty = 0;
	float ex, ey = 1;
	float angulo = 0;
}

Instancia::~Instancia()
{

}

float Instancia::getTx(void)
{
	return tx;
}

float Instancia::getTy(void)
{
	return ty;
}

float Instancia::getEx(void)
{
	return ex;
}

float Instancia::getEy(void)
{
	return ey;
}

float Instancia::getAngulo(void)
{
	return angulo;
}

void Instancia::incrementaAngulo()
{
	angulo += 1;
}

void Instancia::decrementaAngulo()
{
	angulo -= 1;
}

void Instancia::incrementaTx()
{
	tx += 0.1;
}

void Instancia::incrementaTy()
{
	ty += 0.1;
}

void Instancia::incrementaEx()
{
	ex += 0.1;
}

void Instancia::incrementaEy()
{
	ey += 0.1;
}

void Instancia::decrementaTx()
{
	tx -= 0.1;
}

void Instancia::decrementaTy()
{
	ty -= 0.1;
}

void Instancia::decrementaEx()
{
	ex -= 0.1;
}

void Instancia::decrementaEy()
{
	ey -= 0.1;
}
