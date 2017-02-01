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

int TimberRegister::AddTimber(std::string name, std::string dimensions, float amount, float price){
	for (int i = 0; i < size; i++) {
		if (timberArray[i]->GetName() == name) {
			return -1;
		}
	}

	//kopiera all data till temp
	Timber** temp = new Timber*[size];
	for (int i = 0; i < size; i++) {
		temp[i] = timberArray[i];
	}

	//radera gamla timberArray
	delete[] this->timberArray;

	//öka storlek på timberArray och kopiera tillbaka allting från temp till timberArray
	this->timberArray = new Timber*[size + 1];

	for (int i = 0; i < size; i++) {
		timberArray[i] = temp[i];
	}

	//skapa det nya Timber-objektet
	Timber* newTimber = new Timber(name, dimensions, amount, price);

	//sätt in det nya Timber-objektet i timberArray
	timberArray[size] = newTimber;

	this->size = this->size + 1;

	//radera den temporära Timber-arrayen
	delete[] temp;

	return 1;
}

std::string TimberRegister::ReturnTimber(){
	std::string returnString = "";
	for (int i = 0; i < size; i++) {
		returnString += timberArray[i]->ToString() + "\n";
	}
	return returnString;
}

std::string TimberRegister::ReturnTimberUnderLimit(float lowLimit){
	std::string returnString = "";
	for (int i = 0; i < size; i++) {
		if (timberArray[i]->GetAmount() < lowLimit) {
			returnString += timberArray[i]->ToString() + "\n";
		}
	}
	return returnString;
}

float TimberRegister::TotalCost(){
	float totalCost = 0;
	for (int i = 0; i < size; i++) {
		totalCost = totalCost + ((timberArray[i]->GetPrice())*(timberArray[i]->GetAmount()));
	}
	return totalCost;
}

int TimberRegister::RemoveTimber(std::string timberName){
	int iterator = -1;
	for (int i = 0; i < size; i++) {
		if (timberArray[i]->GetName() == timberName) {
			iterator = i;
			i = size;
		}
	}
	if (iterator == -1) {
		return -1;
	}

	//skapa en temporär timberArray
	Timber** temp = new Timber*[size - 1];

	//Fyll temp med alla värden förutom den på plats "iterator"
	for (int i = 0; i < iterator; i++) {
		temp[i] = this->timberArray[i];
	}
	for (int i = iterator + 1; i < size; i++) {
		temp[i-1] = timberArray[i];
	}

	//radera timberArray och timber-objektet som ska bort
	delete timberArray[iterator];
	delete[] this->timberArray;

	//skapa timberArray igen med ny size
	this->timberArray = new Timber*[size - 1];

	//fyll timberArray med rätt värden
	for (int i = 0; i < (size - 1); i++) {
		timberArray[i] = temp[i];
	}

	//radera temp
	delete[] temp;

	//reducera size
	this->size = this->size - 1;

	return 1;
}

int TimberRegister::ModifyTimber(std::string timberName, float newPrice, float newLength){
	for (int i = 0; i < size; i++) {
		if (timberArray[i]->GetName() == timberName) {
			timberArray[i]->SetPrice(newPrice);
			timberArray[i]->SetAmount(newLength);
			return 1;
		}
	}
	return -1;
}

void TimberRegister::CreateImage(std::string &file) {
	//http://www.cplusplus.com/reference/fstream/ofstream/
	//http://www.cplusplus.com/reference/string/to_string/

	std::ofstream Image(file);
	if (Image.is_open()) {
		Image << std::to_string(size) << "\n";
		for (int i = 0; i < size; i++) {
			Image << timberArray[i]->GetName() << "\n";
			Image << timberArray[i]->GetDimensions() << "\n";
			Image << timberArray[i]->GetAmount() << "\n";
			Image << timberArray[i]->GetPrice() << "\n";
		}
		Image.close();
	}
}

void TimberRegister::RestoreImage(std::string &file) {
	//http://www.cplusplus.com/reference/string/string/getline/
	//http://www.cplusplus.com/reference/fstream/ifstream/

	for (int i = 0; i < size; i++) {
		delete timberArray[i];
	}
	delete[] this->timberArray;

	std::string number;
	std::string string1;
	std::string string2;
	std::string string3;
	std::string string4;
	size = 0;
	int counter = 0;

	std::ifstream Image(file);
	if (Image.is_open())
	{
		std::getline(Image, number);
		counter = std::stoi(number);
		this->timberArray = new Timber*[size];
		for (int i = 0; i < counter; i++) {
			std::getline(Image, string1);
			std::getline(Image, string2);
			std::getline(Image, string3);
			std::getline(Image, string4);
			AddTimber(string1, string2, strtof((string3).c_str(), 0), strtof((string4).c_str(), 0));
		}
		Image.close();
	}
}

int TimberRegister::CheckTimberName(std::string name) {
	for (int i = 0; i < this->size; i++) {
		if (timberArray[i]->GetName() == name) {
			return -1;
		}
	}
	return 1;
}

int TimberRegister::TestCopyAndAssignment() {
	Timber *A = new Timber("test1N", "test1D", 1, 1);
	Timber *B = new Timber("test2N", "test2D", 2, 2);
	B = A;
	
	Timber *C = new Timber(*B);

	if ((C->GetName() == A->GetName()) && (C->GetDimensions() == A->GetDimensions())
		&&	(C->GetAmount() == A->GetAmount()) && (C->GetPrice() == A->GetPrice())){
		return 1;
	}

	return -1;
}
