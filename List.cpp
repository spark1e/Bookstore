#include "List.h"

//Private Helper Method
Book* List::getBookAt(const std::string& key) {
	Book* traverse = headPtr;
	while (traverse != nullptr) {
		if (traverse->getIsbn() == key) {
			return traverse;
		}
		else {
			traverse = traverse->getNext();
		}
	}
	return nullptr;

}

List::List() : count(0), headPtr(nullptr) {}

List::~List() {
	clear();
}

bool List::addBook(const std::string& t_isbn, const std::string& t_title, const std::string& t_author, const std::string& t_publisher, const std::string& t_dateAdded,
	const int& t_quantity, const double& t_whCost, const double& t_rPrice, Book* bookPtr) {
	Book* newBook = new Book(t_isbn, t_title, t_author, t_publisher, t_dateAdded, t_quantity, t_whCost, t_rPrice, nullptr);
	if (headPtr == nullptr) {
		headPtr = newBook;
	}
	else {
		newBook->setNext(headPtr);
		headPtr = newBook;

	}
	count++;
	return true;
}

bool List::remove(const std::string& key) {
	bool result = false;
	Book* prevPtr = headPtr;
	Book* traverse = prevPtr->getNext();
	if (prevPtr == nullptr) return result;
	else {
		do {
			if (prevPtr->getIsbn() == key) {	// if first element to delete
				headPtr = traverse;
				delete prevPtr;
				result = true;
				count--;
				return result;
			}
			else {
				if (traverse->getIsbn() == key) {
					prevPtr->setNext(traverse->getNext());
					delete traverse;
					result = true;
					count--;
					return result;
				}
			}
			prevPtr = traverse;
			traverse = traverse->getNext();
		} while (traverse != nullptr);

	}
	return result;
}

void List::printSingleBook(Book& bookObj) const {
	std::cout << "ISBN:\t" << bookObj.getIsbn() << std::endl
		<< "Author:\t" << bookObj.getAuthor() << std::endl
		<< "Title:\t" << bookObj.getTitle() << std::endl
		<< "Publisher:\t" << bookObj.getPublisher() << std::endl
		<< "Date_Added:\t" << bookObj.getDateAdded() << std::endl
		<< "Quatity:\t" << bookObj.getQuantuty() << std::endl
		<< "Wholesale Cost:\t" << bookObj.getWhCost() << std::endl
		<< "Retail Price:\t" << bookObj.getRPrice() << std::endl << std::endl;
}

bool List::isEmpty() const {
	return count == 0;
}
int List::getCount() const {
	return count;
}
void List::clear() {
	Book* traverse = headPtr;
	while (!isEmpty()) {
		traverse = headPtr;
		headPtr = traverse->getNext();
		delete traverse;
		count--;
	}
}
Book* List::searchByIsbn(const std::string& key) {
	return getBookAt(key);
}
bool List::qtyReduce(Book& bookObj) {
	bookObj.setQuantity(bookObj.getQuantuty() - 1);
	return true;
}
Book* List::getFirstBook() const {
	return headPtr;
}

void List::listByQty() const {
	Book** ptrArray = new Book * [getCount()];	// ptrArray is an array of pointers to Book objects
	Book* traverse = getFirstBook();
	for (int i = 0; i < getCount(); i++) {	//fill in array with each book obj pointer
		ptrArray[i] = traverse;
		traverse = traverse->getNext();
	}
	for (int x = 1; x < getCount(); x++) {
		Book* key = ptrArray[x];
		int t = x;
		while (t > 0 && ptrArray[t - 1]->getQuantuty() > key->getQuantuty()) {
			ptrArray[t] = ptrArray[t - 1];
			t--;
		}
		ptrArray[t] = key;
	}
	std::cout << std::setw(10) << "ISBN" << std::setw(30) << "Title" << std::setw(23) << "Author"
		<< std::setw(18) << "Publisher" << std::setw(14) << "Date_Added" << std::setw(5) << "Qty"
		<< std::setw(8) << "WhCost" << std::setw(8) << "RPrice" << std::endl;
	for (int i = getCount() - 1; i >= 0; i--) {
		std::cout << std::setw(10) << ptrArray[i]->getIsbn() << std::setw(30) << ptrArray[i]->getTitle() << std::setw(23) << ptrArray[i]->getAuthor()
			<< std::setw(18) << ptrArray[i]->getPublisher() << std::setw(14) << ptrArray[i]->getDateAdded() << std::setw(5) << ptrArray[i]->getQuantuty()
			<< std::setw(8) << ptrArray[i]->getWhCost() << std::setw(8) << ptrArray[i]->getRPrice() << std::endl;
	}
}

void List::listByRPrice() const {
	Book** ptrArray = new Book * [getCount()];	// ptrArray is an array of pointers to Book objects
	Book* traverse = getFirstBook();
	for (int i = 0; i < getCount(); i++) {	//fill in array with each book obj pointer
		ptrArray[i] = traverse;
		traverse = traverse->getNext();
	}
	for (int x = 1; x < getCount(); x++) {
		Book* key = ptrArray[x];
		int t = x;
		while (t > 0 && ptrArray[t - 1]->getRPrice() > key->getRPrice()) {
			ptrArray[t] = ptrArray[t - 1];
			t--;
		}
		ptrArray[t] = key;
	}
	std::cout << std::setw(10) << "ISBN" << std::setw(30) << "Title" << std::setw(23) << "Author"
		<< std::setw(18) << "Publisher" << std::setw(14) << "Date_Added" << std::setw(5) << "Qty"
		<< std::setw(8) << "WhCost" << std::setw(8) << "RPrice" << std::endl;
	for (int i = getCount() - 1; i >= 0; i--) {
		std::cout << std::setw(10) << ptrArray[i]->getIsbn() << std::setw(30) << ptrArray[i]->getTitle() << std::setw(23) << ptrArray[i]->getAuthor()
			<< std::setw(18) << ptrArray[i]->getPublisher() << std::setw(14) << ptrArray[i]->getDateAdded() << std::setw(5) << ptrArray[i]->getQuantuty()
			<< std::setw(8) << ptrArray[i]->getWhCost() << std::setw(8) << ptrArray[i]->getRPrice() << std::endl;
	}
}

void List::listByDate() const {
	Book** ptrArray = new Book * [getCount()];	// ptrArray is an array of pointers to Book objects
	Book* traverse = getFirstBook();
	for (int i = 0; i < getCount(); i++) {	//fill in array with each book obj pointer
		ptrArray[i] = traverse;
		traverse = traverse->getNext();
	}
	for (int x = 1; x < getCount(); x++) {
		Book* key = ptrArray[x];
		int t = x;
		while (t > 0 && ptrArray[t - 1]->getDateAdded() > key->getDateAdded()) {
			ptrArray[t] = ptrArray[t - 1];
			t--;
		}
		ptrArray[t] = key;
	}
	std::cout << std::setw(10) << "ISBN" << std::setw(30) << "Title" << std::setw(23) << "Author"
		<< std::setw(18) << "Publisher" << std::setw(14) << "Date_Added" << std::setw(5) << "Qty"
		<< std::setw(8) << "WhCost" << std::setw(8) << "RPrice" << std::endl;
	for (int i = getCount() - 1; i >= 0; i--) {
		std::cout << std::setw(10) << ptrArray[i]->getIsbn() << std::setw(30) << ptrArray[i]->getTitle() << std::setw(23) << ptrArray[i]->getAuthor()
			<< std::setw(18) << ptrArray[i]->getPublisher() << std::setw(14) << ptrArray[i]->getDateAdded() << std::setw(5) << ptrArray[i]->getQuantuty()
			<< std::setw(8) << ptrArray[i]->getWhCost() << std::setw(8) << ptrArray[i]->getRPrice() << std::endl;
	}
}

std::ostream& operator<<(std::ostream& outStream, const List& outList) {
	std::cout << std::setw(10) << "ISBN" << std::setw(30) << "Title" << std::setw(23) << "Author"
		<< std::setw(18) << "Publisher" << std::setw(14) << "Date_Added" << std::setw(5) << "Qty"
		<< std::setw(8) << "WhCost" << std::setw(8) << "RPrice" << std::endl;
	Book* traverse = outList.getFirstBook();
	while (traverse != nullptr) {
		std::cout << std::setw(10) << traverse->getIsbn() << std::setw(30) << traverse->getTitle() << std::setw(23) << traverse->getAuthor()
			<< std::setw(18) << traverse->getPublisher() << std::setw(14) << traverse->getDateAdded() << std::setw(5) << traverse->getQuantuty()
			<< std::setw(8) << traverse->getWhCost() << std::setw(8) << traverse->getRPrice() << std::endl;
		traverse = traverse->getNext();
	}
	if (outList.isEmpty()) {
		std::cout << "Bookstore Inventory is empty!\n";
	}
	return outStream;
}