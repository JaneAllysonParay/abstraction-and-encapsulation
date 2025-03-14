/* Paray, Jane Allyson L. | IT2C | Inteprog
This program is all about implentation of Abstraction and Encapsulation for C++ Language*/

#include <iostream>  // Header file for input and output in C++
#include <vector>    // Header file for vector
#include <string>    // Header file for string manipulation
#include <cctype>    // Header file for character manipulation
#include <limits>    // Limits the number being accepted
#include <iomanip>   // Header file for manipulating input and output
using namespace std; // For convenience and easy use of 'cin','cout', and other names

// Employee class with pure virtual functions
class Employee
{
// Private data members: name, ID, and salary
private:
    string name, id;
    double salary;

// Public member functions
public:
    Employee(string name, string id, double salary) : name(name), id(id), salary(salary) {} // Constructor
    virtual ~Employee() {}  // Virtual Destructor
    
    // Pure virtual functions
    virtual void inputDetails(vector<Employee *> &employees) = 0;
    virtual void calculateSalary() = 0;

    // Getters for the private data members
    string getName() 
    {
        return name;
    }
    string getID()
    {
        return id;
    }
    double getSalary()
    {
        return salary;
    }
};

// A validation for user's input (name)
bool isValidName(const string &name)
{
    if (name.empty())
        return false;
    for (char ch : name)
    {
        if (!isalpha(ch) && ch != ' ')
            return false;
    }
    return true;
}

// A validation for user's input (ID)
bool isValidID(const string &id)
{
    if (id.empty())
        return false;
    for (char ch : id)
    {
        if (!isalnum(ch))
            return false;
    }
    return true;
}

// A function for checking if ID is unique
bool isIDUnique(const vector<Employee *> &employees, const string &id)
{
    for (auto &employee : employees)
    {
        if (employee->getID() == id) return false;
    }
    return true;
}
// A function for checking if name is unique
bool isNameUnique(const vector<Employee *> &employees, const string &name)
{
    for (auto &employee : employees)
    {
        if (employee->getName() == name) return false;
    }
    return true;
}

// A function for getting a valid string input
string getValidString(const string &prompt, bool (*isValid)(const string &), const vector<Employee *> &employees, bool checkID)
{
    string input;
    bool valid = false;
    do
    {
        cout << prompt;
        getline(cin, input);
        valid = isValid(input);
        if (!valid)
        {
            cout << "Invalid input! Try again." << endl;
        }
        else if (!checkID && !isNameUnique(employees, input))
        {
            cout << "Duplicate Name!" << endl;
            valid = false;
        }
        else if (checkID && !isIDUnique(employees, input))
        {
            cout << "Duplicate ID!" << endl;
            valid = false;
        }
    } while (!valid);
    return input;
}

// A function for getting a valid double input
double getValidDouble(const string &prompt)
{
    double input;
    bool valid = false;
    do
    {
        cout << prompt;
        cin >> input;
        if (cin.fail() || cin.peek() != '\n' || input < 0)
        {
            cout << "Invalid input! Please enter a valid positive number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            valid = true;
        }
    } while (!valid);
    cin.ignore();
    return input;
}

// A function for getting a valid integer input
int getValidInt(const string &prompt)
{
    int input;
    bool valid = false;
    do
    {
        cout << prompt;
        cin >> input;
        if (cin.fail() || cin.peek() != '\n' || input < 0)
        {
            cout << "Invalid input! Please enter a valid positive number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            valid = true;
        }
    } while (!valid);
    cin.ignore();
    return input;
}

// A function for getting a valid menu input
int getValidMenu(const string &prompt, int minValue, int maxValue)
{
    int input;
    bool valid = false;
    do
    {
        cout << prompt;
        cin >> input;
        if (cin.fail() || cin.peek() != '\n' || input < minValue || input > maxValue)
        {
            cout << "Invalid input! Enter a number between " << minValue << " and " << maxValue << "." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            valid = true;
        }
    } while (!valid);
    cin.ignore();
    return input;
}

// Full-time Class
class Full : public Employee
{

// Public member functions
public:
    // Constructor
    Full(string name, string id, double salary) : Employee(name, id, salary) {}

    // Input Details Function for Full-time Employee
    void inputDetails(vector<Employee *> &employees) override
    {
        cout << endl
             << "Employee Type: Full-Time Employee" << endl;
        string name = getValidString("Enter Employee's Name: ", isValidName, employees, false);
        string id = getValidString("Enter Employee's ID: ", isValidID, employees, true);
        double salary = getValidDouble("Enter Employee's Salary: ");
        employees.emplace_back(new Full(name, id, salary)); // Adding the employee to the vector
    }

    // Calculate Salary and Display Function for Full-time Employee
    void calculateSalary() override
    {
        cout << "Employee: " << getName() << " (ID: " << getID() << ")" << endl;
        cout << "Fixed Monthly Salary: $" << fixed << setprecision(2) <<setw(10) << getSalary() << endl;
    }
};

// Part-time Class
class Part : public Employee
{

// Private data member: hours worked
private:
    double hrWork;

// Public member functions
public:
    // Constructor
    Part(string name, string id, double salary, double hrWork) : Employee(name, id, salary), hrWork(hrWork) {}

    // Input Details Function for Part-time Employee
    void inputDetails(vector<Employee *> &employees) override
    {
        cout << endl
             << "Employee Type: Part-Time Employee" << endl;
        string name = getValidString("Enter Employee's Name: ", isValidName, employees, false);
        string id = getValidString("Enter Employee's ID: ", isValidID, employees, true);
        double salary = getValidDouble("Enter Hourly Wage: ");
        double hrWork = getValidInt("Enter Hours Worked: ");
        employees.emplace_back(new Part(name, id, salary, hrWork)); // Adding the employee to the vector
    }

    // Calculate Salary and Display Function for Part-time Employee
    void calculateSalary() override
    {
        cout << "Employee: " << getName() << " (ID: " << getID() << ")" << endl;
        cout << "Hourly Wage: $" << getSalary() << endl;
        cout << "Hours Worked: " << hrWork << endl;
        cout << "Total Salary: $" << fixed << setprecision(2) << setw(10) << getSalary() * hrWork << endl;
    }
};

// Contract Class
class Contract : public Employee
{
// Private data member: projects completed
private:
    int proj;

// Public member functions
public:
    // Constructor
    Contract(string name, string id, double salary, int proj) : Employee(name, id, salary), proj(proj) {}

    // Input Details Function for Contractual Employee
    void inputDetails(vector<Employee *> &employees) override
    {
        cout << endl
             << "Employee Type: Contractual Employee" << endl;
        string name = getValidString("Enter Employee's Name: ", isValidName, employees, false);
        string id = getValidString("Enter Employee's ID: ", isValidID, employees, true);
        double salary = getValidDouble("Enter Payment Per Project: ");
        int proj = getValidInt("Enter Project/s Completed: ");
        employees.emplace_back(new Contract(name, id, salary, proj)); // Adding the employee to the vector
    }

    // Calculate Salary and Display Function for Contractual Employee
    void calculateSalary() override
    {
        cout << "Employee: " << getName() << " (ID: " << getID() << ")" << endl;
        cout << "Contract Payment Per Project: " << getSalary() << endl;
        cout << "Project/s Completed: " << proj << endl;
        cout << "Total Salary: $" << fixed << setprecision(2) << setw(10) << getSalary() * proj << endl;
    }
};

// Report Class
class Report
{
    // Public member functions
public:
    // Generate Function for Employee Payroll Report
    void generate(vector<Employee *> &employees)
    {
        // Displaying the Payroll Report
        for (auto &employee : employees) // Loop for displaying the employee's details
        {
            employee->calculateSalary();
            cout << "-------------------------------------" << endl;
        }
    }
};

// Main Function
int main()
{
    vector<Employee *> employees; // Vector for storing the employees
    int menu;                     // Menu for choosing the type of employee

    // Do-While Loop for the Menu
    do
    {
        cout << endl
             << "------ Paray Incorporated ------" << endl
             << endl;
        cout << "------------- Menu -------------" << endl;
        cout << "1 - Full-time Employee" << endl;
        cout << "2 - Part-time Employee" << endl;
        cout << "3 - Contractual Employee" << endl;
        cout << "4 - Display Payroll Report" << endl;
        cout << "5 - Exit" << endl;
        cout << "--------------------------------" << endl;
        menu = getValidMenu("Choose Menu [1|2|3|4|5]: ", 1, 5); // Getting the menu input with validation

        // Switch Case for the Menu
        switch (menu)
        {
        case 1:
        {
            Full("", "", 0.0).inputDetails(employees);
        }
        break;
        case 2:
        {
            Part("", "", 0.0, 0.0).inputDetails(employees);
        }
        break;
        case 3:
        {
            Contract("", "", 0.0, 0).inputDetails(employees);
        }
        break;
        case 4:
            cout << endl
                 << "------ Employee Payroll Report ------" << endl;
            Report report;
            report.generate(employees);
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << endl
                 << "Invalid option!" << endl;
        }
    } while (menu != 5); // Loop until the user chooses to exit

    // Deleting the employees to prevent memory leak
    for (auto &employee : employees)
    {
        delete employee;
    }
    return 0;
}