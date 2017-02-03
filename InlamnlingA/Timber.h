#ifndef TIMBER_H
#define TIMBER_H

#include <string>

class Timber {
private:
	std::string dimensions;
	float amount;
	float price;
public:
	std::string GetDimensions();
	void SetDimensions(std::string newDimensions);

	float GetAmount();
	void SetAmount(float newLength);

	float GetPrice();
	void SetPrice(float newPrice);
	
	std::string ToString();

	~Timber();
	Timber(std::string dimensions = "0x0", float length = 0.0f, float price = 0.0f);
	Timber(Timber &newTimberObject);
	void operator=(Timber &newTimberObject);

};
#endif // TIMBER_H