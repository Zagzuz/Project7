
#include "array_sequence.h"
#include "list_sequence.h"
#include "test.h"

template <class T>
int input_t(const char* invite, T min, T& x, T max, const char* error)
{
	for (;;)
	{
		std::cout << invite;
		std::cin >> x;
		if (std::cin.eof()) return 0;
		if (std::cin.bad() || std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (x >= min && x <= max) break;
		std::cout << error;
	}

	return 1;
}

template <class T>
void input_value(const char* invite, T& x, const char* error)
{
	for(;;)
	{
		std::cout << invite;
		std::cin >> x;
		if (std::cin.eof())
		{
			x = T();
			break;
		};
		if (std::cin.bad() || std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else break;
		std::cout << error;
	}
}

template <class T>
void insert_dialog(sequence<T>*& s)
{
	T value;
	input_value("Enter the value you want to insert: ",
		value, "error, repeat please\n");
	int index;
	input_t<int>("Enter index of the value: ",
		0, index, s->empty() ? 0 : s->size() - 1, "error, repeat please\n");
	s->insert(value, index);
}

template <class T>
void push_back_dialog(sequence<T>*& s)
{

	T value;
	input_value("Enter the value you want to insert: ",
		value, "error, repeat please\n");
	s->push_back(value);
}

template <class T>
void push_front_dialog(sequence<T>*& s)
{
	T value;
	input_value("Enter the value you want to insert: ",
		value, "error, repeat please\n");
	s->push_front(value);
}

template <class T>
void get_dialog(sequence<T>*& s)
{
	int index;
	input_t<int>("Enter index of the value: ",
		0, index, s->size() - 1, "error, repeat please\n");
	std::cout << "value[" << index << "] = " << s->get(index) << '\n';
}

template <class T>
void get_first_dialog(sequence<T>*& s)
{
	std::cout << "first value = " << s->get_first() << '\n';
}

template <class T>
void get_last_dialog(sequence<T>*& s)
{
	std::cout << "last value = " << s->get_last() << '\n';
}

template <class T>
void remove_dialog(sequence<T>*& s)
{
	T value;
	input_value("Enter the value you want to remove: ",
		value, "error, repeat please\n");
	s->remove(value);
}

template <class T>
void get_sub_dialog(sequence<T>*& s)
{
	int start, end;
	input_t<int>("Enter start index: ",
		0, start, s->size() - 1, "error, repeat please\n");
	input_t<int>("Enter end index: ",
		start, end, s->size() - 1, "error, repeat please\n");
	sequence<T>* subs = s->get_sub(start, end);
	std::cout << "Sequence: ";
	for (size_t i = 0; i < subs->size(); ++i)
	{
		std::cout << "'" << subs->get(i) << "'";
		if (i != subs->size() - 1) std::cout << ", ";
	}
	std::cout << '\n';
}

template <class T>
void print_dialog(sequence<T>*& s)
{
	std::cout << "Sequence: ";
	for (size_t i = 0; i < s->size(); ++i)
	{
		std::cout << "'" << s->get(i) << "'";
		if (i != s->size() - 1) std::cout << ", ";
	}
	std::cout << '\n';
}

template <class T>
void console_dialog(sequence<T>*& s)
{
	const char* message = "\n"
		"0. Exit\n"
		"1. Insert\n"
		"2. Push back\n"
		"3. Push front\n"
		"4. Remove\n"
		"5. Get\n"
		"6. Get first\n"
		"7. Get last\n"
		"8. Get sub\n"
		"9. Print\n";

	void(*dialog_functions[9])(sequence<T>*&) = 
	{
		insert_dialog, 
		push_back_dialog, 
		push_front_dialog,
		remove_dialog,
		get_dialog,
		get_first_dialog,
		get_last_dialog,
		get_sub_dialog,
		print_dialog
	};

	for (;;)
	{
		std::cout << message << "\n";
		int c;
		input_t("", 0, c, 9, "error, repeat please\n\n");
		if (c == 0) break;
		dialog_functions[c - 1](s);
	}

	delete s;
}

using type = int;

int main()
{
	std::cout << "Running test scenario...\n";
	sequence<int>* test = new array_sequence<type>;
	tester<type>::test_scenario(test);
	delete test;
	std::cout << "Array sequence test scenario success!\n";
	test = new list_sequence<type>;
	tester<type>::test_scenario(test);
	delete test;
	std::cout << "List sequence test scenario success!"
	"\n--------------------------------------\n";

	int c;
	input_t(" Choose sequence to test:\n"
		" 1. Array sequence \n 2. List sequence \n\n> ",
		1, c, 2, "error, repeat please\n\n");


	sequence<type>* s = nullptr;
	if (c == 1) s = new array_sequence<type>;
	else if (c == 2) s = new list_sequence<type>;

	console_dialog(s);

	return 0;
}