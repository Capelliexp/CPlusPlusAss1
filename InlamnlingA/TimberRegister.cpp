#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "TimberRegister.h"

TimberRegister::TimberRegister(int startCapacity){
	this->size = 0;
	this->freeSpace = startCapacity;
	this->timberArray = new Timber*[startCapacity];
}

TimberRegister::~TimberRegister(){
	for(int i = 0; i < (size + freeSpace); i++){
		delete timberArray[i];
	}
	delete[] this->timberArray;
}

int TimberRegister::AddTimber(std::string dimensions, float amount, float price){
	for (int i = 0; i < size; i++) {
		if (timberArray[i]->GetDimensions() == dimensions) {
			return -1;
		}
	}

	if (freeSpace > 0) {
		//skapa det nya Timber-objektet
		Timber* newTimber = new Timber(dimensions, amount, price);

		//sätt in det nya Timber-objektet i timberArray
		timberArray[size] = newTimber;

		this->size = this->size + 1;
		freeSpace--;
	}
	else {
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
		Timber* newTimber = new Timber(dimensions, amount, price);

		//sätt in det nya Timber-objektet i timberArray
		timberArray[size] = newTimber;

		this->size = this->size + 1;

		//radera den temporära Timber-arrayen
		delete[] temp;
	}

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

int TimberRegister::RemoveTimber(std::string timberDimensions){
	int iterator = -1;
	for (int i = 0; i < size; i++) {
		if (timberArray[i]->GetDimensions() == timberDimensions) {
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
		if (timberArray[i]->GetDimensions() == timberName) {
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

	std::ofstream Image;
	Image.open(file);

	if (Image.is_open()){
		Image << std::to_string(size) << "\n";
		for (int i = 0; i < size; i++) {
			Image << timberArray[i]->GetDimensions() << "|";
			Image << timberArray[i]->GetAmount() << "|";
			Image << timberArray[i]->GetPrice() << "\n";
		}
		Image.close();
	}
}

void TimberRegister::RestoreImage(std::string &file) {
	//http://www.cplusplus.com/reference/string/string/getline/
	//http://www.cplusplus.com/reference/fstream/ifstream/

	for (int i = 0; i < size; i++){
		delete timberArray[i];
	}
	delete[] this->timberArray;
	size = 0;

	int nrOfElements = 0;
	std::string number;
	std::string row;
	std::string savedDimension;
	std::string savedAmount;
	std::string savedPrice;
	size_t pos;

	std::ifstream Image;
	Image.open(file);

	if (Image.is_open()){
		std::getline(Image, number);
		nrOfElements = std::stoi(number);
		this->timberArray = new Timber*[size];
		for (int i = 0; i < nrOfElements; i++) {
			std::getline(Image, row);

			pos = row.find("|");
			savedDimension = row.substr(0, pos);
			row = row.substr(pos + 1);

			pos = row.find("|");
			savedAmount = row.substr(0, pos);

			savedPrice = row.substr(pos + 1);

			AddTimber(savedDimension, strtof((savedAmount).c_str(), 0), strtof((savedPrice).c_str(), 0));
		}
		Image.close();
	}
}

int TimberRegister::CheckTimberDimensions(std::string dim) {
	for (int i = 0; i < this->size; i++) {
		if (timberArray[i]->GetDimensions() == dim) {
			return -1;
		}
	}
	return 1;
}

int TimberRegister::TestCopyAndAssignment() {
	bool testAssignment = false;
	bool testCopy = false;
	
	Timber *A = new Timber("1x1", 1, 1);
	Timber *B = new Timber("2x2", 2, 2);

	B = A;
	if ((B->GetDimensions() == A->GetDimensions()) && (B->GetAmount() == A->GetAmount())
		&& (B->GetPrice() == A->GetPrice())) {
		testAssignment = true;
	}
	
	Timber *C = new Timber(*A);
	if ((C->GetDimensions() == A->GetDimensions()) &&	(C->GetAmount() == A->GetAmount())
		&& (C->GetPrice() == A->GetPrice())){
		testCopy = true;
	}

	if (testAssignment == true && testCopy == true) {
		return 1;
	}

	return -1;
}
