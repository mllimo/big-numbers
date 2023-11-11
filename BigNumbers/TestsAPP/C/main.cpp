#include <IntegerLib/H/Integer.h>

#include <iostream>

int main()
{
	std::string numer1 = "-90000000000000000000000000000000000000000";
	std::string numer2 =                                          "1"; // FAIL

	// Todo: Boost UT

	big::Integer integer1(numer1);
	big::Integer integer2(numer2);
	big::Integer result = integer1.Add(integer2);

	std::cout << result.ToString() << '\n';
}
