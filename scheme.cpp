#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <random>


class Scheme {

private:

	double t, T, h, L, cx, cy, N;
	std::map<int, std::vector<std::vector<double>>> data;

public:

	void save_data() {
		std::ofstream out;
		out.open("C:\dev\\data.txt");
		for (auto& c : data) {
			out << "T = " << c.first << "\n" << "--------------------------------------------------------------------------------------------\n";
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					out << c.second[i][j] << " ";
				}
				out << "\n";
			}
			out << "---------------------------------------------------------------------------------------------------\n";
		}
		out.close();
	}
};

class CIR : private Scheme {

private:

	double** U_previous;
	double** U_current;

public:

	CIR(std::vector<std::vector<double>> U0, double time_step, double Nt, double step, double Nl, double speed_x, double speed_y) {
		t = time_step;
		T = Nt;
		h = step;
		L = Nl;
		N = L / h;
		cx = speed_x;
		cy = speed_y;
		U_previous = new double* [N];
		U_current = new double* [N];
		for (int i = 0; i < N; ++i) {
			U_previous[i] = new double[N];
			U_current[i] = new double[N];
		}
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				U_previous[i][j] = U0[i][j];
			}
		}
		if (cx * t / h < 1 && cy * t / h < 1) {
			for (int q = 1; q < T; ++q) {
				U_current[0][0] = U_previous[0][0];
				U_current[1][0] = U_previous[0][0] - (cx * t / h) * (U_previous[1][0] - U_previous[0][0]);
				U_current[0][1] = U_previous[0][0] - (cy * t / h) * (U_previous[0][1] - U_previous[0][0]);
				for (int i = 1; i < N; ++i) {
					for (int j = 1; j < N; ++j) {
						U_current[i][j] = U_previous[i - 1][j - 1] - (cx * t / h) * (U_previous[i][j - 1] - U_previous[i - 1][j - 1])
							- (cy * t / h) * (U_previous[i - 1][j] - U_previous[i - 1][j - 1]);
					}
				}
				for (int i = 0; i < N; ++i) {
					for (int j = 0; j < N; ++j) {
						U_previous[i][j] = U_current[i][j];
					}
				}
				if (q % 10 == 0) {
					std::vector<std::vector<double>> tmp(N);
					for (int i = 0; i < N; ++i) {
						tmp[i].resize(N);
					}
					for (int i = 0; i < N; ++i) {
						for (int j = 0; j < N; ++j) {
							tmp[i][j] = U_current[i][j];
						}
					}
					data[q * t] = tmp;
				}
			}
		}
	}

	~CIR() {
		for (int i = 0; i < N; ++i) {
			delete[] U_current;
			delete[] U_previous;
		}
		delete[] U_current;
		delete[] U_previous;
	}
};

class LW : private Scheme {

private:

	double** U_previous;
	double** U_current;

public:

	LW(std::vector<std::vector<double>> U0, double time_step, double Nt, double step, double Nl, double speed_x, double speed_y) {
		t = time_step;
		T = Nt;
		h = step;
		L = Nl;
		N = L / h;
		cx = speed_x;
		cy = speed_y;
		U_previous = new double* [N];
		U_current = new double* [N];
		for (int i = 0; i < N; ++i) {
			U_previous[i] = new double[N];
			U_current[i] = new double[N];
		}
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				U_previous[i][j] = U0[i][j];
			}
		}
		if (cx * t / h < 1 && cy * t / h < 1) {
			for (int q = 1; q < T; ++q) {
				U_current[0][0] = U_previous[0][0];
				U_current[1][0] = U_previous[0][0] - (cx * t / h) * (U_previous[1][0] - U_previous[0][0])
					+(cx * cx * t * t / (2 * h * h)) * (U_previous[2][0] - 2 * U_previous[1][0] + U_previous[0][0]);
				U_current[1][0] = U_previous[0][0] - (cy * t / h) * (U_previous[1][0] - U_previous[0][0])
					+ (cy * cy * t * t / (2 * h * h)) * (U_previous[0][2] - 2 * U_previous[0][1] + U_previous[0][0]);
				for (int i = 1; i < N; ++i) {
					for (int j = 1; j < N; ++j) {
						U_current[i][j] = U_previous[i - 1][j - 1] - (cx * t / h) * (U_previous[i][j - 1] - U_previous[i - 1][j - 1])
							- (cy * t / h) * (U_previous[i - 1][j] - U_previous[i - 1][j - 1]) + (cx * cx * t * t / (2 * h * h)) * (
								U_previous[i+1][j - 1] - 2 * U_previous[i][j - 1] + U_previous[i - 1][j - 1]);
					}
				}
				for (int i = 0; i < N; ++i) {
					for (int j = 0; j < N; ++j) {
						U_previous[i][j] = U_current[i][j];
					}
				}
				if (q % 10 == 0) {
					std::vector<std::vector<double>> tmp(N);
					for (int i = 0; i < N; ++i) {
						tmp[i].resize(N);
					}
					for (int i = 0; i < N; ++i) {
						for (int j = 0; j < N; ++j) {
							tmp[i][j] = U_current[i][j];
						}
					}
					data[q * t] = tmp;
				}
			}
		}
	}

	~LW() {
		for (int i = 0; i < N; ++i) {
			delete[] U_current;
			delete[] U_previous;
		}
		delete[] U_current;
		delete[] U_previous;
	}
};

int main() {
	double time_step, step, cx, cy, T, L;
	std::cin >> time_step >> step >> cx >> cy >> T >> L;
	double N;
	N= L / step;
	std::vector<std::vector<double>> v(N);
	for (int i = 0; i < N; ++i) {
		v[i].resize(N);
	}
	CIR magic(v, time_step, T, step, L, cx, cy);
	magic.save_data();
	return 0;
}