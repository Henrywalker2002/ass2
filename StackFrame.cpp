#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;

StackFrame::StackFrame() : opStackMaxSize(OPERAND_STACK_MAX_SIZE), localVarSpaceSize(LOCAL_VARIABLE_SPACE_SIZE) {}

int height(Node* x) {
    if (x == NULL) return 0;
    return x->height;
}

Node* rightRotate(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left),
        height(y->right)) + 1;
    x->height = max(height(x->left),
        height(x->right)) + 1;

    // Return new root
    return x;
}

Node* leftRotate(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left),
        height(x->right)) + 1;
    y->height = max(height(y->left),
        height(y->right)) + 1;

    // Return new root
    return y;
}


// Get Balance factor of node N
int getBalance(Node* N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key
// in the subtree rooted with node and
// returns the new root of the subtree.
Node* insert(Node* node, Node* newNode)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newNode);
    int temp = newNode->key.compare(node->key);

    if (temp < 0)
        node->left = insert(node->left, newNode);
    else if (temp > 0)
        node->right = insert(node->right, newNode);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
        height(node->right));

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && (newNode->key.compare(node->left->key) < 0))
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && (newNode->key.compare(node->right->key) > 0))
        return leftRotate(node);
    
    // Left Right Case
    if (balance > 1 && (newNode->key.compare(node->left->key) > 0))
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left Case
    if (balance < -1 && (newNode->key.compare(node->right->key) < 0))
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

Node* search(Node* root, string key) {
	if (root == NULL) return NULL;
	if (root->key.compare(key) == 0) return root;
	else if (key.compare(root->key) > 0) return search(root->right, key);
	else return search(root->left, key);
}

void findParent(Node* root, string var, string parent) {
	if (root == NULL) return;
	if (root->key.compare(var) == 0) {
		cout << parent << endl;
	}
	else {
		findParent(root->left, var, root->key);
		findParent(root->right, var, root->key);
	}
}

void Stack::push(float temp, int type, int count) {
	if (this->size >= maxsize - 1) {
		throw StackFull(count);
	}
	arr[size] = temp;
	arr[size + 1] = float(type);
	size += 2;
}
float Stack::top(int count) {
	if (size == 0) {
		throw StackEmpty(count);
	}
	return arr[size - 2];
}

float Stack::top1(int count) {
	if (this->size == 0) {
		throw StackEmpty(count);
	}
	return arr[size - 1];
}

void calculatorInt(Stack* st, int count, char op) {
	int res;
	int val2 = int(st->top(count));
	int temp = st->top1(count);
	st->pop();
	int val = int(st->top(count));
	if (temp != 0) {
		throw TypeMisMatch(count);
	}
	if (st->top1(count) != 0) {
		throw TypeMisMatch(count);
	}
	st->pop();
	switch (op)
	{
	case '+':
		res = val + val2;
		break;
	case '-':
		res = val - val2;
		break;
	case '*':
		res = val * val2;
		break;
	case '/':
		if (val2 == 0) {
			throw DivideByZero(count);
		}
		res = int(int(val) / int(val2));
		break;
	case '%':
		if (val2 == 0) {
			throw DivideByZero(count);
		}
		res = int(val) % int(val2);
		break;
	case '&':
		res = val & val2;
		break;
	case '|':
		res = val | val2;
		break;
	case '=':
		if (val == val2) res = 1;
		else res = 0;
		break;
	case '!':
		if (val != val2) res = 1;
		else res = 0;
		break;
	case '>':
		if (val > val2) res = 1;
		else res = 0;
		break;
	case '<':
		if (val < val2) res = 1;
		else res = 0;
		break;
	default:
		res = -1;
		break;
	}
	st->push(float(res), 0, count);
}

void calculatorFloat(Stack* st, int count, char op) {
	float res;
	float val2 = st->top(count);
	st->pop();
	float val = st->top(count);
	st->pop();
	switch (op)
	{
	case '+':
		res = val + val2;
		break;
	case '-':
		res = val - val2;
		break;
	case '*':
		res = val * val2;
		break;
	case '/':
		res = val / val2;
		if (val2 == 0) {
			throw DivideByZero(count);
		}
		break;
	case '=':
		if (val == val2) res = 1;
		else res = 0;
		break;
	case '!':
		if (val != val2) res = 1;
		else res = 0;
		break;
	case '>':
		if (val > val2) res = 1;
		else res = 0;
		break;
	case '<':
		if (val < val2) res = 1;
		else res = 0;
		break;
	default:
		res = -1;
		break;
	}
	if (op == '=' || op == '!' || op == '>' || op == '<') {
		st->push(res, 0, count);
	}
	else {
		st->push(res, 1, count);
	}
}

void Myclass::running(std::string filename) {
	fstream f;
	f.open(filename, ios::in);
	std::string line;
	int count = 1;
	while (!f.eof()) {
		getline(f, line);
		int pos = line.find_first_of(' ');
		string act = line.substr(0, pos);
		if (act == "iconst") {
			int val = stoi(line.substr(pos + 1, line.size() - pos));
			st->push(float(val), 0, count);
		}
		else if (act == "fconst") {
			float val = stof(line.substr(pos + 1, line.size() - pos));
			st->push(val, 1, count);
		}
		else if (act == "iload") {
			string val = line.substr(pos + 1, line.size() - pos);
			Node* node = search(this->root, val);
			if (!node) throw UndefinedVariable(count);
			if (node->type != 0) throw TypeMisMatch(count);
			st->push(node->data, node->type, count);
		}
		else if (act == "fload") {
			string val = line.substr(pos + 1, line.size() - pos);
			Node* node = search(this->root, val);
			if (!node) throw UndefinedVariable(count);
			if (node->type != 1) throw TypeMisMatch(count);
			st->push(node->data, node->type, count);
		}
		else if (act == "istore") {
			string val = line.substr(pos + 1, line.size() - pos);
			if (st->top1(count) != 0) throw TypeMisMatch(count);
			Node* newNode = new Node(val, 0, st->top(count));
			if (this->sizeOfTree == this->localVarSpaceSize - 1) throw LocalSpaceFull(count);
			this->root = insert(root, newNode);
			this->sizeOfTree++;
			st->pop();
		}
		else if (act == "fstore") {
			string val = line.substr(pos + 1, line.size() - pos);
			if (st->top1(count) != 1) throw TypeMisMatch(count);
			Node* newNode = new Node(val, 1, st->top(count));
			if (this->sizeOfTree == this->localVarSpaceSize - 1) throw LocalSpaceFull(count);
			this->root = insert(root, newNode);
			this->sizeOfTree++;
			st->pop();
		}
		else if (act == "iadd") {
			calculatorInt(st, count, '+');
		}
		else if (act == "fadd") {
			calculatorFloat(st, count, '+');
		}
		else if (act == "isub") {
			calculatorInt(st, count, '-');
		}
		else if (act == "fsub") {
			calculatorFloat(st, count, '-');
		}
		else if (act == "imul") {
			calculatorInt(st, count, '*');
		}
		else if (act == "idiv") {
			calculatorInt(st, count, '/');
		}
		else if (act == "irem") {
			calculatorInt(st, count, '%');
		}
		else if (act == "ineg") {
			if (st->top1(count) != 0) {
				throw TypeMisMatch(count);
			}
			float temp = st->top(count);
			st->pop();
			if (temp == 0.000000) {
				st->push(0, 0, count);
			}
			else {
				st->push(-temp, 0, count);
			}
		}
		else if (act == "iand") {
			calculatorInt(st, count, '&');
		}
		else if (act == "ior") {
			calculatorInt(st, count, '|');
		}
		else if (act == "ieq") {
			calculatorInt(st, count, '=');
		}
		else if (act == "ineq") {
			calculatorInt(st, count, '!');
		}
		else if (act == "ilt") {
			calculatorInt(st, count, '<');
		}
		else if (act == "igt") {
			calculatorInt(st, count, '>');
		}
		else if (act == "ibnot") {
			if (st->top1(count) != 0) {
				throw TypeMisMatch(count);
			}
			float temp = st->top(count);
			st->pop();
			if (temp == 0) {
				st->push(1, 0, count);
			}
			else st->push(0, 0, count);
		}
		else if (act == "fmul") {
			calculatorFloat(st, count, '*');
		}
		else if (act == "fdiv") {
			calculatorFloat(st, count, '/');
		}
		else if (act == "fneg") {
			float temp = st->top(count);
			st->pop();
			st->push(-temp, 1, count);
		}
		else if (act == "feq") {
			calculatorFloat(st, count, '=');
		}
		else if (act == "fneq") {
			calculatorFloat(st, count, '!');
		}
		else if (act == "flt") {
			calculatorFloat(st, count, '<');
		}
		else if (act == "fgt") {
			calculatorFloat(st, count, '>');
		}
		else if (act == "top") {
			cout << st->top(count) << endl;
		}
		else if (act == "val") {
			string var = line.substr(pos + 1, line.size() - pos);
			Node* node = search(root, var);
			if (!node) throw UndefinedVariable(count);
			cout << node->data << endl;
		}
		else if (act == "par") {
			string var = line.substr(pos + 1, line.size() - pos);
			Node* node = search(root, var);
			if (!node) throw UndefinedVariable(count);
			if (node->key == root->key) cout << "null\n";
			else findParent(root, var, "");
		}
		else if (act == "i2f") {
			if (st->top1(count) != 0) {
				throw TypeMisMatch(count);
			}
			st->i2f();
		}
		else if (act == "f2i") {
			if (st->top1(count) != 1) {
				throw TypeMisMatch(count);
			}
			st->f2i();
		}
		else {
		}
		count++;
	}
	f.close();
}


void StackFrame::run(string filename) {
	Myclass temp(this->opStackMaxSize, this->localVarSpaceSize);
	temp.running(filename);
}