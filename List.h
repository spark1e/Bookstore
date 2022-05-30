#ifndef _LIST_H
#define _LIST_H
#include "Book.h"
#include <iostream>
#include <iomanip>

class List : public Book {
private:
	int count;
	Book* headPtr;
	Book* getBookAt(const std::string&);
public:
	List();
	~List();

	bool addBook(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&,
		const int&, const double&, const double&, Book*);
	bool remove(const std::string&);
	void printSingleBook(Book&) const;
	bool isEmpty() const;
	int getCount() const;
	void clear();
	Book* searchByIsbn(const std::string&);
	bool qtyReduce(Book& bookObj);
	Book* getFirstBook() const;
	void listByQty() const;
	void listByRPrice() const;
	void listByDate() const;

	//operator overloadings
	friend std::ostream& operator<<(std::ostream& outStream, const List& outList);
};



#endif