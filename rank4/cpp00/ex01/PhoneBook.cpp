/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:37:23 by hmensah-          #+#    #+#             */
/*   Updated: 2025/07/31 16:37:26 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <sstream>

PhoneBook::PhoneBook() : _currentIndex(0), _totalContacts(0)
{
}

PhoneBook::~PhoneBook()
{
}

std::string PhoneBook::_truncateString(const std::string &str) const
{
	if (str.length() > 10)
		return str.substr(0, 9) + ".";
	return str;
}

void PhoneBook::_displayContactList() const
{
	std::cout << std::setw(10) << std::right << "Index" << "|";
	std::cout << std::setw(10) << std::right << "First Name" << "|";
	std::cout << std::setw(10) << std::right << "Last Name" << "|";
	std::cout << std::setw(10) << std::right << "Nickname" << std::endl;

	for (int i = 0; i < _totalContacts; i++)
	{
		std::cout << std::setw(10) << std::right << i << "|";
		std::cout << std::setw(10) << std::right << _truncateString(_contacts[i].getFirstName()) << "|";
		std::cout << std::setw(10) << std::right << _truncateString(_contacts[i].getLastName()) << "|";
		std::cout << std::setw(10) << std::right << _truncateString(_contacts[i].getNickname()) << std::endl;
	}
}

void PhoneBook::_displayContact(int index) const
{
	std::cout << "First Name: " << _contacts[index].getFirstName() << std::endl;
	std::cout << "Last Name: " << _contacts[index].getLastName() << std::endl;
	std::cout << "Nickname: " << _contacts[index].getNickname() << std::endl;
	std::cout << "Phone Number: " << _contacts[index].getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret: " << _contacts[index].getDarkestSecret() << std::endl;
}

bool PhoneBook::_isValidIndex(const std::string &input, int &index) const
{
	if (input.length() != 1 || input[0] < '0' || input[0] > '7')
		return false;
	
	index = input[0] - '0';
	return (index < _totalContacts);
}

void PhoneBook::addContact()
{
	std::string input;

	std::cout << "Enter first name: ";
	while (std::getline(std::cin, input) && input.empty())
		std::cout << "First name cannot be empty. Enter first name: ";
	_contacts[_currentIndex].setFirstName(input);

	std::cout << "Enter last name: ";
	while (std::getline(std::cin, input) && input.empty())
		std::cout << "Last name cannot be empty. Enter last name: ";
	_contacts[_currentIndex].setLastName(input);

	std::cout << "Enter nickname: ";
	while (std::getline(std::cin, input) && input.empty())
		std::cout << "Nickname cannot be empty. Enter nickname: ";
	_contacts[_currentIndex].setNickname(input);

	std::cout << "Enter phone number: ";
	while (std::getline(std::cin, input) && input.empty())
		std::cout << "Phone number cannot be empty. Enter phone number: ";
	_contacts[_currentIndex].setPhoneNumber(input);

	std::cout << "Enter darkest secret: ";
	while (std::getline(std::cin, input) && input.empty())
		std::cout << "Darkest secret cannot be empty. Enter darkest secret: ";
	_contacts[_currentIndex].setDarkestSecret(input);

	_currentIndex = (_currentIndex + 1) % 8;
	if (_totalContacts < 8)
		_totalContacts++;

	std::cout << "Contact added successfully!" << std::endl;
}

void PhoneBook::searchContact() const
{
	if (_totalContacts == 0)
	{
		std::cout << "Phone book is empty!" << std::endl;
		return;
	}

	_displayContactList();

	std::cout << "Enter the index of the contact to display: ";
	std::string input;
	int index;

	if (std::getline(std::cin, input) && _isValidIndex(input, index))
		_displayContact(index);
	else
		std::cout << "Invalid index!" << std::endl;
}

void PhoneBook::run()
{
	std::string command;

	std::cout << "Welcome to Your Awesome PhoneBook!" << std::endl;
	std::cout << "Available commands: ADD, SEARCH, EXIT" << std::endl;

	while (true)
	{
		std::cout << "Enter a command: ";
		if (!std::getline(std::cin, command))
			break;

		if (command == "ADD")
			addContact();
		else if (command == "SEARCH")
			searchContact();
		else if (command == "EXIT")
		{
			std::cout << "Goodbye!" << std::endl;
			break;
		}
		else if (!command.empty())
			std::cout << "Invalid command. Use ADD, SEARCH, or EXIT." << std::endl;
	}
}
