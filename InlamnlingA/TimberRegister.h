#ifndef TIMBERREGISTER_H
#define TIMBERREGISTER_H

#include <string>
#include "Timber.h"

class TimberRegister {
private:
	int size;
	int freeSpace;
	Timber** timberArray;
public:
	int AddTimber(std::string dimensions, float length, float price);
	std::string ReturnTimber();
	std::string ReturnTimberUnderLimit(float lowLimit);
	float TotalCost();
	int RemoveTimber(std::string timberName);
	int ModifyTimber(std::string timberName, float newPrice, float newLength);
	void CreateImage(std::string &saveFile);
	void RestoreImage(std::string &saveFile);
	int CheckTimberDimensions(std::string name);
	int TestCopyAndAssignment();

	~TimberRegister();
	TimberRegister(int startCapacity);
};
#endif // TIMBERREGISTER_H