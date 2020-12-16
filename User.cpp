// CS1300 Spring 2020
// Author: Anna Glass
// Recitation: 201 - Abhilash Jahagirdar
// Project2 - Problem #2

#include <iostream>
#include <string>
#include "User.h"
using namespace std;

// user class member functions
// default constructor
User :: User() 
{
    username = "";
    // loop initalizes all elements of ratings array to 0
    for (int i; i < size; i++)
    {
        ratings[i] = 0;
    }
}

// void function takes a string and sets it as the username
void User :: setUsername(string usernameUser)
{
    username = usernameUser;
}

/* bool function takes an index and rating value, assigns rating at index in ratings
   array if valid and returns true, otherwise does nothing and returns false. */
bool User :: setRatingAt(int j, int ratingUser)
{
    // checks if index and rating are valid
    if (j >= 0 && j < size && ratingUser >= 0 && ratingUser <= 5)
    {
        // assigns array index to the rating and returns true
        ratings[j] = ratingUser;
        return true;
    }
    else
    {
        // if invalid, does nothing and returns false
        return false;
    }
}

// string function returns name of the user
string User :: getUsername()
{
    return username;
}

/* int function takes an index, if it is within bounds of ratings array it
returns the rating value at the index, if not returns -1 */
int User :: getRatingAt(int j)
{
    // checks if index is in bounds
    if (j >= 0 && j < size)
    {
        // returns value at the array index
        return ratings[j];
    }
    else
    {
        return -1;
    }
}
