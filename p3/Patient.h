// AUTHOR: Shikha Pallavi
// DATE:   05/20/2024
// PROGRAM: Patient.h
// PURPOSE: Header file for the Patient class, which represents a patient in the
//          hospital triage system. The Patient class includes the patient's name,
//          priority code, and arrival order, and provides functionalities to compare
//          patients, convert patient details to a string representation, and access
//          patient attributes.
//
// INPUT:   The Patient class accepts a patient's name, priority code, and arrival order
//          when creating an instance of the Patient.
//
// OUTPUT:  The class provides a string representation of the patient's details and
//          comparison results for patient priority.
//
// PROCESS: The class processes data by storing patient details, comparing patients
//          based on priority and arrival order, and converting patient information
//          to a string format for display.

#ifndef P3_PATIENT_H
#define P3_PATIENT_H



#include<iostream>
#include<string>


using namespace std;


class Patient{
private:

    // Full legal name of the patient
    string name;

    // Priority code indicating the urgency of the patient's condition
    string priorityCode;

    // Order number indicating the patient's arrival sequence
    int arrivalOrder;
public:

    // Constructor to initialize a Patient object with the given name, priority code, and arrival order
    Patient(string &, string &, int );

    // Overloaded < operator to compare patients based on priority and arrival order
    bool operator<(const Patient& other) const;

    // Returns a string representation of the patient object
    string to_string();

    // Returns the patient's name
    string getName();

    // Returns the patient's priority code
    string getPriorityCode();

    // Returns the integer value corresponding to the patient's priority code for comparison purposes
    int comparingCode() const;

    // Returns the patient's arrival order
    int getArrivalOrder() const;

};

#endif //P3_PATIENT_H
