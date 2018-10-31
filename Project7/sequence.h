#pragma once

#include <exception>
#include <iostream>

template <class T>
class sequence
{
protected:
	size_t size_;
public:
	sequence() : size_(0) {}
	bool empty() const { return size_ == 0; }
	size_t size() const { return size_; }
	virtual T get(size_t index) = 0;
	virtual T get_first() = 0;
	virtual T get_last() = 0;
	virtual void insert(const T& element, size_t index) = 0;
	virtual void push_back(const T& element) = 0;
	virtual void push_front(const T& element) = 0;
	virtual void remove(const T& element) = 0;
	virtual sequence<T>* get_sub(size_t start, size_t end) = 0;
	virtual ~sequence() {}
};