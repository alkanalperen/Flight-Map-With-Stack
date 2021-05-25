//
// Created by Alperen Alkan on 31.12.2020.
//

#include "Stack.h"

// default constructor
Stack::Stack() : topPtr(NULL){

}// destructor
Stack::~Stack(){

    // pop until stack is empty
    while (!isEmpty())
        pop();

}
bool Stack::isEmpty() const {
    return topPtr == NULL;
}
bool Stack::push(string newItem) {

    // create a new node
    StackNode *newPtr = new StackNode;

    // set data portion  of new node
    newPtr->item = newItem;

    // insert the new node
    newPtr->next = topPtr;
    topPtr = newPtr;

    return true;
}
bool Stack::pop() {

    if (isEmpty())
        return false;

        // stack is not empty; delete top
    else{
        StackNode *temp = topPtr;
        topPtr = topPtr->next;

        // return deleted node to system
        temp->next = NULL;  // safeguard
        delete temp;
        return true;
    }
}
bool Stack::pop(string& stackTop) {

    if (isEmpty())
        return false;

        // not empty; retrieve and delete top
    else{
        stackTop = topPtr->item;
        StackNode *temp = topPtr;
        topPtr = topPtr->next;

        // return deleted node to system
        temp->next = NULL;  // safeguard
        delete temp;
        return true;
    }
}
string Stack::getTop() {
    return topPtr->item;
}
