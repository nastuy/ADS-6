// Copyright 2022 NNTU-CS
#include <string>
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

struct SYM {
  char ch;
  int prior;
  SYM* next;
};

template<typename T>
class TPQueue {
 private:
  SYM* head;
  SYM* tail;
  int count;
  int capacity;

 public:
  TPQueue() : head(nullptr), tail(nullptr), count(0), capacity(-1) {}
  explicit TPQueue(int size) : head(nullptr), tail(nullptr), count(0), capacity(size) {
    if (size <= 0) {
      throw std::string("Queue size must be positive");
    }
  }
  bool isFull() const {
    return capacity != -1 && count == capacity;
  }
  bool isEmpty() const {
    return head == nullptr;
  }
  void push(const SYM& item) {
    if (isFull()) {
      throw std::string("Queue is full");
    }
    SYM* tepm = new SYM{ item.ch, item.prior, nullptr };
    if (isEmpty()) {
      head = tail = tepm;
    } else if (item.prior > head->prior) {
      tepm->next = head;
      head = tepm;
    } else {
      SYM* current = head;
      while (current->next && current->next->prior >= item.prior) {
        current = current->next;
      }
      tepm->next = current->next;
      current->next = tepm;
      if (tepm->next == nullptr) {
        tail = tepm;
      }
    }
    count++;
  }
  SYM pop() {
    if (isEmpty()) {
      throw std::string("Queue is empty");
    }
    SYM* temp = head;
    SYM result = *temp;
    head = head->next;
    if (head == nullptr) {
      tail = nullptr;
    }
    delete temp;
    count--;
    return result;
  }
  ~TPQueue() {
    while (!isEmpty()) {
      pop();
    }
  }
};

#endif  // INCLUDE_TPQUEUE_H_
