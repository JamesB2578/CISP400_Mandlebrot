#include "ComplexPlane.h"
#include <cmath>
#include <iostream>
#include <complex>
#include <sstream>
using namespace std;

ComplexPlane::ComplexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);
	m_view.setCenter(0.0, 0.0);
	m_zoomCount = 0;
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float sizeX = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float sizeY = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_view.setSize(sizeX, sizeY);
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float sizeX = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float sizeY = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_view.setSize(sizeX, sizeY);
}

void ComplexPlane::setCenter(Vector2f coord)
{
	m_view.setCenter(coord.x, coord.y);
}

void ComplexPlane::setMouseLoactaion(Vector2f coord)
{
	m_mouseLocation.x = coord.x;
	m_mouseLocation.y = coord.y;
}

void ComplexPlane::loadText(Text& text)
{
	stringstream ss;
	ss << "Mandelbrot Set\n" << "Center: (" << m_view.getCenter().x << ", " << m_view.getCenter().y << ")\n"
		<< "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")\n"
		<< "Left-click to Zoom in\nRight-click to Zoom out";
	text.setString(ss.str());
}

 size_t ComplexPlane::countIterations(Vector2f coord)
{
	complex<double> c(coord.x, coord.y);
	complex<double> z(0, 0);
	size_t i = 0;

	while (abs(z) < 2 && i < 64)
	{
		z = z * z + c;
		i++;
	}

	return i;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count == 64)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	if (count <= 63 && count >= 57)
	{
		r = 196;
		g = 12;
		b = 12;
	}
	else if (count <= 56 && count >= 49)
	{
		r = 230;
		g = 223;
		b = 46;
	}
	else if (count <= 48 && count >= 41)
	{
		r = 35;
		g = 204;
		b = 43;
	}
	else if (count <= 40 && count >= 33)
	{
		r = 48;
		g = 29;
		b = 219;
	}
	else if (count <= 32 && count >= 25)
	{
		r = 84;
		g = 19;
		b = 207;
	}
	else if (count <= 24 && count >= 17)
	{
		r = 147;
		g = 19;
		b = 207;
	}
	else if (count <= 16 && count >= 9)
	{
		r = 191;
		g = 19;
		b = 207;
	}
	else
	{
		r = 207;
		g = 19;
		b = 131;
	}
}