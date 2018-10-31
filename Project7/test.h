#pragma once

#include <cassert>
#include "sequence.h"

template <class T>
struct tester
{
	using sequence_method_pointer = T(sequence<T>::*)(size_t);
	static bool exception_thrown(sequence<T>* s, sequence_method_pointer ptr, size_t i)
	{
		bool exception_thrown = false;
		try { (s->*ptr)(i); }
		catch (std::exception& e) { exception_thrown = true; }
		return exception_thrown;
	}
	static void test_scenario(sequence<T>*& s)
	{
		assert(s->empty());
		s->push_back(23);
		assert(s->size() == 1);
		assert(s->get_first() == 23);
		assert(s->get_last() == 23);
		assert(s->get(0) == 23);
		assert(exception_thrown(s, &sequence<T>::get, -1));
		assert(exception_thrown(s, &sequence<T>::get, 1));
		s->push_back(43);
		assert(s->size() == 2);
		assert(s->get_first() == 23);
		assert(s->get_last() == 43);
		assert(s->get(0) == 23);
		assert(s->get(1) == 43);
		assert(exception_thrown(s, &sequence<T>::get, -1));
		assert(exception_thrown(s, &sequence<T>::get, 2));
		s->push_front(53);
		assert(s->size() == 3);
		assert(s->get_first() == 53);
		assert(s->get_last() == 43);
		assert(s->get(0) == 53);
		assert(s->get(1) == 23);
		assert(exception_thrown(s, &sequence<T>::get, -1));
		assert(exception_thrown(s, &sequence<T>::get, 3));
		sequence<T>* subs = s->get_sub(1, 1);
		assert(subs->size() == 1);
		assert(subs->get_first() == 23);
		assert(subs->get_last() == 23);
	}
};