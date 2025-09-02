#include <iostream>
#include <forward_list>
#include <vector>
#include <cstring>

#include "singly_list.hpp"


template<class T>
std::ostream& operator<<(std::ostream& os, const std::forward_list<T>& list);

template<class T>
std::ostream& operator<<(std::ostream& os, const adt::singly_list<T>& list);

void forward_list() noexcept;

void singly_list() noexcept;

int main(int argc, char* argv[]) {
	singly_list();
	
	return 0;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const std::forward_list<T>& list) {
	os << "{ ";
	for (typename std::forward_list<T>::const_iterator cit = list.cbegin(); cit != list.cend(); cit++) {
		os << *cit << ' ';
	}
	os << '}';

	return os;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const adt::singly_list<T>& list) {
	os << "{ ";
	for (typename adt::singly_list<T>::const_iterator cit = list.cbegin(); cit != list.cend(); cit++) {
		os << *cit << ' ';
	}
	os << '}';

	return os;
}

void forward_list() noexcept {
	adt::singly_list<int> list = {1, 2, 3, 7, 8, 9, 13, 14, 15},
						  other = {4, 5, 6, 10, 11, 12};
	adt::singly_list<int>::const_iterator pos = list.cbegin() + 2,
										  first = other.cbefore_begin(),
										  last = first + 3;

	std::cout << "\"list\" before splice_after(): " << list << std::endl;
	std::cout << "\"other\" before splice after(): " << other << std::endl;
	
	list.splice_after(pos, other, first, last);
	
	std::cout << "\n\"list\" after splice_after(): " << list << std::endl;
	std::cout << "\"other\" after splice after(): " << other << std::endl;
}

void singly_list() noexcept {
	adt::singly_list<int> list;
	adt::singly_list<int>::const_iterator pos = list.cbefore_begin();
	list.insert_after(pos, list.cbegin(), list.cend());
}
