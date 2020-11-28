#include <iostream>
#include <vector>
#include <string>
#include <queue>


class BinaryTree {

public:
	int value;
	BinaryTree* left_child;
	BinaryTree* right_child;
	unsigned int height;
	unsigned int depth;

	BinaryTree() {
		left_child = NULL;
		right_child = NULL;
		value = 0;
		height = 0;
		depth = 0;
	}

	BinaryTree(int val) {
		value = val;
		left_child = NULL;
		right_child = NULL;
		height = 1;
		depth = 0;
	}

	~BinaryTree() {}
	//метод вставляющий в дерево новый элемент
	void insert(int val) {
		if (val < value) {
			if (left_child == NULL) {
				BinaryTree* new_point = new BinaryTree(val);
				left_child = new_point;
			}
			else {
				left_child->insert(val);
			}
		}
		else {
			if (right_child == NULL) {
				BinaryTree* new_point = new BinaryTree(val);
				right_child = new_point;
			}
			else {
				right_child->insert(val);
			}
		}
	}

	void print_height() {
		std::cout << height << "\n";
	}
};
//обхожу в глубь дерево, вычисляю глубину каждого узла, каждый раз когда доходим до узла,
//у котрого нет детей, сравниваем его глубину с текущей высотой дерева, если она больше, меняем высоту
void DFS(BinaryTree* branch, BinaryTree* root) {
	if (branch->left_child != NULL) {
		(branch->left_child)->depth = branch->depth + 1;
		DFS(branch->left_child, root);
	}
	if (branch->right_child != NULL) {
		(branch->right_child)->depth = branch->depth + 1;
		DFS(branch->right_child, root);
	}
	if (branch->depth > root->height) {
		root->height = branch->depth + 1;
	}
}

int main() {
	std::string line;
	std::vector<int> data;
	//считываем строку последовательности чисел
	getline(std::cin, line);
	std::string v = "";
	int x;
	for (const auto& c : line) {
		if (c != ' ') {
			v += c;
		}
		else {
			x = stoi(v);
			v = "";
			data.push_back(x);
		}
	}
	if (v != "") {
		x = stoi(v);
		data.push_back(x);
	}
	//создаем корень и заполняем дерево
	BinaryTree root(data[0]);
	for (int i = 1; i < data.size(); ++i) {
		root.insert(data[i]);
	}
	//выполняем функцию вычисления высоты и печатаем ее
	DFS(&root, &root);
	root.print_height();
	return 0;
}