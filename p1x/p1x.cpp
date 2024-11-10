// AUTHOR: [Your Name]
// PROGRAM: Book Recommendation System
// PURPOSE: Implementation of a book recommendation system.
//          This program allows users to add members, books, and ratings,
//          login/logout, view and rate books, and receive book recommendations.
// INPUT:   File paths to input files containing information about books and ratings.
// PROCESS: The program reads data from input files to populate member, book, and rating records.
//          Users can perform various actions through a menu-driven interface, including adding members/books,
//          logging in, rating books, viewing ratings, and receiving recommendations based on their preferences.
// OUTPUT:  Display messages indicating successful operations, error messages for invalid input or operations,
//          and recommendations for books based on user preferences


#include<iostream>
#include<string>
#include "BookList.h"
#include "MemberList.h"
#include "RatingList.h"
#include<sstream>
#include<fstream>

#define INITIAL_MEM_CAP 100
#define INITIAL_BOOK_CAP	100


using namespace std;

// Struct representing a session in the book recommendation system
struct Session{


    bool AdminLogIn = false;
    MemberList* memRecord;  // Pointer to the member list
    BookList* bookRecord;   // Pointer to the book list
    RatingList* ratings;    // Pointer to the rating list
    int totalMembers = 0;   // Total number of members
    int totalBooks = 0;     // Total number of books
    int capacityMembers;    // Capacity of the member list
    int capacityBooks;      // Capacity of the book list
    int loggedInUser = -1;  // ID of the currently logged-in user



    // Constructor initializes member, book, and rating records with initial capacities
    Session(){
        memRecord = new MemberList(INITIAL_MEM_CAP);
        bookRecord = new BookList(INITIAL_BOOK_CAP);
        ratings = new RatingList(INITIAL_MEM_CAP,INITIAL_BOOK_CAP);
        capacityMembers = INITIAL_MEM_CAP;
        capacityBooks = INITIAL_BOOK_CAP;

    }

    // Getter method to retrieve the rating for a given member and book
    int getRating(int member, int isbn ){
        return (ratings->getRatingMap())[member][isbn];
    }

    // Getter method to retrieve the profile of the currently logged-in user
    Member myProfile(){
        return (memRecord->getMemberArray())[loggedInUser];
    }

    // Getter method to retrieve details of a book based on ISBN
    Book bookDetail(int isbn){
        return (bookRecord->getBookArray())[isbn];
    }

    // Getter method to retrieve the ID of the currently logged-in user
    int currentUser(){
        return loggedInUser;
    }

    // Getter method to retrieve the total number of books
    int getNumBooks(){
        return totalBooks;
    }

    // Getter method to retrieve the total number of members
    int getNumMembers(){
        return totalMembers;
    }

    // Setter method to set the admin login status
    void setAdminLogIn(){
        AdminLogIn = 1;
    }

    // Setter method to unset the admin login status
    void unsetAdminLogIn(){
        AdminLogIn = 0;
    }

    // Method to check the privilege level of the current user
    bool privilageLevel(){
        return AdminLogIn;
    }


    // Method to logout the current user
    void logout(){
        loggedInUser = -1;

    }

    // Method to log in a user given their member ID
    void login(int memID){
        if(loggedInUser != -1 ){
            if(memID == this->loggedInUser){
                cout<<"You are already logged in."<<endl;
                return;
            }
            string verdict;
            cout<<"User with Account no. "<< this->loggedInUser;
            cout<<" already logged in, ";
            cout<<"do you want to logout and login with account ";
            cout<<memID<<" ? (y/n)"<<endl;
            cin>>verdict;
            if(verdict[0] == 'y'){
                this->logout();

                loggedInUser = memID;
            }

        }
        else{
            loggedInUser = memID;
        }
    }

    // Method to add a new member to the system
    void addMember(string name){

        memRecord->addMember(name,loggedInUser);
        totalMembers++;
        if(totalMembers >= capacityMembers){
            ratings->resizeMembers();
            capacityMembers = 2*capacityMembers;
        }

    }

    // Method to add a new book to the system
    void addBook(string Author, string Title, int Year){

        bookRecord->addBook(Author, Title, Year, loggedInUser);
        totalBooks++;
        if(totalBooks >= capacityBooks){
            ratings->resizeBooks();
            capacityBooks = 2*capacityBooks;
        }

    }

    // Method to add a rating for a book given the member ID, book ISBN, and rating
    void addRating(int member, int book, int rating){

        if(loggedInUser == -1 && !AdminLogIn){
            cout<<"Please login to add rating to the database\n";
            return;
        }

        if(member >= totalMembers){
            cout<<"Member with account no. ";
            cout<<member;
            cout<<" does not exist in the database.\n";
        }
        if(book >= totalBooks){
            cout<<"Book with ISBN no. ";
            cout<<book<<"does not exist in the database. \n";
        }


        (ratings->getRatingMap())[member][book] = rating;
    }

    // Method to get recommendations for books based on user preferences
    void getRecomendations(){
        int** similarity;
        similarity = ratings->recomendBook(loggedInUser);

        int* detail = 	similarity[0];
        int* books = similarity[1];
        int similarUser = detail[0];
        int count = detail[1];
        int firstLimit = -1;
        int secondLimit = -1;
        cout<<"You have similar taste in books as ";
        cout<< ((memRecord->getMemberArray())[similarUser]).Name;
        cout<<" !\n\n";

        int* bestbooks = new int[count];
        int* secondBestBooks =new  int[count];
        for(int i = 0 ; i<count ; i++){
            int rating1 = (ratings->getRatingMap())[similarUser][books[i]];
            int rating2 = (ratings->getRatingMap())[similarUser][books[i-1]];
            if(i>0 && rating1 != rating2){

                break;

            }
            bestbooks[i] = books[i];
            firstLimit = i;

        }


        for(int i = firstLimit+1 ; i<count && firstLimit+1 > 0  ; i++){
            int rating1 = (ratings->getRatingMap())[similarUser][books[i]];
            int rating2 = (ratings->getRatingMap())[similarUser][books[i-1]];
            if(i>0 && (i != firstLimit+1) && rating1 != rating2){
                break;
            }
            secondBestBooks[i] = books[i];
            secondLimit = i;
        }

        cout<<"Here are the books they really liked: \n";
        for(int i = firstLimit ; i>=0 ; i--){
            Book b = (bookRecord->getBookArray())[bestbooks[i]];
            cout<< b.ISBN <<", "<< b.Author << ", ";
            cout<< b.Title << ", " << b.Year <<"\n";

        }
        cout<<"\n";
        cout<<"And here are the books they liked: \n";

        for(int i = secondLimit ; i>firstLimit ; i--){
            Book b = (bookRecord->getBookArray())[secondBestBooks[i]];
            cout<< b.ISBN <<", "<< b.Author << ", " ;
            cout<< b.Title << ", " << b.Year <<"\n";
        }



        cout<<"\n\n";


    }


    // Method to write book data to a file
    void writeBookFile(string filePath){
        ofstream outputFile(filePath);
        for(int i = 0 ; i<totalBooks ; i++){
            Book b = (bookRecord->getBookArray())[i];
            outputFile<<b.Author<<","<<b.Title<<","<<b.Year<<"\n";
        }
        outputFile.close();
    }

    // Method to write rating data to a file
    void writeRatingsFile(string filePath){
        ofstream outputFile(filePath);
        for(int i = 0 ; i<totalMembers ; i++){
            outputFile<<(memRecord->getMemberArray())[i].Name<<"\n";
            for(int j = 0 ; j<totalBooks ; j++){
                outputFile<<(ratings->getRatingMap())[i][j]<<" ";
            }
            outputFile<<"\n";
        }
        outputFile.close();
    }


};

// Function to prompt the user to add a new book
void PromtaddBook(Session* s){


    string author,title;
    int year;
    cin.ignore();
    cout<<"Enter the author of the new book: ";
    getline(cin,author);
    cout<<"Enter the title of the new book: ";
    getline(cin,title);
    cout<<"Enter the year of the new book: ";
    cin>>year;
    cin.ignore();
    // cout<<"\n";
    s->addBook(author,title,year);
    cout<<(s->getNumBooks());
    cout << ", " << author << ", " << title << ", " << year ;
    cout<< " was added\n\n";


}

// Function to prompt the user to add a new member
void PromtaddMember(Session* s){
    string member;
    cout<<"Enter the name of the new member: ";
    cin>>member;
    // cout<<"\n";
    s->addMember(member);
    cout<<member<<", "<<"(account #: ";
    cout<<(s->getNumMembers()) <<") "<<"was added.\n\n";

}

// Function to prompt the user to log in
void PromtlogIN(Session* s){
    int mem;
    cout<<"Enter member account: ";
    cin>>mem;

    while(mem <= 0){
        cout<<"\n";
        cout<<"Please enter a valid account number (>0)\n";
        cout<<"Enter member account: ";
        cin>>mem;
    }

    // cout<<"\n";
    s->login(mem-1);
    cout<<(s->myProfile()).Name<<", you are logged in!\n\n";
}

// Function to prompt the user to rate a book
void Promtrate(Session* s){
    int ISBN,rating;
    string verdict;
    cout<<"Enter the ISBN for the book you'd like to rate: ";
    cin>>ISBN;
    // cout<<"\n";
    Book b = s->bookDetail(ISBN-1);
    if((s->getRating(s->currentUser(),ISBN-1)) != 0){

        cout<<"Your current rating for ";
        cout<<ISBN<<", "<<b.Author<<", "<<b.Title<<", "<<b.Year;
        cout<<" => rating: "<<(s->getRating(s->currentUser(),ISBN-1)) <<"\n";
        cout<<"Would you like to re-rate this book (y/n)? ";
        cin>>verdict;
        // cout<<"\n";
        if(verdict[0]=='y'){
            cout<<"Enter your rating: ";
            cin>>rating;
            cout<<"\n";
            s->addRating(s->currentUser(), ISBN-1, rating);
            cout<<"Your new rating for ";
            cout<<ISBN<<", "<<b.Author<<", "<<b.Title<<", "<<b.Year;
            cout <<" => rating: "<< (s->getRating(s->currentUser(),ISBN-1));
            cout<<"\n\n";

        }
    }
    else{
        cout<<"Enter your rating: ";
        cin>>rating;
        // cout<<"\n";
        s->addRating(s->currentUser(), ISBN-1, rating);
        cout<<"Your new rating for ";
        cout<<ISBN<<", "<<b.Author<<", "<<b.Title<<", "<<b.Year ;
        cout<< " => rating: "<< (s->getRating(s->currentUser(),ISBN-1));
        cout<<"\n\n";

    }
}

// Function to print ratings for books
void printRatings(Session* s){
    int numBooks = s->getNumBooks();
    for(int i = 0 ; i<numBooks ; i++){
        Book b = s->bookDetail(i);
        cout<<b.ISBN<<", "<<b.Author<<", "<<b.Title<<", "<<b.Year;
        cout<<" => rating: "<< (s->getRating(s->currentUser(),i))<<"\n";

    }
}

int showMainMenu(){
    int option;
    cout<<"************** MENU **************\n*";
    cout<<" 1. Add a new member            *\n*";
    cout<<" 2. Add a new book              *\n*";
    cout<<" 3. Login                       *\n*";
    cout<<" 4. Quit                        *\n";
    cout<<"**********************************\n\n";
    cout<<endl;
    cout<<"Enter a menu option: ";
    cin>>option;
    cout<<"\n";
    return option;
}

// Function to display the main menu and prompt user for input
int showLogInMenu(){
    int option;
    cout<<"************** MENU **************\n*";
    cout<<" 1. Add a new member            *\n*";
    cout<<" 2. Add a new book              *\n*";
    cout<<" 3. Rate book                   *\n*";
    cout<<" 4. View ratings                *\n*";
    cout<<" 5. See recommendations         *\n*";
    cout<<" 6. Logout                      *\n";
    cout<<"**********************************\n\n";
    cout<<"Enter a menu option: ";
    cin>>option;
    cout<<"\n";
    return option;
}

// Function to read book data from a file and add it to the system
int readBookFile(Session* s, string bookFile ){

    ifstream inputfile;

    inputfile.open(bookFile);
    if(!inputfile){
        cout<<"Error opening book File.\n";
        return 0;
    }


    string word;
    string line;
    string author, title;
    int numBook = 0;
    int year = 1729;



    int indicator;
    while(getline(inputfile, line)){
        indicator = 0;
        stringstream ss(line);
        while(getline(ss, word, ',')){


            if(indicator == 0){
                author = line;

            }
            else if(indicator == 1){
                title = word;

            }
            else if(indicator == 2){
                // cout<<word<<endl;
                year = stoi(word);
                s->addBook(author, title, year);
                numBook++;

            }
            indicator = (indicator+1)%3;


        }

    }

    inputfile.close();
    return numBook;
}

// Function to read rating data from a file and add it to the system
int readRatingFile(Session* s, string ratingFile){

    ifstream inputfile;
    inputfile.open(ratingFile);

    if(!inputfile){
        cout<<"Error opening rating File.\n";
        return 0;
    }


    string member;
    string line;
    int rating;
    int indicator = 0;
    int numMember = 0;
    while(getline(inputfile, line)){
        stringstream ss(line);
        if(indicator == 0){
            member = line;
            s->addMember(member);
            numMember++;
        }
        else{
            int bookIndex = 0;

            while(ss >> rating){
                s->addRating(numMember-1, bookIndex, rating);
                bookIndex++;
            }

        }
        indicator = (indicator + 1) % 2;
        // cin.ignore();
    }
    inputfile.close();
    return numMember;
}

// Main function
int main(){


    // Creating a new session
    Session* currentSession = new Session();


    // Output welcome message
    cout<<"Welcome to the Book Recommendation Program.\n\n";
    cout << "This program is designed to provide book recommendations to users based on their past ratings and \n"
         << "similarities with other users' ratings, implementing algorithms similar to those used by online\n"
         <<"platforms for personalized recommendations.\n\n";

    // Variables to store file paths for book and rating data
    string bookFile;
    string ratingFile;

    // Checking if default files exist, if not, prompting user for file paths
    ifstream inputFile;
    inputFile.open("books-updated.txt");
    if(!inputFile){

        cout<<"Enter file path to books file: ";
        cin>>bookFile;
        cout<<"Enter file path to rating file: ";
        cin>>ratingFile;
        cout<<"\n\n";



    }
    else{
        bookFile = "books-updated.txt";
        ratingFile = "ratings-updated.txt";
    }
    inputFile.close();

    // Setting admin login status, reading data from files, and unsetting admin login status
    currentSession->setAdminLogIn();
    int numBook = readBookFile(currentSession, bookFile);
    int numMember = readRatingFile(currentSession, ratingFile);
    currentSession->unsetAdminLogIn();


    // Outputting the number of books and members read from files
    cout<<"# of books: "<<numBook<<"\n";
    cout<<"# of members: "<<numMember<<"\n";

    cout<<"\n\n";

    // Main loop for interacting with the program
    bool quit = 0;

    while(!quit){
        int option = showMainMenu();

        // Handling user input based on selected option
        while(!(option >=1 && option <= 4)){
            cout<<"Please enter a valid option between 1 and 4\n\n";
            option = showMainMenu();
        }

        if(option == 1){
            PromtaddMember(currentSession);
        }

        else if(option == 2){
            PromtaddBook(currentSession);
        }

        else if(option == 3){
            PromtlogIN(currentSession);
            bool loggedIN = 1;
            while(loggedIN){
                int choice = showLogInMenu();

                while(!(choice >=1 && choice <= 6)){
                    cout<<"Please enter a valid option between 1 and 6\n\n";
                    choice = showLogInMenu();
                }

                if(choice == 1){
                    PromtaddMember(currentSession);
                }
                else if(choice == 2){
                    PromtaddBook(currentSession);
                }
                else if(choice == 3){
                    Promtrate(currentSession);
                }
                else if(choice==4){
                    cout<<(currentSession->myProfile()).Name<<"'s ratings...\n";
                    printRatings(currentSession);
                    cout<<"\n\n";
                }
                else if(choice == 5){
                    currentSession->getRecomendations();
                }
                else if(choice == 6){
                    currentSession->logout();
                    loggedIN = 0;
                    continue;
                }


            }
        }

        else if(option == 4){
            quit = 1;
            cout<<"Thank you for using the Book Recommendation Program!\n\n";
            continue;
        }

    }

    // Writing book and rating data back to files before exiting
    currentSession->writeBookFile("books-updated.txt");
    currentSession->writeRatingsFile("ratings-updated.txt");


    return 0;
}
