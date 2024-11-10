//
// Created by Shikha Pallavi on 4/16/24.
//

#ifndef P1_MEMBERLIST_H
#define P1_MEMBERLIST_H

// AUTHOR: Shikha Pallavi
// PROGRAM: MemberList.h
// DATE: 04/16/2024
// PURPOSE: This header file defines a structure for representing a member and a class for managing a list of members.
// INPUT:The program does not directly take input from users. It can be extended to accept user input for
// adding members.
// PROCESS:The program defines a structure Member to represent individual members and a class MemberList
// to manage a list of members. MemberList provides methods to add members to the list, resize the
// array dynamically, and retrieve the member array pointer.
// OUTPUT:The program does not directly produce any output. It can be extended to output information about
// the members stored in the list.

#include<iostream>
#include<string>

using namespace std;

// Structure for representing a member
struct Member{

    string Name;  // Name of the member
    int Account;  // Account number of the member
    int adddedBY;  // ID of the user who added the member


    // Constructor to initialize all attributes of the member
    Member(string nm, int ac, int loggedInUser){
        Name = nm;
        Account = ac;
        adddedBY = loggedInUser;

    }

    // Default constructor
    Member(){}

};

// Class for managing a list of members
class MemberList{
private:


    Member* memberArray;  // Pointer to an array of members
    int capacity;   // Capacity of the array
    int countMem = 0;  // Number of members currently in the array



public:

    // Constructor to initialize the member array with a specified initial capacity
    MemberList(int initialCapacity){
        memberArray = new Member[initialCapacity];
        capacity = initialCapacity;

    }

    // Destructor to deallocate memory for the member array
    ~MemberList(){
        delete[] memberArray;
    }


    // Method to get the pointer to the member array
    Member* getMemberArray();

    // Method to resize the member array when it reaches capacity
    void resizeArray();

    // Method to add a new member to the list
    void addMember(string name, int loggedInUser);


};

#endif //P1_MEMBERLIST_H