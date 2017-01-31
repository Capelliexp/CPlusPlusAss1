#include <string>
#include <iostream>
#include <algorithm>
#include "TimberRegister.h"

TimberRegister::TimberRegister(){

}

TimberRegister::~TimberRegister(){
	for (int i = 0; i < size; i++) {
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

	size++;
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

void TimberRegister::CreateImage(){

}

void TimberRegister::RestoreImage(){

}
