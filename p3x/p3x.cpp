
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




#include "PatientPriorityQueuex.h"
#include "Patient.h"
#include<algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


// Constructs a Patient object with the provided name, priority code, and arrival order.
Patient::Patient(string &name, string &priorityCode, int arrivalOrder) {
    this->name = name;
    this->priorityCode = priorityCode;
    this->arrivalOrder = arrivalOrder;
}


// Generates a string representation of the patient.
// Returns:
// - A string containing the patient's name, priority code, and arrival order.
string Patient::to_string() {
    string detail = "";
    stringstream ss;
    ss << arrivalOrder;
    detail += (name + " " + "{ pri=" + priorityCode + ", arrive=" + ss.str() + " }");
    return detail;
}


// Retrieves the name of the patient.
// Returns:
// - The name of the patient as a string.

string Patient::getName() {
    return name;
}


// Retrieves the priority code of the patient.
// Returns:
// - The priority code of the patient as a string.
string Patient::getPriorityCode() {
    return priorityCode;
}

// Retrieves the arrival order of the patient.
// Returns:
// - The arrival order of the patient.
int Patient::getArrivalOrder() const {
    return arrivalOrder;
}

void Patient::setPriorityCode(string code) {
    this->priorityCode = code;
}

// Determines the numerical value of the priority code for comparison.
// Returns:
// - 4 for "immediate" priority.
// - 3 for "emergency" priority.
// - 2 for "urgent" priority.
// - 1 for "minimal" priority.
// - 0 for any other priority code.
int Patient::comparingCode() const {
    string priorityCode = this->priorityCode;

    if (priorityCode == "immediate") {
        return 4;
    } else if (priorityCode == "emergency") {
        return 3;
    } else if (priorityCode == "urgent") {
        return 2;
    } else if (priorityCode == "minimal") {
        return 1;
    } else {
        return 0;
    }
}

// Overloads the less-than operator for Patient objects.
// Compares patients based on their priority codes and arrival orders.
// Returns true if 'this' patient has a lower priority or a higher arrival order than 'other', otherwise false.
bool Patient::operator<(const Patient &other) const {
    if (this->comparingCode() == other.comparingCode()) {
        return this->getArrivalOrder() > other.getArrivalOrder();
    } else if (this->comparingCode() < other.comparingCode()) {
        return true;
    } else {
        return false;
    }
}


void welcome();
// Prints welcome message.

void goodbye();
// Prints goodbye message.

void help();
// Prints help menu.

bool processLine(string, PatientPriorityQueuex &);
// Process the line entered from the user or read from the file.

void addPatientCmd(string, PatientPriorityQueuex &);
// Adds the patient to the waiting room.

void peekNextCmd(PatientPriorityQueuex &);
// Displays the next patient in the waiting room that will be called.

void removePatientCmd(PatientPriorityQueuex &);
// Removes a patient from the waiting room and displays the name on the screen.

void showPatientListCmd(PatientPriorityQueuex &);
// Displays the list of patients in the waiting room.

void execCommandsFromFileCmd(string, PatientPriorityQueuex &);
// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.

void writeCommandsToFileCmd(string, PatientPriorityQueuex &);
//write the data on system to outpuut file named 'patients.txt'

void changePriorityCode(string, PatientPriorityQueuex &);

string delimitBySpace(string &);
// Delimits (by space) the string from user or file input.


int main() {
    // declare variables
    string line;

    // welcome message
    welcome();

    // process commands
    PatientPriorityQueuex priQueue;
    do {
        cout << "\ntriage> ";
        getline(cin, line);
    } while (processLine(line, priQueue));

    // goodbye message
    goodbye();
}


// Processes the input line from the user or file.
// Extracts the command from the input line.
// Checks for errors such as missing command.
// Executes the corresponding function based on the command.
// Returns true to continue processing input, false to quit.
bool processLine(string line, PatientPriorityQueuex &priQueue) {
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
    else if (cmd == "save")
        writeCommandsToFileCmd(line, priQueue);
    else if (cmd == "change")
        changePriorityCode(line, priQueue);
    else if (cmd == "quit")
        return false;
    else
        cout << "Error: unrecognized command: " << cmd << endl;

    return true;
}


// Adds a patient to the priority queue based on the input line.
// Parses the priority code and patient name from the input line.
// Checks for errors such as missing priority code or patient name.
// Adds the patient to the priority queue if input is valid.
// Prints a message indicating the successful addition of the patient.
void addPatientCmd(string line, PatientPriorityQueuex &priQueue) {
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
    while (ss >> token) {
        name += (token + " ");
    }
    name = name.substr(0, name.size() - 1);
    if (name.length() == 0) {
        cout << "Error: no patient name given.\n";
        return;
    }

    if (!(priority == "immediate" || priority == "emergency" || priority == "urgent" || priority == "minimal")) {
        cout << "Please enter a valid priority-Code.\n";
        return;
    }

    priQueue.add(name, priority);
    cout << "Added patient " << "\"" << name << "\"" << " to the priority system\n";
}


// Checks if there are patients in the waiting room.
// If no patients are waiting, prints a message.
// Otherwise, prints the highest priority patient to be called next.

void peekNextCmd(PatientPriorityQueuex &priQueue) {
    if (priQueue.size() == 0) {
        cout << "There are no patients in the waiting area.\n";
        return;
    }
    cout << "Highest priority patient to be called next: " << priQueue.peek() << "\n";

}


// Checks if there are patients in the waiting room.
// If no patients are waiting, prints a message.
// Otherwise, prints the next patient to be seen.
// Removes the next patient from the queue.
void removePatientCmd(PatientPriorityQueuex &priQueue) {
    if (priQueue.size() == 0) {
        cout << "No patient in waiting\n";
        return;
    }
    cout << "This patient will now be seen: " << priQueue.peek() << "\n";
    priQueue.remove();
}


// Displays the number of waiting patients.
// Prints a formatted table header.
// Retrieves and prints the patient list from the queue.
void showPatientListCmd(PatientPriorityQueuex &priQueue) {
    cout << "# patients waiting: " << priQueue.size() << endl;
    cout << "  Arrival #   Priority Code   Patient Name\n"
         << "+-----------+---------------+--------------+\n";
    cout << priQueue.to_string();
}


// Writes commands to a file based on the current patient queue.
// Parses patient details from the queue's string representation.
// Constructs commands for adding patients with arrival order and priority code.
// Sorts commands based on arrival order for sequential execution.
// Opens the file for writing and handles errors if unable to open.
// Writes commands to the file and prints a confirmation message.
// Closes the file after writing.

void writeCommandsToFileCmd(string filename, PatientPriorityQueuex &priQueue) {
    // int size = priQueue.size();
    stringstream ss0(filename);
    ss0 >> filename;
    vector<pair<int, string>> commands;
    stringstream ss(priQueue.to_string());
    int counter = 0;
    string buff;
    int arrivalID;
    string priorityCode;
    string patientName;
    while (ss >> buff) {

        if (counter == 0) {

            arrivalID = stoi(buff);
        } else if (counter == 1) {
            priorityCode = buff;
            ss
                    >> buff; // buff here contains patient's first name , in the next getline i'll get the patients mid/last name in patient name.
            getline(ss, patientName, '\n');
            // cout<<patientName<<"\n";
            commands.push_back({arrivalID, "add " + priorityCode + " " + (buff + patientName)});
        }

        counter = (counter + 1) % 2;
    }
    sort(commands.begin(), commands.end());
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Unable to open file " << filename << "\n";
        return;
    }
    for (long unsigned int i = 0; i < commands.size(); i++) {
        outfile << commands[i].second << "\n";
    }
    cout << "Saved " << commands.size() << " " << "patients to file " << filename << "\n";
    outfile.close();


}


// Executes commands from a file.
// Opens the specified file for reading.
// Reads each line from the file and processes it as a command.
// Prints the command before processing.
// Handles errors if the file cannot be opened.
// Closes the file after processing.
void execCommandsFromFileCmd(string filename, PatientPriorityQueuex &priQueue) {
    ifstream infile;
    string line;
    stringstream ss(filename);
    ss >> filename;
    infile.open(filename);
    if (infile) {
        while (getline(infile, line)) {
            cout << "\ntriage> " << line << "\n";
            // process file input
            processLine(line, priQueue);
        }
    } else {
        cout << "Error: could not open file.\n";
    }
    // close file
    infile.close();
}

// Parses input line to extract patient ID and new priority code.
// Checks for errors in input format and validity.
// Updates priority code for patient in the priority queue.
void changePriorityCode(string line, PatientPriorityQueuex &priQueue) {
    // Initialize token counter to track the number of tokens read from the input line
    int tokenCounter = 0;
    int pID;
    string id = "-1";
    string priority = "default";
    string buff;

    // Create a stringstream from the input line
    stringstream ss(line);
    while (ss >> buff) {
        if (tokenCounter == 0) {
            id = buff;
        } else if (tokenCounter == 1) {
            priority = buff;
        }
        tokenCounter++;
    }
    if (tokenCounter == 0) {
        cout << "Error: No patient id provided\n";
        return;
    }
    try {
        pID = stoi(id);
    }
    catch (...) {
        cout << "Please enter a valid patient id, it must be an integer.\n";
        return;
    }
    if (tokenCounter == 1) {
        cout << "Error: No priority code given.\n";
        return;
    }
    if (!((priority == "immediate" || priority == "emergency" || priority == "urgent" || priority == "minimal"))) {
        cout << "Error: invalid priority level code.\n";
        return;
    }
    priQueue.changePriorityCode(pID, priority);
}

// Function: delimitBySpace
// Description: Splits a string by space and returns the first token, updating the input string to contain the remaining tokens.
// Parameters:
//   - s: A reference to the string to be split.
// Return Value: The first token of the input string.
string delimitBySpace(string &s) {

    stringstream ss(s);
    string result, remaining;
    ss >> result;
    getline(ss, remaining);
    s = remaining;
    return result;

}

// Prints welcome message.
void welcome() {
    cout << "Welcome to the hospital triage system.\n\n";
}

// Prints goodbye message.
void goodbye() {
    cout << "Thanks for using the hospital triage system\n\n";
}


// Prints help menu.
void help() {
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

