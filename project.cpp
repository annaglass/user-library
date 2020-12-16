// CS1300 Spring 2020
// Author: Anna Glass
// Recitation: 201 - Abhilash Jahagirdar
// Project2 - Problem #4

#include <iostream>
#include "Book.cpp"
#include "User.cpp"
#include "Library.cpp"
#include <string>
using namespace std;

int main()
{
    // calls constructor and creates object lib
    Library lib;
    int userChoice;
    
    // do while loop for menu
    do
    {
        // prints menu
        cout << "Select a numerical option:" << endl;
        cout << "======Main Menu=====" << endl;
        cout << "1. Read books" << endl << "2. Read ratings" << endl << 
        "3. View ratings" << endl << "4. Print all books" << endl <<
        "5. Update a rating" << endl << "6. Add a user" << endl <<
        "7. Get recommendations" << endl << "8. Add a book" << endl <<
        "9. Print all unread books" << endl << "10. Get discussion group"
        << endl << "11. Quit" << endl;
        // cin user choice, getline to ignore any returns/endlines
        cin >> userChoice;
        string str;
        getline(cin, str);
    
        // switch statement for user choice
        switch (userChoice)
        {
            case 1: // read books
            {
                // takes user filename
                cout << "Enter a book file name:" << endl;
                string bookFilename;
                cin >> bookFilename;
                // calls readBooks function, parameter filename
                int booksMain = lib.readBooks(bookFilename);
                // if it returns -1, print no books statement
                if (booksMain == -1)
                {
                    cout << "No books saved to the library." << endl;
                }
                // else prints statement and return value
                else
                {
                    cout << "Total books in the library: " << booksMain << endl;
                }
                break;
            }
            case 2: // read ratings
            {
                // takes user filename
                cout << "Enter a user file name:" << endl;
                string userFilename;
                cin >> userFilename;
                // calls readRatings function, parameter filename
                int usersMain = lib.readRatings(userFilename);
                
                // if it returns -1, print no users statement
                if (usersMain == -1)
                {
                    cout << "No users saved to the library." << endl;
                }
                // else prints statement and return value
                else
                {
                    cout << "Total users in the library: " << usersMain << endl;
                }
                break;
            }
            case 3: // view ratings
            {
                /* takes username and min rating, getline includes spaces. 
                   got help from someone else's piazza post for getline and cin */
                cout << "Enter a user name:" << endl;
                string userName;
                getline(cin, userName);
                cout << "Enter a minimum rating:" << endl;
                int minimumRating;
                cin >> minimumRating;
                // calls viewRatings function, parameters username and min rating
                lib.viewRatings(userName, minimumRating);
                break;
            }
            case 4: // print all books
                // calls printAllBooks function
                lib.printAllBooks();
                break;
            case 5: // update user's ratings
            {
                // gets username, book title, new rating
                cout << "Enter a user name:" << endl;
                string userName;
                getline(cin, userName);
                cout << "Enter a book title:" << endl;
                string bookTitle;
                getline(cin, bookTitle);
                cout << "Enter a new rating:" << endl;
                int newRate;
                cin >> newRate;
                // calls updateRating function
                lib.updateRating(userName, bookTitle, newRate);
                break;
            }
            case 6: // add a user
            {
                // takes username
                cout << "Enter a user name:" << endl;
                string userName;
                getline(cin, userName);
                // calls addUser function
                lib.addUser(userName);
                break;
            }
            case 7: // get recommendations
            {
                // takes username
                cout << "Enter a user name:" << endl;
                string userName;
                getline(cin, userName);
                // calls getRecommendations function
                lib.getRecommendations(userName);
                break;
            }
            case 8: // add a book
            {
                cout << "Enter a book title:" << endl;
                string bookTitle;
                getline(cin, bookTitle);
                cout << "Enter the author:" << endl;
                string authorBook;
                getline(cin, authorBook);
                lib.addBook(bookTitle, authorBook);
                break;
            }
            case 9: // print all unread books
            {
                cout << "Enter a user name:" << endl;
                string userName;
                getline(cin, userName);
                lib.viewUnreadBooks(userName);
                break;
            }
            case 10: // get discussion group
            {
                cout << "Enter a user name:" << endl;
                string userName;
                getline(cin, userName);
                cout << "Enter a book title:" << endl;
                string bookTitle;
                getline(cin, bookTitle);
                lib.getDiscussionGroup(userName, bookTitle);
                break;
            }
            case 11: // quit
                cout << "Good bye!" << endl;
                break;
            default: // default to invalid option takes user back to menu
                cout << "Invalid option." << endl;
                break;
        }
    } while (userChoice != 11);
}