
#include "array_sequence.h"
#include "list_sequence.h"

int main()
{
	sequence<int>* x = new array_sequence<int>;
	x->push_back(8);

	for (size_t i = 0; i < x->size(); ++i)
		std::cout << x->get(i);

	return 0;
}