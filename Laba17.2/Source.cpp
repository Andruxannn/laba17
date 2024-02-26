#include <iostream>
#include <stdexcept>
#include <locale.h>

template<typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t listSize;

public:
    List() : head(nullptr), tail(nullptr), listSize(0) {}

    ~List() {
        clear();
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }

        listSize++;
    }

    void push_front(const T& value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        listSize++;
    }

    std::size_t size() const {
        return listSize;
    }

    void find_and_erase(const T& value) {
        Node* currentNode = head;

        while (currentNode != nullptr) {
            if (currentNode->data == value) {
                if (currentNode == head) {
                    head = currentNode->next;
                }
                else if (currentNode == tail) {
                    tail = currentNode->prev;
                }

                if (currentNode->prev != nullptr) {
                    currentNode->prev->next = currentNode->next;
                }

                if (currentNode->next != nullptr) {
                    currentNode->next->prev = currentNode->prev;
                }

                delete currentNode;
                listSize--;
                return;
            }

            currentNode = currentNode->next;
        }
    }

    T& at(std::size_t index) const {
        if (index >= listSize) {
            throw std::out_of_range("Index out of range");
        }

        Node* currentNode = head;
        std::size_t currentIndex = 0;

        while (currentIndex != index) {
            currentNode = currentNode->next;
            currentIndex++;
        }

        return currentNode->data;
    }

    void clear() {
        Node* currentNode = head;

        while (currentNode != nullptr) {
            Node* nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }

        head = tail = nullptr;
        listSize = 0;
    }
};

struct Point {
    int x;
    int y;
    int z;
};

int main() {
    setlocale(LC_ALL, "RUS");
    List<int> intList;
    intList.push_back(1);
    intList.push_back(2);
    intList.push_front(0);

    std::cout << "intList size: " << intList.size() << std::endl;
    std::cout << "intList values: ";
    for (std::size_t i = 0; i < intList.size(); i++) {
        std::cout << intList.at(i) << " ";
    }
    std::cout << std::endl;

    intList.find_and_erase(1);

    std::cout << "–азмер IntList после удалени€ " << intList.size() << std::endl;
    std::cout << "значени€ IntList после удалени€: ";
    for (std::size_t i = 0; i < intList.size(); i++) {
        std::cout << intList.at(i) << " ";
    }
    std::cout << std::endl;

    List<Point> pointList;
    Point p1{ 1, 2, 3 };
    Point p2{ 4, 5, 6 };
    pointList.push_back(p1);
    pointList.push_back(p2);

    std::cout << "pointList size: " << pointList.size() << std::endl;
    std::cout << "pointList values: ";
    for (std::size_t i = 0; i < pointList.size(); i++) {
        Point& point = pointList.at(i);
        std::cout << "(" << point.x << ", " << point.y << ", " << point.z << ") ";
    }
    std::cout << std::endl;

    return 0;
}
//выгрузить на гит хаб , 
//как дела 