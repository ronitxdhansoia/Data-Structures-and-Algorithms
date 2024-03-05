#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Student {
    string name;
    int id;
    float cgpa;
    Student* next;
};

class StudentList {
private:
    Student* head;

public:
    StudentList() : head(NULL) {}

    ~StudentList() {
        while (head != NULL) {
            Student* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertStudent(int position, string name, int id, float cgpa) {
        Student* newStudent = new Student{name, id, cgpa, NULL};
        if (position == 1 || head == NULL) {
            newStudent->next = head;
            head = newStudent;
        } else {
            Student* temp = head;
            for (int i = 1; temp != NULL && i < position - 1; i++) {
                temp = temp->next;
            }
            if (temp != NULL) {
                newStudent->next = temp->next;
                temp->next = newStudent;
            } else {
                delete newStudent; // Position out of bounds
                cout << "Position out of bounds\n";
            }
        }
    }

    void searchByName(string name) {
        Student* temp = head;
        while (temp != NULL) {
            if (temp->name == name) {
                cout << "Found: " << temp->name << " ID: " << temp->id << " CGPA: " << temp->cgpa << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Student not found\n";
    }

    void deleteByName(string name) {
        Student* temp = head;
        Student* prev = NULL;
        while (temp != NULL && temp->name != name) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL) {
            cout << "Student not found\n";
            return;
        }
        if (prev == NULL) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }
        delete temp;
        cout << "Student deleted\n";
    }

    void retrieveByPosition(int position) {
        Student* temp = head;
        for (int i = 1; temp != NULL && i < position; i++) {
            temp = temp->next;
        }
        if (temp != NULL) {
            cout << "Found: " << temp->name << " ID: " << temp->id << " CGPA: " << temp->cgpa << "\n";
        } else {
            cout << "Position out of bounds\n";
        }
    }

    void displayAll() {
        Student* temp = head;
        if (temp == NULL) {
            cout << "List is empty\n";
            return;
        }
        while (temp != NULL) {
            cout << temp->name << " " << temp->id << " " << temp->cgpa << "\n";
            temp = temp->next;
        }
    }

    int size() {
        int count = 0;
        Student* temp = head;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    bool isEmpty() {
        return head == NULL;
    }
};

int main() {
    StudentList sl;
    int choice, position, id;
    string name;
    float cgpa;

    do {
        cout << "\n1. Insert Student\n";
        cout << "2. Search by Name\n";
        cout << "3. Delete by Name\n";
        cout << "4. Retrieve by Position\n";
        cout << "5. Display All Records\n";
        cout << "6. List Size\n";
        cout << "7. Check if Empty\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter position: ";
                cin >> position;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter CGPA: ";
                cin >> cgpa;
                sl.insertStudent(position, name, id, cgpa);
                break;
            case 2:
                cout << "Enter name to search: ";
                cin >> name;
                sl.searchByName(name);
                break;
            case 3:
                cout << "Enter name to delete: ";
                cin >> name;
                sl.deleteByName(name);
                break;
            case 4:
                cout << "Enter position to retrieve: ";
                cin >> position;
                sl.retrieveByPosition(position);
                break;
            case 5:
                sl.displayAll();
                break;
            case 6:
                cout << "List size: " << sl.size() << "\n";
                break;
            case 7:
                cout << "List is " << (sl.isEmpty() ? "empty" : "not empty") << "\n";
                break;
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while(choice != 0);

    return 0;
}
    
