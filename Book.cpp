// CS1300 Spring 2020
// Author: Anna Glass
// Recitation: 201 - Abhilash Jahagirdar
// Project2 - Problem #1

#include <iostream>
#include <string>
#include "Book.h"
using namespace std;

// book class member functions
//default constructor
Book :: Book() 
{
    title = "";
    author = "";
}

//parameterized constructor
Book :: Book(string titleBook, string authorBook) 
{
    title = titleBook;
    author = authorBook;
}

// returns title
string Book :: getTitle() 
{
    return title;
}

// returns author
string Book :: getAuthor()
{
    return author;
}

// sets title
void Book :: setTitle(string titleBook)
{
    title = titleBook;
}

// sets author
void Book :: setAuthor(string authorBook) 
{
    author = authorBook;
}
