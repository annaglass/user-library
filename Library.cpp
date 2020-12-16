// CS1300 Spring 2020
// Author: Anna Glass
// Recitation: 201 - Abhilash Jahagirdar
// Project2 - Problem #3

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "Library.h"
#include "User.h"
#include "split.cpp"
using namespace std;

// library class member functions
// default constructor
Library :: Library()
{
    numBooks = 0;
    numUsers = 0;
}

// int function returns number of books
int Library :: getNumBooks()
{
    return numBooks;
}

// int function returns number of users
int Library :: getNumUsers()
{
    return numUsers;
}

/* int function takes a filename, reads a list of books in the file, stores them
   in the books array, and returns the number of books stored in the array */
int Library :: readBooks(string filename)
{
    // created ifstream object project2
    ifstream project2;
    // opens file, if file can't be opened return -1
    project2.open(filename);
    if (project2.fail())
    {
        return -1;
    }
    
    string author;
    string title;
    
    /* loop adds each book in list to the array, given the number of current books
       is less than 50 and the end of file hasn't been reached. getline puts
       all chars before the delimeter comma into the author string  */
    while (numBooks < maxBooks && getline(project2, author, ','))
    {
        // adds found author to current index in books array 
        books[numBooks].setAuthor(author);
        // gets rest of line and puts into title string
        getline(project2, title);
        // adds found title to current index in books array
        books[numBooks].setTitle(title);
        // adds one to number of books, next loop the index in array will move up
        numBooks++;
    }
    // close file and return the number of books
    project2.close();
    return numBooks;
}

/* int function takes a filename, reads a list of users and ratings, stores them
   in users array, then returns number of users in array */
int Library :: readRatings(string filename)
{
    // creates ifstream object project2
    ifstream project2;
    // opens file, if it can't be opened return -1
    project2.open(filename);
    if (project2.fail())
    {
        return -1;
    }
    
    string username;
    string ratingsLine;
    int rating;
    string ratingstr[maxBooks];
    
    /* loop continues if current num books is less than 50, current num users is
       less than 100, and end of file hasn't been reached */
    while ((numBooks < maxBooks) && (numUsers < maxUsers) 
    && (getline(project2, username)))
    {
        // adds found username from getline to current index in users array
        users[numUsers].setUsername(username);
        // gets the next line into string ratingsLine
        getline(project2, ratingsLine);
        // calls split function, splits string by delimeter and puts into ratingstr
        int count = split(ratingsLine, ',', ratingstr, maxBooks);
        /* for loop changes string into integer, adds this value to current index 
            in users array */
        for (int i = 0; i < count; i++)
        {
            rating = stoi(ratingstr[i]);
            users[numUsers].setRatingAt(i, rating);
        }
        // increases index for each loop
        numUsers++;
    }
    // closes file and returns the number of users
    project2.close();
    return numUsers;
}

//HELPER FUNCTIONS
// toLower function makes any string all lowercase
string toLower(string str)
{
    // goes through each char of the string
    for (int i = 0; i < str.length(); i++)
    {
        // if the letter is uppercase
        if(str[i] >= 65 && str[i] <= 90)
        {
            // changes to lowercase using ASCII values
            str[i] = str[i] + 32;
        }
    }
  // returns lowercase string
  return str; 
}

// bool function checks if the library is initialized
bool Library :: initialized()
{
    // if there are users and books in library, return true
    if (numUsers > 0 && numBooks > 0)
    {
        return true;
    }
    // if not, cout not initialized statement and return false
    cout << "The library has not been fully initialized." << endl;
    return false;
}

// int function takes username and returns its index in the users array
int Library :: findUserIndex(string user)
{
    // loop goes through users array
    for (int i = 0; i < numUsers; i++)
    {
        // if the username is found, return that index
        if (toLower(users[i].getUsername()) == toLower(user))
        {
            return i;
        }
    }
    // if username is never found, returns -1
    return -1;
}

// int function takes a book title and returns its index in the books array
int Library :: findBookIndex(string title)
{
    // loop goes through books array
    for (int i = 0; i < numBooks; i++)
    {
        // if the title is found, return that index
        if (toLower(books[i].getTitle()) == toLower(title))
        {
            return i;
        }
    }
    // if title is never found, return -1
    return -1;
}

// bool function takes an rating integer and determines if it is valid
bool Library :: validRate(int rate)
{
    // if rate is between 0 and 5 inclusive, return true
    if (rate >= 0 && rate <= 5)
    {
        return true;
    }
    // if invalid, cout statement and return false
    cout << rate << " is not valid." << endl;
    return false;
}

/* bool function takes user index and the min value, checks if user has any
   ratings above the min value */
bool Library :: minRate(int user, int min)
{
    // loop goes through ratings array
    for (int i = 0; i < numBooks; i++)
    {
        // if the user's rating for the current book index is more than min return true
        if (users[user].getRatingAt(i) >= min)
        {
            return true;
        }
    }
    // if no ratings are above the min return false
    return false;
}

/* bool function takes the index of 2 users, the one receiving and giving
   the recommendation. checks if any recommendations can be given based on
   value of ratings */
bool Library :: recFound(int user1, int user2)
{
    // loop goes through ratings array
    for (int i = 0; i < numBooks; i++)
    {
        /* if the recommending users rating at the book index is more than 2
           and the recomendee rating for the book is 0, return true 
           (a recommendation can be made)  */
        if (users[user2].getRatingAt(i) >= 3 && users[user1].getRatingAt(i) == 0)
        {
            return true;
        }
    }
    // else no recommendations can be made, return false
    return false;  
}

/* int function takes index for recommendee user and finds the most similar
   user using the sum of squares formula  */
int Library :: findSimilarUser(int user1)
{
    // 2500 is the max sumofsquares possible
    int minimum = 2501;
    int foundUser = -1;
    
    // loop looks for user
    for (int i = 0; i < numUsers; i++)
    {
        int sumSquares = 0;
        //if the user found is not the recomendee
        if (i != user1)
        {     
            bool valid = false;
            // loop looks for ratings
            for (int j = 0; j < numBooks; j++)
            {
                // sets squares back to 0 for each book
                int squares = 0;
                // temp rate stores users rating for the current book
                int tempRate = users[i].getRatingAt(j);
                // if a rating is more than 0, user is made valid
                if (tempRate > 0)
                {
                    valid = true;
                }
                // gets rating for the first user
                int user1Rate = users[user1].getRatingAt(j);
                // uses squares formula to compare similarity of users for that book
                squares = pow((user1Rate-tempRate), 2);
                // sums all the squares for the users similarity
                sumSquares = sumSquares + squares;
            }
            // if sumofsquares is a new minimum we have found a more similar user
            if (sumSquares < minimum && valid)
            {
                // sets the new minimum, sets the index as the found user
                minimum = sumSquares;
                foundUser = i;
            }
        }
    }
    // returns found user
    return foundUser;
}

// bool function checks if user has not read a book
bool Library :: checkUnreadBooks(int user)
{
    // loop goes through ratings array and looks for 0
    for (int i = 0; i < numBooks; i++)
    {
        if (users[user].getRatingAt(i) == 0)
        {
            return true;
        }
    }
    return false;
}

// bool function checks if any user has a rating 3 or more for a given book 
bool Library :: checkDiscussionGroup(int user, int title)
{
    // goes through ratings array and looks for a rating 3 or more
    for (int i = 0; i < numUsers; i++)
    {
        if (i != user && users[i].getRatingAt(title) >= 3)
        {
            return true;
        }
    }
    return false;
}
//END HELPER FUNCTIONS

/* void function takes username and minimum rating, prints books that the user
   has rated above or equal to the min rating value  */
void Library :: viewRatings(string username, int minRating)
{
    // calls user index and minimum function
    int userIndex = findUserIndex(username);
    bool minimum = minRate(userIndex, minRating);
    
    // calls initialized function, returns if not initialized
    if (!initialized())
    {
        return;
    }
    // if user index is -1, cout dne and return
    if (userIndex == -1)
    {
        cout << username << " does not exist." << endl;
        return;
    }
    /* if minimum function returns false, cout statement and return
       as no ratings are higher than min  */
    if (minimum == false)
    {
        cout << username << " has not rated any books with " << minRating 
        << " or higher." << endl;
        return;
    }

    cout << "Here are the books that " << username << " rated" << endl;
    // loop prints books that user has rated above the minimum
    for (int i = 0; i < numBooks; i++)
    {
        if (users[userIndex].getRatingAt(i) >= minRating)
        {
            cout << "Title : " << books[i].getTitle() << endl;
            cout << "Rating : " << users[userIndex].getRatingAt(i) << endl;
            cout << "-----" << endl;
        }
    }
}

//EC function, prints the books that a user has not yet read
void Library :: viewUnreadBooks(string username)
{
    // looks for user by calling userIndex function
    int userIndex = findUserIndex(username);
    // calls initialized function, returns if not initialized
    if (!initialized())
    {
        return;
    }
    // if user index isn't found, cout dne and return
    if (userIndex == -1)
    {
        cout << username << " does not exist." << endl;
        return;
    }
    // called checkUnreadBooks helper function, if not ratings are 0 print and return
    if (checkUnreadBooks(userIndex) == false)
    {
        cout << username << " has read all of the books in the library." << endl;
        return;
    }
    cout << "Here are the books that " << username << " has not read." << endl;
    // loop looks for books with a rating of 0 by given user
    for (int i = 0; i < numBooks; i++)
    {
        if (users[userIndex].getRatingAt(i) == 0)
        {
            // prints title and author of unread books
            cout << "Title : " << books[i].getTitle() << " by" 
            << books[i].getAuthor() << endl;
            cout << "-----" << endl;
        }
    }
}

// void function prints all books in the library
void Library :: printAllBooks()
{
    // checks if library is initialized
    if (!initialized())
    {
        return;
    }
    // loop goes through books
    for (int i = 0; i < numBooks; i++)
    {
        int count = 0;
        int sum = 0;
        
        // loop goes through ratings
        for (int j = 0; j < numUsers; j++)
        {
            // if the users rating for the book isn't zero it is included in calculations
            if (users[j].getRatingAt(i) != 0)
            {
                // sum adds ratings for the book, increments count to be used in average
                sum = sum + users[j].getRatingAt(i);
                count++;
            }
        }
        // average calculated
        double average = 1.0 * sum / count;
        // print average with set precision 2 and the book title/author
        cout << "(" << fixed << setprecision(2) << average << ") " << books[i].getTitle(); 
        cout << " by " << books[i].getAuthor() << endl;
    }
}

// void function takes username and adds it to users array
void Library :: addUser(string username)
{
    // if the library is full, print statement and don't add user
    if (numUsers == maxUsers)
    {
        cout << "The library is already full. " << username << " was not added." << endl;
        return;
    }
    // calls findUserIndex function, if it is found cout statement and don't add user
    if (findUserIndex(username) != -1)
    {
        cout << username << " already exists in the library." << endl;
        return;
    }
    // else add the user to the library and print statement
    users[numUsers++].setUsername(username);
    cout << "Welcome to the library " << username << endl;
}

// void function takes a title and author of a book and adds it to the books array
void Library :: addBook(string book, string author)
{
    // if there are already 50 books don't add the book, print statement
    if (numBooks == maxBooks)
    {
        cout << "There is no space in the library for a new book. " << book <<
        " by " << author << " was not added." << endl;
        return;
    }
    // calls findBookIndex, if it was found print statement and don't add
    if (findBookIndex(book) != -1)
    {
        cout << book << " by " << author << " already exists in the library." << endl;
        return;
    }
    // sets title and author of book to the next available spot in array, prints statement
    books[numBooks++].setTitle(book);
    books[numBooks].setAuthor(author);
    cout << book << " by " << author << " was added to the library." << endl;
}

/* void function takes username, title, and the users new rating for the book,
   then updates it in the ratings array  */
void Library :: updateRating(string username, string title, int newRating)
{
    // checks if library is initialized
    if (!initialized())
    {
        return;
    }
    // calls findUserIndex function, if user isn't found print dne and return
    int userIndex = findUserIndex(username);
    if (userIndex == -1)
    {
        cout << username << " does not exist." << endl;
        return;
    }
    // calls findBookIndex function, if book isn't found return
    int bookIndex = findBookIndex(title);
    if (bookIndex == -1)
    {
        cout << title << " does not exist." << endl;
        return;
    }
    // if the new rating isn't valid, return
    if (!validRate(newRating))
    {
        return;
    }
    // else change the rating for the given book and user and print statement
    users[userIndex].setRatingAt(bookIndex, newRating);
    cout << "The rating has been updated." << endl;
}

/* void function takes a username and prints the recommendations from the most
   similar user  */
void Library :: getRecommendations(string username)
{
    // checks if library is initialized
    if (!initialized())
    {
        return;
    }
    // calls findUserIndex function, if not found print statement and return
    int userIndex = findUserIndex(username);
    if (userIndex == -1)
    {
        cout << "This user does not exist." << endl;
        return;
    }
    // calls findSimilarUser function
    int similarUser = findSimilarUser(userIndex);
    /* if recommendation isn't found for the user and most similar user, 
       print statement and return */
    if (!recFound(userIndex, similarUser))
    {
        cout << "There are no recommendations for " << username << " at present." << endl;
        return;
    }

    cout << "Here is the list of recommendations" << endl;
    int count = 0;
    /* loop goes through books and prints recommendations if similar user rating
       is more than 3 and the recomendee rating is 0 for the same book, with a 
       max of 5 books recommended */
    for (int i = 0; i < numBooks; i++)
    {
        if (users[similarUser].getRatingAt(i) >= 3 && users[userIndex].getRatingAt(i) == 0 && count < 5)
        {
            // prints title and author, increments count to continue loop
            cout << books[i].getTitle() << " by " << books[i].getAuthor() << endl;
            count++;
        }
    }
}

/* void function takes a username and book title and finds them a discussion group
  of other people who rated the book 3 or more, capped at 9 other people  */
void Library :: getDiscussionGroup(string username, string book)
{
    // check if library is initialized
    if (!initialized())
    {
        return;
    }
    // calls findUserIndex and findBookIndex functions, if not found print statement and return
    int userIndex = findUserIndex(username);
    int bookIndex = findBookIndex(book);
    if (userIndex == -1)
    {
        cout << "This user does not exist." << endl;
        return;
    }
    if (bookIndex == -1)
    {
        cout << "This book does not exist." << endl;
        return;
    }
    // if user didn't rate book 3 or above, print statement and return
    if (users[userIndex].getRatingAt(bookIndex) < 3)
    {
        cout << username << " rated " << book << " lower than 3, no discussion group given." << endl;
        return;
    }
    // call checkDiscussionGroup helper function, if returns false no group was found. return
    if (checkDiscussionGroup(userIndex, bookIndex) == false)
    {
        cout << "No other users rated " << book << " 3 or higher, no discussion group given." << endl;
        return;
    }
    
    cout << "Here is " << username << "'s discussion group for " << book << endl;
    int count = 0;
    // loop looks for users who rated the book 3 or more, prints name
    for (int i = 0; i < numUsers; i++)
    {
        // if i is not the user looking for a discussion group
        if (i != userIndex)
        {
            // if rating is 3 or more and 9 users haven't already been found for group
            if (users[i].getRatingAt(bookIndex) >= 3 && count < 10)
            {
                // print username and increment count
                cout << users[i].getUsername() << endl;
                count++;
            }
        }
    }
}
