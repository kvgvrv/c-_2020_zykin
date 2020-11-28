#include <iostream>
#include <vector>
#include <string>


struct branch {
	int value;
	int left;
	int right;
};

bool DFS(std::vector<branch>& tree, int i, int big, int smoll) {
	if (tree[i].left != -1) {
		if (tree[tree[i].left].value > tree[i].value or tree[tree[i].left].value < smoll) {
			return 0;
		}
		else {
			return DFS(tree, tree[i].left, tree[i].value, smoll);	//если заходим в левый узел, меняем верхнюю границу
		}
	}
	if (tree[i].right != -1) {		//если заходим в правый узел, меняем нижнюю границу
		if (tree[tree[i].right].value < tree[i].value or tree[tree[i].right].value > big) {
			return 0;
		}
		else {
			return DFS(tree, tree[i].right, big, tree[i].value);
		}
	}
	if (i == 0) {
		return 1;
	}
}

int main() {
	int N;
	std::cin >> N;
	std::vector<branch> tree(N);
	for (int i = 0; i < N; ++i) {
		int v, l, r;
		std::cin >> v >> l >> r;
		tree[i].value = v;
		tree[i].left = l;
		tree[i].right = r;
	}
	if (DFS(tree, 0, 2000000000, -2000000000)) {
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}
	return 0;
}
