#ifndef BOOK_H
#define BOOK_H
#include <string>
using namespace std;

#include <string>

class Book
{
private:
    string title;
    string author;
    string isbn;
    int year;
    bool checkedOut;

public:
    Book();
    Book(string t, string a, string isbn, int y);

    string getTitle() const;  // const - do not wish to change title
    string getAuthor() const; // const - do not wish to change author
    string getIsbn() const;
    int getYear() const;
    void setCheckedOut(bool status);
    bool isCheckedOut() const;                  // const - isCheckedOut() is for getting, not setting
    bool containsKeyword(string keyword) const; // const - finding keyword should not change title
    string toString() const;                    // const - toString() should not change title, author, or year.
};

#endif