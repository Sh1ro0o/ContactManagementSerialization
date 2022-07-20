#include <iostream>
#include <fstream>
#include <string>
#include "Contact.h"
#include "ContactType.h"
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <nlohmann/json.hpp>

//keypress definitions
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27
 
//function that helps converting lists of structs into JSON lists of objects
void to_json(nlohmann::json& j, const Contact& contact) {
	j = nlohmann::json{
		{"name", contact.getName()},
		{"surname", contact.getSurname()},
		{"email", contact.getEmail()},
		{"phoneNumber", contact.getPhoneNumber()},
		{"type", contact.getTypeToString()}
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
	std::ifstream fileStream;

	fileStream.exceptions(std::ifstream::failbit);
	try {
		fileStream.open("savedata.json");
		std::cout << "File savedata.json found!" << std::endl;
		std::cout << "Loading file..." << std::endl;
		//reads whole file and saves it into a string
		std::string content((std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));
		fileStream.close();

		//parses string into json object
		nlohmann::json j = nlohmann::json::parse(content);
		//std::cout << j << std::endl;

		//We convert JSON list of objects into vector of Contacts
		std::vector<Contact> contacts2 = j;
		contacts = contacts2;
		
		std::cout << "File loaded!" << std::endl;
	}
	catch (std::ifstream::failure fail) {
		std::cout << "File does not exist yet so nothing was loaded!" << std::endl;
	}
}

//Serializes a vector of Contact structs into a JSON list of objects
void contactsSerialization(std::vector<Contact> &contacts) {
	//Seserialization
	//converting Contacts struct into JSON
	nlohmann::json j(contacts);
	//::cout << j.dump(3) << std::endl;

	//write JSON data to file named "savedata.json"
	std::fstream fileStream;
	fileStream.exceptions(std::ifstream::badbit);
	try {
		fileStream.open("savedata.json", std::fstream::out);
		fileStream << j.dump(3);
	}
	catch (std::ifstream::failure fail) {
		std::cout << "Failed to write!" << std::endl;
	}
	fileStream.close();
}

//Prompts a contact selection screen. When a contact is selected it returns an index of that contact otherwise it returns -1
int selectContact(std::vector<Contact>& contacts) {
	short selection = 0;
	bool exitloop = false;

	if (contacts.size() > 0) {
		while (contacts.size() > 0 && !exitloop) {
			for (int i = 0; i < contacts.size(); i++) {
				if (i == selection)
					std::cout << "=> " + contacts[i].toString() << std::endl;
				else
					std::cout << "   " + contacts[i].toString() << std::endl;
			}
			std::cout << "   =================================" << std::endl;
			std::cout << "   ==PRESS ESC TO EXIT==" << std::endl;

			char input = 0;
			switch (input = _getch()) {
			case KEY_UP:
				selection--;
				if (selection < 0)
					selection = contacts.size() - 1;
				break;

			case KEY_DOWN:
				selection++;
				if (selection == contacts.size())
					selection = 0;
				break;

			case KEY_ENTER:
				//return index of the selected contact
				return selection;
				break;

				//exits with esc press
			case KEY_ESC:
				exitloop = true;
				break;
			}
			system("cls");
		}
		//returns -1 if no contact has been selected
		return -1;
	}
	else {
		std::cout << "Sorry, NO FRIENDS :(" << std::endl << std::endl;
		system("pause");
		return -1;
	}
}

ContactType selectFriendType() {
	system("cls");

	int typeSelection = 0;
	while (true) {
		std::cout << "Friend type:";
		if (typeSelection == 0)
			std::cout << "  => Normal";
		else
			std::cout << "     Normal";
		if (typeSelection == 1)
			std::cout << "  => Favorite";
		else
			std::cout << "     Favorite";
		if (typeSelection == 2)
			std::cout << "  => Emergency";
		else
			std::cout << "     Emergency";


		char typeInput = 0;
		switch (typeInput = _getch()) {
		case KEY_UP:
		case KEY_RIGHT:
			if (typeSelection == 2)
				typeSelection = 0;
			else
				typeSelection++;
			break;

		case KEY_DOWN:
		case KEY_LEFT:
			if (typeSelection == 0)
				typeSelection = 2;
			else
				typeSelection--;
			break;
		}

		if (typeInput == KEY_ENTER) {
			return static_cast<ContactType>(typeSelection);
			system("cls");
			break;
		}

		system("cls");
	}
}


int main() {
	//vector with all the contacts
	std::vector<Contact> myContacts;

	//load all contacts from file if it already exists
	contactsDeserialization(myContacts);

	//variables for storing into a Contact object
	std::string name;
	std::string surname;
	std::string email;
	std::string phoneNumber;
	ContactType type;

	int Selection = 0;

	while (true) {
		while (true) {
			system("cls");

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
			if (Selection == 3)
				std::cout << "|| => DISPLAY FRIENDS                                 ||" << std::endl;
			else
				std::cout << "||    DISPLAY FRIENDS                                 ||" << std::endl;
			if (Selection == 4)
				std::cout << "|| => EXIT                                            ||" << std::endl;
			else
				std::cout << "||    EXIT                                            ||" << std::endl;
			std::cout << "||                                                    ||" << std::endl;
			std::cout << "========================================================" << std::endl;

			char input = 0;
			switch (input = _getch()) {
			case KEY_UP:
				Selection--;
				if (Selection < 0)
					Selection = 4;
				break;

			case KEY_DOWN:
				Selection++;
				if (Selection > 4)
					Selection = 0;
				break;
			}

			if (input == KEY_ENTER) {
				system("cls");
				break;
			}
		}

		switch (Selection) {
			//ADD A FRIEND CASE
		case 0:
		{
			std::cout << "Name: ";
			std::getline(std::cin, name);

			std::cout << "Surname: ";
			std::getline(std::cin, surname);

			std::cout << "email: ";
			std::getline(std::cin, email);

			std::cout << "Phone number: ";
			std::getline(std::cin, phoneNumber);

			type = selectFriendType();

			std::cout << name;
			std::cout << surname;
			std::cout << email;
			std::cout << phoneNumber;

			std::cout << std::endl;
			Contact person(name, surname, email, phoneNumber, type);
			system("cls");

			std::cout << "Do you wish to add a friend: " << person.toString() << " ?" << std::endl;
			std::cout << "\npress ENTER to confirm, ANY key to cancel..." << std::endl;

			//confirmation that you want to add the created friend to your friends list
			char input = 0;
			switch (input = _getch()) {
			case KEY_ENTER:
				myContacts.emplace_back(person);

				system("cls");
				std::cout << "Friend successfully added!" << std::endl << std::endl;
				//saves the new person created
				contactsSerialization(myContacts);
				system("pause");
				break;

			default:
				std::cout << "Aborted, a friend has not been added!" << std::endl;
				break;
			}

			break;
		}

		//REMOVE A FRIEND CASE
		case 1:
		{
			std::cout << "   ||  SELECT A FRIEND TO REMOVE  ||" << std::endl;
			std::cout << "   =================================" << std::endl;
			int removalIndex = selectContact(myContacts);
			char input = 0;
			if (removalIndex > -1) {
				system("cls");
				//contact removal confirmation and removal
				std::cout << "\nAre you sure you wish to remove " << myContacts[removalIndex].getName() << " "
					<< myContacts[removalIndex].getSurname() << " ?" << std::endl;
				std::cout << "\npress ENTER to confirm, ANY key to cancel..." << std::endl;
				input = _getch();
				if (input == KEY_ENTER) {
					myContacts.erase(myContacts.begin() + removalIndex);
					//saving updates to file
					contactsSerialization(myContacts);
				}
			}
			break;
		}

		//EDIT A FRIEND CASE
		case 2:
		{
			//returns index of a friend you wish to edit
			std::cout << "   ||  SELECT A FRIEND TO EDIT  ||" << std::endl;
			std::cout << "   =================================" << std::endl;
			int editIndex = selectContact(myContacts);			
			system("cls");

			int editSelection = 0;
			while (editIndex != -1) {
				std::cout << "   ||   SELECT PROPERTY TO EDIT   ||" << std::endl;
				std::cout << "   =================================" << std::endl;
				if (editSelection == 0)
					std::cout << " => Name: " << myContacts[editIndex].getName() << std::endl;
				else
					std::cout << "    Name: " << myContacts[editIndex].getName() << std::endl;
				if (editSelection == 1)
					std::cout << " => Surname: " << myContacts[editIndex].getSurname() << std::endl;
				else
					std::cout << "    Surname: " << myContacts[editIndex].getSurname() << std::endl;
				if (editSelection == 2)
					std::cout << " => Email: " << myContacts[editIndex].getEmail() << std::endl;
				else
					std::cout << "    Email: " << myContacts[editIndex].getEmail() << std::endl;
				if (editSelection == 3)
					std::cout << " => Phone number: " << myContacts[editIndex].getPhoneNumber() << std::endl;
				else
					std::cout << "    Phone number: " << myContacts[editIndex].getPhoneNumber() << std::endl;
				if (editSelection == 4)
					std::cout << " => Type: " << myContacts[editIndex].getTypeToString() << std::endl;
				else
					std::cout << "    Type: " << myContacts[editIndex].getTypeToString() << std::endl;
				std::cout << "   =================================" << std::endl;
				std::cout << "   ==PRESS ESC TO EXIT==" << std::endl;

				char input = 0;
				switch (input = _getch()) {
				case KEY_DOWN:
					if (editSelection == 4)
						editSelection = 0;
					else
						editSelection++;
					break;

				case KEY_UP:
					if (editSelection == 0)
						editSelection = 2;
					else
						editSelection--;
					break;
				}

				if (input == KEY_ENTER) {
					system("cls");
					std::string newInput;
					if (editSelection == 0) {
						std::cout << "Change " << myContacts[editIndex].getName() << " to: ";
						std::getline(std::cin, newInput);
						myContacts[editIndex].setName(newInput);
					}
					else if (editSelection == 1) {
						std::cout << "Change " << myContacts[editIndex].getSurname() << " to: ";
						std::getline(std::cin, newInput);
						myContacts[editIndex].setSurname(newInput);
					}
					else if (editSelection == 2) {
						std::cout << "Change " << myContacts[editIndex].getEmail() << " to: ";
						std::getline(std::cin, newInput);
						myContacts[editIndex].setEmail(newInput);
					}
					else if (editSelection == 3) {
						std::cout << "Change " << myContacts[editIndex].getPhoneNumber() << " to: ";
						std::getline(std::cin, newInput);
						myContacts[editIndex].setPhoneNumber(newInput);
					}
					else if (editSelection == 4) {
						myContacts[editIndex].setType(selectFriendType());
					}
					//saving updated contacts to file
					contactsSerialization(myContacts);
					break;
				}
				else if (input == KEY_ESC)
					break;

				system("cls");
			}
			break;
		}

		//DISPLAY FRIENDS
		case 3:
			if (myContacts.size() > 0) {
				for (int i = 0; i < myContacts.size(); i++) {
					std::cout << myContacts[i].toStringPretty() << std::endl;
				}
			}
			else
				std::cout << "Sorry, NO FRIENDS :(" << std::endl << std::endl;
			system("pause");
			break;

		//EXIT PROGRAM
		case 4:
			return 0;
		}
	}
		return 0;
}