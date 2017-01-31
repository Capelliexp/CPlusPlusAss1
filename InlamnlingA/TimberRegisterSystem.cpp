#include <string>
#include <iostream>
#include <crtdbg.h>
#include "TimberRegister.h"


int main() {
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

	delete[] &A;
	return 0;
}