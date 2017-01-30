#ifndef TIMBER_H
#define TIMBER_H

#include <string>

class Timber {
private:
	std::string name;
	std::string dimensions;
	float length;
	float price;
	//Timber();
public:
	Timber(std::string name = "new timber", std::string dimensions = "0x0", float length = 0, float price = 0);
	~Timber();
	Timber(Timber &obj);
	int operator=(Timber &other);

	std::string getName();
	std::string getDimensions();
	float getLength();
	float getPrice();

	void setName(std::string newName);
	void setDimensions(std::string newDimensions);
	void setLength(float newLength);
	void setPrice(float newPrice);

	std::string toString();

};

#endif // TIMBER_H