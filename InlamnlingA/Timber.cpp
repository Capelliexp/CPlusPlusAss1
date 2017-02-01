#include <string>
#include <iostream>
#include "Timber.h"

Timber::Timber(std::string name, std::string dimensions, float length, float price){
	this->name = name;
	this->dimensions = dimensions;
	this->amount = length;
	this->price = price;
}

Timber::~Timber(){
	//empty
}

Timber::Timber(Timber &newTimberObject){
	this->name = newTimberObject.GetName();
	this->dimensions = newTimberObject.GetDimensions();
	this->amount = newTimberObject.GetAmount();
	this->price = newTimberObject.GetPrice();
}

void Timber::operator=(Timber &newTimberObject) {
	this->name = newTimberObject.GetName();
	this->dimensions = newTimberObject.GetDimensions();
	this->amount = newTimberObject.GetAmount();
	this->price = newTimberObject.GetPrice();
}

std::string Timber::GetName(){
	return name;
}
void Timber::SetName(std::string newName) {
	this->name = newName;
}

std::string Timber::GetDimensions(){
	return dimensions;
}
void Timber::SetDimensions(std::string newDimensions) {
	this->dimensions = newDimensions;
}

float Timber::GetAmount(){
	return amount;
}
void Timber::SetAmount(float newLength) {
	this->amount = newLength;
}

float Timber::GetPrice(){
	return price;
}
void Timber::SetPrice(float newPrice) {
	this->price = newPrice;
}

std::string Timber::ToString() {
	std::string priceString = std::to_string(price);
	priceString.erase(priceString.find_last_not_of('0') + 2, std::string::npos);

	std::string lengthString = std::to_string(amount);
	lengthString.erase(lengthString.find_last_not_of('0') + 2, std::string::npos);

	return("* " + name + " || " + dimensions + " || Price: " + priceString + " sek/m || Remaining length: " + lengthString + " m");
}
