#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include <string>
#include <stack>

using namespace std;
/*
StackFrame declaration
*/
class StackFrame {
    int opStackMaxSize; // max size of operand stack
    int localVarSpaceSize; // size of local variable array
public:
    /*
    Constructor of StackFrame
    */
    StackFrame();
    
    /*
    Run the method written in the testcase
    @param filename name of the file
    */
    void run(std::string filename);
};

class Node {
public:
    int type;
    float data;
    Node* left;
    Node* right;
    int height;
    string key;
    Node() {
        this->key = "";
        this->type = this->data = 0;
        this->left = this->right = NULL;
        height = 1;
    }
    Node(string key, int type, float data) {
        this->key = key;
        this->type = type;
        this->data = data;
        this->left = this->right = NULL;
        this->height = 1;
    }
};

class Stack {
public:
    float* arr;
    int size;
    int maxsize;
    Stack(int maxSize) {
        arr = new float[maxSize];
        this->size = 0;
        this->maxsize = maxSize;
    }
    Stack() {
        this->arr = NULL;
        this->size = 0;
        this->maxsize = 0;
    }
    ~Stack() {
        delete[] arr;
    }
    void push(float temp, int type, int count);
    float top(int count); // get data
    float top1(int count); // get type
    void i2f() {
        arr[size - 1] = 1;
    }
    void f2i() {
        arr[size - 2] = int(arr[size - 2]);
        arr[size - 1] = 0;
    }
    void pop() {
        if (size == 0) {

        }
        else {
            this->size -= 2;
        }
    }
};

class Myclass {
public:
    Stack* st;
    Node* root;
    int opmax;
    int localVarSpaceSize;
    int sizeOfTree;
    Myclass(int opmax, int localVarSpaceSize) {
        st = new Stack(opmax);
        this->localVarSpaceSize = localVarSpaceSize;
        this->opmax = opmax;
        this->sizeOfTree = 0;
        this->root = NULL;
    }
    void running(std::string filename);
};

#endif // !__STACK_FRAME_H__