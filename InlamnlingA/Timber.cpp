#include <string>
#include <iostream>
#include "Timber.h"

Timber::Timber(std::string name, std::string dimensions, float length, float price){
	this->name = name;
	this->dimensions = dimensions;
	this->length = length;
	this->price = price;
}

Timber::~Timber(){
	//empty
}

Timber::Timber(Timber &obj){
	this->name = obj.getName();
	this->dimensions = obj.getDimensions();
	this->length = obj.getLength();
	this->price = obj.getPrice();
}

int Timber::operator=(Timber &other) {
	this->name = other.getName();
	this->dimensions = other.getDimensions();
	this->length = other.getLength();
	this->price = other.getPrice();
	return 1;
}

//Getters
std::string Timber::getName(){
	return name;
}
std::string Timber::getDimensions(){
	return dimensions;
}
float Timber::getLength(){
	return length;
}
float Timber::getPrice(){
	return price;
}

//Setters
void Timber::setName(std::string newName){
	this->name = newName;
}
void Timber::setDimensions(std::string newDimensions){
	this->dimensions = newDimensions;
}
void Timber::setLength(float newLength){
	this->length = newLength;
}
void Timber::setPrice(float newPrice){
	this->price = newPrice;
}

std::string Timber::toString() {
	return("* " + name + " - " + dimensions + " - Pris: " + std::to_string(price))
		+ " - Resterande längd: " + std::to_string(length);
}
