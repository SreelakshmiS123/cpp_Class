#include <iostream>
#include <string>
using namespace std;

const int MAX_PATIENTS = 100;  // Maximum number of patients

// Function to add patient details
void addPatientDetails(string patients[], string patientIDs[], int& patientCount) {
    if (patientCount >= MAX_PATIENTS) {
        cout << "Cannot add more patients. Maximum limit reached!" << endl;
        return;
    }
    
    string patientName, patientID;
    cout << "Enter Patient Name: ";
    cin >> patientName;
    cout << "Enter Patient ID: ";
    cin >> patientID;

    patients[patientCount] = patientName;
    patientIDs[patientCount] = patientID;

    cout << "Patient added successfully!" << endl;
    patientCount++;
}

// Function to add doctor details
void addDoctorDetails(string doctors[], string doctorIDs[], int& doctorCount) {
    string doctorName, doctorID;
    cout << "Enter Doctor Name: ";
    cin >> doctorName;
    cout << "Enter Doctor ID: ";
    cin >> doctorID;

    doctors[doctorCount] = doctorName;
    doctorIDs[doctorCount] = doctorID;

    cout << "Doctor added successfully!" << endl;
    doctorCount++;
}

// Function to select room for the patient
void selectRoom(string rooms[], string roomAssignments[], int patientCount) {
    string room;
    cout << "Enter room number for patient " << patientCount + 1 << ": ";
    cin >> room;
    roomAssignments[patientCount] = room;

    cout << "Room " << room << " assigned to patient " << patientCount + 1 << endl;
}

// Function to handle treatment details
void treatmentDetails(string treatmentDetails[], int patientCount) {
    string treatment;
    cout << "Enter treatment details for patient " << patientCount + 1 << ": ";
    cin >> treatment;
    treatmentDetails[patientCount] = treatment;

    cout << "Treatment details added successfully!" << endl;
}

int main() {
    string patients[MAX_PATIENTS], patientIDs[MAX_PATIENTS];
    string doctors[MAX_PATIENTS], doctorIDs[MAX_PATIENTS];
    string roomAssignments[MAX_PATIENTS], treatmentDetailsArray[MAX_PATIENTS];

    int patientCount = 0, doctorCount = 0;

    int choice;
    do {
        cout << "\nHospital Management System\n";
        cout << "1. Add Patient\n";
        cout << "2. Add Doctor\n";
        cout << "3. Select Room for Patient\n";
        cout << "4. Add Treatment Details\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addPatientDetails(patients, patientIDs, patientCount);
                break;
            case 2:
                addDoctorDetails(doctors, doctorIDs, doctorCount);
                break;
            case 3:
                if (patientCount > 0) {
                    selectRoom(roomAssignments, patientCount);
                } else {
                    cout << "No patients to assign rooms!" << endl;
                }
                break;
            case 4:
                if (patientCount > 0) {
                    treatmentDetails(treatmentDetailsArray, patientCount);
                } else {
                    cout << "No patients to add treatment details!" << endl;
                }
                break;
            case 5:
                cout << "Exiting Hospital Management System.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
