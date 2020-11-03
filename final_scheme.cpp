#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <random>
#include <string>


class Scheme {

public:

	double t, T, h, L, c;
	int N;
	std::map<int, std::map<double, double>> data;

	void save_data() {
		std::ofstream out;
		for (auto& c : data) {
			std::string name = std::to_string(c.first);
			out.open("C:\dev\\" + name + ".txt");
			for (auto& s : c.second) {
				out << s.first << " " << s.second << "\n";
			}
			out.close();
		}
	}

	void print_data() {
		for (auto& c : data) {
			std::cout << "T = " << c.first << "\n-------------------------------------------------------------------------------------------------------------------\n";
			for (auto& s : c.second) {
				std::cout << s.first << " : " << s.second << "\n";
			}
			std::cout << "-------------------------------------------------------------------------------------------------------------------\n";
		}
	}
};

class CIR : public Scheme {

public:

	double* U_previous;
	double* U_current;

	CIR(std::vector<double> U0, double time_step, double Nt, double step, double Nl, double speed) {
		t = time_step;
		T = Nt;
		h = step;
		L = Nl;
		N = L / h;
		c = speed;
		U_previous = new double[N];
		U_current = new double[N];
		for (int i = 0; i < N; ++i) {
				U_previous[i] = U0[i];
		}
		if (c * t / h < 1) {
			for (int q = 1; q < T; ++q) {
				U_current[0] = U_previous[0];
				for (int i = 1; i < N; ++i) {
					for (int j = 1; j < N; ++j) {
						U_current[i] = U_previous[i] - (c * t / h) * (U_previous[i] - U_previous[i - 1]);
					}
				}
				for (int i = 0; i < N; ++i) {
						U_previous[i] = U_current[i];
				}
				if (q % 1 == 0) {
					std::map<double, double> tmp;
					for (int i = 0; i < N; ++i) {
							tmp[i * h] = U_current[i] ;
					}
					data[q * t] = tmp;
				}
			}
		}
	}

	~CIR() {
		delete[] U_previous;
		delete[] U_current;
	}
};

class LW : public Scheme {

public:

	double* U_previous;
	double* U_current;

	LW(std::vector<double> U0, double time_step, double Nt, double step, double Nl, double speed) {
		t = time_step;
		T = Nt;
		h = step;
		L = Nl;
		N = L / h;
		c = speed;
		U_previous = new double [N];
		U_current = new double [N];
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				U_previous[i] = U0[i];
			}
		}
		for (int q = 1; q < T; ++q) {
			U_current[0] = U_previous[0];
			U_current[N - 1] = U_previous[N - 1];
			for (int i = 1; i < N - 1; ++i) {
				U_current[i] = U_previous[i] - c * t / (2 * h) * (U_previous[i + 1] - U_previous[i - 1]) +
					c * c * t * t / (2 * h * h) * (U_previous[i + 1] - 2 * U_previous[i] + U_previous[i - 1]);
			}
			if (q % 1 == 0) {
				std::map<double, double> tmp;
				for (int i = 0; i < N; ++i) {
					tmp[i * h] = U_current[i];
				}
				data[q * t] = tmp;
			}
		}
	}
	
	~LW() {
		delete[] U_current;
		delete[] U_previous;
	}
};

int main() {
	double time_step, step, c, T, L;
	std::cin >> time_step >> step >> c >> T >> L;
	double N;
	N = L / step;
	std::vector<double> v(N);
	for (int i = 0; i < N; ++i) {
		v[i] = i % 2;
	}
	CIR magic(v, time_step, T, step, L, c);
	magic.print_data();
	return 0;
}
