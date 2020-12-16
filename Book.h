// CS1300 Spring 2020
// Author: Anna Glass
// Recitation: 201 - Abhilash Jahagirdar
// Project2 - Problem #1

#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
using namespace std;

// class definition
class Book
{
    public:
        Book();
        Book(string, string);
        string getTitle();
        string getAuthor();
        void setTitle(string);
        void setAuthor(string);
    
    private:
        string title;
        string author;
};

#endif
