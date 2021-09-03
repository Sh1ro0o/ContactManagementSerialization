#pragma once
#ifndef CONTACT_H // include guard
#define CONTACT_H

#include <string>
#include <sstream>
#include "ContactType.h"

struct Contact {
private:
	std::string name;
	std::string surname;
	std::string email;
	std::string phoneNumber;
	ContactType type;
public:
	Contact(std::string name, std::string surname, std::string email, std::string phoneNumber, ContactType type) {
		this->name = name;
		this->surname = surname;
		this->email = email;
		this->phoneNumber = phoneNumber;
		this->type = type;
	}

	//SETTERS
	void setName(std::string name) {
		this->name = name;
	}

	void setSurname(std::string surname) {
		this->surname = surname;
	}

	void setEmail(std::string email) {
		this->email = email;
	}

	void setPhoneNumber(std::string phoneNumber) {
		this->phoneNumber = phoneNumber;
	}

	void setType(ContactType type) {
		this->type = type;
	}

	//GETTERS
	std::string getName() const {
		return name;
	}

	std::string getSurname() const {
		return surname;
	}

	std::string getEmail() const {
		return email;
	}

	std::string getPhoneNumber() const {
		return phoneNumber;
	}

	ContactType getType() const {
		return type;
	}

	std::string typeToString() const {
		if (type == ContactType::emergency)
			return "emergency";
		else if (type == ContactType::favorite)
			return "favorite";
		else
			return "normal";
	}

	std::string toString() const {
		std::stringstream ss;
		ss << name << " " << surname << " " << email << " " << phoneNumber << " " << typeToString();
		return ss.str();
	}
};

#endif
