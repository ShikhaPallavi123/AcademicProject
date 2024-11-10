
// AUTHOR: Shikha Pallavi
// PROGRAM: main.cpp
// DATE: 04/16/2024
// PURPOSE: This program implements a Book Recommendation System where users can add members, add books, rate books,
// view ratings, and receive recommendations based on their preferences.
// INPUT: The program takes input from the user through the command line interface. Users can input options to perform
//        various tasks such as adding members, adding books, rating books, and more.
//        Additionally, the program reads book and rating data from external files provided by the user.
// PROCESS: The program utilizes several classes including Session, BookList, MemberList, and RatingList to manage
//           members, books, and ratings. It provides functionalities such as adding members and books, logging in
//           users, rating books, viewing ratings, and generating book recommendations.
// OUTPUT: The program outputs information and prompts for user interaction through the command line interface.
//         It displays messages confirming successful operations, error messages for invalid inputs or file errors,
//         and recommendations based on user preferences.
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

// Structure representing a session with members, books, and ratings
struct Session{


    bool AdminLogIn = 0;  // Flag to indicate admin login status
    MemberList* memRecord;  // Pointer to the member record
    BookList* bookRecord;  // Pointer to the book record
    RatingList* ratings;  // Pointer to the rating record
    int totalMembers = 0;  // Total number of members
    int totalBooks = 0; // Total number of books
    int capacityMembers;  // Capacity of members array
    int capacityBooks;  // Capacity of books array
    int loggedInUser = -1;  // ID of the currently logged-in user


    // Constructor to initialize session with default capacities
    Session(){
        memRecord = new MemberList(INITIAL_MEM_CAP);
        bookRecord = new BookList(INITIAL_BOOK_CAP);
        ratings = new RatingList(INITIAL_MEM_CAP,INITIAL_BOOK_CAP);
        capacityMembers = INITIAL_MEM_CAP;
        capacityBooks = INITIAL_BOOK_CAP;

    }

    // Method to get the rating of a member for a book
    int getRating(int member, int isbn ){
        return (ratings->getRatingMap())[member][isbn];
    }

    // Method to get the profile of the currently logged-in user
    Member myProfile(){
        return (memRecord->getMemberArray())[loggedInUser];
    }

    // Method to get details of a book by its ISBN
    Book bookDetail(int isbn){
        return (bookRecord->getBookArray())[isbn];
    }

    // Method to get the ID of the currently logged-in user
    int currentUser(){
        return loggedInUser;
    }

    // Method to get the total number of books
    int getNumBooks(){
        return totalBooks;
    }

    // Method to get the total number of members
    int getNumMembers(){
        return totalMembers;
    }

    // Method to set admin login status
    void setAdminLogIn(){
        AdminLogIn = 1;
    }

    // Method to unset admin login status
    void unsetAdminLogIn(){
        AdminLogIn = 0;
    }

    // Method to check admin privileges
    bool privilageLevel(){
        return AdminLogIn;
    }

    // Method to log out the current user
    void logout(){
        loggedInUser = -1;

    }

    // Method to log in a user
    void login(int memID){

        // Check if user is already logged in
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

    // Method to add a new member
    void addMember(string name){

        memRecord->addMember(name,loggedInUser);
        totalMembers++;

        // Resize members array if capacity reached
        if(totalMembers >= capacityMembers){
            ratings->resizeMembers();
            capacityMembers = 2*capacityMembers;
        }

    }

    // Method to add a new book
    void addBook(string Author, string Title, int Year){

        bookRecord->addBook(Author, Title, Year, loggedInUser);
        totalBooks++;

        // Resize books array if capacity reached
        if(totalBooks >= capacityBooks){
            ratings->resizeBooks();
            capacityBooks = 2*capacityBooks;
        }

    }

    // Method to add a rating for a book by a member
    void addRating(int member, int book, int rating){

        if(loggedInUser == -1 && !AdminLogIn){
            cout<<"Please login to add rating to the database\n";
            return;
        }

        // Check if member or book index is valid
        if(member >= totalMembers){
            cout<<"Member with account no. ";
            cout<<member;
            cout<<" does not exist in the database.\n";
        }
        if(book >= totalBooks){
            cout<<"Book with ISBN no. ";
            cout<<book<<"does not exist in the database. \n";
        }


        // Add rating to the rating map
        (ratings->getRatingMap())[member][book] = rating;
    }

    // Method to get recommendations for the current user
    void getRecomendations(){

        // Get recommendations based on similarity
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

        // Find Top rated books by similar user
        for(int i = 0 ; i<count ; i++){
            int rating1 = (ratings->getRatingMap())[similarUser][books[i]];
            int rating2 = (ratings->getRatingMap())[similarUser][books[i-1]];
            if(i>0 && rating1 != rating2){

                break;

            }
            bestbooks[i] = books[i];
            firstLimit = i;

        }


        // Find second Top rated books by similar user
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

};

// Function to prompt user for adding a new book
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
    //cout<<"\n";
    s->addBook(author,title,year);
    cout<<(s->getNumBooks());
    cout << ", " << author << ", " << title << ", " << year ;
    cout<< " was added\n\n";


}

// Function to prompt user for adding a new member
void PromtaddMember(Session* s){
    string member;
    cout<<"Enter the name of the new member: ";
    cin>>member;
    //cout<<"\n";
    s->addMember(member);
    cout<<member<<", "<<"(account #: ";
    cout<<(s->getNumMembers()) <<") "<<"was added.\n\n";

}

// Function to prompt user for login
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

// Function to prompt user for rating a book
void Promtrate(Session* s){
    int ISBN,rating;
    string verdict;
    cout<<"Enter the ISBN for the book you'd like to rate: ";
    cin>>ISBN;
    //cout<<"\n";
    Book b = s->bookDetail(ISBN-1);
    if((s->getRating(s->currentUser(),ISBN-1)) != 0){

        cout<<"Your current rating for ";
        cout<<ISBN<<", "<<b.Author<<", "<<b.Title<<", "<<b.Year;
        cout<<" => rating: "<<(s->getRating(s->currentUser(),ISBN-1)) <<"\n";
        cout<<"Would you like to re-rate this book (y/n)? ";
        cin>>verdict;
        //cout<<"\n";
        if(verdict[0]=='y'){
            cout<<"Enter your rating: ";
            cin>>rating;
            //cout<<"\n";
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
        //cout<<"\n";
        s->addRating(s->currentUser(), ISBN-1, rating);
        cout<<"Your new rating for ";
        cout<<ISBN<<", "<<b.Author<<", "<<b.Title<<", "<<b.Year ;
        cout<< " => rating: "<< (s->getRating(s->currentUser(),ISBN-1));
        cout<<"\n\n";

    }
}

// Function to print ratings of books
void printRatings(Session* s){
    int numBooks = s->getNumBooks();
    for(int i = 0 ; i<numBooks ; i++){
        Book b = s->bookDetail(i);
        cout<<b.ISBN<<", "<<b.Author<<", "<<b.Title<<", "<<b.Year;
        cout<<" => rating: "<< (s->getRating(s->currentUser(),i))<<"\n";

    }
}

// Function to display main menu and get user choice
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

// Function to display login menu and get user choice
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

// Function to read book data from a file
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

// Function to read rating data from a file
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


    Session* currentSession = new Session();



    cout<<"Welcome to the Book Recommendation Program.\n";
    cout << "This program is designed to provide book recommendations to users based on their past ratings and \n"
         << "similarities with other users' ratings, implementing algorithms similar to those used by online\n"
         <<"platforms for personalized recommendations.\n\n";

    string bookFile;
    string ratingFile;

    cout<<"Enter file path to books file: ";
    cin>>bookFile;

    cout<<"Enter file path to rating file: ";
    cin>>ratingFile;
    cout<<"\n\n";

    currentSession->setAdminLogIn();
    int numBook = readBookFile(currentSession, bookFile);
    int numMember = readRatingFile(currentSession, ratingFile);
    currentSession->unsetAdminLogIn();


    cout<<"# of books: "<<numBook<<"\n";
    cout<<"# of members: "<<numMember<<"\n";

    cout<<"\n\n";

    bool quit = 0;

    while(!quit){
        int option = showMainMenu();

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

    return 0;
}