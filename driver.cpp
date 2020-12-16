#include <iostream>
#include "Book.cpp"
#include "User.cpp"
#include "Library.cpp"
using namespace std;

int main()
{
    /*
    Book hungerGame ("The Hunger Games", "Suzanne Collins");
    cout << hungerGame.getTitle() << endl;
    cout << hungerGame.getAuthor() << endl;

    Book divergent;
    divergent.setTitle("Divergent");
    divergent.setAuthor("Veronica Roth");
    cout << divergent.getTitle() << endl;
    cout << divergent.getAuthor() << endl;
    
    Book chronicle;
    cout << chronicle.getTitle() << endl;
    cout << chronicle.getAuthor() << endl;
    
    User hector;
    hector.setUsername("Hector Ramirez");
    hector.setRatingAt(0,4);
    cout << hector.getUsername() << endl;
    cout << hector.getRatingAt(0) << endl;
    */
    
    Library akriti;
    cout << akriti.getNumBooks() << endl;
    cout << akriti.getNumUsers() << endl;
    cout << akriti.readBooks("bad.txt");
    /*
    akriti.readRatings("ratings_mini.txt");
    akriti.viewRatings("Akriti", 4);
    akriti.printAllBooks();
    akriti.addUser("Akriti");
    akriti.updateRating("Akriti", "The Rosie Project", 4);
    akriti.getRecommendations("Akriti");
    
    
    Library vipra;
    vipra.readBooks("books_mini.txt");
    vipra.readRatings("ratings_mini.txt");
    vipra.viewRatings("Vipra", 2);
    */
    
return 0;
}