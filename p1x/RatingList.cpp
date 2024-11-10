//
// Created by Shikha Pallavi on 4/16/24.
//


// AUTHOR: Shikha Pallavi
// PROGRAM: RatingList.cpp
// DATE: 04/16/2024

// PURPOSE: This file contains the implementation of methods to manage a list of ratings.

// INPUT: The resizeMembers and resizeBooks methods do not directly take input from users.
// They resize the rating map based on the number of members and books, respectively.
// The recomendBook method takes the ID of the user for whom book recommendations are needed.

// PROCESS: The resizeMembers method doubles the capacity of the rating map for members and initializes
// new rows for additional members. The resizeBooks method doubles the capacity of the rating map for
// books and initializes new columns for additional books. The recomendBook method finds the most similar
// user based on ratings and recommends books not rated by the given user but rated by the most similar user.

// OUTPUT: The resizeMembers and resizeBooks methods manipulate the rating map to accommodate changes in the number
// of members and books, respectively. The recomendBook method returns a pair containing information about the similar
// user and an array of recommended books not rated by the given user. These methods do not directly
// produce any visible output but facilitate the recommendation process based on user ratings.

#include<iostream>
#include<string>
#include<algorithm>
#include "RatingList.h"


using namespace std;

// Method to resize the rating map when the number of members changes
void RatingList::resizeMembers(){

    // Allocate a new array with double the capacity for members
    int** extendedMembers = new int*[2*members];

    // Update the number of members
    members = 2*members;

    // Copy existing members to the extended array and initialize new rows
    for(int i = 0 ; i<members ; i++){
        if(i<members/2){
            extendedMembers[i] = ratingMap[i];
        }
        else{
            extendedMembers[i] = new int[books];
            for(int j = 0 ; j<books ; j++){
                ratingMap[i][j] = 0;
            }
        }
    }

    // Deallocate memory for the old array and update the pointer
    for(int i = 0 ; i<members/2 ; i++){
        delete[] ratingMap[i];
    }
    delete[] ratingMap;
    ratingMap = extendedMembers;
}

// Method to get the rating map
int** RatingList::getRatingMap(){
    return ratingMap;
}

// Method to resize the rating map when the number of books changes
void RatingList::resizeBooks(){

    // Allocate a new array with double the capacity for books
    int** extendedBooks = new int*[members];

    //Update the number of books
    books = 2*books;

    // Copy existing books to the extended array and initialize new columns
    for(int i = 0 ; i<members ; i++){
        extendedBooks[i] = new int[books];
        for(int j = 0 ; j<books; j++){
            if(j<books/2){
                extendedBooks[i][j] = ratingMap[i][j];
            }
            else{
                extendedBooks[i][j] = 0;
            }

        }
    }

    // Deallocate memory for the old array and update the pointer
    for(int i = 0 ; i<members ; i++){
        delete[] ratingMap[i];
    }
    delete[] ratingMap;
    ratingMap = extendedBooks;

}



void swap(int** arr, int i, int j) {
    int* temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}


void bubbleSort(int** arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j][0] > arr[j + 1][0]) {
                swap(arr, j, j + 1);
            }
        }
    }
}



// Method to recommend books based on user ratings
int** RatingList::recomendBook(int user){

    // Find the most similar user based on ratings
    int maxSimilarity = -1;
    int similarUser;
    for(int i = 0 ; i<members ; i++){
        if(i == user) continue;
        int currSimilarity = 0;
        for(int j = 0 ; j<books ; j++){
            if(ratingMap[user][j] != 0 && ratingMap[i][j] != 0){

                currSimilarity += ratingMap[user][j]*ratingMap[i][j];
            }
        }
        if(currSimilarity > maxSimilarity){
            maxSimilarity = currSimilarity;
            similarUser = i;
        }
    }

    // Sort the books based on ratings of the most similar user
    int** arr = new int*[books];

    for(int j = 0 ; j<books ; j++){
        arr[j] = new int[2];
        arr[j][0] = ratingMap[similarUser][j];
        arr[j][1] = j;
    }


    bubbleSort(arr, books);

    // Find books not rated by the given user but rated by the most similar user
    int* bestBooks = new int[books];
    int count = 0;

    for(int i = books-1; i>=0 ; i--){
        int rating1 = ratingMap[user][arr[i][1]];
        int rating2 = ratingMap[similarUser][arr[i][1]];
        if( rating1 == 0 && rating2 != 0){
            bestBooks[count] = arr[i][1];
            count++;
        }
    }


    // Create and return a pair containing information about the similar user and recommended books
    int** ans;
    ans = new int*[2];
    int* detail = new int[2];
    detail[0] = similarUser;
    detail[1] = count;
    ans[0] = detail;
    ans[1] = bestBooks;

    return ans;
}
