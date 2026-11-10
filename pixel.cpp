#include "main.h"
/*
* This is the implementation of the Pixel classes.
*/
Pixel::Pixel(LinearAlgebra::Point2D& p, Color& c) : color(c) {
	position.x = p.x;
	position.y = p.y;
}
