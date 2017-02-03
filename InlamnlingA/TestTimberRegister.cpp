#include <string>
#include <iostream>
#include <crtdbg.h>
#include "TimberRegister.h"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	TimberRegister A(2);				//1

	A.AddTimber("axa", 1, 11);			//2
	A.AddTimber("bxb", 2, 22);

	A.AddTimber("cxc", 3, 33);			//3

	A.RemoveTimber("dxd");				//4
	std::cout << "output:" << std::endl;
	std::cout << A.ReturnTimber() << std::endl;

	A.RemoveTimber("axa");				//5
	std::cout << "output:" << std::endl;
	std::cout << A.ReturnTimber() << std::endl;

	A.RemoveTimber("bxb");				//6
	A.RemoveTimber("cxc");
	std::cout << "output:" << std::endl;
	std::cout << A.ReturnTimber() << std::endl;

	A.AddTimber("axa", 1, 11);			//7
	A.AddTimber("exe", 5, 55);
	std::cout << "output:" << std::endl;
	std::cout << A.ReturnTimber() << std::endl;

	if (A.TestCopyAndAssignment() == 1)	//8
		std::cout << "TestCopyAndAssignment() succeeded" << std::endl;
	else
		std::cout << "TestCopyAndAssignment() failed" << std::endl;


	getchar();

	return 0;
}

