#include <iostream>
#include <vector>
using namespace std;

// ===== TASK 2 =====
//class PrintedMaterial {
//public:
//protected:
//private:
//    unsigned numberOfPages;
//};
//
//class Magazine : public PrintedMaterial {
//public:
//protected:
//private:
//    unsigned numberOfPages;
//};
//
//class Book : public PrintedMaterial {
//public:
//protected:
//private:
//    unsigned numberOfPages;
//};
//
//class TextBook : public Book {
//public:
//protected:
//private:
//    unsigned numberOfPages;
//};
//
//class Novel : public Book {
//public:
//protected:
//private:
//    unsigned numberOfPages;
//};


// ===== TASK 3 + TASK 4 + TASK 5 =====
//class PrintedMaterial {
//public:
//	PrintedMaterial( unsigned numPages = 0 ): numOfPages(numPages)
//	{}
//protected:
//private:
//	unsigned numOfPages;
//};
//
//class Magazine : public PrintedMaterial {
//public:
//	Magazine( unsigned numPages = 0)
//		: PrintedMaterial(numPages)
//	{}
//protected:
//private:
//};
//
//class Book : public PrintedMaterial {
//public:
//	Book( unsigned numPages = 0)
//		: PrintedMaterial(numPages)
//	{}
//protected:
//private:
//};
//
//class TextBook : public Book {
//public:
//	TextBook( unsigned numPages = 0)
//		: Book(numPages)
//	{}
//protected:
//private:
//};
//
//class Novel : public Book {
//public:
//	Novel( unsigned numPages = 0)
//		: Book(numPages)
//	{}
//protected:
//private:
//};

// ===== TASK 6 =====
//class PrintedMaterial {
//friend ostream& operator<<(ostream& os, const PrintedMaterial& pm);
//public:
//    void displayNumPages() const { cout << numberOfPages << endl; }
//protected:
//private:
//    unsigned numberOfPages = 0;
//};
//
//class Magazine : public PrintedMaterial {
//public:
//protected:
//private:
//    unsigned numberOfPages;
//};
//
//class Book : public PrintedMaterial {
//public:
//protected:
//private:
//    unsigned numberOfPages;
//};
//
//class TextBook : public Book {
//public:
//protected:
//private:
//    unsigned numberOfPages;
//};
//
//class Novel : public Book {
//public:
//protected:
//private:
//    unsigned numberOfPages;
//};
//
//
//ostream& operator<<(ostream& os, const PrintedMaterial& pm){
//    os << pm.numberOfPages << endl;
//    return os;
//}

// ===== TASK 7 + TASK 8 =====
//class PrintedMaterial {
//public:
//	PrintedMaterial( unsigned numPages )
//		: numOfPages(numPages)
//	{}
//	void displayNumPages() const
//	{ cout << numOfPages << endl; }
//protected:
//private:
//	unsigned numOfPages;
//};
//
//class Magazine : public PrintedMaterial {
//public:
//	Magazine( unsigned numPages )
//		: PrintedMaterial(numPages)
//	{}
//protected:
//private:
//};
//
//class Book : public PrintedMaterial {
//public:
//	Book( unsigned numPages )
//		: PrintedMaterial(numPages)
//	{}
//protected:
//private:
//};
//
//class TextBook : public Book {
//public:
//	TextBook( unsigned numPages, unsigned numIndxPgs  )
//		: Book(numPages),
//		  numOfIndexPages(numIndxPgs)
//	{}
//	void displayNumPages() const
//	{
//		cout << numOfIndexPages << endl;
//		PrintedMaterial::displayNumPages();
//	}
//protected:
//private:
//	unsigned numOfIndexPages;
//};
//
//class Novel : public Book {
//public:
//	Novel( unsigned numPages )
//		: Book(numPages)
//	{}
//protected:
//private:
//};

// ===== TASK 9 =====
//class PrintedMaterial {
//public:
//	PrintedMaterial( unsigned numPages )
//		: numOfPages(numPages)
//	{}
//	void displayNumPages() const
//	{ cout << numOfPages << endl; }
//protected:
//private:
//	unsigned numOfPages;
//};
//
//class Magazine : public PrintedMaterial {
//public:
//	Magazine( unsigned numPages )
//		: PrintedMaterial(numPages)
//	{}
//protected:
//private:
//};
//
//class Book : public PrintedMaterial {
//public:
//	Book( unsigned numPages )
//		: PrintedMaterial(numPages)
//	{}
//protected:
//private:
//};
//
//class TextBook : public Book {
//public:
//	TextBook( unsigned numPages, unsigned numIndxPgs  )
//		: Book(numPages),
//		  numOfIndexPages(numIndxPgs)
//	{}
//	void displayNumPages() const
//	{
//		cout << "Textbook: " << numOfIndexPages << endl;
//		PrintedMaterial::displayNumPages();
//	}
//protected:
//private:
//	unsigned numOfIndexPages;
//};
//
//class Novel : public Book {
//public:
//	Novel( unsigned numPages )
//		: Book(numPages)
//	{}
//protected:
//private:
//};

// ===== TASK 11 =====
//class PrintedMaterial {
//public:
//	PrintedMaterial( unsigned numPages )
//		: numOfPages(numPages)
//	{}
//	virtual void displayNumPages() const
//	{ cout << numOfPages << endl; }
//protected:
//private:
//	unsigned numOfPages;
//};
//
//class Magazine : public PrintedMaterial {
//public:
//	Magazine( unsigned numPages )
//		: PrintedMaterial(numPages)
//	{}
//protected:
//private:
//};
//
//class Book : public PrintedMaterial {
//public:
//	Book( unsigned numPages )
//		: PrintedMaterial(numPages)
//	{}
//protected:
//private:
//};
//
//class TextBook : public Book {
//public:
//	TextBook( unsigned numPages, unsigned numIndxPgs  )
//		: Book(numPages),
//		  numOfIndexPages(numIndxPgs)
//	{}
//	void displayNumPages() const
//	{
//		cout << "Textbook: " << numOfIndexPages << endl;
//		PrintedMaterial::displayNumPages();
//	}
//protected:
//private:
//	unsigned numOfIndexPages;
//};
//
//class Novel : public Book {
//public:
//	Novel( unsigned numPages )
//		: Book(numPages)
//	{}
//protected:
//private:
//};

//===== TASK 12 =====
//void displayAnyNumPages(const PrintedMaterial& pm){
//    pm.displayNumPages();
//}

//===== TASK 13 =====
class PrintedMaterial {
public:
	PrintedMaterial( unsigned numPages )
		: numOfPages(numPages)
	{}
	virtual void displayNumPages() const = 0;
protected:
private:
	unsigned numOfPages;
};

class Magazine : public PrintedMaterial {
public:
	Magazine( unsigned numPages )
		: PrintedMaterial(numPages)
	{}

	void displayNumPages() const{
        cout << "Magazine: ";
        PrintedMaterial::displayNumPages();
	}
protected:
private:
};

class Book : public PrintedMaterial {
public:
	Book( unsigned numPages )
		: PrintedMaterial(numPages)
	{}
protected:
private:
};

class TextBook : public Book {
public:
	TextBook( unsigned numPages, unsigned numIndxPgs  )
		: Book(numPages),
		  numOfIndexPages(numIndxPgs)
	{}
	void displayNumPages() const
	{
		cout << "Textbook: " <<endl;
		cout << "Index Pages: " << numOfIndexPages << endl << "      ";
		cout << "Pages: ";
		PrintedMaterial::displayNumPages();
	}
protected:
private:
	unsigned numOfIndexPages;
};

class Novel : public Book {
public:
	Novel( unsigned numPages )
		: Book(numPages)
	{}
	void displayNumPages() const{
        cout << "Novel: ";
        PrintedMaterial::displayNumPages();
	}
protected:
private:
};

void PrintedMaterial::displayNumPages() const{
    cout << numOfPages << endl;
}
// tester/modeler code
int main()
{
	TextBook t(5430, 234);
	Novel n(213);
	Magazine m(6);

	t.displayNumPages();
	n.displayNumPages();
	m.displayNumPages();

	// ===== TASK 9 =====
//    PrintedMaterial pm = t;
//    pm.displayNumPages();

    // ===== TASK 10 =====
//    PrintedMaterial* pmPtr;
//    pmPtr = &t;
//    pmPtr->displayNumPages();

    // ===== TASK 12 =====
//    displayAnyNumPages(t);
//    displayAnyNumPages(n);

    //===== TASK 15 =====
    cout << "==== Now testing vector of PrintedMaterials!" << endl;
    vector<PrintedMaterial*> thingsToRead;
    thingsToRead.push_back(&t);
    thingsToRead.push_back(&n);
    thingsToRead.push_back(&m);
    for(PrintedMaterial* pm: thingsToRead){
        pm->displayNumPages();
    }
}
