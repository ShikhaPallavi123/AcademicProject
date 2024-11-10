// AUTHOR: Shikha Pallavi
// DATE:   05/23/2024
// PROGRAM: PatientPriorityQueuex.h
// PURPOSE: Header file for the PatientPriorityQueuex class, which manages a priority
//          queue of Patient objects. This class provides functionalities to add, remove,
//          and modify patients in the priority queue based on their priority codes and
//          arrival order.
//
// INPUT:   The PatientPriorityQueuex class accepts patient names, priority codes, and
//          arrival order when creating or modifying instances of Patient objects.
//
// OUTPUT:  The class provides methods to peek at the top-priority patient, get the size
//          of the queue, and convert the queue's details to a string representation.
//
// PROCESS: The class processes data by maintaining a heap-based priority queue of patients,
//          allowing for efficient addition, removal, and priority code changes.


#ifndef P3X_PATIENTPRIORITYQUEUEX_H
#define P3X_PATIENTPRIORITYQUEUEX_H


#include <iomanip>
#include "Patient.h"
#include<iostream>
#include<string>
#include <sstream>
#include<vector>
#include<queue>

using namespace std;

class PatientPriorityQueuex {
private:

    // List of patients in the priority queue
    vector<Patient> paitentList;

    // Next patient number to be assigned
    int nextPatientNumber;

    // Helper function to maintain heap property when removing elements
    void heapifyDown(int);

    // Helper function to maintain heap property when adding elements
    void heapifyUp(int);

public:

    // Constructor to initialize the PatientPriorityQueuex object
    PatientPriorityQueuex();

    // Returns the name of the patient with the highest priority
    string peek();

    // Removes the patient with the highest priority from the queue
    void remove();

    // Adds a new patient with the given name and priority code to the queue
    void add(string &, string &);

    // Returns the number of patients in the queue
    int size();

    // Returns a string representation of the priority queue
    string to_string();

    // Removes a patient with the given arrival order ID from the queue
    void remove(int);

    // Adds a new patient with the given name, priority code, and arrival order to the queue
    void add(string &, string &, int);

    // Changes the priority code of the patient with the given arrival order ID
    void changePriorityCode(int, string);
};


// Restores the heap property by moving a node down the heap.
// The index of the node to be heapified down
void PatientPriorityQueuex::heapifyDown(int index) {

    // Initialize largest as root
    int largest = index;

    // left = 2*i + 1
    int leftChild = 2 * index + 1;

    // right = 2*i + 2
    int rightChild = 2 * index + 2;

    // Cast leftChild to std::vector<Patient>::size_type for comparison
    if (static_cast<vector<Patient>::size_type>(leftChild) < paitentList.size()) {
        if (paitentList[index] < paitentList[leftChild]) {

            // Update largest if left child is larger
            largest = leftChild;
        }
    }

    // Cast rightChild to vector<Patient>::size_type for comparison
    if (static_cast<vector<Patient>::size_type>(rightChild) < paitentList.size()) {
        if (paitentList[index] < paitentList[rightChild]) {

            // Update largest if right child is larger
            largest = rightChild;
        }
    }

    // If largest is not root
    if (largest != index) {
        Patient temp = paitentList[index];

        // Swap current element with the largest child
        paitentList[index] = paitentList[largest];
        paitentList[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapifyDown(largest);
    }
}


//Restores the heap property by moving a node up the heap.
// The index of the node to be heapified up
void PatientPriorityQueuex::heapifyUp(int index) {

    // Base case: if the element is already at the root, return
    if (index == 0) return;


    // Calculate the parent index
    // Compare the current element with its parent
    if (paitentList[(index - 1) / 2] < paitentList[index]) {

        // Swap the current element with its parent
        Patient temp = paitentList[index];
        paitentList[index] = paitentList[(index - 1) / 2];
        paitentList[(index - 1) / 2] = temp;

        // Recursively heapify the parent element
        heapifyUp(((index - 1) / 2));
    }
}

//Removes the next patient from the priority queue.
void PatientPriorityQueuex::remove(int id) {

    // Iterate through the patient list to find the patient with the specified ID
    for (int i = 0; i < this->size(); i++) {

        // If the patient with the specified ID is found
        if (paitentList[i].getArrivalOrder() == id) {

            // Replace the patient with the last patient in the list
            paitentList[i] = paitentList.back();

            // Remove the last patient from the list
            paitentList.pop_back();

            // Restore the heap property by moving the new element at index i down
            heapifyDown(i);
        }
    }
}


// Adds a patient to the queue with given name, priority code, and ID.
void PatientPriorityQueuex::add(string &name, string &priorityCode, int id) {

    // Creates a new patient object.
    Patient newPatient(name, priorityCode, id);

    // Adds the new patient to the end of the list.
    paitentList.push_back(newPatient);

    // Restores the heap property by moving the new element up.
    heapifyUp(this->size() - 1);
}

// Changes priority code of patient with specified ID.
void PatientPriorityQueuex::changePriorityCode(int id, string priorityCode) {

    // Searches for the patient with the given ID.
    for (int i = 0; i < this->size(); i++) {
        if (paitentList[i].getArrivalOrder() == id) {
            // Stores the name of the patient.
            string name = paitentList[i].getName();
            int oldCompareCode = paitentList[i].comparingCode();
            paitentList[i].setPriorityCode(priorityCode);
            int newCompareCode = paitentList[i].comparingCode();

            if (newCompareCode > oldCompareCode) {
                heapifyUp(i);
            } else {
                heapifyDown(i);
            }

            // Prints a message indicating the change.
            cout << "Changed patient " << "\"" << name << "\"" << "'s priority to " << priorityCode << " \n";
            return;
        }
    }

    // Prints a message if no patient with the given ID is found.
    cout << "Error: no patient with the given id was found\n";
}


// Constructor initializes next patient number.
PatientPriorityQueuex::PatientPriorityQueuex() {
    this->nextPatientNumber = 1;
}

// Returns name of patient at front of queue.
string PatientPriorityQueuex::peek() {

    // Returns the name of the patient at the front of the list.
    return this->paitentList[0].getName();
}

// Removes patient at front of queue.
void PatientPriorityQueuex::remove() {

    // Replaces the first patient with the last patient.
    this->paitentList[0] = this->paitentList.back();

    // Removes the last patient.
    this->paitentList.pop_back();

    // Restores the heap property by moving the replaced element down.
    this->heapifyDown(0);
}

// Adds patient to queue with given name and priority code.
void PatientPriorityQueuex::add(string &name, string &priorityCode) {

    // Creates a new patient object with the next patient number.
    Patient newPatient(name, priorityCode, nextPatientNumber);

    // Adds the new patient to the end of the list.
    paitentList.push_back(newPatient);

    // Restores the heap property by moving the new element up.
    heapifyUp(this->size() - 1);

    // Increments the next patient number.
    nextPatientNumber++;
}


// Returns size of the priority queue.
int PatientPriorityQueuex::size() {

    // Returns the size of the patient list.
    return (this->paitentList).size();
}

string PatientPriorityQueuex::to_string() {

    // Check if the priority queue is empty
    if (this->size() == 0) {

        // If the queue is empty, return a newline character
        return "\n";
    }
    // Initialize a stringstream to build the output string

    stringstream ss;

    // Get the index of the current node (patient) from the front of the queue
    queue<int> levelq;
    levelq.push(0);

    // Continue the traversal until there are no more nodes to process
    while (!levelq.empty()) {
        stringstream ss2;
        int pid = levelq.front();
        levelq.pop();
        Patient p = paitentList[pid];
        ss2 << p.getArrivalOrder();

        // Format and append the patient's details to the output string
        ss << std::right << std::setw(10) << ss2.str() + "    "
           << std::left << std::setw(15) << p.getPriorityCode()
           << std::left << std::setw(20) << p.getName() << "\n";

        // Add the left child to the queue if it exists
        if (2 * pid + 1 < this->size()) {
            levelq.push(2 * pid + 1);
        }

        // Add the right child to the queue if it exists
        if (2 * pid + 2 < this->size()) {
            levelq.push(2 * pid + 2);
        }
    }

    // Return the constructed string representation of the priority queue
    return ss.str();
}

#endif //P3X_PATIENTPRIORITYQUEUEX_H