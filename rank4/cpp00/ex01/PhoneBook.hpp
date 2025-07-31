#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include <iostream>
#include <iomanip>

class PhoneBook
{
private:
	Contact _contacts[8];
	int _currentIndex;
	int _totalContacts;

	std::string _truncateString(const std::string &str) const;
	void _displayContactList() const;
	void _displayContact(int index) const;
	bool _isValidIndex(const std::string &input, int &index) const;

public:
	PhoneBook();
	~PhoneBook();

	void addContact();
	void searchContact() const;
	void run();
};

#endif
