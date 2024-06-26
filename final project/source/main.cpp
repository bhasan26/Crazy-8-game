#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Employee {
protected:
    string name;
    string position;
    double baseSalary;
    string bankAccount;
    double totalHoursWorked;

public:
    Employee(string name, string position, double baseSalary, string bankAccount, double totalHoursWorked)
        : name(name), position(position), baseSalary(baseSalary), bankAccount(bankAccount), totalHoursWorked(totalHoursWorked) {}

    virtual double calculatePay() = 0;
    virtual void printPayStub() = 0;
};

class HourlyEmployee : public Employee {
private:
    double hourlyRate;

public:
    HourlyEmployee(string name, string position, double baseSalary, string bankAccount, double totalHoursWorked)
        : Employee(name, position, baseSalary, bankAccount, totalHoursWorked) {
        hourlyRate = baseSalary / 40; // Assuming 40 hours is full-time
    }

    double calculatePay() override {
        return totalHoursWorked * hourlyRate;
    }

    void printPayStub() override {
        cout << "Name: " << name << endl;
        cout << "Position: " << position << endl;
        cout << "Base Salary: $" << baseSalary << endl;
        cout << "Bank Account: " << bankAccount << endl;
        cout << "Total Hours Worked: " << totalHoursWorked << endl;
        cout << "Total Pay: $" << calculatePay() << endl;
    }
};

class SalariedEmployee : public Employee {
public:
    SalariedEmployee(string name, string position, double baseSalary, string bankAccount, double totalHoursWorked)
        : Employee(name, position, baseSalary, bankAccount, totalHoursWorked) {}

    double calculatePay() override {
        return baseSalary;
    }

    void printPayStub() override {
        cout << "Name: " << name << endl;
        cout << "Position: " << position << endl;
        cout << "Base Salary: $" << baseSalary << endl;
        cout << "Bank Account: " << bankAccount << endl;
        cout << "Total Hours Worked: " << totalHoursWorked << endl;
        cout << "Total Pay: $" << calculatePay() << endl;
    }
};

int main() {
    ifstream inFile("employee_info.txt");
    if (!inFile) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    vector<Employee*> employees;
    string name, position, bankAccount;
    double baseSalary, totalHoursWorked;

    while (inFile >> name >> position >> baseSalary >> bankAccount >> totalHoursWorked) {
        if (position == "Hourly") {
            employees.push_back(new HourlyEmployee(name, position, baseSalary, bankAccount, totalHoursWorked));
        } else if (position == "Salaried") {
            employees.push_back(new SalariedEmployee(name, position, baseSalary, bankAccount, totalHoursWorked));
        } else {
            cerr << "Error: Invalid position specified for employee " << name << endl;
        }
    }
    inFile.close();

    // Printing pay stubs
    for (auto emp : employees) {
        emp->printPayStub();
        cout << endl;
    }

    // Deallocating memory
    for (auto emp : employees) {
        delete emp;
    }

    return 0;
}
