// CS1300 Spring 2020
// Author: Anna Glass
// Recitation: 201 - Abhilash Jahagirdar
// Project2 - Problem #2

#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
using namespace std;

// user class definition
class User
{
    public:
        User();
        void setUsername(string);
        bool setRatingAt(int, int);
        string getUsername();
        int getRatingAt(int);
        
    private:
        string username;
        // static const size for the max number of ratings
        static const int size = 50; //shared between all instances of the class
        // array of integers for ratings
        int ratings[size]; 

};

#endif
