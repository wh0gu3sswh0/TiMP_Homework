// var - 59 | ukazateli / ochered' s odnoi golovoy / prostaya vstavka
#include <iostream>
#include <windows.h>


class Node {
public:
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// Класс очереди с "Головой" и "Хвостом"
class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    // Проверка, пуста ли очередь
    bool isEmpty() {
        return front == nullptr;
    }

    // Вставка элемента в очередь (enqueue)
    void enqueue(int val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Удаление элемента из очереди (dequeue)
    int dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Очередь пуста");
        }
        int val = front->data;
        Node* temp = front;
        front = front->next;
        delete temp;
        return val;
    }

    // Печать очереди
    void printQueue() {
        Node* current = front;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Сортировка очереди методом простой вставки (пр.: https://www.geeksforgeeks.org/cpp-program-for-insertion-sort/)
    void sortQueue() {
        if (isEmpty()) return;

        Node* sorted = nullptr;

        // Извлечь все элементы из очереди
        while (!isEmpty()) {
            int value = dequeue();

            // Вставить в отсортированное место
            if (sorted == nullptr || sorted->data >= value) {
                Node* newNode = new Node(value);
                newNode->next = sorted;
                sorted = newNode;
            }
            else {
                Node* current = sorted;
                while (current->next != nullptr && current->next->data < value) {
                    current = current->next;
                }
                Node* newNode = new Node(value);
                newNode->next = current->next;
                current->next = newNode;
            }
        }

        // Сохранить отсортированные элементы обратно в очередь
        Node* temp = sorted;
        while (temp != nullptr) {
            enqueue(temp->data);
            temp = temp->next;
        }

        // Очистка временного связанного списка
        while (sorted != nullptr) {
            Node* toDelete = sorted;
            sorted = sorted->next;
            delete toDelete;
        }
    }

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Queue q;
    q.enqueue(22);
    q.enqueue(14);
    q.enqueue(36);
    q.enqueue(9);
    q.enqueue(23);

    std::cout << "Исходная очередь: ";
    q.printQueue();

    q.sortQueue();

    std::cout << "Отсортированная очередь: ";
    q.printQueue();
    return 0;
}