/*
BOOKSTORE REGISTER SOFTWARE
Coded By Nick Volkov
github.com/spark1e
Project repo: github.com/spark1e/Bookstore
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include "Book.h"
#include "List.h"
#include "InputValidException.h"

using namespace std;	//using namespace std in main.cpp only

//functions used in main prototypes
int menu();
void setupBookstore(fstream&, List&);
void setupSingleBook(List&);
int inputValidation(int&, int);
void cashier(List&);
void inventory(List&);
void report(List&);
void updateTxt(fstream&, List&);

//ostream& operator<<(ostream&, const List&);

int main() {
	fstream file("DB.txt", ios::in | ios::app);	//opened for output

	List bookstore;
	setupBookstore(file, bookstore);
	int mode;
	do {
		mode = menu();
		switch (mode) {
		case 1:
			cashier(bookstore);
			break;
		case 2:
			inventory(bookstore);
			break;
		case 3:
			report(bookstore);
		case 4:
			break;
		}
	} while (mode != 4);

	updateTxt(file, bookstore);
	file.close();
	return 0;
}


// Function prints main menu with modes options, asks for user input, does input vilidation
// @param none
// @return key for Mode selection
int menu() {
	int key;
	string main_display = "\t[1] Cashier Mode\n\t[2] Inventory DB Mode\n\t[3] Report Mode\n\t[4] Exit\n\tChoice: ";
	cout << main_display;
	inputValidation(key, 4);
	return key;
}

// Function reads database file and initializes every Book instance.
// @pre File database is successfully opened, List of books is instantiated.
// @post Object List contains records of every entry from the database.
// @param Fstream object, List object
void setupBookstore(fstream& inFile, List& booksList) {
	int index = 0;
	//temp local variables
	int t_int;
	double t_double[2];
	string stemp[5];

	while (inFile >> stemp[0]) {
		inFile.ignore();

		//for 2-4 elements which are string type get data
		//from the txt database and save to temp array stemp.
		for (int i = 1; i < 5; i++) {
			inFile >> stemp[i];
			inFile.ignore();
		}
		inFile >> t_int;
		inFile.ignore();
		inFile >> t_double[0];
		inFile.ignore();
		inFile >> t_double[1];
		inFile.ignore();
		index++;
		booksList.addBook(stemp[0], stemp[1], stemp[2], stemp[3], stemp[4], t_int, t_double[0], t_double[1], nullptr);
	}
}

// Function adds a new node into List object and gets all the book data from user.
void setupSingleBook(List& booksList) {
	//temp local variables
	int t_int;
	double t_double[2];
	std::string stemp[5];

	std::cout << "Enter ISBN:";
	cin >> stemp[0];
	cin.clear();
	cin.ignore();

	std::cout << "Enter Title:";
	cin >> stemp[1];
	cin.clear();
	cin.ignore();

	std::cout << "Enter Author (FirstName_LastName):";
	cin >> stemp[2];
	cin.clear();
	cin.ignore();

	std::cout << "Enter Publisher:";
	cin >> stemp[3];
	cin.clear();
	cin.ignore();

	std::cout << "Enter date [YYYY-MM-DD]:";
	cin >> stemp[4];
	cin.clear();
	cin.ignore();

	std::cout << "Enter quantity:";
	cin >> t_int;
	cin.clear();
	cin.ignore();

	std::cout << "Enter wholesale cost:";
	cin >> t_double[0];
	cin.clear();
	cin.ignore();

	std::cout << "Enter retail price:";
	cin >> t_double[1];
	cin.clear();
	cin.ignore();

	booksList.addBook(stemp[0], stemp[1], stemp[2], stemp[3], stemp[4], t_int, t_double[0], t_double[1], nullptr);
	std::cout << "Successfully added!\n";
}

// Function to get and validate user input.
// @param int choice passed by ref as a menu choice, int upTo number of options in the menu.
// @return validated menu choice - key.
int inputValidation(int& choice, int upTo) {
	cin >> choice;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');	//ignore until end of the line
	while (choice > upTo || choice < 1) {
		try {
			if (!(choice > 0 && choice < upTo + 1)) {		// user input validation: if not in scope 1-upTo then exception is thrown
				throw InputValidException("Input violation exception...\n");
			}
		}
		catch (InputValidException exc_main) {
			cout << exc_main.what();
			for (int i = 1; i < upTo + 1; i++) 
				std::cout << "[" << i << "] ";
			std::cout << ": ";
			std::cin >> choice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}

// Cashier Mode Function. This mode is for selling books at the counter.
// Enter Isbn to add to current cart, add items one by one, once ready for checkout enter 'q'.
// @param List booklist of books object passed by ref.
// @post new node added to the List of books.
void cashier(List& booksList) {
	std::string temp = "0";
	double subtotal = 0;
	Book* booksSold[50];
	int qty[50] = {};
	int counter = 0;

	std::cout << "De Anza Campus Bookstore\n";
	do {
		std::cout << "###################################################################################\n";
		Book* temp_obj = booksList.searchByIsbn(temp);
		if (temp_obj != nullptr) {		//found

			bool hadPtr = false;
			for (int i = 0; i <= counter; i++) {
				if (booksSold[i] == temp_obj) {
					hadPtr = true;
					if (temp_obj->getQuantuty() <= 0) {
						std::cout << "---!!!We are out of this item!!!---\n";
						subtotal -= temp_obj->getRPrice();
						break;
					}
					qty[i]++;
					booksList.qtyReduce(*temp_obj);
					break;
				}
			}
			if (!hadPtr) {
				booksSold[counter] = temp_obj;
				qty[counter]++;
				counter++;
				booksList.qtyReduce(*temp_obj);
			}
			subtotal += temp_obj->getRPrice();
		}
		std::cout << std::setw(5) << "Qty" << std::setw(14) << "ISBN" << std::setw(30) << "Title"
			<< std::setw(17) << "Price" << std::setw(17) << "Total" << std::endl;
		for (int i = 0; i < counter; i++) {
			std::cout << std::setw(5) << qty[i] << std::setw(14) << booksSold[i]->getIsbn() << std::setw(30) << booksSold[i]->getTitle()
				<< std::setw(17) << booksSold[i]->getRPrice() << std::setw(17) << subtotal << std::endl;
		}
		std::cout << "\t\tSubtotal: " << setprecision(2) << fixed << subtotal << std::endl
			<< "\t\tTax 9%: " << setprecision(2) << fixed << subtotal * 0.09 << std::endl << "\t\tTotal: " << setprecision(2) << fixed << subtotal * 1.09 << std::endl;

		std::cout << "Enter ISBN to add to cart [q for chechout]: ";
		cin >> temp;
		cin.ignore();
		cin.clear();


	} while (temp != "q");
}

// Inventory Mode Function. This mode is to add, delete, change or view specific book node by isbn.
// @param List booklist of books object passed by ref.
// @post List booklist is altered if used adds/deletes/changes any book record.
void inventory(List& booksList) {
	int action;
	std::string key;
	Book* temp_ptr = nullptr;
	do {
		std::cout << "\t\tInventory Menu:\n"
			<< "\t\t[1] Look up a book\n" << "\t\t[2] Add new entry\n"
			<< "\t\t[3] Delete an entry\n" << "\t\t[4] Change book info\n"
			<< "\t\t[5] Return to mainscreen\n" << "\t\tChoice : ";
		inputValidation(action, 5);

		switch (action) {
		case 1:	//cout single book info based on ISBN
			std::cout << "Enter ISBN to search: ";
			cin >> key;
			cin.ignore();
			temp_ptr = booksList.searchByIsbn(key);
			if (temp_ptr == nullptr) {
				std::cout << "No match with bookstore database.\n";
			}
			else booksList.printSingleBook(*temp_ptr);
			break;
		case 2:	//add new entry to the list
			setupSingleBook(booksList);
			break;
		case 3:
			std::cout << "Enter ISBN to delete: ";
			cin >> key;
			temp_ptr = booksList.searchByIsbn(key);
			if (temp_ptr == nullptr) {	//not found
				std::cout << "No match with bookstore database. Unable to delete.\n";
			}
			else {
				booksList.remove(key);
				std::cout << "Removed successfully.\n";
			}
			break;
		case 4:
			std::cout << "Enter ISBN for a change:";
			cin >> key;
			temp_ptr = booksList.searchByIsbn(key);
			if (temp_ptr == nullptr) {
				std::cout << "No match with bookstore database. Unable to modify.\n";
			}
			else {
				booksList.remove(key);
				setupSingleBook(booksList);
			}
			break;
		}
	} while (action != 5);

}

// Report Mode Function. List current database by quantity in stock, retail price, date added.
// List entire database with no sorting. Output total wholesale and retail prices for whole inventory.
// @param List booklist of books object passed by ref.
// @post no change to database.
void report(List& booksList) {
	int action;
	do {
		double t_double = 0;

		std::cout << "\t\tReport Module Menu:\n"
			<< "\t\t[1] List entire Database\n" << "\t\t[2] Total Wholesale value\n"
			<< "\t\t[3] Total Retal value\n" << "\t\t[4] List by quantity\n"
			<< "\t\t[5] List by Retail Price\n" << "\t\t[6] List by Date Added\n"
			<< "\t\t[7] Return to mainscreen\n"	<< "\t\tChoice: ";
		inputValidation(action, 7);
		std::string key;
		Book* temp_ptr = nullptr;
		switch (action) {
		case 1:
			cout << booksList;
			break;
		case 2:
			temp_ptr = booksList.getFirstBook();
			while (temp_ptr != nullptr) {
				t_double += (temp_ptr->getWhCost()) * (temp_ptr->getQuantuty());
				temp_ptr = temp_ptr->getNext();
			}
			std::cout << "Sum(wholesale)= " << t_double << std::endl;
			break;
		case 3:
			temp_ptr = booksList.getFirstBook();
			while (temp_ptr != nullptr) {
				t_double += (temp_ptr->getRPrice()) * (temp_ptr->getQuantuty());
				temp_ptr = temp_ptr->getNext();
			}
			std::cout << "Sum(retail)= " << t_double << std::endl;
			break;
		case 4:
			std::cout << "SORTED BY QUANTITY IN DESCENDING ORDER\n";
			booksList.listByQty();
			break;
		case 5:
			std::cout << "SORTED BY PRICE IN DESCENDING ORDER\n";
			booksList.listByRPrice();
			break;
		case 6:
			std::cout << "SORTED BY DATE IN DESCENDING ORDER\n";
			booksList.listByDate();
			break;
		case 7:
			break;
		}
	} while (action != 7);
}

// Function to update database in txt file once user exits program.
// @param database object fstream fileIO and List booklist passed by ref.
// @post updated database
void updateTxt(fstream& fileIO, List& booksList) {
	fileIO.close();
	fileIO.open("DB.txt", ios::out | ios::trunc);
	Book* traverse = booksList.getFirstBook();
	while (traverse != nullptr) {
		fileIO << traverse->getIsbn() << ' ';
		fileIO << traverse->getTitle() << ' ';
		fileIO << traverse->getAuthor() << ' ';
		fileIO << traverse->getPublisher() << ' ';
		fileIO << traverse->getDateAdded() << ' ';
		fileIO << traverse->getQuantuty() << ' ';
		fileIO << traverse->getWhCost() << ' ';
		fileIO << traverse->getRPrice() << '\n';
		traverse = traverse->getNext();
	}

}

