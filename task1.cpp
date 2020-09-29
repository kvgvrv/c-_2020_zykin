#include <iostream>
#include <set>

int main() {
	std::set<int> m;
	int n;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		int a;
		std::cin >> a;
		m.insert(a);
	}
	std::cout << m.size();
return 0;
}
