#include <iostream>
#include <vector>


/*
int factorial(int x) {										// творческая петля,
	if (x == 0) {											// не понадобилось внутри класса но все равно пусть будет 
		return 1;											// на память
	}		
	else {
		return x * factorial(x - 1);
	}
}

int combination(int a, int b) {
	return factorial(a) / (factorial(b) * factorial(a - b));
}

double Binome(double* P1, double* P2, int n) {
	double Q = 0;
	for (int i = 0; i <= n; ++i) {
		Q += *(P1 + n - i) * *(P2 + i);
	}
	return Q;
} */

class Poly {


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

	Poly operator*(Poly rhs) {
		int n = power + rhs.power;
		Poly result(0, n);
		for (int i = 0; i <= n; ++i) {
			*(result.C + i) = Binome(C, rhs.C, i);
		}
		return result;
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

	friend std::ostream& operator<<(std::ostream &stream, Poly rhs) {
		stream << *(rhs.C);
		for (int i = 1; i < rhs.capacity; ++i) {
			if (*(rhs.C + i) >= 0) {
				stream << "+";
			}
			stream << *(rhs.C + i) << "x^" << i;
		}
		return stream;
	}

	Poly dif() {
		Poly result(0, power - 1);
		for (int i = 0; i < power; ++i) {
			*(result.C + i) = *(C + i + 1) * (i + 1);
		}
		return result;
	}

	Poly integral(const double& x, const double& y) {	//принимает начальные условия(значение интеграла y в точке x
		Poly result(0, power + 1);						//необходимо чтобы однозначно определить свободный член
		for (int i = 1; i <= power + 1; ++i) {
			*(result.C + i) = *(C + i - 1) / i;
		}
		*(result.C) = y - result.value(x);
		return result;
	}

	private:

		double degree(double& x, int n) {
			if (n == 0) {
				return 1;
			}
			else {
				return (x * degree(x, --n));
			}
		}

		void copy(double* Poly1, double* Poly2, int size) {

			for (int i = 0; i < size; ++i) {
				*(Poly1 + i) = *(Poly2 + i);
			}
		}

		double* C;
		int power, capacity;
};

int main() {
	std::vector<double> v1 = {-3, 2, 1, 3};
	std::vector<double> v2 = { 1, -1, 2, 1};
	Poly test1(v1), test2(v2);
	std::cout << test1 << "; " << test1.integral(2, 24);

	return 0;
}
