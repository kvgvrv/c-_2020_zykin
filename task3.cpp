#include <iostream>


class MinStack {

public:

	MinStack() {
		int* New_Stack = new int[1];
		int* New_Min_Stack = new int[1];
		size = 0;
		min_size = 0;
		capacity = 1;
		min_capacity = 1;
		Stack = New_Stack;
		Min_Stack = New_Min_Stack;
		min_el = Min_Stack;
	}

	~MinStack() {
		delete[] Stack;
		delete[] Min_Stack;
	}

	void push(int x) {
		if (size == 0) {
			push_back_min(x);
		}
		if (size == capacity) {
			capacity *= 2;
			int* New_Stack = new int[capacity];
			copy(Stack, New_Stack, size);
			Stack = New_Stack;
			*(Stack + size) = x;
			delete[] New_Stack;
		}
		else {
			*(Stack + size) = x;
		}
		if (x < *min_el) {
			push_back_min(x);
		}
		++size;
	}

	void pop() {
		if (*(Stack + size - 1) == *min_el) {
			--min_size;
			--size;
		}
		else {
			--size;
		}
	}

	int top() {
		return *(Stack + size - 1);
	}

	int getMin() {
		return *(Min_Stack + min_size - 1);
	}

	void print() {
		for (int i; i < size; ++i) {
			std::cout << *(Stack + i) << " ";
		}
		std::cout << "\n";
	}

private:

	int size, capacity, min_capacity, min_size;
	int* Stack = new int[capacity];
	int* Min_Stack = new int[min_capacity];
	int* min_el;

	void copy(int* Old_Stack, int* New_Stack, int size) {
		for (int i = 0; i < size; ++i) {
			*(New_Stack + i) = *(Old_Stack + i);
		}
		delete[] Old_Stack;
	}

	void push_back_min(int x) {
		if (min_size == min_capacity) {
			min_capacity *= 2;
			int* New_Min_Stack = new int[min_capacity];
			copy(Min_Stack, New_Min_Stack, min_size);
			Min_Stack = New_Min_Stack;
			*(Min_Stack + min_size) = x;
			delete[] New_Min_Stack;
		}
		else {
			*(Min_Stack + min_size) = x;
		}
		min_el = Min_Stack + min_size;
		++min_size;
	}

};


int main() {
	MinStack* m = new MinStack;

  	m->push(2); m->push(3); std::cout <<"top is: " << m->top() << " min is: " << m->getMin() << "\n";
	m->print();
	m->push(1); std::cout <<"top is: " << m->top() << " min is: " << m->getMin() << "\n";
	m->print();
	m->pop(); std::cout <<"top is: " << m->top() << " min is: " << m->getMin() << "\n";
	m->print();

	m->push(5); std::cout <<"top is: " << m->top() << " min is: " << m->getMin() << "\n";
	m->print();

return 0;
}
