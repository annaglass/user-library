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
        static const int size = 50;
        int ratings[size];

};

User :: User()
{
    username = "";
    for (int i; i < size; i++)
    {
        ratings[i] = 0;
    }
}

void User :: setUsername(string usernameUser)
{
    username = usernameUser;
}

bool User :: setRatingAt(int j, int ratingUser)
{
    int size = 50;
    if (j >= 0 && j < size && ratingUser >= 0 && ratingUser <= 5)
    {
        ratings[j] = ratingUser;
        return true;
    }
    else
    {
        return false;
    }
}

string User :: getUsername()
{
    return username;
}

int User :: getRatingAt(int j)
{
    int size = 50;
    if (j >= 0 && j < size)
    {
        return ratings[j];
    }
    else
    {
        return -1;
    }
}

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


Book :: Book() //default construction
{
    title = "";
    author = "";
}

Book :: Book(string titleBook, string authorBook)
{
    title = titleBook;
    author = authorBook;
}

string Book :: getTitle()
{
    return title;
}

string Book :: getAuthor()
{
    return author;
}

void Book :: setTitle(string titleBook)
{
    title = titleBook;
}

void Book :: setAuthor(string authorBook)
{
    author = authorBook;
}

int split (string userString, char separator, string str[],int size)
{
    // if the user string is empty or array size is 0, return 0
    if (userString.length() == 0 || size==0)
    {
    return 0;
    }

    string storeString = "";
    int j = 0;
    //creates user string as the words plus the separators
    userString = userString + separator;

    for (int i = 0; i < userString.length(); i++)
    {
        // goes through string, if character is the separator
        if (userString[i] == separator)
        {
            //if the length of storeString is 0 skip to next if
            if (storeString.length() == 0) continue;
            //else array becomes storeString, add 1 to times split
            str[j]=storeString;
            j++;
            //if times split is same as size, return the size
            if(j==size)
            {
                return size;
            }
        //initialize storeString as 0 again
        storeString = "";
        }
        else
        {
            //else if the character is not the separator, the character is added to storeString
            storeString = storeString + userString[i];
        }
    }
    //return number of times split
    return j;
}
class Library
{
    public:
        Library();
        int getNumBooks();
        int getNumUsers();
        int readBooks(string);
        int readRatings(string);
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
    
    private:
        Book books[50];
        User users[100];
        int numBooks;
        int numUsers;
        static const int maxBooks = 50;
        static const int maxUsers = 100;
};

Library :: Library()
{
    numBooks = 0;
    numUsers = 0;
}

int Library :: getNumBooks()
{
    return numBooks;
}

int Library :: getNumUsers()
{
    return numUsers;
}

int Library :: readBooks(string filename)
{
    ifstream project2;
    project2.open(filename);
    if (project2.fail())
    {
        return -1;
    }
    
    string author;
    string title;
    while ((numBooks < maxBooks) && (getline(project2, author, ',')))
    {
        books[numBooks].setAuthor(author);
        getline(project2, title);
        books[numBooks].setTitle(title);
        numBooks++;
    }
    project2.close();
    return numBooks;
}

int Library :: readRatings(string filename)
{
    ifstream project2;
    project2.open(filename);
    if (project2.fail())
    {
        return -1;
    }
    
    string username;
    string ratingsLine;
    int rating;
    string ratingstr[maxBooks];
    while ((numBooks < maxBooks) && (numUsers < maxUsers) && (getline(project2, username)))
    {
        users[numUsers].setUsername(username);
        getline(project2, ratingsLine);
        int count = split(ratingsLine, ',', ratingstr, maxBooks);
        for (int i = 0; i < count; i++)
        {
            rating = stoi(ratingstr[i]);
            users[numUsers].setRatingAt(i, rating);
        }
        numUsers++;
    }
    project2.close();
    return numUsers;
}

//HELPER FUNCTIONS
string toLower(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if(str[i] >= 65 && str[i] <= 90)
        {
            str[i] = str[i] + 32;
        }
    }
  return str; 
}

bool Library :: initialized()
{
    if (numUsers > 0 && numBooks > 0)
    {
        return true;
    }
    cout << "The library has not been fully initialized." << endl;
    return false;
}

int Library :: findUserIndex(string user)
{
    for (int i = 0; i < 100; i++)
    {
        if (toLower(users[i].getUsername()) == toLower(user))
        {
            return i;
        }
    }
    return -1;
}

int Library :: findBookIndex(string title)
{
    for (int i = 0; i < numBooks; i++)
    {
        if (toLower(books[i].getTitle()) == toLower(title))
        {
            return i;
        }
    }
    cout << title << " does not exist." << endl;
    return -1;
}

bool Library :: validRate(int rate)
{
    if (rate >= 0 && rate <= 5)
    {
        return true;
    }
    cout << rate << " is not valid." << endl;
    return false;
}

bool Library :: minRate(int user, int min)
{
    for (int i = 0; i < 50; i++)
    {
        if (users[user].getRatingAt(i) >= min)
        {
            return true;
        }
    }
    return false;
}

bool Library :: recFound(int user1, int user2)
{
    for (int i = 0; i < numBooks; i++)
    {
        if ((users[user2].getRatingAt(i) >= 3) && (users[user1].getRatingAt(i) == 0))
        {
            return true;
        }
    }
    return false;  
}

int Library :: findSimilarUser(int user1)
{
    int minimum = 2501;
    int foundUser = -1;
    for (int i = 0; i < numUsers; i++) // looks for user
    {
        int sumSquares = 0;
        if (i != user1)  //if the user found is not user1
        {     
            bool valid = false;
            for (int j = 0; j < numBooks; j++) // looks for ratings
            {
                int squares = 0;
                int tempRate = users[i].getRatingAt(j);
                if (tempRate > 0)
                {
                    valid = true;
                }
                int user1Rate = users[user1].getRatingAt(j);
                squares = pow((user1Rate-tempRate), 2);
                sumSquares = sumSquares + squares;
            }
            if (sumSquares < minimum && valid) //finds minimum sumsquares
            {
                minimum = sumSquares;
                foundUser = i;
            }
        }
    }
    return foundUser;
}
//END HELPER FUNCTIONS


void Library :: viewRatings(string username, int minRating)
{
    int userIndex = findUserIndex(username);
    bool minimum = minRate(userIndex, minRating);
    
    if (!initialized())
    {
        return;
    }
    if (userIndex == -1)
    {
        cout << username << " does not exist." << endl;
        return;
    }
    if (minimum == false)
    {
        cout << username << " has not rated any books with " << minRating << " or higher." << endl;
        return;
    }

    cout << "Here are the books that " << username << " rated" << endl;
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

void Library :: printAllBooks()
{
    if (!initialized())
    {
        return;
    }
    for (int i = 0; i < numBooks; i++)
    {
        int count = 0;
        int sum = 0;
        
        for (int j = 0; j < numUsers; j++)
        {
            if (users[j].getRatingAt(i) != 0)
            {
                sum = sum + users[j].getRatingAt(i);
                count++;
            }
        }
        double average = 1.0 * sum / count;
        cout << "(" << fixed << setprecision(2) << average << ") " << books[i].getTitle(); 
        cout << " by " << books[i].getAuthor() << endl;
    }
}

void Library :: addUser(string username)
{
    if (numUsers == maxUsers)
    {
        cout << "The library is already full. " << username << " was not added." << endl;
        return;
    }
    if (findUserIndex(username) != -1)
    {
        cout << username << " already exists in the library." << endl;
        return;
    }
    users[numUsers++].setUsername(username);
    cout << "Welcome to the library " << username << endl;
}

void Library :: updateRating(string username, string title, int newRating)
{
    if (!initialized())
    {
        return;
    }
    int userIndex = findUserIndex(username);
    if (userIndex == -1)
    {
        cout << username << " does not exist." << endl;
        return;
    }
    int bookIndex = findBookIndex(title);
    if (bookIndex == -1)
    {
        return;
    }
    if (!validRate(newRating))
    {
        return;
    }
    users[userIndex].setRatingAt(bookIndex, newRating);
    cout << "The rating has been updated." << endl;
}

void Library :: getRecommendations(string username)
{
    if (!initialized())
    {
        return;
    }
    int userIndex = findUserIndex(username);
    if (userIndex == -1)
    {
        cout << "This user does not exist." << endl;
        return;
    }
    int similarUser = findSimilarUser(userIndex);
    if (!recFound(userIndex, similarUser))
    {
        cout << "There are no recommendations for " << username << " at present." << endl;
        return;
    }

    cout << "Here is the list of recommendations" << endl;
    int count = 0;
    for (int i = 0; i < numBooks; i++)
    {
        if (users[similarUser].getRatingAt(i) >= 3 && users[userIndex].getRatingAt(i) == 0 && count < 5)
        {
            cout << books[i].getTitle() << " by " << books[i].getAuthor() << endl;
            count++;
        }
    }
}

int main()
{
    int userChoice = 0;
    while (userChoice != 8)
    {
        cout << "Select a numerical option:" << endl;
        cout << "=====Main Menu=====" << endl;
        cout << "1. Read books" << endl << "2. Read ratings" << endl << 
        "3. View ratings" << endl << "4. Print all books" << endl <<
        "5. Update a rating" << endl << "6. Add a user" << endl <<
        "7. Get recommendations" << endl << "8. Quit" << endl;
        cin >> userChoice;
    
        Library lib;
        string userName;
        switch (userChoice)
        {
            case 1:
            {
                cout << "Enter a book file name:" << endl;
                string bookFilename;
                cin >> bookFilename;
                int booksMain = lib.readBooks(bookFilename);
                if (booksMain == -1)
                {
                    cout << "No books saved to the library." << endl;
                }
                else
                {
                    cout << "Total books in the library: " << booksMain << endl;
                }
                break;
            }
            case 2:
            {
                cout << "Enter a user file name:" << endl;
                string userFilename;
                cin >> userFilename;
                int usersMain = lib.readRatings(userFilename);
                if (usersMain == -1)
                {
                    cout << "No users saved to the library." << endl;
                }
                else
                {
                    cout << "Total users in the library: " << usersMain << endl;
                }
                break;
            }
            case 3:
            {
                cout << "Enter a user name:" << endl;
                cin >> userName;
                cout << "Enter a minimum rating:" << endl;
                int minimumRating;
                cin >> minimumRating;
                lib.viewRatings(userName, minimumRating);
                break;
            }
            case 4:
                lib.printAllBooks();
                break;
            case 5:
            {
                cout << "Enter a user name:" << endl;
                cin >> userName;
                cout << "Enter a book title:" << endl;
                string bookTitle;
                cin >> bookTitle;
                cout << "Enter a new rating:" << endl;
                int newRate;
                cin >> newRate;
                lib.updateRating(userName, bookTitle, newRate);
                break;
            }
            case 6:
                cout << "Enter a user name:" << endl;
                cin >> userName;
                lib.addUser(userName);
                break;
            case 7:
                cout << "Enter a user name:" << endl;
                cin >> userName;
                lib.getRecommendations(userName);
                break;
            case 8:
                cout << "Good bye!" << endl;
                break;
            default:
                cout << "Invalid option." << endl;
        }
    }
}