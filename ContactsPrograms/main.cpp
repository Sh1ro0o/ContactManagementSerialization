#include <iostream>
#include <fstream>
#include <string>
#include "Contact.h"
#include "ContactType.h"
#include <vector>

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

	//serialization - read from file
	std::ifstream myFileReading;

	myFileReading.exceptions(std::ifstream::failbit);
	try {
		myFileReading.open("savedata.txt");
		myFileReading.close();
	}
	catch(std::ifstream::failure e) {
		std::cout << "File name not correct or it does not exist! Make sure to name your text file \"savedata\"" << std::endl;
	}

	//serialization - write to file
	std::ofstream myFileWriting;



	return 0;
}