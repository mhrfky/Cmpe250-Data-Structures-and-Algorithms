#include "LinkedList.h"
#include <iostream>
using namespace std;
void ddelete(Node *node){
    if(node->next!=nullptr) {

        ddelete(node->next);
    }
    delete node;
}

LinkedList::LinkedList() {}


LinkedList::LinkedList(const LinkedList &list) {
    head = new Node(*list.head);
    Node* temp = head;
    while(true){
        if(temp->next==nullptr) {

            tail = temp;
            break;
        }
         temp = temp->next;

    }
    length = list.length;

}
LinkedList& LinkedList::operator=(const LinkedList &list) {
    delete(head);
    head = new Node(*list.head);
    Node* temp = head;
    while(true){
        if(temp->next==nullptr) {
            tail = temp;
            break;
        }
        temp = temp->next;

    }
    length = list.length;
    return *this;
}



LinkedList& LinkedList::operator=(LinkedList &&list) {
    if(this != &list){
        delete this->head;

        this->head = list.head;
        this->tail = list.tail;
        this->length = list.length;

        list.head = nullptr;
        list.tail = nullptr;
        list.length = 0;
    }

    return *this;
}

LinkedList::LinkedList(LinkedList &&list) {
    this->head = list.head;
    this->tail = list.tail;
    this->length = list.length;

    list.head = nullptr;
    list.tail = nullptr;
    list.length = 0;
}




void LinkedList::updateNode(string _name, float _amount) {
    Node* temp = head;
    while(true){
        if(temp->name ==_name){
            temp->amount = _amount;
        }
        temp =temp->next;
    }
}



void LinkedList::pushTail(string _name, float _amount) {
    if(head==nullptr){
        head = new Node(_name,_amount);
        tail = head;
    }
    else {
        tail->next = new Node(_name, _amount);
        tail = tail->next;

    }
    length++;
}



LinkedList::~LinkedList() {
   // ddelete(head);
   length=0;
delete head;

}


