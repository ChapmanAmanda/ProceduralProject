/** @file filename.cpp
 *  @brief This is a procedural project using only functions, no classes
 *
 *  The procedural project is a demonstration of what we learned through the COP2001 course
 *  This simulates a program created for a media player production facility that will keep track of what products are
 *  produced
 *
 *  @author Amanda Chapman
 *  @bug There are no bugs.
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

int production_number = 0;

// create structure for product line
struct Product_Line {
    string manufacturer;
    string name;
    string type;
};

// create structure for statistics
struct Statistics {
    int production_number = 0;
    int audio_num = 0;
    int visual_num = 0;
    int audiomobile_num = 0;
    int visualmobile_num = 0;
};

// create structure for production record
struct Product {
    int production_num = 0;
    string manufacturer;
    string name;
    string type;
    string serial_number;
};

#include "main.h" // included to use prototypes

/**@brief main is the starting point of the program
 It first loads information from previous entries from files in importData()
 A do-while loop is used to display the program menu and get user input to direct to functions
 showMenu() and menuChoice() are called each time a function ends, until user chooses to exit program
 Vectors and struct variables are created and passed to functions
 * @return returns 0 if program runs smoothly
 */
int main() {
    vector<Product> record;                     // holds production record
    vector<Product_Line> productline;           // holds product line
    vector<string> user_id;                    // holds user ids of employees
    vector<string> user_password;               // holds user passwords

    Statistics stats;   // declare Statistics variable named stats
    Product prods;      // declare Product variable named prods

    std::cout << "\nProduction Line Tracker\n";
    bool cont;
    do {
        importData(record, productline, &stats, &prods); // get data each time program runs through main

        showMenu(); // displays the menu
        cont = menuChoice(record, productline, &stats, user_id, user_password, &prods);
        // sets return value from menu choice to cont
    } while (cont); // ends the program when cont = false
    return 0;
}

/** @ brief showMenu function displays the program menu to the user
 **/
void showMenu() {
    std::cout << "\n___________________________________________\n\n";
    std::cout << "1. Produce Item\n";
    std::cout << "2. Add Employee Account\n";
    std::cout << "3. Add Music Player\n";
    std::cout << "4. Add Movie Player\n";
    std::cout << "5. Display Production Statistics\n";
    std::cout << "6. Exit\n";
}

/** @brief menuChoice function gets user input for the menu from showMenu
 * user is then directed to corresponding functions based on input
 * Each time they leave the function, showMenu is displayed and they will be here again
 * ALL parameters are passed to corresponding functions :
 * @param record        displayProductionStats
 * @param productline   displayProductionStats, produceItems
 * @param stats         displayProductionStats, produceItems
 * @param user_id       addEmployeeAccount
 * @param user_password  addEmployeeAccount
 * @param prods         produceItems
 * @return  returns bool cont that determines whether the program keeps running or not
 */
bool menuChoice(vector<Product> &record, vector<Product_Line> &productline, Statistics *stats,
                vector<string> &user_id, vector<string> &user_password, Product *prods) {
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1:
            produceItems(prods, productline, stats);
            // calls produceItems function where they can see catalog and produce or create new item for catalog
            break;
        case 2:
            addEmployeeAccount(user_id, user_password);
            // calls addEmployeeAccount function where they create username and password for users.txt
            break;
        case 3:
            addMusicPlayer(); // calls addMusicPlayer function
            break;
        case 4:
            addMoviePlayer(); // calls addMoviePlayer function
            break;
        case 5:
            displayProductionStats(record, productline, stats);
            // calls displayProductionStats function where user can see production history,
            // see catalog items sorted by name, search for production number with serial number
            // and see production statistics
            break;
        case 6:
            cout << "Goodbye! ";
            return false; // sets cont = false to end program
        default:
            std::cout << "Not a valid selection\n"; // prints when user enters bad input
    }
    return true; // after each function call, true is returned to cont in order to display menu again
}

/**@brief produceItems function gets user input to direct them to the right function for the task they want to perform
 * user can either see catalog and produce items, or add new items to the catalog
 *
 * ALL parameters are passed to corresponding functions:
 * @param prods         showCatalog
 * @param productline   showCatalog, addNewItem
 * @param stats         showCatalog
 */
void produceItems(Product *prods, vector<Product_Line> &productline, Statistics *stats) {
    int selection;

    cout << "Production Line menu: " << endl;
    cout << "1. See available products" << endl;
    cout << "2. Produce new item" << endl;
    cin >> selection; // user input for menu shown above

    switch (selection) {
        case 1:
            cout << "Selected: See available products" << endl;
            showCatalog(prods, productline, stats); // calls showCatalog() which displays available items to produce
            // showCatalog displays menu and calls function addItems to produce
            break;
        case 2:
            cout << "Selected: Produce new item" << endl;
            addNewItem(productline);
            // goes to produce new item function where they can input new products to the catalog
            break;
        default:
            cout << "Not a valid input";
    }
}

/**@brief this function gets user input for new items
 * It stores manufacturer, name, and itemType to product_line vectors and to the catalog file
 *
 * @param productline new items are added to productline vector which is later used to produce in addItems
 */
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

        // turn type choice to itemType string
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


        Product_Line prodLine; //declare Product_Line variable prodLine
        //set structure variables to user input
        prodLine.manufacturer = manufacturer;
        prodLine.name = name;
        prodLine.type = itemType;

        // create catalog
        std::ofstream catalogFile;
        catalogFile.open("ProductLine.csv", std::ios::app); // this creates and opens a file named ProductLine.csv

        // stores: manufacturer name type : on one line
        catalogFile << prodLine.manufacturer << " " << prodLine.name << " " << prodLine.type << endl;
        catalogFile.close(); // closes file
    }
}

/**@brief showCatalog function reads data from ProductLine file and prints to the user
 * In order for it to print catalog file, there must be previously added information
 * Information can be added to ProductLine file by choosing to Produce New Items in the produceItems() function
 * This function is followed by addItems(), user is expected to produce items from this menu
 * ALL parameters are used to pass to corresponding functions:
 * @param prods         addItems
 * @param productline   addItems
 * @param stats         addItems
 */
void showCatalog(Product *prods, vector<Product_Line> &productline, Statistics *stats) {
    string manufacturer, name, type;
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
        if(index > 1) {
            addItems(prods, productline, stats);
            // addItems is called after we make sure there are items in the catalog that can be produced
        }else {
            cout << "There is nothing in the catalog" << endl;
        }
    }
    catalogFile.close(); // closes file
}

/**@brief addItems function is called from showCatalog() when user selects See Available Products
 * function starts by importing data to keep production number/ item type numbers up to date
 * all products that are added get stored into ProductionLog file and data file
 *
 * @param prods  structure variables are filled using productline vector elements
 * @param productline  used at [index] element to fill prods structure variables
 * @param stats used to keep count of item types and production number while writing to files
 */
void addItems(Product *prods, vector<Product_Line> &productline, Statistics *stats) {
    int add, index, catalog_selection;
    string manufacturer, name, type;


    //create file to write product history to
    fstream productionFile;
    productionFile.open("ProductionLog.csv", ios::app); // create ProductionLog.csv file

    fstream dataFile;
    dataFile.open("data.txt", ios::app); // create data.txt file

    cout << "To produce, select an item from the catalog: " << endl;
    cin >> catalog_selection; // selection from the catalog, used to set the index
    cout << "How many items are being produced? " << endl;
    cin >> add;
    index = catalog_selection - 1;
    // index = catalog_selection -1 to line their selection up with the index of productline
    // catalog_selection = 1 from the menu, index = 0 for the elements


    for (int i = 0; i < add; i++) {

        // fill prods structure variables with productline vector info corresponding to the users catalog selection
        prods->manufacturer = productline[index].manufacturer;
        prods->name = productline[index].name;
        prods->type = productline[index].type;
        stats->production_number = production_number + 1; // update production number

        // store each production in ProductionLog
        // stored in format: production number serial number manufacturer name type
        // four different if statements are used to separate the item types
        // in each if statement, the product type number is incremented
        // serial number is incremented separately for each item type
        if (prods->type == "MM") {
            stats->audio_num = stats->audio_num + 1;

            productionFile << setfill('0') << setw(3) << stats->production_number << " "
                           << prods->manufacturer.substr(0, 3) << prods->type << setfill('0')
                           << setw(5) << stats->audio_num << " " // serial number
                           << prods->manufacturer << " " << prods->name << " "
                           << prods->type << endl;

            dataFile << prods->manufacturer << "\n" << prods->name << "\n"
                     << prods->type << "\n"
                     << prods->manufacturer.substr(0, 3) << prods->type << setfill('0')
                     << setw(5) << stats->audio_num << "\n" << stats->production_number << endl;

        }
        if (prods->type == "VI") {
            stats->visual_num = stats->visual_num + 1;

            productionFile << setfill('0') << setw(3) << stats->production_number << " "
                           << prods->manufacturer.substr(0, 3) << prods->type << setfill('0') << setw(5)
                           << stats->visual_num << " "
                           << prods->manufacturer << " " << prods->name << " "
                           << prods->type << endl;

            dataFile << prods->manufacturer << "\n" << prods->name << "\n"
                     << prods->type << "\n"
                     << prods->manufacturer.substr(0, 3) << prods->type << setfill('0')
                     << setw(5) << stats->visual_num << "\n" << stats->production_number << endl;
        }
        if (prods->type == "AM") {
            stats->audiomobile_num = stats->audiomobile_num + 1;

            productionFile << setfill('0') << setw(3) << stats->production_number << " "
                           << prods->manufacturer.substr(0, 3) <<
                           prods->type << setfill('0') << setw(5) << stats->audiomobile_num << " "
                           << prods->manufacturer << " " << prods->name << " "
                           << prods->type << endl;

            dataFile << prods->manufacturer << "\n" << prods->name << "\n"
                     << prods->type << "\n"
                     << prods->manufacturer.substr(0, 3) << prods->type << setfill('0')
                     << setw(5) << stats->audiomobile_num << "\n" << stats->production_number << endl;
        }
        if (prods->type == "VM") {
            stats->visualmobile_num = stats->visualmobile_num + 1;

            productionFile << setfill('0') << setw(3) << stats->production_number << " "
                           << prods->manufacturer.substr(0, 3) <<
                           prods->type << setfill('0') << setw(5) << stats->visualmobile_num << " "
                           << prods->manufacturer << " " << prods->name << " "
                           << prods->type << endl;

            dataFile << prods->manufacturer << "\n" << prods->name << "\n"
                     << prods->type << "\n"
                     << prods->manufacturer.substr(0, 3) << prods->type << setfill('0')
                     << setw(5) << stats->visualmobile_num << "\n" << stats->production_number << endl;
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

/**@brief createPassword function is called from addEmployeeAccount
 * user is prompted to create a password following the guidelines
 * function tests to make sure the password is valid before storing it in the vector
 * if password is not valid, user is informed and prompted to try again
 * user_id and encrypted user_password are stored to user.txt file
 *
 * @param user_id           user_id at the new users index is stored in users.txt file
 * @param user_password     user_password holds their approved password at a parallel index to user_id
 */
void createPassword(vector<string> &user_id, vector<string> &user_password) {
    string password; // stores password
    bool valid; // used to keep do-while loop running until user enters approved password

    // Tell user the rules for the password
    cout << "Now create a password: \n" << "Your password must be no more than 10 characters including: \n" <<
         "\tAt least one uppercase letter\n\tAt least one lowercase letter\n\tAt least one letter\n" <<
         "\t(No special characters or spaces allowed.)" << endl;

    // loop continues until user enters password following the standards
    do {
        cin >> password;
        bool upper = false, lower = false, digit = false; // booleans used to test if password is valid
        // declared inside loop to reset each time a new password is entered

        // use range based for loop to check each letter for uppercase, lowercase, and digits
        for (char &ch : password) {
            if (isupper(ch)) {
                upper = true;
            } else if (islower(ch)) {
                lower = true;
            } else if (isdigit(ch)) {
                digit = true;
            }
        }

        // if there is an uppercase, lowercase, AND digit then valid = true
        valid = upper && lower && digit;

        // test for other characters, valid set to false if there are any symbols or spaces
        for (char &ch : password) {
            if (!isalnum(ch)) {
                valid = false;
            }
        }

        // if the user did not meet requirements, tell them and let them try again
        if (!valid) {
            cout << "your password did not meet all the requirements, try again: " << endl;
        }
    } while (!valid); // loop continues until valid is true

    // if password meets requirements, add it to the password vector
    // then encrypt it
    user_password.push_back(password); // valid password gets stored in the vector
    string encrypted = encrypt_password(password); // valid password gets encrypted

    // encrypted password gets stored to userFile along with username
    ofstream userFile;
    userFile.open("Users.txt", std::ios::app);
    if (userFile.is_open()) {
        userFile << user_id[user_id.size() - 1] << " " << encrypted << endl;
    }

}

/**@brief addEmployeeAccount function lets user enter their full name to create user id
 * that is stored in the user_id vector the function then calls the createPassword() function
 *
 * @param user_id generated user id is stored to vector user_id and sent to createPassword
 * @param user_password     passed to createPassword
 */
void addEmployeeAccount(vector<string> &user_id, vector<string> &user_password) {
    string first_name; // used to hold user input for their first name
    string last_name; // used to hold user input for their last name
    string first_initial; // holds the first initial of users first name to apply to username

    cout << "To begin, enter your first and last name: " << endl;
    cin >> first_name >> last_name;

    //convert all letters in first_name and last_name to lowercase
    for (int i = 0; i < first_name.size(); i++) {
        first_name[i] = tolower(first_name[i]);
    }
    for (int i = 0; i < last_name.size(); i++) {
        last_name[i] = tolower(last_name[i]);
    }

    // create username for user in format: first initial of first_name + last_name
    first_initial = first_name.substr(0, 1);
    user_id.push_back(first_initial + last_name);
    cout << "Your User ID is: " << first_initial + last_name << "\n\n"; // tell user their username

    createPassword(user_id, user_password); // call function createPassword
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

/** @brief sortnames function is a small function used to sort item names alphabetically from Product_Line
 *
 * @param a     used to sort item names from Product_Line structure
 * @param b     used to sort item names from Product_Line structure
 * @return      returns boolean to displayProduction stats selection 3
 */
bool sortnames(const Product_Line &a, const Product_Line &b) {
    return a.name < b.name;
    // returns true/false to sort the structure Product_line by name
}

/**@brief displayProductionStats is able to display production history, find and display production number
 * and item information corresponding to user input for serial number, sort catalog items by name and display sorted
 * structures, and display production statistics
 *
 * @param record  used to search for serial number and display production number and item info at the found index
 * @param productline  used to sort and display Product_Line structures by name
 * @param stats  used to display production statistics
 */
void displayProductionStats(vector<Product> const &record, std::vector<Product_Line> &productline, Statistics *stats) {
    bool found = false; // set to false to search through vector serial_number
    int element = 0; // used to increment through serial_number vector
    int catalog_num; // used to store the number of items in the catalog for looping
    int statistics_selection; // holds user selection
    string serial; // user input to search for serial number
    string line; // used to read each line from ProductionLog.csv

    // display menu and get user selection
    cout << "Would you like to: \n";
    cout << "1. View all production history " << endl;
    cout << "2. Search for production number by serial number" << endl;
    cout << "3. See items sorted by name" << endl;
    cout << "4. Display production statistics" << endl;
    cin >> statistics_selection;

    // if user selects 1 the production history is read from ProductionLog and is displayed
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

        // when statistics_selection == 2 we are searching for a serial number and printing its production number/item info
    } else if (statistics_selection == 2) {
        cout << " Enter the serial number to search: " << endl;
        cin >> serial;

        //while the serial number has not been found, and record vector hasn't been fully searched:
        while (!found && element < record.size()) {
            if (record[element].serial_number == serial) {
                found = true; // stops searching serial_number vector once serial number is found
            } else {
                element += 1; // increments element and keeps searching array
            }
        }
        if (found) {
            // prints production number & item info at the corresponding element once serial number is found
            std::cout << "The production number of that product is " << record[element].production_num << std::endl;
            cout << "Product information : " << record[element].manufacturer << " " << record[element].name << " "
                 << record[element].type << endl;
        } else {
            // if the whole array is searched and found still equals false, tell the user the serial number wasn't found
            std::cout << "That product name was not found." << std::endl;
        }
    }

    // when statistics_selection == 3, we sort the catalog names and print them in order
    else if (statistics_selection == 3) {
        catalog_num = productline.size(); // set catalog_num to size of productline vector
        cout << "Sorted products available: " << endl;

        sort(productline.begin(), productline.end(), sortnames); // sortnames is called
        //productline vector is sorted by name
        for (int i = 0; i < catalog_num; i++) {
            // catalog sorted by item name is displayed using productline vector
            cout << productline[i].manufacturer << " " << productline[i].name << " " << productline[i].type << endl;
        }
    }

    // when statistics_selection = 4 we display the production statistics: total number of items produced, and number
    // of each item type produced
    else if (statistics_selection == 4) {
        cout << "Total number of items produced: " << stats->production_number << endl;
        cout << "Total number of audio products produced: " << stats->audio_num << endl;
        cout << "Total number of visual products produced: " << stats->visual_num << endl;
        cout << "Total number of audiomobile products produced: " << stats->audiomobile_num << endl;
        cout << "Total number of visualmobile products produced: " << stats->visualmobile_num << endl;
    } else {
        cout << "Not a valid selection.";
    }

}

/**@brief importData function imports the data file into the variables of the Product structure, push back to record vector
 * And imports the ProductLine file into the variables of the Product_Line structure, push back into productline vector
 * This let's the program store and manipulate the data each time it runs so that previous entries are not lost.
 * This function is called each time the program returns to the main menu after executing selected functions
 *
 * @param record -information from the data file is imported to the prods structure and pushed into this record vector
 * @param productline -information from the ProductLine file is imported to the prodLine structure & pushed into this vector
 * @param stats - used to increment and store number of each item type
 * @param prods - filled with data from data file and used to fill record vector for use throughout the program
 */
void importData(vector<Product> &record, vector<Product_Line> &productline, Statistics *stats, Product *prods) {
    int t = 1;
    int audio_num = 0;
    int visual_num = 0;
    int audiomobile_num = 0;
    int visualmobile_num = 0;


    // t starts at 1 and gets incremented for each line
    // when it reaches 5 it is set back to 0
    string line;
    string manufacturer, name, type, serialNumber; // used to store from catalog

    ifstream dataFile;
    dataFile.open("data.txt", ios::in); //opens data.txt file


    // while the file is open and has lines,
    // line 1 stores into product manufacturer
    // line 2 stores into product name
    // line 3 stores into product type, item types are incremented
    // line 4 stores into serial number
    // line 5 stores into product number
    while (dataFile.is_open()) {
        while (getline(dataFile, line)) {
            switch (t) {
                case 1:
                    manufacturer = line;
                    prods->manufacturer = manufacturer;
                    // manufacturer gets line 1
                    break;
                case 2:
                    name = line;
                    prods->name = name;
                    // product name gets line 2
                    break;
                case 3:
                    type = line;
                    prods->type = type;
                    // product type gets line 3

                    // increment each product type count
                    if (type == "MM") {
                        audio_num = audio_num + 1;
                    }
                    if (type == "VI") {
                        visual_num = visual_num + 1;
                    }
                    if (type == "AM") {
                        audiomobile_num = audiomobile_num + 1;
                    }
                    if (type == "VM") {
                        visualmobile_num = visualmobile_num + 1;
                    }
                    break;
                case 4:
                    serialNumber = line;
                    prods->serial_number = serialNumber;
                    // serial number gets line 4
                    break;
                case 5:
                    // product number gets line 5
                    production_number = stoi(line); // converts the string on line 5 to an int
                    stats->production_number = production_number;
                    prods->production_num = production_number; // keeps the production number in line for use in display production statistics

                    // once the end of each data set is reached, push the structure prods variable info into record vector
                    record.push_back(*prods);
                    t = 0; // set t back to 0 to keep lines in order
                    break;
                default:
                    t = 0;
                    break;
            }
            t++; // increments t each loop so it goes to the next case
        }
        //fill stats structure variables with updated item type count
        stats->audio_num = audio_num;
        stats->visual_num = visual_num;
        stats->audiomobile_num = audiomobile_num;
        stats->visualmobile_num = visualmobile_num;

        dataFile.close();

        //open catalogFile to get data
        ifstream catalogFile;
        catalogFile.open("ProductLine.csv");

        if (catalogFile.is_open()) {
            while (catalogFile >> manufacturer >> name >> type) {
                //create variable of the structure Product_Line
                Product_Line prodLine;
                //set prodLine variables to the data obtained from the ProductLine file
                // useful later while displaying available products and adding items
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
 * @return the encrypted password to be stored in users.txt
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
