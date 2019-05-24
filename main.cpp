/*@file main.cpp
* @brief media player production program.
 *
 * Software for a media player production
 * facility that will keep track of what products are produced.
 *
 * @author Amanda Chapman
 * @bugs no known bugs.
*/
//Amanda Chapman
//This is my Procedural Project
//I am using C++ Core Guidelines

#include <iostream>
#include <iomanip>
#include <fstream> // included to use ofstream
#include <string> // included to use string
#include "main.h"

using namespace std;

int main() {

    std::cout << "\nProduction Line Tracker\n";
    bool cont;
    do {
        showMenu(); // displays the menu
        cont = menuChoice(); // sets return value from menu choice to cont
    } while (cont); // ends the program when cont = false
    return 0;
}

// @brief showMenu function displays the menu to the user
void showMenu() {
    std::cout << "\n___________________________________________\n\n";
    std::cout << "1. Produce Item\n";
    std::cout << "2. Add Employee Account\n";
    std::cout << "3. Add Music Player\n";
    std::cout << "4. Add Movie Player\n";
    std::cout << "5. Display Production Statistics\n";
    std::cout << "6. Exit\n";
}

// @brief menuChoice function gets user input and calls functions based on user input
bool menuChoice() {
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1:
            produceItems(); // calls produceItems function
            break;
        case 2:
            addEmployeeAccount(); // calls addEmployeeAccount function
            break;
        case 3:
            addMusicPlayer(); // calls addMusicPlayer function
            break;
        case 4:
            addMoviePlayer(); // calls addMoviePlayer function
            break;
        case 5:
            displayProductionStats(); // calls displayProductionStats function
            break;
        case 6:
            return false; // sets cont = false to end program
        default:
            std::cout << "Not a valid selection\n"; // prints when user enters bad input
    }
    return true;
}

// @brief produceItems function
void produceItems() {
    std::cout << "Produce Item Stub\n"; // header
    string manufacturer;
    string name;
    int type;
    string itemType;

    int num;
    cout << "How many items are being produced?" << endl;
    cin >> num;
    cout << "Please enter the Manufacturer of the item: " << endl;
    cin >> manufacturer; //  gets user input for manufacturer
    cout << "Please enter the name of the product: " << endl;
    cin >> name; // gets user input for name of product
    cout << "Please enter the type of item being produced: \n";
    cout << "1. Audio: (\"MM\")\n2. Visual: (\"VI\")\n3. AudioMobile: (\"AM\")\n4. VisualMobile: (\"VM\")\n";
    cin >> type; // gets user input for item type
    if (type == 1) {
        itemType = "MM";
    } else if (type == 2) {
        itemType = "VI";
    } else if (type == 3) {
        itemType = "AM";
    } else if (type == 4) {
        itemType = "VM";
    } else {
        cout << "Not a valid input";
    }

    // track production for product
    std::fstream productionFile;
    productionFile.open("production.txt", ofstream::app); // create production.txt file
    for (int i = 1; i <= num; i++) { // lets user input more than one product


        productionFile << "Production number: " << i << " ";
        productionFile << "Serial number: " << manufacturer.substr(0, 3) << itemType << setfill('0') << setw(5) << i
                       << "\n"; // prints serial number
        productionFile.close(); // closes file
    }

    // create catalog
    std::ofstream catalogFile;
    catalogFile.open("catalog.txt", std::ios::app); // this creates and opens a file named catalog.txt
    catalogFile << "Available Products: \n";
    catalogFile << "Manufacturer: " << manufacturer << "\n"; // writes manufacturer to file
    catalogFile << "Item Name: " << name << "\n"; // writes name to file
    catalogFile << "Item Type: " << itemType << "\n"; // writes itemType to file
    catalogFile.close(); // closes file

    // prints catalog to user
    std::string line; // create variable line
    std::ifstream inputCatalog;
    inputCatalog.open("catalog.txt"); // opens catalog.txt
    if (inputCatalog.is_open()) {
        while (getline(inputCatalog, line))// this stores a line from the file to the variable line
        {
            cout << line << endl; // prints info from catalog.txt
        }
    }
    inputCatalog.close(); // closes file
}

// @brief addEmployeeAccount function
void addEmployeeAccount() {
    std::cout << "Add Employee Account Stub\n";
}

/* @brief addMusicPlayer function
 * @param This has no parameters for now
*/
void addMusicPlayer() {
    std::cout << "Add Music Player Stub\n";
}

// @brief addMoviePlayer function
void addMoviePlayer() {
    std::cout << "Add Movie Player Stub\n";
}

// @brief displayProductionStats
void displayProductionStats() {
    std::cout << "Display Production Statistics Stub\n";
}
