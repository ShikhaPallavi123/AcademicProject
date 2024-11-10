//
// Created by Shikha Pallavi on 4/16/24.
//
// AUTHOR: Shikha Pallavi
// PROGRAM: BookList.cpp
// DATE: 04/16/2024
// PURPOSE: This file contains the implementation of methods to manage a list of books.
// INPUT:   The addBook method takes details of a new book (author, title, year, and user ID)
// as input to add it to the list.
// PROCESS: The resizeArray method increases the capacity of the book array when it's full,ensuring space
// for more books. getBookArray returns the book array pointer for accessing and modifying book data.
// addBook checks if there's room to add a new book. If not, it expands the array first using resizeArray.
// OUTPUT:  The methods here manipulate the book array to facilitate book management, but they don't directly
// produce any output.

#include<iostream>
#include<string>

#include "BookList.h"
using namespace std;


// Method to resize the book array when it reaches capacity
void BookList::resizeArray(){

    // Allocate a new array with double the capacity
    Book* copyArray = new Book[2*capacity];

    // Update the capacity
    capacity = 2*capacity;

    // Copy existing books to the new array
    for(int i = 0 ; i<capacity/2 ;i++){
        copyArray[i] = bookArray[i];
    }

    // Deallocate memory for the old array and update the pointer
    delete[] bookArray;
    bookArray = copyArray;
}

// Method to get the pointer to the book array
Book* BookList::getBookArray(){
    return bookArray;
}

// Method to add a new book to the list
void BookList::addBook(string Author,string Title,int Year,int loggedInUser){


    // Check if there is enough space in the array
    if(countBooks < capacity){

        // Create a new book object with the provided details
        Book newBook(countBooks+1, Author, Title, Year, loggedInUser);

        // Add the new book to the array and update the book count
        (this->bookArray)[countBooks] = newBook;
        this->countBooks++;

    }
    else{

        // If the array is full, resize it and then add the new book
        this->resizeArray();
        Book newBook(capacity+1, Author, Title, Year, loggedInUser);

        // Add the new book at the end of the resized array
        (this->bookArray)[capacity] = newBook;
        this->countBooks++;
    }

}
