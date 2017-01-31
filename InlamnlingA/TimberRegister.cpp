#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "TimberRegister.h"

TimberRegister::TimberRegister(){
	this->size = 0;
}

TimberRegister::~TimberRegister(){
	for(int i = 0; i < size; i++){
		delete timberArray[i];
	}
	delete[] this->timberArray;
}

int TimberRegister::AddTimber(std::string name, std::string dimensions, float length, float price){
	for (int i = 0; i < size; i++) {
		if (timberArray[i]->getName() == name) {
			return -1;
		}
	}

	//skapa det nya Timber-objektet
	Timber* newTimber = new Timber(name, dimensions, length, price);

	//kopiera all data till temp
	Timber** temp = new Timber*[size];
	for (int i = 0; i < size; i++) {
		temp[i] = timberArray[i];
	}

	delete[] this->timberArray;

	//öka storlek på timberArray och kopiera tillbaka allting från temp till timberArray
	this->timberArray = new Timber*[size + 1];

	for (int i = 0; i < size; i++) {
		timberArray[i] = temp[i];
	}

	//sätt in det nya Timber-objektet i timberArray
	timberArray[size] = newTimber;

	//radera den temporära Timber-arrayen
	delete[] temp;

	this->size = this->size + 1;
	return 1;
}

std::string TimberRegister::ReturnAllTimber(){
	std::string totalString = "";
	for (int i = 0; i < size; i++) {
		totalString += timberArray[i]->toString() + "\n";
	}
	return totalString;
}

std::string TimberRegister::ReturnLowValueTimber(float lowLimit){
	std::string allLow = "";
	for (int i = 0; i < size; i++) {
		if (timberArray[i]->getLength() < lowLimit) {
			allLow += timberArray[i]->toString() + "\n";
		}
	}
	return allLow;
}

float TimberRegister::TotalCost(){
	float totalCost = 0;
	for (int i = 0; i < size; i++) {
		totalCost = totalCost + ((timberArray[i]->getPrice())*(timberArray[i]->getLength()));
	}
	return totalCost;
}

int TimberRegister::RemoveTimber(std::string timberName){
	int iterator = -1;
	for (int i = 0; i < size; i++) {
		if (timberArray[i]->getName() == timberName) {
			iterator = i;
			i = size;
		}
	}
	if (iterator == -1) {
		return -1;
	}

	size--;
	Timber** temp = new Timber*[size];
	for (int i = 0; i < iterator; i++) {
		temp[i] = timberArray[i];
	}
	for (int i = iterator + 1; i < size+1; i++) {
		temp[i-1] = timberArray[i];
	}
	//delete[] timberArray;
	timberArray = temp;

	return 1;
}

int TimberRegister::ModifyTimber(std::string timberName, float newPrice, float newLength){
	for (int i = 0; i < size; i++) {
		if (timberArray[i]->getName() == timberName) {
			timberArray[i]->setPrice(newPrice);
			timberArray[i]->setLength(newLength);
			return 1;
		}
	}
	return -1;
}

void TimberRegister::CreateImage(std::string &saveFile) {
	std::ofstream Image(saveFile);
	if (Image.is_open()) {
		Image << std::to_string(size) << "\n";
		for (int i = 0; i < size; i++) {
			Image << timberArray[i]->getName() << "\n";
			Image << timberArray[i]->getDimensions() << "\n";
			Image << timberArray[i]->getLength() << "\n";
			Image << timberArray[i]->getPrice() << "\n";
		}
		Image.close();
	}
}

void TimberRegister::RestoreImage(std::string &saveFile) {
	for (int i = 0; i < size; i++) {
		delete timberArray[i];
	}
	delete[] this->timberArray;

	std::string temp;
	std::string temp1;
	std::string temp2;
	std::string temp3;
	std::string temp4;
	size = 0;
	int cntr = 0;

	std::ifstream Image(saveFile);
	if (Image.is_open())
	{
		std::getline(Image, temp);
		cntr = std::stoi(temp);
		this->timberArray = new Timber*[size];
		for (int i = 0; i < cntr; i++) {
			std::getline(Image, temp1);
			std::getline(Image, temp2);
			std::getline(Image, temp3);
			std::getline(Image, temp4);
			AddTimber(temp1, temp2, strtof((temp3).c_str(), 0), strtof((temp4).c_str(), 0));
		}
		Image.close();
	}
}

int TimberRegister::CheckTimberName(std::string name) {
	for (int i = 0; i < this->size; i++) {
		if (timberArray[i]->getName() == name) {
			return -1;
		}
	}
	return 1;
}
