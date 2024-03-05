#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    string idno;
    string name;
    string dob;
    double cgpa;
};

class Queue {
private:
    Student* arr;
    int capacity;
    int front;
    int rear;
    int count;

public:
    Queue(int size = 10);
    ~Queue();

    void enqueue(Student element);
    Student dequeue();
    Student peek();
    int size();
    bool isEmpty();
    bool isFull();
};

Queue::Queue(int size) {
    arr = new Student[size];
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
}

Queue::~Queue() {
    delete[] arr;
}

void Queue::enqueue(Student element) {
    if (isFull()) {
        cout << "Queue is full." << endl;
        return;
    }
    rear = (rear + 1) % capacity;
    arr[rear] = element;
    count++;
}

Student Queue::dequeue() {
    if (isEmpty()) {
        cout << "Queue is empty." << endl;
        return Student();
    }
    Student element = arr[front];
    front = (front + 1) % capacity;
    count--;
    return element;
}

Student Queue::peek() {
    if (isEmpty()) {
        cout << "Queue is empty." << endl;
        return Student(); 
    }
    return arr[front];
}

int Queue::size() {
    return count;
}

bool Queue::isEmpty() {
    return (size() == 0);
}

bool Queue::isFull() {
    return (size() == capacity);
}

void readFromFileAndEnqueue(Queue &queue, const string &filename) {
    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Could not open file " << filename << endl;
        return;
    }
    Student student;
    while (file >> student.idno >> student.name >> student.dob >> student.cgpa) {
        queue.enqueue(student);
    }
    file.close();
}

void dequeueAndWriteToFile(Queue &queue, const string &outputFilename) {
    ofstream outFile(outputFilename.c_str());
    if (!outFile.is_open()) {
        cout << "Could not open file " << outputFilename << endl;
        return;
    }
    while (!queue.isEmpty()) {
        Student student = queue.dequeue();
        cout << student.idno << " " << student.name << " " << student.dob << " " << student.cgpa << endl;
        outFile << student.idno << " " << student.name << " " << student.dob << " " << student.cgpa << endl;
    }
    outFile.close();
}

void displayStudentsWithCGPALessThan9(Queue &queue) {
    Queue tempQueue(queue.size());
    int originalSize = queue.size();

    for (int i = 0; i < originalSize; i++) {
        Student student = queue.dequeue();
        if (student.cgpa < 9.0) {
            cout << student.name << endl;
        }
        tempQueue.enqueue(student);
    }

    while (!tempQueue.isEmpty()) {
        queue.enqueue(tempQueue.dequeue());
    }
}


int main() {
    Queue queue(10);

    readFromFileAndEnqueue(queue, "studentin.dat");
    dequeueAndWriteToFile(queue, "studentout.dat");

    return 0;
}
