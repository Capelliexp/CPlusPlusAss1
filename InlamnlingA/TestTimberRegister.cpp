#include <string>
#include <iostream>
#include <crtdbg.h>
#include "TimberRegister.h"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	TimberRegister A;	//1

	A.AddTimber("A", "axa", 1, 11);	//2
	A.AddTimber("B", "bxb", 2, 22);

	A.AddTimber("C", "cxc", 3, 33);	//3

	A.RemoveTimber("D");	//4
	std::cout << "output:" << std::endl;
	std::cout << A.ReturnAllTimber() << std::endl;

	A.RemoveTimber("A");	//5
	std::cout << "output:" << std::endl;
	std::cout << A.ReturnAllTimber() << std::endl;

	A.RemoveTimber("B");	//6
	A.RemoveTimber("C");
	std::cout << "output:" << std::endl;
	std::cout << A.ReturnAllTimber() << std::endl;

	A.AddTimber("A", "axa", 1, 11);	//7
	A.AddTimber("E", "exe", 5, 55);
	std::cout << "output:" << std::endl;
	std::cout << A.ReturnAllTimber() << std::endl;

	if (A.TestCopyAndAssignment() == 1)	//8
		std::cout << "TestCopyAndAssignment() succeeded" << std::endl;
	else
		std::cout << "TestCopyAndAssignment() failed" << std::endl;


	getchar();

	return 0;
}

