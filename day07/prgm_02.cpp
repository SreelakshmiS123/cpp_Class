#include <iostream>
#include <string>
using namespace std;

const int MAX_PATIENTS = 100;
const int MAX_DOCTORS = 10;

struct Patient {
    int id;
    string name;
    string disease;
    int roomNo;
    int daysAdmitted;
    float totalBill;
};

struct Doctor {
    int id;
    string name;
    string specialization;
    bool isAvailable;
};

Patient patients[MAX_PATIENTS];
Doctor doctors[MAX_DOCTORS];
int patientCount = 0;
int doctorCount = 0;

void addDoctor() {
    if (doctorCount >= MAX_DOCTORS) {
        cout << "Doctor capacity reached!" << endl;
        return;
    }

    Doctor newDoctor;
    newDoctor.id = doctorCount + 1;

    cout << "Enter doctor's name: ";
    cin.ignore();
    getline(cin, newDoctor.name);

    cout << "Enter specialization: ";
    getline(cin, newDoctor.specialization);

    cout << "Enter availability (1 for available, 0 for not available): ";
    cin >> newDoctor.isAvailable;

    doctors[doctorCount] = newDoctor;
    doctorCount++;

    cout << "Doctor added successfully!" << endl;
}

void displayDoctors() {
    if (doctorCount == 0) {
        cout << "No doctors available." << endl;
        return;
    }

    cout << "\nID\tName\tSpecialization\tAvailability\n";
    for (int i = 0; i < doctorCount; i++) {
        cout << doctors[i].id << "\t" << doctors[i].name << "\t" << doctors[i].specialization
             << "\t" << (doctors[i].isAvailable ? "Available" : "Not Available") << endl;
    }
}

void addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        cout << "Hospital is at full capacity!" << endl;
        return;
    }

    Patient newPatient;
    newPatient.id = patientCount + 1;

    cout << "Enter patient's name: ";
    cin.ignore();
    getline(cin, newPatient.name);

    cout << "Enter disease: ";
    getline(cin, newPatient.disease);

    cout << "Enter room number: ";
    cin >> newPatient.roomNo;

    cout << "Enter number of days admitted: ";
    cin >> newPatient.daysAdmitted;

    newPatient.totalBill = newPatient.daysAdmitted * 250; // Assuming Rs. 250 per day

    patients[patientCount] = newPatient;
    patientCount++;

    cout << "Patient added successfully!" << endl;
}

void displayPatients() {
    if (patientCount == 0) {
        cout << "No patients in the system." << endl;
        return;
    }

    cout << "\nID\tName\tDisease\tRoom No\tDays\tBill\n";
    for (int i = 0; i < patientCount; i++) {
        cout << patients[i].id << "\t" << patients[i].name << "\t" << patients[i].disease
             << "\t" << patients[i].roomNo << "\t" << patients[i].daysAdmitted
             << "\t" << patients[i].totalBill << endl;
    }
}

void assignDoctorToPatient() {
    int patientId, doctorId;
    cout << "Enter patient ID: ";
    cin >> patientId;

    if (patientId <= 0 || patientId > patientCount) {
        cout << "Invalid patient ID!" << endl;
        return;
    }

    cout << "Enter doctor ID: ";
    cin >> doctorId;

    if (doctorId <= 0 || doctorId > doctorCount) {
        cout << "Invalid doctor ID!" << endl;
        return;
    }

    if (!doctors[doctorId - 1].isAvailable) {
        cout << "Doctor is not available!" << endl;
        return;
    }

    cout << "Doctor " << doctors[doctorId - 1].name << " assigned to patient " << patients[patientId - 1].name << endl;
    doctors[doctorId - 1].isAvailable = false; // Mark doctor as unavailable
}

int main() {
    int choice;
    do {
        cout << "\nHospital Management System\n";
        cout << "1. Add Doctor\n";
        cout << "2. Display Doctors\n";
        cout << "3. Add Patient\n";
        cout << "4. Display Patients\n";
        cout << "5. Assign Doctor to Patient\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addDoctor(); break;
            case 2: displayDoctors(); break;
            case 3: addPatient(); break;
            case 4: displayPatients(); break;
            case 5: assignDoctorToPatient(); break;
            case 6: cout << "Exiting system..." << endl; break;
            default: cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
