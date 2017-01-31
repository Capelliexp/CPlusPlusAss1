#ifndef TIMBERREGISTER_H
#define TIMBERREGISTER_H

#include <string>
#include "Timber.h"

class TimberRegister {
private:
	int size;
	Timber** timberArray = new Timber*[0];
public:
	TimberRegister();
	~TimberRegister();

	int AddTimber(std::string name, std::string dimensions, float length, float price);	//1
	std::string ReturnAllTimber();						//2
	std::string ReturnLowValueTimber(float lowLimit);	//3
	float TotalCost();									//4
	int RemoveTimber(std::string timberName);			//5
	int ModifyTimber(std::string timberName, float newPrice, float newLength);	//6
	void CreateImage(std::string &saveFile);			//7
	void RestoreImage(std::string &saveFile);			//8
	int CheckTimberName(std::string name);
};
#endif // TIMBERREGISTER_H