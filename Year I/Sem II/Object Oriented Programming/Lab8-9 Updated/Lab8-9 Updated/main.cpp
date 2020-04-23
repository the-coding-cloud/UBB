#include "Tests.h"
#include "Console.h"

int main()
{
	Tests tests = Tests();
	tests.testDomain();
	tests.testRepo();
	tests.testController();
	tests.testValidator();
	tests.testIsolated();
	//Console console = Console();
	//console.run();
}