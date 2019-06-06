/** @file filename.cpp
 *  @brief This is a procedural project using only functions, no classes
 *
 *  The procedural project is a demonstration of what we learned through the COP2001 course
 *  This simulates a program created for a media player production facility that will keep track of what products are
 *  produced
 *
 *  @author Amanda Chapman
 *  @bug No known bugs.
 */

#include <iostream>
#include <iomanip>
#include <fstream> // included to use fstream
#include <string> // included to use string
#include <vector> // allows use of vectors
#include <algorithm> // allows sorting
#include <sstream> // allows use of stringstream
#include "main.h" // included to use prototypes

using namespace std;

// Global Variables:
// These will not remain global
// These will be passed between functions as arguments and parameters
int production_number = 0;

/* These will be used later
int audio_num = 0;
int visual_num = 0;
int audiomobile_num = 0;
int visualmobile_num = 0;
 */

// store in catalog
vector<string> product_line_manufacturer;   // stores manufacturers for items that can be produced
vector<string> product_line_name;           // stores names for items that can be produced
vector<string> product_line_type;           // stores type for items that can be produced

// hold production stats
// store in production.txt
vector<string> product_manufacturer;        // stores manufacturer for each product that has been produced
vector<string> product_name;                // stores name for each product that has been produced
vector<string> product_type;                // stores type for each product that has been produced
vector<string> serial_number;               // stores serial number for each product that has been produced
vector<int> product_number;                 // stores product number for each product that has been produced


vector<string> user_id;                    // holds user ids of employees
vector<string> user_password;


/** @ brief main is the starting point of the program
 It first loads information from previous entries from files in importData()
 A do-while loop is used to display the program menu and get user input to direct to functions
 showMenu() and menuChoice() are called each time a function ends, until user chooses to exit program
 @ return this function returns 0 when it executes properly
 **/
int main() {

    std::cout << "\nProduction Line Tracker\n";
    bool cont;
    do {
        importData();
        showMenu(); // displays the menu
        cont = menuChoice(); // sets return value from menu choice to cont
    } while (cont); // ends the program when cont = false
    return 0;
}

/** @ brief showMenu function displays the program menu to the user
 * **/
void showMenu() {
    std::cout << "\n___________________________________________\n\n";
    std::cout << "1. Produce Item\n";
    std::cout << "2. Add Employee Account\n";
    std::cout << "3. Add Music Player\n";
    std::cout << "4. Add Movie Player\n";
    std::cout << "5. Display Production Statistics\n";
    std::cout << "6. Exit\n";
}

/** @ brief menuChoice function gets user input for the menu from showMenu()
* They are then directed to the corresponding functions
* Each time they leave the function, showMenu() is displayed and the will be directed here again
**/
bool menuChoice() {
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1:
            produceItems();
            // calls produceItems function where they can see catalog and produce or create new item for catalog
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
            displayProductionStats();
            // calls displayProductionStats function where user can see production history,
            // see catalog items sorted by name, and search for production number with serial number
            break;
        case 6:
            return false; // sets cont = false to end program
        default:
            std::cout << "Not a valid selection\n"; // prints when user enters bad input
    }
    return true; // after each function call, true is returned to cont in order to display menu again
}

/** @ brief produceItems function gets user input to direct them to the right function
 for the task they want to perform
 **/
void produceItems() {
    int selection;

    cout << "Production Line menu: " << endl;
    cout << "1. See available products" << endl;
    cout << "2. Produce new item" << endl;
    cin >> selection;

    switch (selection) {
        case 1:
            cout << "Selected: See available products" << endl;
            showCatalog(); // calls showCatalog() which displays available items to produce
            break;
        case 2:
            cout << "Selected: Produce new item" << endl;
            addNewItem(); // goes to produce new item function where they can input new products to the catalog
            break;
        default:
            cout << "Not a valid input";
    }
}

/** @ brief this function gets user input for new items
 it stores manufacturer, name, and itemType to product_line vectors and to the catalog file
 **/
void addNewItem() {
    string manufacturer;
    string name;
    int type;
    string itemType;
    int num;

    cout << "How many new products would you like to create? " << endl;
    cin >> num;

    for (int i = 0; i < num; i++) {
        cout << "Please enter the Manufacturer of the item: " << endl;
        cin >> manufacturer;         //  gets user input for manufacturer
        cout << "Please enter the name of the product: " << endl;
        cin >> name;                // gets user input for name of product
        cout << "Please enter the type of item being produced: \n";
        cout << "1. Audio: (\"MM\")\n2. Visual: (\"VI\")\n3. AudioMobile: (\"AM\")\n4. VisualMobile: (\"VM\")\n";
        cin >> type;                // gets user input for item type
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

        //store the users input in a new element in the vectors
        product_line_manufacturer.push_back(manufacturer);
        product_line_name.push_back(name);
        product_line_type.push_back(itemType);

        // create catalog
        std::ofstream catalogFile;
        catalogFile.open("catalog.txt", std::ios::app); // this creates and opens a file named catalog.txt
        // stores: manufacturer name type -on one line
        catalogFile << manufacturer << " " << name << " " << itemType << endl;
        catalogFile.close(); // closes file
    }
}

/** @ brief showCatalog function reads data from catalog file and prints to the user
 In order for it to print catalog file, there must be previously added information
 Information can be added to catalog file by choosing to Produce New Items in the produceItems() function
 This function is followed by addItems(), user is expected to produce items from this menu
 **/
void showCatalog() {
    // importData
    // prints catalog to user
    std::string line; // create variable line
    string manufacturer;
    string name;
    string type;
    int index = 1; // index keeps count for each line to display it like a menu

    std::ifstream catalogFile;
    catalogFile.open("catalog.txt"); // opens catalog.txt

    if (catalogFile.is_open()) {
        if (!product_line_name.empty()) {
            while (catalogFile >> manufacturer >> name >> type) {
                // manufacturer, name, and type are set to the three strings on each line (in order)
                // prints as: 1. manufacturer name type
                cout << index << ". " << manufacturer << " " << name << " " << type << endl;
                index++;
            }
            addItems(); // addItems is called after we make sure there are items in the catalog that can be produced
        } else {
            cout << "There is nothing in the catalog" << endl;
        }
    } else {
        cout << "The catalog file is not open" << endl;
    }
    catalogFile.close(); // closes file
}

/** @ brief addItems function is called from produceItems() when user selects See Available Products
 function starts by importing data to keep production number up to date
 all products that are added get stored into product_ vectors, production file, and data file
 **/
void addItems() {
    int add, index, catalog_selection;
    //importData(); // import data before starting catalog to get production number
    //production_number = product_number.size();

    //create file to write product history to
    fstream productionFile;
    productionFile.open("production.txt", ios::app); // create production.txt file

    fstream dataFile;
    dataFile.open("data.txt", ios::app); // create data.txt file

    cout << "To produce, select an item from the catalog: " << endl;
    cin >> catalog_selection; // selection from the catalog, used to set the index
    cout << "How many items are being produced? " << endl;
    cin >> add;
    index = catalog_selection - 1; // catalogselection = 1 from the menu, index = 0 for the elements


    for (int i = 0; i < add; i++) {

        // Adds another element holding the product information at the index
        product_manufacturer.push_back(product_line_manufacturer[index]);
        product_name.push_back(product_line_name[index]);
        product_type.push_back(product_line_type[index]);
        product_number.push_back(production_number);

        // store each production in production.txt
        // stored in format:
        // production number serial number manufacturer name type
        productionFile << setfill('0') << setw(3) << production_number + 1 << " "
                       << product_line_manufacturer[index].substr(0, 3) <<
                       product_line_type[index] << setfill('0') << setw(5) << production_number + 1 << " "
                       << product_line_manufacturer[index] << " " << product_line_name[index] << " "
                       << product_line_type[index] << endl;


        // write to data file to import in the beginning of the program
        // each line holds information in order, used to import data in importData()
        // line 1: product manufacturer
        // line 2: product name
        // line 3: product type
        // line 4: product serial number
        // line 5: production number
        dataFile << product_line_manufacturer[index] << "\n" << product_line_name[index] << "\n"
                 << product_line_type[index] << "\n"
                 << product_line_manufacturer[index].substr(0, 3) << product_line_type[index] << setfill('0') << setw(5)
                 << production_number + 1 << "\n" << production_number + 1 << endl;
        production_number++; // increment production number each time it loops
    }
    productionFile.close(); // closes file
}

/** @brief addEmployeeAccount function lets user enter their full name to create user id
 * that is stored in the user_id vector the function then calls the createPassword() function
 **/
void addEmployeeAccount() {
    string first_name; // used to hold user input for their first name
    string last_name; // used to hold user input for their last name
    string first_initial; // holds the first initial of users first name to apply to username

    cout << "To begin, enter your first and last name: " << endl;
    cin >> first_name >> last_name;

    // transform first and last name to all lower case to use in user id
    transform(first_name.begin(), first_name.end(), first_name.begin(), tolower);
    transform(last_name.begin(), last_name.end(), last_name.begin(), tolower);

    first_initial = first_name.substr(0, 1);
    user_id.push_back(first_initial + last_name);
    cout << "Your User ID is: " << first_initial + last_name << "\n\n";

    createPassword();
}

/** @brief addMusicPlayer function
 */
void addMusicPlayer() {
    std::cout << "Add Music Player Stub\n";
}

/** @brief addMoviePlayer function
 *
 */
void addMoviePlayer() {
    std::cout << "Add Movie Player Stub\n";
}

/** @brief displayProductionStats is able to display production statistics,
 find and display production number corresponding to user input for serial number
 and sort catalog items by name and display
 **/
void displayProductionStats() {
    //importData(); // import data in order to display production and find serial number
    bool found = false; // set to false to search through vector serial_number
    int element = 0; // used to increment through serial_number vector
    int catalog_num; // used to store the number of items in the catalog for looping
    int statistics_selection; // holds user selection
    string serial; // user input to search for serial number
    string line; // used to read each line from production.txt

    cout << "Display Production Statistics Stub\n";
    cout << "1. View all production statistics " << endl;
    cout << "2. Search for production number by serial number" << endl;
    cout << "3. See items sorted by name" << endl;
    cin >> statistics_selection;

    // if user selects 1 the production history is displayed
    if (statistics_selection == 1) {
        ifstream productionFile; // sets up productionFile
        productionFile.open("production.txt", ios::in); // opens catalog.txt
        if (productionFile.is_open()) {
            while (getline(productionFile, line))// this stores a line from the file to the variable line
            {
                cout << line << endl; // prints info from production.txt
            }
        }
        productionFile.close(); // closes file

        // when statistics_selection == 2 we are searching for a serial number and printing its production number
    } else if (statistics_selection == 2) {
        cout << " Enter the serial number to search: " << endl;
        cin >> serial;

        while (!found && element < serial_number.size()) {
            if (serial_number[element] == serial) {
                found = true; // stops searchning serial_number vector once serial is found
            } else {
                element += 1; // increments element and keeps searching array
            }
        }
        if (found) {
            // prints production number at the corresponding element once serial is found
            std::cout << "The production number of that product is " << product_number[element] << std::endl;
        } else {
            // if the whole array is searched and found still = false, tell the user the serial number wasn't found
            std::cout << "That product name was not found." << std::endl;
        }
    }

        // when statistics_selection == 3, we sort the catalog names and print them in order
    else if (statistics_selection == 3) {
        catalog_num = product_line_name.size();
        cout << "Sorted products available: " << endl;
        sort(product_line_name.begin(), product_line_name.end());
        for (int i = 0; i < catalog_num; i++) {
            cout << product_line_name[i] << endl;
        }
    } else {
        cout << "Not a valid selection.";
    }
}

/** @brief importData function imports the production history into the product_ vectors
 * And the catalog information into the product_line vectors
 * This let's the program store and manipulate the data each time it runs so that previous entries are not lost.
 */
void importData() {
    int t = 1;
    // t starts at 1 and gets incremented for each line
    // when it reaches 5 it is set back to 0
    string line;
    string manufacturer, name, type; // used to store from catalog

    ifstream dataFile;
    dataFile.open("data.txt", ios::in); //opens data.txt file

    // while the file is open and has lines,
    // line 1 stores into product_manufacturer
    // line 2 stores into product_name
    // line 3 stores into product_type
    // line 4 stores into serial_number
    // line 5 stores into product_number
    while (dataFile.is_open()) {
        while (getline(dataFile, line)) {
            switch (t) {
                case 1:
                    product_manufacturer.push_back(line); // manufacturer gets line 1
                    break;
                case 2:
                    product_name.push_back(line); // product name gets line 2
                    break;
                case 3:
                    product_type.push_back(line); // product type gets line 3
                    break;
                case 4:
                    serial_number.push_back(line); // serial number gets line 4
                    break;
                case 5:
                    // product number gets line 5
                    production_number = stoi(line); // converts the string on line 5 to an int
                    product_number.push_back(production_number); // now an int can be stored into product_number
                    t = 0; // set t back to 0 to keep lines in order
                    break;
                default:
                    t = 0;
                    break;
            }
            t++; // increments t each loop so it goes to the next case
        }
        dataFile.close();

        //open catalogFile to get data
        ifstream catalogFile;
        catalogFile.open("catalog.txt");

        if (catalogFile.is_open()) {
            while (catalogFile >> manufacturer >> name >> type) {
                product_line_manufacturer.push_back(manufacturer);
                product_line_name.push_back(name);
                product_line_type.push_back(type);
            }
        } else {
            cout << endl;
        }
        catalogFile.close();

        /*  This is code I will work on next
          for(string element: serial_number){
              if(element.substr(3,2)== "MM"){
                  audio_num++;
              }
              else if(element.substr(3,2) == "VI"){
                  visual_num++;
              }
              else if(element.substr(3,2) == "AM"){
                  audiomobile_num++;
              }
              else if(element.substr(3,2) == "VM"){
                  visualmobile_num++;
              }
          }*/
    }
}

/** @ brief createPassword function is called from addEmployeeAccount
 * user is prompted to create a password following the guidelines
 * function tests to make sure the password is valid before storing it in the vector
 */
void createPassword() {
    string password; // stores password
    bool valid; // boolean used to test if password is valid
    bool upper = false; // boolean used when testing for uppercase letters
    bool lower = false; // boolean used when testing for lowercase letters
    bool digit = false; // boolean used when testing for digits

    cout << "Now create a password: \n" << "Your password must be no more than 10 characters including: \n" <<
         "\tAt least one uppercase letter\n\tAt least one lowercase letter\n\tAt least one letter\n" <<
         "\t(No special characters or spaces allowed.)" << endl;

    do {
        cin >> password;

        // use for loop to check each letter for uppercase, lowercase, and digits
        for (int i = 0; i < password.length(); i++) {
            if (isupper(password[i])) {
                upper = true;
            }
            if (islower(password[i])) {
                lower = true;
            }
            if (isdigit(password[i])) {
                digit = true;
            }
        }

        // if there is an uppercase, lowercase, AND digit then valid = true
        if (upper && lower) {
            if (digit) {
                valid = true;
            } else {
                valid = false;
            }
        } else {
            valid = false;
        }

        // test for other characters, valid set to false if there are any symbols or spaces
        for (int i = 0; i < password.length(); i++) {
            if (!isalnum(password[i])) {
                valid = false;
            }
        }
        if (!valid) {
            cout << "your password did not meet all the requirements, try again: " << endl;
        }
    } while (!valid);

    // if password meets requirements, add it to the password vector
    // then encrypt and decrypt it
    if (valid) {
        user_password.push_back(password); // valid password gets stored in the vector

        string encrypted = encrypt_password(password);

        cout << "Encrypted password: " << encrypted;
    }
}

/** @brief encrypt_password function takes the users password input and encrypts it.
 * @param pass is the users input for their password
 * @return the encrypted password
 */
string encrypt_password(string pass) {
    if (pass.length() == 1) {
        return pass;
    } else {
        int ascii_code = (int) pass[0];
        int ascii_code_of_char = ascii_code + 3;
        char encrypted_char = (char) ascii_code_of_char;

        return encrypted_char + encrypt_password(pass.substr(1, pass.length() - 1));
    }
}
