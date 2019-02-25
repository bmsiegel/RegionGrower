#include "Node.hpp"
#include <stdexcept>

#ifndef STACK_H
#define STACK_H

template<typename T>
class Stack
{
private:
  Node<T> *head;
  int count;
public:
  Stack();
  Stack(const Stack& s);
  Stack& operator=(Stack s);
  virtual ~Stack();
  bool push(T data);
  bool pop();
  T peek();
  void clear();
  void swap(Stack<T> &x, Stack<T> &y);
  bool isEmpty() const {return (count == 0);}
  int size() const {return count;}
};

template<typename T>
Stack<T>::Stack()
{
  count = 0;
  head = nullptr;
}
template<typename T>
Stack<T>::Stack(const Stack& s) //Deep copy, copies all data into new memory address
{
  count = s.count;
  if (s.head == nullptr)
  {
    head = nullptr;
  }
  else
  {
    head = new Node<T>(s.head->getData());
    Node<T>*scurrent = s.head;
    Node<T>*current = head;
    while (scurrent->getNext() != nullptr)
    {
      scurrent = scurrent->getNext();
      current->setNext(new Node<T> (scurrent->getData()));
      current = current->getNext();
    }
  }
}
template<typename T>
Stack<T>& Stack<T>::operator=(Stack s) //Works because pass by copy to create Stack s, and delete s when it goes out of scope
{
  swap(*this, s);
  return *this;
}
template<typename T>
Stack<T>::~Stack() //Removes all dynamic data, so clear is good for that
{
  clear();
}
template<typename T>
bool Stack<T>::push(T data)
{
  if (head == nullptr) //check if stack is empty so we don't go to a node that doesn't exist
  {
    head = new Node<T>(data);
  }
  else
  {
    Node<T>* add = new Node<T> (data);
    add->setNext(head); //Places add before head
    head = add;
  }
  count++;
  return true;
}
template<typename T>
bool Stack<T>::pop() //removes data from top of stack
{
  if (head == nullptr)
  {
    return false;
  }
  Node<T> *temp = head;
  head = head->getNext();
  count--;
  delete temp;
  temp = nullptr;
  return true;
}
template<typename T>
T Stack<T>::peek()
{
  if (head != nullptr)
  {
    return head->getData();
  }
  else
  {
    throw std::range_error("Stack Empty.");
  }
}
template<typename T>
void Stack<T>::clear()
{
  while (pop()); //while it returns true there's still stuff it in, and when it's false there's nothing left and everything is delete
  count = 0;
}
template<typename T>
void Stack<T>::swap(Stack<T> &x, Stack<T> &y) //switches private variables
{
  std::swap(x.count, y.count);
  std::swap(x.head, y.head);
}

#endif
