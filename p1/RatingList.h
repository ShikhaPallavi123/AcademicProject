//
// Created by Shikha Pallavi on 4/16/24.
//

#ifndef P1_RATINGLIST_H
#define P1_RATINGLIST_H

// AUTHOR: Shikha Pallavi
// PROGRAM: RatingList.h
// DATE: 04/16/2024
// PURPOSE:Header file for defining a struct for representing a rating and a class for managing a list of ratings.
// INPUT:None directly from the user. The program initializes the rating map with the number of members and books.
// PROCESS:The program defines a Rating struct to represent individual ratings and a RatingList class to manage a
// list of ratings. The RatingList class provides methods to initialize the rating map, resize it dynamically,
// and recommend books based on user ratings.
// OUTPUT:  None directly returned by the program. The program can be extended to output recommendations
// based on user ratings.

#include<iostream>
#include<string>


using namespace std;

// Struct for representing a rating
struct Rating{

    int book;       // Book ID
    int member;     // Member ID
    int rating;     // Rating given by the member to the book


    // Constructor to initialize all attributes of the rating
    Rating(int b, int m, int r){
        book = b;
        member = m;
        rating = r;
    }

    // Default constructor
    Rating(){}

};

// Class for managing a list of ratings
class RatingList{
private:

    int** ratingMap;    // 2D array to store ratings
    int members;        // Number of members
    int books;          // Number of books

public:

    // Constructor to initialize the rating map with the number of members and books
    RatingList(int m, int b){
        members = m;
        books = b;
        ratingMap = new int*[members];
        for(int i = 0 ; i<members ; i++){
            ratingMap[i] = new int[books];
            for(int j = 0 ; j<books; j++){
                ratingMap[i][j] = 0;
            }
        }
    }

    // Destructor to deallocate memory for the rating map
    ~RatingList(){
        for(int i = 0 ; i<members ; i++){
            delete[] ratingMap[i];
        }
        delete[] ratingMap;
    }

    // Method to get the rating map
    int** getRatingMap();

    // Method to resize the rating map when the number of members changes
    void resizeMembers();

    // Method to resize the rating map when the number of books changes
    void resizeBooks();

    // Method to recommend books based on user ratings
    int** recomendBook(int user);

};

#endif //P1_RATINGLIST_H
