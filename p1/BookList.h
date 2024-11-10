
//
// Created by Shikha Pallavi on 4/16/24.
//

#ifndef P1_BOOKLIST_H
#define P1_BOOKLIST_H

// AUTHOR: Shikha Pallavi
// PROGRAM: BookList.h
// DATE: 04/16/2024
// PURPOSE: This program defines a struct for representing a book and a class for managing a list of books.
// INPUT:   None directly from the user. The program can be extended to accept user input for adding books.
// PROCESS: The program defines a Book struct to represent individual books and a BookList class to manage
// a list of books.The BookList class provides methods to add books to the list, resize the array dynamically,
// and retrieve the book array pointer.
// OUTPUT:  None directly returned by the program. The program can be extended to output information
// about the books stored in the list.
#include<iostream>
#include<string>


using namespace std;

// Struct for representing a book
struct Book{

    int ISBN;  // Unique identifier for the book
    string Author;  // Name of the author
    string Title;  // Title of the book
    int Year;  // Year of publication
    int introducer;  // ID of the user who introduced the book


    // Constructor to initialize all attributes of the book
    Book(int _ISBN, string _Author, string _Title, int _Year, int _introducer ){
        ISBN = _ISBN;
        Author = _Author;
        Title = _Title;
        Year = _Year;
        introducer = _introducer;
    }

    // Default constructor
    Book(){}

};


// Class for managing a list of books
class BookList{
private:

    Book* bookArray;  // Pointer to an array of books
    int capacity;  // Capacity of the array
    int countBooks=0;  // Number of books currently in the array

public:


    // Constructor to initialize the book array with a specified initial capacity
    BookList(int initialCapacity){
        bookArray = new Book[initialCapacity];
        capacity = initialCapacity;

    }

    // Destructor to deallocate memory for the book array
    ~BookList(){
        delete[] bookArray;
    }

    // Method to get the pointer to the book array
    Book* getBookArray();

    // Method to resize the book array when it reaches capacity
    void resizeArray();

    // Method to add a new book to the list
    void addBook(string Author, string Title, int Year, int loggedInUser);


};

#endif //P1_BOOKLIST_H
