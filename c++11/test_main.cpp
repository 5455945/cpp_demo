#include "test_main.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	test_events();

	test_Singleton();
	TestVisitor();

	TestWrap();

	TestObjPool();

	return 0;
}