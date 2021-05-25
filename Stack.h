//
// Created by Alperen Alkan on 31.12.2020.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H
#include <iostream>
using namespace std;


class Stack {
public:
    Stack();
    ~Stack();
    bool push( string newItem);
    bool pop();
    bool pop(string& stackTop);
    string getTop();
    bool isEmpty()const;

private:
    struct StackNode {            // a node on the stack
        string item;        // a data item on the stack
        StackNode  *next;        // pointer to next node
    };
    StackNode *topPtr;     // pointer to first node in the stack
};


#endif //STACK_STACK_H
