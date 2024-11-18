#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <sstream>

using namespace std;

// Class for Student Records
class Student {
private:
    string RegistrationNo, Name, Grade;
    int studentID;

public:
    // Default Constructor
    Student() : RegistrationNo(""), Name(""), Grade(""), studentID(0) {}

    // Setter functions
    void setRegistrationNo(const string& registrationNo) {
        RegistrationNo = registrationNo;
    }

    void setName(const string& name) {
        Name = name;
    }

    void setGrade(const string& grade) {
        Grade = grade;
    }

    void setStudentID(int id) {
        studentID = id;
    }

    // Getter functions
    string getRegistrationNo() const {
        return RegistrationNo;
    }

    string getName() const {
        return Name;
    }

    string getGrade() const {
        return Grade;
    }

    int getStudentID() const {
        return studentID;
    }
};

// Function to write header and table format to file (only once)
void writeHeaderToFile(const string& filePath) {
    ofstream output("D:/Student.txt", ios::app);
    if (output) {
        static bool headerWritten = false; // Prevent multiple header writes
        if (!headerWritten) {
            output << left << setw(10) << "StudentID"
                   << setw(20) << "RegistrationNo"
                   << setw(20) << "Name"
                   << setw(10) << "Grade"
                   << setw(10) << "Physics"
                   << setw(10) << "Computer"
                   << setw(10) << "Math"
                   << setw(10) << "Total"
                   << setw(10) << "Average" << endl;

            // Print a horizontal separator line after header
            output << setfill('-') << setw(100) << "" << setfill(' ') << endl;

            headerWritten = true;
        }
        output.close();
    } else {
        cerr << "Error: Unable to write header to file!" << endl;
    }
}

// Function to delete record based on StudentID
void deleteRecord(int id, const string& filePath) {
    ifstream input("D:/Student.txt");
    ofstream tempFile("D:/temp.txt", ios::app);

    if (!input) {
        cerr << "Error: Unable to read from file!" << endl;
        return;
    }

    if (!tempFile) {
        cerr << "Error: Unable to create temporary file!" << endl;
        return;
    }

    string line;
    bool found = false;

    // Read each line from the original file and copy it to the temp file
    while (getline(input, line)) {
        stringstream ss(line);
        int studentID;
        ss >> studentID;  // Extract StudentID from each record

        if (studentID != id) {
            tempFile << line << endl;  // Copy the record to temp file if IDs don't match
        } else {
            found = true;  // Mark that the record was found and deleted
        }
    }

    input.close();
    tempFile.close();

    // Replace the original file with the temp file
    if (found) {
        remove(filePath.c_str());
        rename("D:/temp.txt", filePath.c_str());
        cout << "\nRecord with StudentID " << id << " has been deleted!\n";
    } else {
        cout << "\nRecord with StudentID " << id << " not found.\n";
        remove("D:/temp.txt");  // Remove the temp file if no deletion occurred
    }
}

// Function to update record based on StudentID
void updateRecord(int id, const string& filePath) {
    ifstream input("D:/Student.txt");
    ofstream tempFile("D:/temp.txt", ios::app);

    if (!input) {
        cerr << "Error: Unable to read from file!" << endl;
        return;
    }

    if (!tempFile) {
        cerr << "Error: Unable to create temporary file!" << endl;
        return;
    }

    string line;
    bool found = false;
    int studentID;
    string registrationNo, name, grade;
    int phy, comp, math, total, avg;

    // Read each line from the original file and copy it to the temp file
    while (getline(input, line)) {
        stringstream ss(line);
        ss >> studentID;  // Extract StudentID from each record

        if (studentID == id) {
            found = true;
            cout << "\nRecord Found. Please enter updated information:\n";

            // Ask for new details
            cout << "\tEnter New Registration Number: ";
            cin >> registrationNo;
            cout << "\tEnter New Name: ";
            cin >> name;

            // Input new Marks
            cout << "\tEnter Physics Marks: ";
            cin >> phy;
            cout << "\tEnter Computer Marks: ";
            cin >> comp;
            cout << "\tEnter Math Marks: ";
            cin >> math;

            // Calculate new Total and Average
            total = phy + comp + math;
            avg = total / 3;

            // Assign new Grade
            if (avg >= 90 && avg <= 100) {
                grade = "A";
            } else if (avg >= 80 && avg <= 89) {
                grade = "B";
            } else if (avg >= 70 && avg <= 79) {
                grade = "C";
            } else if (avg >= 60 && avg <= 69) {
                grade = "D";
            } else {
                grade = "F";
            }

            // Write the updated data to the temporary file
            tempFile << left << setw(10) << id
                     << setw(20) << registrationNo
                     << setw(20) << name
                     << setw(10) << grade
                     << setw(10) << phy
                     << setw(10) << comp
                     << setw(10) << math
                     << setw(10) << total
                     << setw(10) << avg << endl;

        } else {
            // Copy the existing record if it doesn't match the ID
            tempFile << line << endl;
        }
    }

    input.close();
    tempFile.close();

    // Replace the original file with the temp file
    if (found) {
        remove(filePath.c_str());
        rename("D:/temp.txt", filePath.c_str());
        cout << "\nRecord with StudentID " << id << " has been updated!\n";
    } else {
        cout << "\nRecord with StudentID " << id << " not found.\n";
        remove("D:/temp.txt");  // Remove the temp file if no update occurred
    }
}

// Function to see all records from the file
void seeRecords(const string& filePath) {
    ifstream input("D:/Student.txt");

    if (!input) {
        cerr << "Error: Unable to read from file!" << endl;
        return;
    }

    string line;
    bool foundRecords = false;

    // Read and display each line in the file
    while (getline(input, line)) {
        cout << line << endl;
        foundRecords = true;
    }

    if (!foundRecords) {
        cout << "\nNo records found!" << endl;
    }

    input.close();
}

// Function to search for a record based on StudentID
void searchRecord(int id, const string& filePath) {
    ifstream input("D:/Student.txt");

    if (!input) {
        cerr << "Error: Unable to read from file!" << endl;
        return;
    }

    string line;
    bool found = false;

    // Read each line and check if it matches the StudentID
    while (getline(input, line)) {
        stringstream ss(line);
        int studentID;
        ss >> studentID;  // Extract StudentID from each record

        if (studentID == id) {
            cout << "\nRecord Found:\n" << line << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nRecord with StudentID " << id << " not found.\n";
    }

    input.close();
}
int main() {
    Student s;
    string filePath = "D:/Student.txt";
    int studentCounter = 1; // Counter to assign unique ID

    writeHeaderToFile(filePath); // Ensure the header is written once

    bool exit = false;
    do {
        system("cls");
        int choice;

        // Main Menu
        cout << "\tWelcome to Report Card Management System\n";
        cout << "\t-----------------------------------------\n";
        cout << "\t1. Generate Report Card\n";
        cout << "\t2. Delete Report Card\n";
        cout << "\t3. Update Report Card\n";
        cout << "\t4. See Records (Watch Records)\n";  // Added option
        cout << "\t5. Search Record by ID\n";  // Added search option
        cout << "\t6. Exit\n";  // Exit option
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            system("cls");
            s.setStudentID(studentCounter++);
            string regNo, name, grade;
            int phy, comp, math;

            cout << "Enter Registration Number: ";
            cin >> regNo;
            cout << "Enter Name: ";
            cin >> name;

            // Input Marks
            cout << "Enter Physics Marks: ";
            cin >> phy;
            cout << "Enter Computer Marks: ";
            cin >> comp;
            cout << "Enter Math Marks: ";
            cin >> math;

            // Calculate Total and Average
            int total = phy + comp + math;
            int avg = total / 3;

            // Assign Grade
            if (avg >= 90 && avg <= 100) grade = "A";
            else if (avg >= 80 && avg <= 89) grade = "B";
            else if (avg >= 70 && avg <= 79) grade = "C";
            else if (avg >= 60 && avg <= 69) grade = "D";
            else grade = "F";

            // Store in file
            ofstream output("D:/Student.txt", ios::app);
            output << left << setw(10) << s.getStudentID()
                   << setw(20) << regNo
                   << setw(20) << name
                   << setw(10) << grade
                   << setw(10) << phy
                   << setw(10) << comp
                   << setw(10) << math
                   << setw(10) << total
                   << setw(10) << avg << endl;

            output.close();
            system("cls");
            cout << "Record Added Successfully!" << endl;
        } else if (choice == 2) {
            system("cls");
            int id;
            cout << "Enter Student ID to Delete: ";
            cin >> id;
            system("cls");
            deleteRecord(id, filePath);
        } else if (choice == 3) {
            system("cls");
            int id;
            cout << "Enter Student ID to Update: ";
            cin >> id;
            system("cls");
            updateRecord(id, filePath);
        } else if (choice == 4) {
            system("cls");
            seeRecords(filePath);
        } else if (choice == 5) {  // Search option
            system("cls");
            int id;
            cout << "Enter Student ID to Search: ";
            cin >> id;
            system("cls");
            searchRecord(id, filePath);
        } else if (choice == 6) {
            exit = true;
        }

        // Ask the user if they want to continue
        char continueChoice;
        cout << "\nDo you want to perform another action? (y/n): ";
        cin >> continueChoice;

        // If user presses 'y' or 'Y', the loop will continue, otherwise it will exit
        if (continueChoice != 'y' && continueChoice != 'Y') {
            exit = true;
        }

    } while (!exit);

    return 0;
}
