/** @file filename.cpp
 *  @brief This is a procedural project using only functions, no classes
 *
 *  The procedural project is a demonstration of what we learned through the COP2001 course
 *  This simulates a program created for a media player production facility that will keep track of what products are
 *  produced
 *
 *  @author Amanda Chapman
 *  @bug There are bugs.
 */

#include <iostream>
#include <iomanip>
#include <fstream> // included to use fstream
#include <string> // included to use string
#include <vector> // allows use of vectors
#include <algorithm> // allows sorting
#include <sstream> // allows use of stringstream
#include <functional>


using namespace std;

// Global Variables:
// These will not remain global
// These will be passed between functions as arguments and parameters
int production_number = 0;


// create structure for production record
struct Product {
    int production_num = 0;
    string manufacturer;
    string name;
    string type;
    string serial_number;
};

// create structure for product line
struct Product_Line {
    string manufacturer;
    string name;
    string type;
};

// create structure for statistics
struct Statistics {
    int production_number;
    int audio_num = 0;
    int visual_num = 0;
    int audiomobile_num = 0;
    int visualmobile_num = 0;
};

#include "main.h" // included to use prototypes

/** @ brief main is the starting point of the program
 It first loads information from previous entries from files in importData()
 A do-while loop is used to display the program menu and get user input to direct to functions
 showMenu() and menuChoice() are called each time a function ends, until user chooses to exit program
 @ return this function returns 0 when it executes properly
 **/
int main() {
    vector<Product> record;
    vector<Product_Line> productline;
    vector<Statistics> statistics;
    vector<string> user_id;                    // holds user ids of employees
    vector<string> user_password;


    std::cout << "\nProduction Line Tracker\n";
    bool cont;
    do {
        importData(record, productline, statistics);
        showMenu(); // displays the menu
        cont = menuChoice(record, productline, statistics, user_id,
                          user_password); // sets return value from menu choice to cont
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
bool menuChoice(vector<Product> &record, vector<Product_Line> &productline, vector<Statistics> &statistics,
                vector<string> &user_id, vector<string> &user_password) {
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1:
            produceItems(record, productline, statistics);
            // calls produceItems function where they can see catalog and produce or create new item for catalog
            break;
        case 2:
            addEmployeeAccount(user_id, user_password); // calls addEmployeeAccount function
            break;
        case 3:
            addMusicPlayer(); // calls addMusicPlayer function
            break;
        case 4:
            addMoviePlayer(); // calls addMoviePlayer function
            break;
        case 5:
            displayProductionStats(record, productline);
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
void produceItems(vector<Product> &record, vector<Product_Line> &productline, vector<Statistics> &statistics) {
    int selection;

    cout << "Production Line menu: " << endl;
    cout << "1. See available products" << endl;
    cout << "2. Produce new item" << endl;
    cin >> selection;

    switch (selection) {
        case 1:
            cout << "Selected: See available products" << endl;
            showCatalog(record, productline,
                        statistics); // calls showCatalog() which displays available items to produce
            break;
        case 2:
            cout << "Selected: Produce new item" << endl;
            addNewItem(
                    productline); // goes to produce new item function where they can input new products to the catalog
            break;
        default:
            cout << "Not a valid input";
    }
}

/** @ brief this function gets user input for new items
 it stores manufacturer, name, and itemType to product_line vectors and to the catalog file
 **/
void addNewItem(vector<Product_Line> &productline) {
    string manufacturer;
    string name;
    int type;
    string itemType;
    int num;

    cout << "How many new products would you like to create? " << endl;
    cin >> num;

    for (int i = 0; i < num; i++) {
        cout << "Please enter the Manufacturer of the item: " << endl;
        cin >> manufacturer;                                          // gets user input for manufacturer
        cout << "Please enter the name of the product: " << endl;
        cin >> name;                                                 // gets user input for name of product
        cout << "Please enter the type of item being produced: \n";
        cout << "1. Audio: (\"MM\")\n2. Visual: (\"VI\")\n3. AudioMobile: (\"AM\")\n4. VisualMobile: (\"VM\")\n";
        cin >> type;                                                 // gets user input for item type
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
        Product_Line prodLine;
        prodLine.manufacturer = manufacturer;
        prodLine.name = name;
        prodLine.type = itemType;

        productline.push_back(prodLine);

        // create catalog
        std::ofstream catalogFile;
        catalogFile.open("ProductLine.csv", std::ios::app); // this creates and opens a file named ProductLine.csv
        // stores: manufacturer name type on one line
        catalogFile << prodLine.manufacturer << " " << prodLine.name << " " << prodLine.type << endl;
        catalogFile.close(); // closes file
    }
}

/** @ brief showCatalog function reads data from catalog file and prints to the user
 In order for it to print catalog file, there must be previously added information
 Information can be added to catalog file by choosing to Produce New Items in the produceItems() function
 This function is followed by addItems(), user is expected to produce items from this menu
 **/
void showCatalog(vector<Product> &record, vector<Product_Line> &productline, vector<Statistics> &statistics) {
    // importData
    // prints catalog to user
    string manufacturer;
    string name;
    string type;
    int index = 1; // index keeps count for each productline to display it like a menu

    std::ifstream catalogFile;
    catalogFile.open("ProductLine.csv"); // opens ProductLine.csv

    if (catalogFile.is_open()) {
        while (catalogFile >> manufacturer >> name >> type) {
            // manufacturer, name, and type are set to the three strings on each line (in order)
            // prints as: 1. manufacturer name type
            cout << index << ". " << manufacturer << " " << name << " " << type << endl;
            index++;
        }
        addItems(record, productline,
                 statistics); // addItems is called after we make sure there are items in the catalog that can be produced
    } else {
        cout << "There is nothing in the catalog" << endl;
    }
    catalogFile.close(); // closes file
}

/** @ brief addItems function is called from produceItems() when user selects See Available Products
 function starts by importing data to keep production number up to date
 all products that are added get stored into product_ vectors, production file, and data file
 **/
void addItems(vector<Product> &record, vector<Product_Line> &productline, vector<Statistics> &statistics) {
    int add, index, catalog_selection;
    string manufacturer, name, type;
    Product prods;
    Statistics stats;

    //create file to write product history to
    fstream productionFile;
    productionFile.open("ProductionLog.csv", ios::app); // create ProductionLog.csv file

    fstream dataFile;
    dataFile.open("data.txt", ios::app); // create data.txt file

    cout << "To produce, select an item from the catalog: " << endl;
    cin >> catalog_selection; // selection from the catalog, used to set the index
    cout << "How many items are being produced? " << endl;
    cin >> add;
    index = catalog_selection - 1; // catalog_selection = 1 from the menu, index = 0 for the elements


    for (int i = 0; i < add; i++) {

        prods.manufacturer = productline[index].manufacturer;
        prods.name = productline[index].name;
        prods.type = productline[index].type;
        stats.production_number = production_number + 1;


        // store each production in ProductionLog
        // stored in format:
        // production number serial number manufacturer name type
        // in each if statement, the product type number is incremented
        if (prods.type == "MM") {
            stats.audio_num = stats.audio_num + 1;

            productionFile << setfill('0') << setw(3) << stats.production_number << " "
                           << prods.manufacturer.substr(0, 3) << prods.type << setfill('0')
                           << setw(5) << stats.audio_num << " " // serial number
                           << prods.manufacturer << " " << prods.name << " "
                           << prods.type << endl;

            dataFile << prods.manufacturer << "\n" << prods.name << "\n"
                     << prods.type << "\n"
                     << prods.manufacturer.substr(0, 3) << prods.type << setfill('0')
                     << setw(5) << stats.audio_num << "\n" << stats.production_number << endl;
        }
        if (prods.type == "VI") {
            stats.visual_num = stats.visual_num + 1;

            productionFile << setfill('0') << setw(3) << stats.production_number << " "
                           << prods.manufacturer.substr(0, 3) <<
                           prods.type << setfill('0') << setw(5) << stats.visual_num << " "
                           << prods.manufacturer << " " << prods.name << " "
                           << prods.type << endl;

            dataFile << prods.manufacturer << "\n" << prods.name << "\n"
                     << prods.type << "\n"
                     << prods.manufacturer.substr(0, 3) << prods.type << setfill('0')
                     << setw(5) << stats.visual_num << "\n" << stats.production_number << endl;
        }
        if (prods.type == "AM") {
            stats.audiomobile_num = stats.audiomobile_num + 1;

            productionFile << setfill('0') << setw(3) << stats.production_number << " "
                           << prods.manufacturer.substr(0, 3) <<
                           prods.type << setfill('0') << setw(5) << stats.audiomobile_num << " "
                           << prods.manufacturer << " " << prods.name << " "
                           << prods.type << endl;

            dataFile << prods.manufacturer << "\n" << prods.name << "\n"
                     << prods.type << "\n"
                     << prods.manufacturer.substr(0, 3) << prods.type << setfill('0')
                     << setw(5) << stats.audiomobile_num << "\n" << stats.production_number << endl;
        }
        if (prods.type == "VM") {
            stats.visualmobile_num = stats.visualmobile_num + 1;

            productionFile << setfill('0') << setw(3) << stats.production_number << " "
                           << prods.manufacturer.substr(0, 3) <<
                           prods.type << setfill('0') << setw(5) << stats.visualmobile_num << " "
                           << prods.manufacturer << " " << prods.name << " "
                           << prods.type << endl;

            dataFile << prods.manufacturer << "\n" << prods.name << "\n"
                     << prods.type << "\n"
                     << prods.manufacturer.substr(0, 3) << prods.type << setfill('0')
                     << setw(5) << stats.visualmobile_num << "\n" << stats.production_number << endl;
        }

        // write to data file to import in the beginning of the program
        // each line holds information in order, used to import data in importData()
        // line 1: product manufacturer
        // line 2: product name
        // line 3: product type
        // line 4: product type serial number
        // line 5: production number

        production_number++; // increment production number each time it loops
    }
    productionFile.close(); // closes file
}

/** @ brief createPassword function is called from addEmployeeAccount
 * user is prompted to create a password following the guidelines
 * function tests to make sure the password is valid before storing it in the vector
 */
void createPassword(vector<string> &user_id, vector<string> &user_password) {
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

        ofstream userFile;
        userFile.open("Users.txt", std::ios::app);
        if (userFile.is_open()) {
            userFile << user_id[0] << " " << encrypted << endl;
        }
    }
}

/** @brief addEmployeeAccount function lets user enter their full name to create user id
 * that is stored in the user_id vector the function then calls the createPassword() function
 **/
void addEmployeeAccount(vector<string> &user_id, vector<string> &user_password) {
    string first_name; // used to hold user input for their first name
    string last_name; // used to hold user input for their last name
    string first_initial; // holds the first initial of users first name to apply to username

    cout << "To begin, enter your first and last name: " << endl;
    cin >> first_name >> last_name;

    for (int i = 0; first_name[i]; i++) {
        first_name[i] = tolower(first_name[i]);
    }
    for (int i = 0; last_name[i]; i++) {
        last_name[i] = tolower(last_name[i]);
    }

    first_initial = first_name.substr(0, 1);
    user_id.push_back(first_initial + last_name);
    cout << "Your User ID is: " << first_initial + last_name << "\n\n";

    createPassword(user_id, user_password);
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

bool sortnames(const Product_Line &a, const Product_Line &b) {
    return a.name < b.name;
}

/** @brief displayProductionStats is able to display production statistics,
 find and display production number corresponding to user input for serial number
 and sort catalog items by name and display
 **/
void displayProductionStats(vector<Product> const &record, std::vector<Product_Line> &productline) {
    bool found = false; // set to false to search through vector serial_number
    int element = 0; // used to increment through serial_number vector
    int catalog_num; // used to store the number of items in the catalog for looping
    int statistics_selection; // holds user selection
    string serial; // user input to search for serial number
    string line; // used to read each line from ProductionLog.csv
    Product_Line products;

    cout << "Display Production Statistics Stub\n";
    cout << "1. View all production statistics " << endl;
    cout << "2. Search for production number by serial number" << endl;
    cout << "3. See items sorted by name" << endl;
    cin >> statistics_selection;

    // if user selects 1 the production history is displayed
    if (statistics_selection == 1) {
        ifstream productionFile; // sets up productionFile
        productionFile.open("ProductionLog.csv", ios::in);
        if (productionFile.is_open()) {
            while (getline(productionFile, line))// this stores a line from the file to the variable line
            {
                cout << line << endl; // prints info from ProductionLog.csv
            }
        }
        productionFile.close(); // closes file

        // when statistics_selection == 2 we are searching for a serial number and printing its production number
    } else if (statistics_selection == 2) {
        cout << " Enter the serial number to search: " << endl;
        cin >> serial;

        while (!found && element < record.size()) {
            if (record[element].serial_number == serial) {
                found = true; // stops searching serial_number vector once serial is found
            } else {
                element += 1; // increments element and keeps searching array
            }
        }
        if (found) {
            // prints production number at the corresponding element once serial is found
            std::cout << "The production number of that product is " << record[element].production_num << std::endl;
        } else {
            // if the whole array is searched and found still = false, tell the user the serial number wasn't found
            std::cout << "That product name was not found." << std::endl;
        }
    }

        // when statistics_selection == 3, we sort the catalog names and print them in order
    else if (statistics_selection == 3) {
        catalog_num = productline.size();
        cout << "Sorted products available: " << endl;

        sort(productline.begin(), productline.end(), sortnames);
        for (int i = 0; i < catalog_num; i++) {
            cout << productline[i].manufacturer << " " << productline[i].name << " " << productline[i].type << endl;
        }
    } else {
        cout << "Not a valid selection.";
    }
}


/** @brief importData function imports the production history into the product_ vectors
 * And the catalog information into the product_line vectors
 * This let's the program store and manipulate the data each time it runs so that previous entries are not lost.
 */
void importData(vector<Product> &record, vector<Product_Line> &productline, vector<Statistics> &statistics) {
    int t = 1;
    // t starts at 1 and gets incremented for each line
    // when it reaches 5 it is set back to 0
    string line;
    string manufacturer, name, type, serialNumber; // used to store from catalog

    ifstream dataFile;
    dataFile.open("data.txt", ios::in); //opens data.txt file

    // declare variable to hold Product
    Product aProduct;
    Statistics stats;

    // while the file is open and has lines,
    // line 1 stores into product manufacturer
    // line 2 stores into product name
    // line 3 stores into product type
    // line 4 stores into serial number
    // line 5 stores into product number
    while (dataFile.is_open()) {
        while (getline(dataFile, line)) {
            switch (t) {
                case 1:
                    manufacturer = line;
                    aProduct.manufacturer = manufacturer;
                    // manufacturer gets line 1
                    break;
                case 2:
                    name = line;
                    aProduct.name = name;
                    // product name gets line 2
                    break;
                case 3:
                    type = line;
                    aProduct.type = type;
                    // product type gets line 3

                    // increment product type count
                    if (aProduct.type == "MM") {
                        stats.audio_num = stats.audio_num + 1;
                    }
                    if (aProduct.type == "VI") {
                        stats.visual_num = stats.visual_num + 1;
                    }
                    if (aProduct.type == "AM") {
                        stats.audiomobile_num = stats.audiomobile_num + 1;
                    }
                    if (aProduct.type == "VM") {
                        stats.visualmobile_num = stats.visualmobile_num + 1;
                    }

                    break;
                case 4:
                    serialNumber = line;
                    aProduct.serial_number = serialNumber;
                    // serial number gets line 4
                    break;
                case 5:
                    // product number gets line 5
                    production_number = stoi(line); // converts the string on line 5 to an int
                    stats.production_number = production_number;
                    aProduct.production_num = production_number; // keeps the production number in line for use in display production statistics

                    record.push_back(aProduct);
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
        catalogFile.open("ProductLine.csv");

        if (catalogFile.is_open()) {
            while (catalogFile >> manufacturer >> name >> type) {

                Product_Line prodLine;
                prodLine.manufacturer = manufacturer;
                prodLine.name = name;
                prodLine.type = type;

                productline.push_back(prodLine);
            }
        }
        catalogFile.close();
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
