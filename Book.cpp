#include "Book.h"
#include <string>
#include <algorithm>
using namespace std;

Book::Book()
{
    title = "Unknown";
    author = "Unknown";
    isbn = "0000000000";
    year = 0;
    checkedOut = false;
}

Book::Book(string t, string a, string i, int y)
{
    title = t;
    author = a;
    isbn = i;
    year = y;
    checkedOut = false;
}

string Book::getTitle() const
{
    return title;
}

string Book::getAuthor() const
{
    return author;
}

string Book::getIsbn() const
{
    return isbn;
}

int Book::getYear() const
{

    return year;
}

void Book::setCheckedOut(bool status)
{
    checkedOut = status;
}

bool Book::isCheckedOut() const
{
    return checkedOut;
}

bool Book::containsKeyword(string kw) const
{
    string lTitle = title;
    string lAuthor = author;
    string lKw = kw;

    // convert all three to lowercase before searching
    transform(lTitle.begin(), lTitle.end(), lTitle.begin(), ::tolower);
    transform(lAuthor.begin(), lAuthor.end(), lAuthor.begin(), ::tolower);
    transform(lKw.begin(), lKw.end(), lKw.begin(), ::tolower);

    return (lTitle.find(lKw) != string::npos ||
            lAuthor.find(lKw) != string::npos);
}

string Book::toString() const
{
    // Determine the status string tag based on the boolean
    string status = checkedOut ? "[CHECKED OUT]" : "[AVAILABLE]";

    // Construct the exact layout: [ISBN] Title — Author (Year) [STATUS]
    return "[" + isbn + "] " + title + " — " + author + " (" + to_string(year) + ") " + status;
}