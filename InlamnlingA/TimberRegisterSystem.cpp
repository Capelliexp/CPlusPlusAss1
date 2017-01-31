#include <string>
#include <iostream>
#include <crtdbg.h>
#include "TimberRegister.h"

int AddTimber(TimberRegister* A);
int PresentTimber(TimberRegister* A);
int PresentTimberLow(TimberRegister* A);
int PresentCost(TimberRegister* A);
int RemoveTimber(TimberRegister* A);
int ChangeTimber(TimberRegister* A);
int CreateImage(TimberRegister* A);
int RestoreImage(TimberRegister* A);

int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//TimberRegister A = *new TimberRegister();
	TimberRegister A;
	int errorCheck;
	int exit = 0;

	while (exit == 0) {
		errorCheck = 1;
		int choice;
		std::cout <<
			"1. Add new timber" << std::endl <<
			"2. Present all timber in storage" << std::endl <<
			"3. Present alla timber in storage where length is below a chosen value" << std::endl <<
			"4. Present total cost for all timber in storage" << std::endl <<
			"5. Remove timber" << std::endl <<
			"6. Change price or length of chosen timber" << std::endl <<
			"7. Create storage image" << std::endl <<
			"8. Restore storage image" << std::endl <<
			"9. Exit" << std::endl <<
			"-----------------------------------------------------------------------" << std::endl << std::endl;
		std::cout << ">> ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			errorCheck = AddTimber(&A);
			break;
		case 2:
			errorCheck = PresentTimber(&A);
			break;
		case 3:
			errorCheck = PresentTimberLow(&A);
			break;
		case 4:
			errorCheck = PresentCost(&A);
			break;
		case 5:
			errorCheck = RemoveTimber(&A);
			break;
		case 6:
			errorCheck = ChangeTimber(&A);
			break;
		case 7:
			errorCheck = CreateImage(&A);
			break;
		case 8:
			errorCheck = RestoreImage(&A);
			break;
		case 9:

			exit = 1;
			break;
		default:
			std::cout << "Unhandled command" << std::endl;
			break;
		}

		if (errorCheck == -1) {
			std::cout << "Error" << std::endl;
		}

		std::cout << std::endl << std::endl;
	}

	return 0;
	
	//----------------------------------------------
	/*
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	TimberRegister A = *new TimberRegister();

	A.AddTimber("A", "axa", 1, 10);
	A.AddTimber("B", "bxb", 2, 20);
	A.AddTimber("C", "cxc", 3, 30);
	A.AddTimber("D", "dxd", 4, 40);
	A.AddTimber("E", "exe", 5, 50);

	std::cout << "AllTimber:" << std::endl;
	std::cout << A.ReturnAllTimber() << "------------------------- \n" << std::endl;

	std::cout << "Tar bort A" << std::endl << std::endl;
	A.RemoveTimber("A");

	std::cout << "AllTimber:" << std::endl;
	std::cout << A.ReturnAllTimber() << "------------------------- \n" << std::endl;

	std::cout << "Ändrar B" << std::endl << std::endl;
	A.ModifyTimber("B", 22, 222);

	std::cout << "AllTimber:" << std::endl;
	std::cout << A.ReturnAllTimber() << "------------------------- \n" << std::endl;

	std::cout << "Lägger till F o G" << std::endl << std::endl;
	A.AddTimber("F", "dxd", 4, 40);
	A.AddTimber("G", "exe", 5, 50);

	std::cout << "LowValue (4):" << std::endl;
	std::cout << A.ReturnLowValueTimber(4) << "------------------------- \n" << std::endl;

	std::cout << "TotalCost:" << std::endl;
	std::cout << A.TotalCost() << std::endl;

	getchar();

	delete[0] &A;

	return 0;
	*/
}

int AddTimber(TimberRegister* A) {
	int errorCheck = -1;

	std::string name;
	std::string dimensions;
	float length;
	float price;

	while (errorCheck == -1) {
		std::cout << "Set timber name: ";
		std::cin >> name;

		errorCheck = A->CheckTimberName(name);
		if (errorCheck == -1) {
			std::cout << "Timber name occupied" << std::endl;
		}
	}

	std::cout << "Set timber dimensions (AxB): ";
	std::cin >> dimensions;

	std::cout << "Set timber length (m): ";
	std::cin >> length;

	std::cout << "Set timber price (sek/m): ";
	std::cin >> price;

	errorCheck = A->AddTimber(name, dimensions, length, price);
	if (errorCheck == -1)
		return -1;
	else
		std::cout << "Timber successfully added" << std::endl;

	return 1;
}

int PresentTimber(TimberRegister* A) {
	std::cout << A->ReturnAllTimber() << "-------------------------" << std::endl << std::endl;
	return 1;
}

int PresentTimberLow(TimberRegister* A) {
	float lowestLength;
	std::cout << "Set lowest acceptable length: ";
	std::cin >> lowestLength;

	std::cout << A->ReturnLowValueTimber(lowestLength) << "-------------------------" << std::endl << std::endl;
	return 1;
}

int PresentCost(TimberRegister* A) {
	float totPrice = A->TotalCost();

	std::string priceString = std::to_string(totPrice);
	priceString.erase(priceString.find_last_not_of('0') + 2, std::string::npos);

	std::string finalString = priceString + " sek";

	std::cout << finalString << std::endl;
	return 1;
}

int RemoveTimber(TimberRegister* A) {
	int errorCheck = 1;
	std::string removeTimberName = "";

	std::cout << "Name of timber to be removed: ";
	std::cin >> removeTimberName;

	errorCheck = A->RemoveTimber(removeTimberName);
	if (errorCheck == -1) {
		std::cout << "Timber not found" << std::endl;
		return -1;
	}

	std::cout << "Timber successfully removed" << std::endl;
	return 1;
}

int ChangeTimber(TimberRegister* A) {
	int errorCheck = 1;
	std::string nameToModify;
	float newPrice;
	float newlength;

	std::cout << "Name of timber to be modified: ";
	std::cin >> nameToModify;

	errorCheck = A->CheckTimberName(nameToModify);
	if (errorCheck != -1) {
		std::cout << "No timber found with that name" << std::endl;
		return -1;
	}

	std::cout << "New price: ";
	std::cin >> newPrice;

	std::cout << "New length: ";
	std::cin >> newlength;

	errorCheck = A->ModifyTimber(nameToModify, newPrice, newlength);
	if (errorCheck == -1) {
		std::cout << "Unable to modify " + nameToModify << std::endl;
		return -1;
	}

	return 1;
}

int CreateImage(TimberRegister* A) {
	std::string fileName;

	std::cout << "Image name: ";
	std::cin >> fileName;

	A->CreateImage(fileName);

	return 1;
}

int RestoreImage(TimberRegister* A) {
	std::string fileName;

	std::cout << "Image name to restore from: ";
	std::cin >> fileName;

	A->RestoreImage(fileName);

	return 1;
}
