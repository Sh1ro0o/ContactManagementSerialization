#include <iostream>
#include <fstream>
#include <string>
#include "Contact.h"
#include "ContactType.h"
#include <vector>
#include <nlohmann/json.hpp>
 
//boilerplate that helps converting lists of structs into JSON lists of objects
void to_json(nlohmann::json& j, const Contact& contact) {
	j = nlohmann::json{
		{"name", contact.getName()},
		{"surname", contact.getSurname()},
		{"email", contact.getEmail()},
		{"phoneNumber", contact.getPhoneNumber()},
		{"type", contact.typeToString()}
	};
}

//boilerplate that helps converting JSON lists of objects into vector of structs
void from_json(const nlohmann::json& j, Contact& contact) {
	contact.setEmail(j.at("email").get<std::string>());
	contact.setName(j.at("name").get<std::string>());
	contact.setPhoneNumber(j.at("phoneNumber").get<std::string>());
	contact.setSurname(j.at("surname").get<std::string>());
	contact.setTypeString(j.at("type").get<std::string>());
}

void contactsDeserialization(std::vector<Contact> &contacts) {
	//Deserialization - read from file
	std::ifstream myFileReading;

	myFileReading.exceptions(std::ifstream::failbit);
	try {
		myFileReading.open("savedata.json");
		//reads whole file and saves it into a string
		std::string content((std::istreambuf_iterator<char>(myFileReading)),
		(std::istreambuf_iterator<char>()));
		myFileReading.close();

		std::cout << "Loading file..." << std::endl;
		//parses string into json object
		nlohmann::json j = nlohmann::json::parse(content);
		std::cout << j << std::endl;

		//We convert JSON list of objects into vector of Contacts
		std::vector<Contact> contacts2 = j;
		std::cout << "File loaded!" << std::endl;
	}
	catch (std::ifstream::failure fail) {
		std::cout << "File name not correct or it does not exist! Make sure to name your text file \"savedata\"" << std::endl;
	}
}

void contactsSerialization(std::vector<Contact> &contacts) {
	//Seserialization
	//converting Contacts struct into JSON
	nlohmann::json j(contacts);
	std::cout << j.dump(3) << std::endl;

	//write JSON data to file named "savedata.json"
	std::fstream myFileWriting;
	myFileWriting.exceptions(std::ifstream::badbit);
	try {
		myFileWriting.open("savedata.json", std::fstream::out);
		myFileWriting << j.dump(3);
	}
	catch (std::ifstream::failure fail) {
		std::cout << "Failed to write!" << std::endl;
	}
	myFileWriting.close();
}

int main() {
	//vector with all the contacts
	std::vector<Contact> myContacts;

	//variables for storing into a Contact object
	std::string name;
	std::string surname;
	std::string email;
	std::string phoneNumber;
	ContactType type;

	//input
	std::cout << "Name: ";
	std::cin >> name;

	std::cout << "Surname: ";
	std::cin >> surname;

	std::cout << "email: ";
	std::cin >> email;

	std::cout << "Phone number: ";
	std::cin >> phoneNumber;

	std::cout << "Friend type: ";

	std::cout << name;
	std::cout << surname;
	std::cout << email;
	std::cout << phoneNumber;

	std::cout << std::endl;
	Contact person("Howdy", "Snow", "random.email@something.com", "031425960", ContactType::normal);
	std::cout << person.toString() << std::endl;
	myContacts.emplace_back(person);

	Contact tmp("Rowdy", "Snow", "random.email@something.com", "031425960", ContactType::emergency);
	myContacts.emplace_back(tmp);

	contactsSerialization(myContacts);
	contactsDeserialization(myContacts);

	return 0;
}