#include "SurveyClass.h"

SurveyClass::SurveyClass(){
members = new LinkedList();
}
SurveyClass::SurveyClass(const SurveyClass& other){
members = new LinkedList(*other.members);
}
SurveyClass& SurveyClass::operator=(const SurveyClass& list){
members = new LinkedList(*list.members);
return *this;
}
SurveyClass::SurveyClass(SurveyClass&& other){
    this->members = other.members;
    other.members = nullptr;

}
SurveyClass& SurveyClass::operator=(SurveyClass&& list){

    if(this != &list) {
        delete this->members;
        this->members = list.members;
        list.members = nullptr;
    }

    return *this;
}
SurveyClass::~SurveyClass(){
    delete members;
}

// Adds a new Node to the linked list or updates the corresponding Node in the linked list
void SurveyClass::handleNewRecord(string _name, float _amount){
if(!members->head){
    members->pushTail(_name,_amount);
}
else{
    Node* temp = members->head;
    bool updated = false;
    while(temp!=nullptr){
        if(_name == temp->name){

            temp->amount=_amount;
            updated = true;
            break;
        }

        temp = temp->next;
    }
    if(!updated){
        members->pushTail(_name,_amount);
    }

}


}
// Calculates and returns the minimum amount of expense.
// The minimum amount can have up to two decimal points.
float SurveyClass::calculateMinimumExpense(){
float min =members->head->amount;
for(Node* temp = members->head;temp!=nullptr;temp= temp->next){
    if(temp->amount<min) {
        min = temp->amount;
    }
}

    return (int)(min*100)/100.0;
}
// Calculates and returns the maximum amount of expense.
// The maximum amount can have up to two decimal points.
float SurveyClass::calculateMaximumExpense(){
    float max = members->head->amount;
    for(Node* temp = members->head;temp!=nullptr;temp= temp->next){
        if(temp->amount>max) {
            max = temp->amount;
        }
    }



    return (int)(max*100)/100.0;
}
// Calculates and returns the average amount of expense.
// The average amount can have up to two decimal points.
float SurveyClass::calculateAverageExpense(){
    float sum = 0;
    for(Node* temp = members->head;temp!=nullptr;temp=temp->next){
        sum+=temp->amount;
    }

    float x =sum/members->length;


    return (int)(x*100)/100.0 ;
}

