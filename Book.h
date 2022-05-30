#ifndef _BOOK_H
#define _BOOK_H

#include <string>

class Book {
private:
	std::string isbn, title, author, publisher, dateAdded;
	int quantity;
	double whCost, rPrice; //Wholesale cost and retail price
	Book* next;

public:
	//default ctor
	Book() : isbn("null"), title("null"), author("null"), publisher("null"), dateAdded("null"),
		quantity(0), whCost(0), rPrice(0), next(nullptr) {}
	Book(const std::string& t_isbn, const std::string& t_title, const std::string& t_author, const std::string& t_publisher, const std::string& t_dateAdded,
		const int& t_quantity, const double& t_whCost, const double& t_rPrice, Book* bookPtr) : isbn(t_isbn), title(t_title), author(t_author),
		publisher(t_publisher), dateAdded(t_dateAdded), quantity(t_quantity), whCost(t_whCost), rPrice(t_rPrice), next(bookPtr) {}

	//copy ctor
	Book(const Book& bookObj) {
		isbn = bookObj.isbn;
		title = bookObj.title;
		author = bookObj.author;
		publisher = bookObj.publisher;
		dateAdded = bookObj.dateAdded;
		quantity = bookObj.quantity;
		whCost = bookObj.whCost;
		rPrice = bookObj.rPrice;
	}

	//setters and getters
	void setIsbn(const std::string& t_isbn) { isbn = t_isbn; }
	void setTitle(const std::string& t_title) { title = t_title; }
	void setAuthor(const std::string& t_author) { author = t_author; }
	void setPublisher(const std::string& t_publisher) { publisher = t_publisher; }
	void setDateAdded(const std::string& t_dateAdded) { dateAdded = t_dateAdded; }
	void setQuantity(const int& t_quantity) { quantity = t_quantity; }
	void setWhCost(const double& t_whCost) { whCost = t_whCost; }
	void setRPrice(const double& t_rPrice) { rPrice = t_rPrice; }
	void setNext(Book* bookPtr) { next = bookPtr; }

	std::string getIsbn() const { return isbn; }
	std::string getTitle() const { return title; }
	std::string getAuthor() const { return author; }
	std::string getPublisher() const { return publisher; }
	std::string getDateAdded() const { return dateAdded; }
	int getQuantuty() const { return quantity; }
	double getWhCost() const { return whCost; }
	double getRPrice() const { return rPrice; }
	Book* getNext() const { return next; }

	

};

#endif