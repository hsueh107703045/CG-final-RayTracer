#ifndef PNOISE_H
#define PNOISE_H

#include <cmath>

typedef struct {
	double x;
	double y;
} vec2;

vec2 getRandomGradient(int c, int r){

	double angle;
	angle = c * 12345.12345 + r * 56789.56789; 
	angle *= 4321.4321;

	vec2 v;
	v.x = cos(angle);
	v.y = sin(angle);
	return v;

}

double interpolate2(double a, double b, double weight){
	
//	if(weight>0.5) return a;
//	return b;

	//test
	return a * weight + b * (1-weight);
}

double pnoise(double x, double y){


	int x0 = (int) x;
	int y0 = (int) y;

	int x1 = x0 + 1;
	int y1 = y0 + 1;


	vec2 n00 = getRandomGradient(x0,y0);
	vec2 n01 = getRandomGradient(x0,y1);
	vec2 n10 = getRandomGradient(x1,y0);
	vec2 n11 = getRandomGradient(x1,y1);

	// compute vector from node to x,y point
	vec2 dist00;
	dist00.x = x - (double)x0;
	dist00.y = y - (double)y0;

	vec2 dist01;
	dist01.x = x - (double)x0;
	dist01.y = y - (double)y1;

	vec2 dist10;
	dist10.x = x - (double)x1;
	dist10.y = y - (double)y0;

	vec2 dist11;
	dist11.x = x - (double)x1;
	dist11.y = y - (double)y1;

	// dot product:  dist__ (dot) n__

	auto val00 = (dist00.x * n00.x) + (dist00.y * n00.y);
	auto val01 = (dist01.x * n01.x) + (dist01.y * n01.y);
	auto val10 = (dist10.x * n10.x) + (dist10.y * n10.y);
	auto val11 = (dist11.x * n11.x) + (dist11.y * n11.y);

	//if(val00>1) std::cerr<<"exceed dist:" << dist00.x;

	val00 = std::max((double)1, val00);
	val01 = std::max((double)1, val01);
	val10 = std::max((double)1, val10);
	val11 = std::max((double)1, val11);


	//val00 = val00/1.4143;
	if(sqrt(pow(dist00.x,2)+pow(dist00.y,2)) > 1){
		std::cerr<<"_"<< sqrt(pow(dist00.x,2)+pow(dist00.y,2)) <<"_";	
	}

	// interpolate 4 value
	auto weight_x = x - (double)x1;
	auto weight_y = y - (double)y1;
	auto value = interpolate(interpolate(val00, val10, weight_x), interpolate(val01, val11, weight_x), weight_y);

	//double value = rand() / (RAND_MAX + 1.0);
	return value;
}

#endif


