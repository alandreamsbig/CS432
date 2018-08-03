#ifndef __SQUARE_H__
#define __SQAURE_H__

#include "Angel.h"
#include "Drawable.h"

class Square : public Drawable {  //derived from drawable class


public:

	//constructors
	Square(float rnormalized, float rnomralized);


	//destructor
	~Square();

	void builds();

	void drawSquare();
	void buildSquare();


private:

	vec3 squareLocations[4];


};
#endif
