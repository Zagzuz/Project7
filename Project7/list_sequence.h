#pragma once

#include "sequence.h"

template <class T>
class list_sequence : public sequence<T>
{
	struct node
	{
		T element;
		node *prev, *next;
		node() : prev(nullptr), next(nullptr) {}
		node(const T& e) : element(e), prev(nullptr), next(nullptr) {}
		node(node* p, node* n, const T& e) : element(e), prev(p), next(n) {}
	};
	node *head_, *tail_;
public:
	list_sequence() : head_(nullptr), tail_(nullptr) {}
	T get(size_t index);
	T get_first();
	T get_last();
	void insert(const T& element, size_t index);
	void push_back(const T& element);
	void push_front(const T& element);
	void remove(const T& element);
	sequence<T>* get_sub(size_t start, size_t end);
	~list_sequence();
};

template<class T>
T list_sequence<T>::get(size_t index)
{
	if (index >= this->size_)
		throw std::exception("index out of bounds");

	node* temp = head_;
	for (size_t i = 0; i < index; ++i)
		temp = temp->next;
	
	return temp->element;
}

template<class T>
T list_sequence<T>::get_first()
{
	if (this->size_ == 0)
		throw std::exception("sequence is empty");
	return head_->element;
}

template<class T>
T list_sequence<T>::get_last()
{
	if (this->size_ == 0)
		throw std::exception("sequence is empty");
	return tail_->element;
}

template <class T>
void list_sequence<T>::insert(const T& element, size_t index)
{
	if (head_ == nullptr)
	{
		head_ = tail_ = new node(element);
		this->size_ = 1;
		return;
	}

	if (index == this->size_)
	{
		tail_->next = new node(tail_, nullptr, element);
		tail_ = tail_->next;
		this->size_ += 1;
		return;
	}

	if (index > this->size_) 
		throw std::exception("index out of bounds");
	
	node* temp = head_;
	for (size_t i = 0; i < index; ++i)
		temp = temp->next;
	
	node* n = new node(temp->prev, temp, element);
	if (temp->prev) temp->prev->next = n;
	temp->prev = n;

	if (index == 0) head_ = n;
	this->size_ += 1;
}

template <class T>
void list_sequence<T>::push_back(const T& element)
{
	if (head_ == nullptr) head_ = tail_ = new node(element);
	else
	{
		tail_->next = new node(tail_, nullptr, element);
		tail_ = tail_->next;
	}
	this->size_ += 1;
}

template <class T>
void list_sequence<T>::push_front(const T& element)
{
	if (head_ == nullptr) head_ = tail_ = new node(element);
	else 
	{
		head_->prev = new node(nullptr, head_, element);
		head_ = head_->prev;
	}
	this->size_ += 1;
}

template<class T>
void list_sequence<T>::remove(const T& element)
{
	for (node* temp = head_; temp;)
	{
		if (temp->element == element)
		{
			if (temp->prev) temp->prev->next = temp->next;
			if (temp->next) temp->next->prev = temp->prev;
			node* temp_saver = temp->next;
			if (head_ == temp) head_ = temp_saver;
			if (tail_ == temp) tail_ = temp->prev;
			delete temp;
			temp = temp_saver;
			--this->size_;
		}
		else temp = temp->next;
	}
}

template <class T>
sequence<T>* list_sequence<T>::get_sub(size_t start, size_t end)
{ 
	if (start >= this->size_) throw std::exception("start index out of bound");
	if (end >= this->size_) throw std::exception("end index out of bound");
	if (end < start) throw std::exception("end index is less than start");

	list_sequence<T>* n = new list_sequence<T>;
	node* temp = head_;
	for (size_t i = 0; i < this->size_; ++i)
	{
		if (i >= start && i <= end) n->push_back(temp->element);
		temp = temp->next;
	}

	return n;
}

template <class T>
list_sequence<T>::~list_sequence()
{
	for (node* temp = head_->next; temp; temp = temp->next)
		delete temp->prev;
	delete tail_;
	tail_ = head_ = nullptr;
}
