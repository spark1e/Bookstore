#ifndef _CASHIER_H
#define _CASHIER_H
#include <string>
#include <iostream>



	void cashier(Book bookObj[]) {
		std::string isbn_sell = "-";
		double subtotal = 0, tax = 0, total = 0;

		while (isbn_sell != "q") {
			cashierDisplay();
			Book temp_book(searchByIsbn(bookObj, isbn_sell));
			std::cout << "Found: " << temp_book.getIsbn() << std::endl;


			std::cout << "Enter ISBN for the sale [q for checkout]:";
			std::cin >> isbn_sell;
		}
	}


	void cashierDisplay() {
		std::cout << "De Anza Bookstore" << std::endl
			<< "Date:\n";
		std::cout << std::setw(5) << "Qty" << std::setw(15) << "ISBN" << std::setw(30) << "Title"
			<< std::setw(8) << "Price" << std::setw(10) << "Total" << std::endl;
		std::cout << "======================================================================\n";
		
	/*	(searchByIsbn(key));

		std::cout << "\t\tSubtotal " << subtotal << std::endl
			<< "\t\tTax " << tax << std::endl
			<< "\t\tTotal " << total << std::endl;*/

	}


#endif