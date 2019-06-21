/* @file main.h
 * This file contains prototypes for the main function
 *
 * @author AmandaChapman
// Created by Amanda on 5/20/2019.
*/

#ifndef HELLOWORLD_MAIN_H
#define HELLOWORLD_MAIN_H


//prototypes

void showMenu();

bool
menuChoice(std::vector<Product> &record, std::vector<Product_Line> &productline, Statistics *, vector<string> &user_id,
           vector<string> &user_password, Product *);

void addEmployeeAccount(vector<string> &user_id, vector<string> &user_password);


void displayProductionStats(std::vector<Product> const &record, vector<Product_Line> &productline, Statistics *);

void importData(std::vector<Product> &record, std::vector<Product_Line> &productline, Statistics *, Product *);

void addNewItem(std::vector<Product_Line> &productline);

void showCatalog(Product *, std::vector<Product_Line> &productline, Statistics *);

void addItems(Product *, std::vector<Product_Line> &productline, Statistics *);

void createPassword(vector<string> &user_id, vector<string> &user_password);

bool sortnames(const Product_Line &a, const Product_Line &b);

std::string encrypt_password(std::string);

#endif //HELLOWORLD_MAIN_H
