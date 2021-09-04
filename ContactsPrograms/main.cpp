#include <iostream>
#include <fstream>
#include <string>
#include "Contact.h"
#include "ContactType.h"
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <nlohmann/json.hpp>

//keypress definitions
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
 
//function that helps converting lists of structs into JSON lists of objects
void to_json(nlohmann::json& j, const Contact& contact) {
	j = nlohmann::json{
		{"name", contact.getName()},
		{"surname", contact.getSurname()},
		{"email", contact.getEmail()},
		{"phoneNumber", contact.getPhoneNumber()},
		{"type", contact.typeToString()}
	};
}

//function that helps converting JSON lists of objects into vector of structs
void from_json(const nlohmann::json& j, Contact& contact) {
	contact.setEmail(j.at("email").get<std::string>());
	contact.setName(j.at("name").get<std::string>());
	contact.setPhoneNumber(j.at("phoneNumber").get<std::string>());
	contact.setSurname(j.at("surname").get<std::string>());
	contact.setTypeString(j.at("type").get<std::string>());
}

//Deserializes a vector of Contact structs into a JSON list of objects
void contactsDeserialization(std::vector<Contact> &contacts) {
	//Deserialization - read from file
	std::ifstream myFileReading;

	myFileReading.exceptions(std::ifstream::failbit);
	try {
		myFileReading.open("savedata.json");
		//reads whole file and saves it into a string
		std::string content((std::istreambuf_iterator<char>(myFileReading)), (std::istreambuf_iterator<char>()));
		myFileReading.close();

		std::cout << "Loading file..." << std::endl;
		//parses string into json object
		nlohmann::json j = nlohmann::json::parse(content);
		std::cout << j << std::endl;

		//We convert JSON list of objects into vector of Contacts
		std::vector<Contact> contacts2 = j;
		contacts = contacts2;

		std::cout << "File loaded!" << std::endl;
	}
	catch (std::ifstream::failure fail) {
		std::cout << "File name not correct or it does not exist! Make sure to name your text file \"savedata\"" << std::endl;
	}
}

//Serializes a vector of Contact structs into a JSON list of objects
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

	int Selection = 0;

	while (true) {
		while (true) {
			std::cout << "========================================================" << std::endl;
			std::cout << "||                                                    ||" << std::endl;
			if (Selection == 0)
				std::cout << "|| => ADD A FRIEND/PERSON                             ||" << std::endl;
			else
				std::cout << "||    ADD A FRIEND/PERSON                             ||" << std::endl;
			if (Selection == 1)
				std::cout << "|| => REMOVE A FRIEND                                 ||" << std::endl;
			else
				std::cout << "||    REMOVE A FRIEND                                 ||" << std::endl;
			if (Selection == 2)
				std::cout << "|| => EDIT A FRIEND                                   ||" << std::endl;
			else
				std::cout << "||    EDIT A FRIEND                                   ||" << std::endl;
			std::cout << "||                                                    ||" << std::endl;
			std::cout << "========================================================" << std::endl;

			char input = 0;
			switch (input = _getch()) {
			case KEY_UP:
				Selection--;
				if (Selection < 0)
					Selection = 2;
				break;

			case KEY_DOWN:
				Selection++;
				if (Selection > 2)
					Selection = 0;
				break;
			}

			system("cls");

			if (input == KEY_ENTER)
				break;
		}

		switch (Selection) {
		//ADD A FRIEND CASE
		case 0:
		{
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
			Contact person(name, surname, email, phoneNumber, ContactType::normal);

			std::cout << "Do you wish to add a friend: " << person.toString() << " ?" << std::endl;
			std::cout << "press ENTER to confirm, ANY key to cancel" << std::endl;

			//confirmation that you want to add the created friend to your friends list
			char input = 0;
			switch (input = _getch()) {
			case KEY_ENTER:
				myContacts.emplace_back(person);
				std::cout << "Friend successfully added!";
				//saves the new person created
				contactsSerialization(myContacts);
				break;

			default:
				std::cout << "Aborted, a friend has not been added!";
				break;
			}
		}

		//REMOVE A FRIEND CASE
		case 1:
			std::cout << "REMOVED A FRIEND" << std::endl;
		}

		Contact tmp("Rowdy", "Snow", "random.email@something.com", "031425960", ContactType::emergency);
		myContacts.emplace_back(tmp);
	}

	//contactsDeserialization(myContacts);

	return 0;
}

//TO-DO:
//load from file when launched
//make the selection a function you call in a loop
//create friend type input Left arrow right arrow selection