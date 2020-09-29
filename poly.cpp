#include <iostream>
#include <vector>

class Poly {

private:

	int factorial(int x) {
		if (x == 1)
			return 1;
		else
			return x * factorial(x - 1);
	}

	int combination(int a, int b) {
			return factorial(a) / (factorial(b) * factorial(a - b));
		}

	double degree(double& x, int n) {
	//
		if (n == 0) {
			return 1;
		}
		else {
		return (x * degree(x, --n));
		}
		}
	/*	catch (int i) {
			std::cout << "а степень отрицательная откуда взялась??? О_О " << "\n";
		} */

	void copy(double* Poly1, double* Poly2, int size) {

		for (int i = 0; i < size; ++i) {
			*(Poly1 + i) = *(Poly2 + i);
		}
	}

double* C;
int power, capacity;

public:

	Poly() {
		double* P = new double[0];
		capacity = 0;
		power = -1;
		C = P;
	}

	Poly(const double& a) {
	double* P = new double[1];
	power = 0;
	capacity = 1;
	*P = a;
	C = P;
	}

	Poly(const double& a, const int& n) {
		double* P = new double[n + 1];
		capacity = n + 1;
		power = n;
		for (int i = 0; i < n; ++i) {
			*(P + i) = 0;
		}
		*(P + n) = a;
		C = P;
	}

	Poly(std::vector<double>& v) {
		capacity = v.size();
		double* P = new double[capacity];
		power = v.size() - 1;
		for (int i = 0; i < capacity; ++i) {
			*(P + i) = v[i];
		}
		C = P;
	}

	Poly(const Poly& rhs) {
		capacity = rhs.capacity;
		power = rhs.power;
		double* P = new double[rhs.capacity];
		copy(P, rhs.C, capacity);
		C = P;
	}

	~Poly() {
		delete[] C;
	}

	Poly& operator=(Poly& rhs) {
		capacity = rhs.capacity;
		power = rhs.power;
		double* P = new double[capacity];
		copy(P, rhs.C, capacity);
		C = P;
		return *this;
	}

	Poly operator+(Poly rhs) {
		int generals;
		Poly P;
		if (capacity > rhs.capacity) {
			generals = rhs.capacity;
			P = *this;
			for (int i = 0; i < generals; ++i) {
				*(P.C + i) += *(rhs.C + i);
			}
		}
		else {
			generals = capacity;
			P = rhs;
			for (int i = 0; i < generals; ++i) {
			*(P.C + i) += *(C + i);
			}
		}
		return P;
	}

	Poly operator-(Poly rhs) {
		int generals;
		Poly P;
		if (capacity > rhs.capacity) {
			generals = rhs.capacity;
			P = *this;
			for (int i = 0; i < generals; ++i) {
				*(P.C + i) -= *(rhs.C + i);
			}
		}
		else {
			generals = capacity;
			P = rhs;
			for (int i = 0; i < generals; ++i) {
			*(P.C + i) -= *(C + i);
			}
		}
		return P;
	}

	double value(double x) {
		if (capacity == 1) {
			return *C * degree(x, power);
		}
		else {
			double Q = 0;
			for (int i = 0; i <= power; ++i) {
				Q += *(C + i) * degree(x, i);
			}
			return Q;
		}
	}
};

int main() {

std::vector<double> v = {1, 2, 5, 1};
Poly sasalka(v);
Poly kvgvrv(1, 3);
std::cout << (kvgvrv - sasalka).value(2);
return 0;
}
