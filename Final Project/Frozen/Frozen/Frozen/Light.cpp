#include "Light.h"





void Light::printLight()
{
	std::cout << "Light\n" << "Position: " << getPosition() << "\nAmbient: " << getAmbient() << "\nDiffuse: " << getDiffuse() << "\nSpecular: " << getSpecular() << "\n";
}

Light::~Light()
{
}
