// AUTHOR: Shikha Pallavi
// DATE:   05/20/2024
// PROGRAM: PatientPriorityQueue.cpp
// PURPOSE: Implementation of the PatientPriorityQueue class and associated
//          functions for managing patients in a hospital triage system.
// INPUT:   Patient data including names and priority codes, commands from the user or a text
//          file for managing the triage system.
// PROCESS: Defines classes for Patient and PatientPriorityQueue, implements functions for adding,
//          removing, and displaying patients, and manages the priority queue based on patient priority
//          codes and arrival order.
// OUTPUT:  Displays information about patients in the triage system, such as the next
//          patient to be seen, the list of patients waiting, and provides a help menu for user guidance.


#include "PatientPriorityQueue.h"
#include "Patient.h"


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


// Class: Patient

/**
 * @brief Constructs a Patient object with the given name, priority code, and arrival order.
 *
 * @param name The name of the patient
 * @param priorityCode The priority code of the patient
 * @param arrivalOrder The order in which the patient arrived
 */
Patient :: Patient(string &name, string &priorityCode, int arrivalOrder ){
    this->name = name;
    this->priorityCode = priorityCode;
    this->arrivalOrder = arrivalOrder;
}

/**
 * @brief Converts the Patient object to a string representation.
 *
 * @return A string representing the patient's details
 */
string Patient :: to_string(){
    string detail = "";
    stringstream ss;
    ss << arrivalOrder;
    detail += (name + " " + "{ pri=" + priorityCode + ", arrive=" + ss.str() + " }");
    return detail;
}

/**
 * @brief Gets the name of the patient.
 *
 * @return The name of the patient
 */
string Patient ::  getName(){
    return name;
}

/**
 * @brief Gets the priority code of the patient.
 *
 * @return The priority code of the patient
 */
string Patient ::  getPriorityCode(){
    return priorityCode;
}

/**
 * @brief Gets the arrival order of the patient.
 *
 * @return The arrival order of the patient
 */
int Patient ::  getArrivalOrder() const{
    return	arrivalOrder;
}

/**
 * @brief Compares the priority code of the patient and returns an integer value based on the code.
 *
 * @return An integer value representing the priority of the patient
 */
int Patient ::  comparingCode() const{
    string priorityCode = this->priorityCode;

    if(priorityCode ==  "immediate"){
        return 4;
    }
    else if(priorityCode == "emergency") {
        return 3;
    }
    else if(priorityCode ==  "urgent"){
        return 2;
    }
    else if(priorityCode == "minimal"){
        return 1;
    }
    else{
        return 0;
    }
}


/**
 * @brief Compares the priority of the current patient with another patient.
 *
 * @param other The other patient to compare with
 * @return True if the current patient's priority is less than the other patient's priority, otherwise false
 */
bool Patient::operator< (const Patient& other) const{
    if(this->comparingCode() < other.comparingCode()){
        return 1;
    }
    else if(this->comparingCode() == other.comparingCode()){
        if(this->getArrivalOrder() > other.getArrivalOrder()){
            return 1;
        }
    }
    return 0;
}



// Global function prototypes

/**
 * @brief Prints a welcome message.
 */
void welcome();

/**
 * @brief Prints a goodbye message.
 */
void goodbye();


 // Prints a help menu.
void help();

/**
 * @brief Processes the line entered from the user or read from the file.
 *
 * @param line The line entered by the user or read from the file
 * @param priQueue The PatientPriorityQueue object
 * @return True if the program should continue processing, otherwise false
 */
bool processLine(string, PatientPriorityQueue &);
// Process the line entered from the user or read from the file.


/**
 * @brief Adds a patient to the waiting room.
 *
 * @param line The command line entered by the user
 * @param priQueue The PatientPriorityQueue object
 */
void addPatientCmd(string, PatientPriorityQueue &);
// Adds the patient to the waiting room.


/**
 * @brief Displays the next patient in the waiting room that will be called.
 *
 * @param priQueue The PatientPriorityQueue object
 */
void peekNextCmd(PatientPriorityQueue &);
// Displays the next patient in the waiting room that will be called.


/**
 * @brief Removes a patient from the waiting room and displays the name on the screen.
 *
 * @param priQueue The PatientPriorityQueue object
 */
void removePatientCmd(PatientPriorityQueue &);
// Removes a patient from the waiting room and displays the name on the screen.


/**
 * @brief Displays the list of patients in the waiting room.
 *
 * @param priQueue The PatientPriorityQueue object
 */
void showPatientListCmd(PatientPriorityQueue &);
// Displays the list of patients in the waiting room.


// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.
void execCommandsFromFileCmd(string, PatientPriorityQueue &);



// Delimits (by space) the string from user or file input.
string delimitBySpace(string &);



/**
 * @brief Main function of the program.
 *
 * @return 0 upon successful execution
 */
int main() {

    // declare variables
    string line;

    // welcome message
    welcome();

    // process commands
    PatientPriorityQueue priQueue;
    do {
        cout << "\ntriage> ";
        getline(cin, line);
    } while (processLine(line, priQueue));

    // goodbye message
    goodbye();
}


/**
 * @brief Processes the command entered by the user.
 *
 * @param line The command entered by the user
 * @param priQueue The PatientPriorityQueue object
 * @return True if the program should continue processing, otherwise false
 */
bool processLine(string line, PatientPriorityQueue &priQueue) {
    // get command
    string cmd = delimitBySpace(line);
    if (cmd.length() == 0) {
        cout << "Error: no command given.";
        return false;
    }

    // process user input
    if (cmd == "help")
        help();
    else if (cmd == "add")
        addPatientCmd(line, priQueue);
    else if (cmd == "peek")
        peekNextCmd(priQueue);
    else if (cmd == "next")
        removePatientCmd(priQueue);
    else if (cmd == "list")
        showPatientListCmd(priQueue);
    else if (cmd == "load")
        execCommandsFromFileCmd(line, priQueue);
    else if (cmd == "quit")
        return false;
    else
        cout << "Error: unrecognized command: " << cmd << endl;

    return true;
}

/**
 * @brief Adds a patient to the waiting room based on the command line input.
 *
 * @param line The command line entered by the user
 * @param priQueue The PatientPriorityQueue object
 */
void addPatientCmd(string line, PatientPriorityQueue &priQueue) {
    string priority;
    string name = "";

    // get priority and name
    priority = delimitBySpace(line);
    if (priority.length() == 0) {
        cout << "Error: no priority code given.\n";
        return;
    }
    stringstream ss(line);
    string token;
    while(ss >> token){
        name += (token + " ");
    }
    name = name.substr(0,name.size()-1);
    if (name.length() == 0) {
        cout << "Error: no patient name given.\n";
        return;
    }

    if(!(priority == "immediate" || priority == "emergency" || priority == "urgent" || priority =="minimal")){
        cout<< "Please enter a valid priority-Code.\n";
        return;
    }

    priQueue.add(name, priority);
    cout<<"Added patient "<<"\""<<name<<"\""<<" to the priority system\n";


}

/**
 * @brief Displays the next patient in the waiting room without removing them from the queue.
 *
 * @param priQueue The PatientPriorityQueue object
 */
void peekNextCmd(PatientPriorityQueue &priQueue) {
    if(priQueue.size() == 0){
        cout<<"There are no patients in the waiting area.\n";
        return;
    }
    cout<<"Highest priority patient to be called next: "<< priQueue.peek() << "\n";

}
/**
 * @brief Removes the next patient in line from the waiting room and displays their name.
 *
 * @param priQueue The PatientPriorityQueue object
 */
void removePatientCmd(PatientPriorityQueue &priQueue) {
    if(priQueue.size() == 0){
        cout<<"There are no patients in the waiting area.\n";
        return;
    }
    cout<<"This patient will now be seen: "<<priQueue.peek()<<"\n";
    priQueue.remove();
}

/**
 * @brief Displays the list of patients in the waiting room.
 *
 * @param priQueue The PatientPriorityQueue object
 */
void showPatientListCmd(PatientPriorityQueue &priQueue) {
    cout << "# patients waiting: " << priQueue.size() << endl;
    cout << "  Arrival #   Priority Code   Patient Name\n"
         << "+-----------+---------------+--------------+\n";
    cout<<priQueue.to_string();
}

/**
 * @brief Reads commands from a file and executes them.
 *
 * @param filename The name of the file containing commands
 * @param priQueue The PatientPriorityQueue object
 */
void execCommandsFromFileCmd(string filename, PatientPriorityQueue &priQueue) {
    ifstream infile;
    string line;
    stringstream ss(filename);
    ss >> filename;
    infile.open(filename);
    if (infile) {
        while (getline(infile, line)) {
            cout << "\ntriage> " << line ;
            // process file input
            processLine(line, priQueue);
        }
    } else {
        cout << "Error: could not open file.\n";
    }
    // close file
    infile.close();
}

/**
 * @brief Delimits the input string by space and returns the first token.
 *
 * @param s The input string to be delimited
 * @return The first token extracted from the input string
 */
string delimitBySpace(string &s) {

    // Create a stringstream from the input string
    stringstream ss(s);

    // Initialize variables to store the result and remaining part of the string
    string result, remaining;

    // Extract the first token from the stringstream
    ss >> result;

    // Get the remaining part of the string after the first token
    getline(ss, remaining);
    s = remaining;

    // Return the first token
    return result;

}

// Prints welcome message.
void welcome(){
    cout<<"Welcome to the hospital triage system.\n\n";
}


// Prints goodbye message.
void goodbye(){
    cout<<"Thanks for using the hospital triage system\n\n";
}



void help() {

    // Prints help menu.
    cout << "add <priority-code> <patient-name>\n"
         << "            Adds the patient to the triage system.\n"
         << "            <priority-code> must be one of the 4 accepted priority codes:\n"
         << "                1. immediate 2. emergency 3. urgent 4. minimal\n"
         << "            <patient-name>: patient's full legal name (may contain spaces)\n"
         << "next        Announces the patient to be seen next. Takes into account the\n"
         << "            type of emergency and the patient's arrival order.\n"
         << "peek        Displays the patient that is next in line, but keeps in queue\n"
         << "list        Displays the list of all patients that are still waiting\n"
         << "            in the order that they have arrived.\n"
         << "load <file> Reads the file and executes the command on each line\n"
         << "help        Displays this menu\n"
         << "quit        Exits the program\n";
}
