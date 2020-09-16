#include <iostream>
#include <string>
#include <map>

using namespace std;

typedef struct Node {
	Node() : end(false){}
	map<char, Node*> next;
	bool end;
	string word;
} Node;

void tree_insert(Node *tree, string s) {
	for(auto c : s) {
		if(tree->next.find(c) == tree->next.end())
			tree->next[c] = new Node();
		tree = tree->next[c];
	}
	tree->end = true;
	tree->word = s;
}

void delete_tree(Node *tree) {
	if(tree == nullptr)
		return;
	for(auto &t : tree->next)
		delete_tree(t.second);

	delete tree;
}

void longest_autocomplete(Node *tree, string &longest_word) {
	if(tree->next.empty() && tree->end) {
		longest_word = tree->word;
		return;
	}

	for(auto t : tree->next) {
		string current_word; longest_autocomplete(t.second, current_word);
		if(current_word.length() >= longest_word.length()) {
			longest_word = current_word;
		}
	}
}

string longest_word_with_prefix(Node *tree, string prefix) {
	for(auto c : prefix) {
		if(tree->next.find(c) != tree->next.end())
			tree = tree->next[c];
		else
			return "";
	}
	string longest_word = prefix;
	longest_autocomplete(tree, longest_word);
	return longest_word;
}


int main() {
	
	Node *tree = new Node();

	int n;
	cin >> n;
	while(n--) {
		string word;
		cin >> word;
		tree_insert(tree, word);
	}

	string prefix;
	cin >> prefix;
	
	string longest_word = longest_word_with_prefix(tree, prefix);
	cout << ((longest_word == "")? "-1" : longest_word) << endl;

	delete_tree(tree);

	return 0;
}