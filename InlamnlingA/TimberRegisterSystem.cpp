#include <string>
#include <iostream>
#include <crtdbg.h>
#include "TimberRegister.h"

int AddTimber(TimberRegister* timber);
int PresentTimber(TimberRegister* timber);
int PresentTimberLow(TimberRegister* timber);
int PresentCost(TimberRegister* timber);
int RemoveTimber(TimberRegister* timber);
int ChangeTimber(TimberRegister* timber);
int CreateImage(TimberRegister* timber);
int RestoreImage(TimberRegister* timber);

int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	TimberRegister timber;
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
			errorCheck = AddTimber(&timber);
			break;
		case 2:
			errorCheck = PresentTimber(&timber);
			break;
		case 3:
			errorCheck = PresentTimberLow(&timber);
			break;
		case 4:
			errorCheck = PresentCost(&timber);
			break;
		case 5:
			errorCheck = RemoveTimber(&timber);
			break;
		case 6:
			errorCheck = ChangeTimber(&timber);
			break;
		case 7:
			errorCheck = CreateImage(&timber);
			break;
		case 8:
			errorCheck = RestoreImage(&timber);
			break;
		case 9:
			exit = 1;
			break;
		default:
			std::cout << "Unhandled command" << std::endl;
			errorCheck = -1;
			break;
		}

		if (errorCheck == -1) {
			std::cout << "Error" << std::endl;
		}

		std::cout << std::endl << std::endl;
	}

	return 0;
}

int AddTimber(TimberRegister* timber) {
	int errorCheck = -1;

	std::string name;
	std::string dimensions;
	float length;
	float price;

	while (errorCheck == -1) {
		std::cout << "Set timber name: ";
		std::cin >> name;

		errorCheck = timber->CheckTimberName(name);
		if (errorCheck == -1) {
			std::cout << "timber name occupied" << std::endl;
		}
	}

	std::cout << "Set timber dimensions (AxB): ";
	std::cin >> dimensions;

	std::cout << "Set timber length (m): ";
	std::cin >> length;

	std::cout << "Set timber price (sek/m): ";
	std::cin >> price;

	errorCheck = timber->AddTimber(name, dimensions, length, price);
	if (errorCheck == -1)
		return -1;
	else
		std::cout << "timber successfully added" << std::endl;

	return 1;
}

int PresentTimber(TimberRegister* timber) {
	std::cout << timber->ReturnTimber() << "-------------------------" << std::endl << std::endl;
	return 1;
}

int PresentTimberLow(TimberRegister* timber) {
	float lowestLength;
	std::cout << "Set lowest acceptable length: ";
	std::cin >> lowestLength;

	std::cout << timber->ReturnTimberUnderLimit(lowestLength) << "-------------------------" << std::endl << std::endl;
	return 1;
}

int PresentCost(TimberRegister* timber) {
	float totPrice = timber->TotalCost();

	std::string priceString = std::to_string(totPrice);
	priceString.erase(priceString.find_last_not_of('0') + 2, std::string::npos);

	std::string finalString = priceString + " sek";

	std::cout << finalString << std::endl;
	return 1;
}

int RemoveTimber(TimberRegister* timber) {
	int errorCheck = 1;
	std::string removeTimberName = "";

	std::cout << "Name of timber to be removed: ";
	std::cin >> removeTimberName;

	errorCheck = timber->RemoveTimber(removeTimberName);
	if (errorCheck == -1) {
		std::cout << "timber not found" << std::endl;
		return -1;
	}

	std::cout << "timber successfully removed" << std::endl;
	return 1;
}

int ChangeTimber(TimberRegister* timber) {
	int errorCheck = 1;
	std::string nameToModify;
	float newPrice;
	float newlength;

	std::cout << "Name of timber to be modified: ";
	std::cin >> nameToModify;

	errorCheck = timber->CheckTimberName(nameToModify);
	if (errorCheck != -1) {
		std::cout << "No timber found with that name" << std::endl;
		return -1;
	}

	std::cout << "New price: ";
	std::cin >> newPrice;

	std::cout << "New length: ";
	std::cin >> newlength;

	errorCheck = timber->ModifyTimber(nameToModify, newPrice, newlength);
	if (errorCheck == -1) {
		std::cout << "Unable to modify " + nameToModify << std::endl;
		return -1;
	}

	return 1;
}

int CreateImage(TimberRegister* timber) {
	std::string fileName;

	std::cout << "Image name: ";
	std::cin >> fileName;

	timber->CreateImage(fileName);

	return 1;
}

int RestoreImage(TimberRegister* timber) {
	std::string fileName;

	std::cout << "Image name to restore from: ";
	std::cin >> fileName;

	timber->RestoreImage(fileName);

	return 1;
}
