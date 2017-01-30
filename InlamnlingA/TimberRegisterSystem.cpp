#include <string>
#include <iostream>
#include "TimberRegister.h"


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	TimberRegister A = *new TimberRegister();

	A.AddTimber("A", "axa", 1, 10);
	A.AddTimber("B", "bxb", 2, 20);
	A.AddTimber("C", "cxc", 3, 30);
	A.AddTimber("D", "dxd", 4, 40);
	A.AddTimber("E", "exe", 5, 50);

	std::cout << A.ReturnAllTimber() << "------------------------- \n" << std::endl;

	A.RemoveTimber("A");

	std::cout << A.ReturnAllTimber() << "------------------------- \n" << std::endl;

	A.ModifyTimber("B", 22, 222);

	std::cout << A.ReturnAllTimber() << "------------------------- \n" << std::endl;

	A.AddTimber("F", "dxd", 4, 40);
	A.AddTimber("G", "exe", 5, 50);

	std::cout << "wwowowowowowwowowowolo" << std::endl;
	std::cout << A.ReturnLowValueTimber(35) << "------------------------- \n" << std::endl;

	std::cout << A.TotalCost() << std::endl;

	getchar();
	return 0;
}