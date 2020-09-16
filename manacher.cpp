#include <iostream>
#include <vector>
#include <string>

using namespace std;

string manacher(string s) {
	string tmp = "$";
	for(auto c : s) {
		tmp += "#";
		tmp += c;
	}
	tmp += "#@";

	int n = tmp.length();
	vector<int> tmp_arr(n, 0);

	int c = 1, r = 1;
	int mirror;
	for(int i=1; i<n; i++) {
		mirror = c*2 -1;

		if(i < r)
			tmp_arr[i] = min(r - i, tmp_arr[mirror]);

		while(tmp[i + (tmp_arr[i] + 1)] == tmp[i - (tmp_arr[i] + 1)])
			tmp_arr[i]++;

		if(i + tmp_arr[i] > r) {
			c = i;
			r = i + tmp_arr[i];
		}
	}

	int max_index = 0;
	for(int i=0; i<n; i++) {
		if(tmp_arr[i] >= tmp_arr[max_index])
			max_index = i;
	}

	string result;
	int start = max_index - tmp_arr[max_index] + 1;
	int end = start + 2*tmp_arr[max_index];
	for(int i=start; i<end; i+=2) 
		result += tmp[i];

	return result;
}

int main() {

	string s;
	cin >> s;
	cout << manacher(s) << endl;

	return 0;
}