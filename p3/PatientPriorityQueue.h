// AUTHOR: Shikha Pallavi
// DATE:   05/20/2024
// PROGRAM: PatientPriorityQueue.h
// PURPOSE: Header file for the PatientPriorityQueue class, which implements a
//          priority queue system for managing patients in a hospital triage setting.
//          The priority queue ensures that patients are seen based on the urgency of
//          their condition and their arrival order.
// INPUT:   Includes necessary headers and defines the interface for the PatientPriorityQueue class.
// PROCESS: Manages the addition, removal, and retrieval of patients in a priority queue,
//          ensuring that the highest priority patient is always at the front.
// OUTPUT:  Provides methods to add patients to the queue, remove the highest priority patient,
//          peek at the highest priority patient, and get a string representation of the queue.

#ifndef P3_PATIENTPRIORITYQUEUE_H
#define P3_PATIENTPRIORITYQUEUE_H


#include "Patient.h"
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<queue>
#include<iomanip>

using namespace std;

class PatientPriorityQueue{
private:

    // Stores the patients in a vector to maintain heap order
    vector<Patient> paitentList;

    // Tracks the arrival order of patients
    int nextPatientNumber;


    // Helper function to maintain heap order by moving an element down
    // INPUT: Index of the element to heapify down
    // MODIFY: patientList to restore heap property
    void heapifyDown(int);

    // Helper function to maintain heap order by moving an element up
    // INPUT: Index of the element to heapify up
    // MODIFY: patientList to restore heap property
    void heapifyUp(int);



public:

    // Constructor
    // PURPOSE: Initializes an empty PatientPriorityQueue with no patients and sets the
    //  nextPatientNumber to 1.
    PatientPriorityQueue();

    // Retrieves the name of the highest priority patient without removing them from the queue
    // OUTPUT: The name of the highest priority patient as a string
    string peek();

    // Removes the highest priority patient from the queue
    // MODIFY: patientList to remove the highest priority patient
    void remove();

    // Adds a new patient to the priority queue
    // INPUT: name - The name of the patient
    //        priorityCode - The priority code of the patient
    // MODIFY: patientList to add a new patient while maintaining heap order
    void add(string &, string &);

    // Returns the number of patients currently in the priority queue
    // OUTPUT: The number of patients in the queue as an integer
    int size();

    // Returns a string representation of the priority queue in heap order
    // OUTPUT: A string showing the patients in the queue with their details
    string to_string();



};

// Class: PatientPriorityQueue

/**
 * @brief Restores the heap property by moving a node down the heap.
 *
 * @param index The index of the node to be heapified down
 */

void PatientPriorityQueue::heapifyDown(int index) {
    int largest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    // Cast leftChild to std::vector<Patient>::size_type for comparison
    if (static_cast<vector<Patient>::size_type>(leftChild) < paitentList.size()) {
        if (paitentList[index] < paitentList[leftChild]) {
            largest = leftChild;
        }
    }

    // Cast rightChild to vector<Patient>::size_type for comparison
    if (static_cast<vector<Patient>::size_type>(rightChild) < paitentList.size()) {
        if (paitentList[index] < paitentList[rightChild]) {
            largest = rightChild;
        }
    }

    if (largest != index) {
        Patient temp = paitentList[index];
        paitentList[index] = paitentList[largest];
        paitentList[largest] = temp;
        heapifyDown(largest);
    }
}


/**
 * @brief Restores the heap property by moving a node up the heap.
 *
 * @param index The index of the node to be heapified up
 */
void PatientPriorityQueue ::  heapifyUp(int index){
    if(index == 0) return;

    if(paitentList [(index-1)/2] < paitentList[index]){
        Patient temp = paitentList[index];
        paitentList[index] = paitentList[(index-1)/2];
        paitentList[(index-1)/2] = temp;
        heapifyUp(((index-1)/2));
    }
}

 //Constructs a new PatientPriorityQueue object.
 PatientPriorityQueue :: PatientPriorityQueue(){
    this->nextPatientNumber = 1;
}


/**
 * @brief Gets the name of the next patient in the priority queue.
 *
 * @return The name of the next patient
 */
string PatientPriorityQueue ::  peek(){
    return this->paitentList[0].getName();
}

 //Removes the next patient from the priority queue.

void PatientPriorityQueue :: remove(){
    this->paitentList[0] = this->paitentList.back();
    this->paitentList.pop_back();
    this->heapifyDown(0);
}

/**
 * @brief Adds a patient to the priority queue.
 *
 * @param name The name of the patient
 * @param priorityCode The priority code of the patient
 */
void PatientPriorityQueue :: add(string &name, string &priorityCode){
    Patient newPatient(name, priorityCode, nextPatientNumber);
    paitentList.push_back(newPatient);
    heapifyUp(this->size()-1);
    nextPatientNumber++;
}

/**
 * @brief Gets the size of the priority queue.
 *
 * @return The size of the priority queue
 */
int PatientPriorityQueue :: size(){
    return (this->paitentList).size();
}

/**
 * @brief Converts the priority queue to a string representation.
 *
 * @return A string representing the priority queue
 */
string PatientPriorityQueue :: to_string(){

    // Check if the priority queue is empty
    if(this->size() == 0){

        // If the queue is empty, return a newline character
        return "\n";
    }
    // Initialize a stringstream to build the output string

    stringstream ss;

    // Get the index of the current node (patient) from the front of the queue
    queue<int> levelq;
    levelq.push(0);

    // Continue the traversal until there are no more nodes to process
    while(!levelq.empty()){
        stringstream ss2;
        int pid = levelq.front();
        levelq.pop();
        Patient p = paitentList[pid];
        ss2 << p.getArrivalOrder();

        // Format and append the patient's details to the output string
        ss << std::right<<std::setw(10) << ss2.str() + "    "
           << std::left << std::setw(15) << p.getPriorityCode()
           << std::left << std::setw(20) << p.getName() << "\n";

        // Add the left child to the queue if it exists
        if(2*pid + 1 < this->size()){
            levelq.push(2*pid + 1);
        }

        // Add the right child to the queue if it exists
        if(2*pid + 2 < this->size()){
            levelq.push(2*pid + 2);
        }
    }

    // Return the constructed string representation of the priority queue
    return ss.str();
}

#endif //P3_PATIENTPRIORITYQUEUE_H
