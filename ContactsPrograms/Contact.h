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

	Contact() {
		this->name = "none";
		this->surname = "none";
		this->email = "none";
		this->phoneNumber = "none";
		this->type = ContactType::normal;
	};

	Contact(std::string name, std::string surname, std::string email, std::string phoneNumber, ContactType type) {
		this->name = name;
		this->surname = surname;
		this->email = email;
		this->phoneNumber = phoneNumber;
		this->type = type;
	}

	//if type isnt "emergency" or "favorite" it's set to normal by default
	Contact(std::string name, std::string surname, std::string email, std::string phoneNumber, std::string type) {
		this->name = name;
		this->surname = surname;
		this->email = email;
		this->phoneNumber = phoneNumber;
		if (type == "emergency")
			this->type = ContactType::emergency;
		else if (type == "favorite")
			this->type = ContactType::favorite;
		else
			this->type = ContactType::normal;
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

	void setTypeString(std::string type) {
		if (type == "emergency")
			this->type = ContactType::emergency;
		else if (type == "favorite")
			this->type = ContactType::favorite;
		else
			this->type = ContactType::normal;
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
