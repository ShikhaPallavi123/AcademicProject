
// AUTHOR: Shikha Pallavi
// PROGRAM: MemberList.cpp
// DATE: 04/16/2024
// PURPOSE: This file contains methods to manage a list of members.
// INPUT:The addMember method takes the name of the member and the ID of the logged-in user who added the member.
// These parameters are used to create a new Member object and add it to the list of members.
// PROCESS:The resizeArray method increases the capacity of the member array when it's full, ensuring space
// for more members. getMemberArray returns the member array pointer for accessing and modifying member data.
// addMember checks if there's room to add a new member. If not, it expands the array first using resizeArray.
// OUTPUT:  The methods here manipulate the member array to facilitate member management, but they don't
// directly produce any output.

#include<iostream>
#include<string>
#include "MemberList.h"


using namespace std;

// Method to resize the member array when it reaches capacity
void MemberList::resizeArray(){

    // Allocate a new array with double the capacity
    Member* copyArray = new Member[2*capacity];

    // Update the capacity
    capacity = 2*capacity;

    // Copy existing members to the new array
    for(int i = 0 ; i<capacity/2 ;i++){
        copyArray[i] = memberArray[i];
    }

    // Deallocate memory for the old array and update the pointer
    delete[] memberArray;
    memberArray = copyArray;
}

// Method to get the pointer to the member array
Member* MemberList::getMemberArray(){
    return memberArray;
}

// Method to add a new member to the list
void MemberList::addMember(string name, int loggedInUser){


    // Check if there is enough space in the array
    if(countMem < capacity){

        // Create a new member object with the provided details
        Member newMem(name, countMem+1, loggedInUser);

        // Add the new member to the array and update the member count
        (this->memberArray)[countMem] = newMem;
        this->countMem++;

    }
    else{

        // If the array is full, resize it and then add the new member
        this->resizeArray();
        Member newMem(name, capacity+1, loggedInUser);

        // Add the new member at the end of the resized array
        (this->memberArray)[capacity] = newMem;
        this->countMem++;
    }

}
