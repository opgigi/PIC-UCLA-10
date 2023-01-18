#include "SpellCheck.h"

using namespace std;

int main()
{
	Checking_the_spell test_search;

	test_search.read_dictionary();

	test_search.process_file();

	cout << "\n" << "\n";


	return 0;
}
