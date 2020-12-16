// CS1300 Spring 2020
// Author: Anna Glass
// Recitation: 201 - Abhilash Jahagirdar
// Project2 - Problem #3

#ifndef LIBRARY_H
#define LIBRARY_H
#include <iostream>
#include <string>
#include "Book.h"
#include "User.h"
using namespace std;

// library class definition
class Library
{
    public:
        Library();
        int getNumBooks();
        int getNumUsers();
        int readBooks(string);
        int readRatings(string);
        // next 7 are helper functions
        bool initialized();
        int findUserIndex(string);
        int findBookIndex(string);
        bool validRate(int);
        bool minRate(int, int);
        bool recFound(int, int);
        int findSimilarUser(int);
        void viewRatings(string, int);
        void printAllBooks();
        void addUser(string);
        void updateRating(string, string, int);
        void getRecommendations(string);
        // extra credit functions
        bool checkUnreadBooks(int);
        bool checkDiscussionGroup(int, int);
        void viewUnreadBooks(string);
        void addBook(string, string);
        void getDiscussionGroup(string, string);
    
    private:
        // array of book objects (from book parameterized constructor)
        Book books[50];
        // array of user objects (from user member function)
        User users[100];
        int numBooks;
        int numUsers;
        // static constants made for maxbooks and users
        static const int maxBooks = 50;
        static const int maxUsers = 100;
};

#endif
