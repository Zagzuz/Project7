#pragma once

#include "sequence.h"

template <class T>
class array_sequence : public sequence<T>
{
	size_t capacity_;
	T* elements_;
public:
	array_sequence() : capacity_(0), elements_(nullptr) {}
	T get(size_t index);
	T get_first();
	T get_last();
	void insert(const T& element, size_t index);
	void push_back(const T& element);
	void push_front(const T& element);
	void remove(const T& element);
	sequence<T>* get_sub(size_t start, size_t end);
};

template<class T>
T array_sequence<T>::get(size_t index)
{
	if (index >= this->size_)
		throw std::exception("index out of bounds");
	return elements_[index];
}

template<class T>
T array_sequence<T>::get_first()
{
	if (this->size_ == 0)
		throw std::exception("sequence is empty");
	return elements_[0];
}

template<class T>
T array_sequence<T>::get_last()
{
	if (this->size_ == 0)
		throw std::exception("sequence is empty");
	return elements_[this->size_ - 1];
}

template <class T>
void array_sequence<T>::insert(const T& element, size_t index)
{
	if (index > this->size_)
		throw std::exception("index out of bounds");

	if (elements_ == nullptr)
	{
		capacity_ = 1;
		elements_ = new T;
		elements_[this->size_++] = element;
		return;
	}

	if (this->size_ == capacity_)
	{
		capacity_ *= 2;
		T* temp = new T[capacity_];
		for (size_t i = 0; i < index; ++i)
			temp[i] = elements_[i];
		for (size_t j = index; j < this->size_; ++j)
			temp[j + 1] = elements_[j];
		temp[index] = element;
		delete elements_;
		elements_ = temp;
		++this->size_;
		return;
	}

	for (size_t i = this->size_; i > index; ++i)
		elements_[i] = elements_[i - 1];
	elements_[index] = element;
	++this->size_;
}

template<class T>
void array_sequence<T>::push_back(const T& element)
{
	if (elements_ == nullptr)
	{
		elements_ = new T;
		elements_[this->size_++] = element;
		capacity_ = 1;
		return;
	}

	if (this->size_ == capacity_)
	{
		capacity_ *= 2;
		T* temp = new T[capacity_];
		for (size_t i = 0; i < this->size_; ++i)
			temp[i] = elements_[i];
		delete[] elements_;
		elements_ = temp;
	}

	elements_[this->size_++] = element;
}


template<class T>
void array_sequence<T>::push_front(const T& element)
{
	if (elements_ == nullptr)
	{
		elements_ = new T;
		elements_[this->size_++] = element;
		capacity_ = 1;
		return;
	}

	if (this->size_ == capacity_)
	{
		capacity_ *= 2;
		T* temp = new T[capacity_];
		for (size_t i = 0; i < this->size_; ++i)
			temp[i + 1] = elements_[i];
		delete[] elements_;
		elements_ = temp;
		elements_[0] = element;
		this->size_++;
		return;
	}

	for (size_t i = this->size_++; i > 0; ++i)
		elements_[i] = elements_[i - 1];
	elements_[0] = element;
}

template <class T>
void array_sequence<T>::remove(const T& element)
{
	size_t new_size = this->size_;
	for (size_t i = 0, j, k = 0; i < this->size_; ++i)
	{
		for (j = k + 1; j < this->size_; ++j, --new_size)
			if (elements_[j] != element) break;

		if (j == this->size_) break;

		if (j != i + 1)
		{
			elements_[i + 1] = elements_[j];
			i += 1;
			k = j;
		}
		else ++k;
	}

	this->size_ = new_size;
}

template <class T>
sequence<T>* array_sequence<T>::get_sub(size_t start, size_t end)
{
	if (start >= this->size_)	throw std::exception("start index out of bound");
	if (end >= this->size_) throw std::exception("end index out of bound");
	if (end < start) throw std::exception("end index is less than start");

	T* temp = new T[end - start];
	for (size_t i = start; i <= end; ++i)
		temp[i - start] = elements_[i];
	
	array_sequence<T>* n = new array_sequence<T>;
	n->elements_ = temp;
	n->capacity_ = n->size_ = end - start;
	return n;
}
