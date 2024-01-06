#include <bits/stdc++.h>
using namespace std;
// Function to return the count of common words
// in all the sentences
int commonWords(vector<string> S)
{
	int m, n, i, j;
	// To store separate words
	string str;
	// It will be used to check if a word is present
	// in a particular string
	unordered_map<string, bool> has;
	// To store all the words of first string
	vector<pair<string, bool> > ans;
	pair<string, bool> tmp;
	// m will store number of strings in given vector
	m = S.size();
	i = 0;
	// Extract all words of first string and store it in ans
	while (i < S[0].size()) {
		str = "";
		while (i < S[0].size() && S[0][i] != ' ') {
			str += S[0][i];
			i++;
		}
		// Increase i to get at starting index
		// of the next word
		i++;
		// If str is not empty store it in map
		if (str != "") {
			tmp = make_pair(str, true);
			ans.push_back(tmp);
		}
	}
	// Start from 2nd line check if any word of
	// the first string did not match with
	// some word in the current line
	for (j = 1; j < m; j++) {
		has.clear();
		i = 0;
		while (i < S[j].size()) {
			str = "";
			while (i < S[j].size() && S[j][i] != ' ') {
				str += S[j][i];
				i++;
			}
			i++;
			if (str != "") {
				has[str] = true;
			}
		}
		// Check all words of this vector
		// if it is not present in current line
		// make it false
		for (int k = 0; k < ans.size(); k++) {
			if (ans[k].second != false
				&& has[ans[k].first] == false) {
				ans[k].second = false;
			}
			// This line is used to consider only distinct words
			else if (ans[k].second != false
					&& has[ans[k].first] == true) {
				has[ans[k].first] = false;
			}
		}
	}
	// This function will print
	// the count of common words
	int cnt = 0;
	// If current word appears in all the sentences
	for (int k = 0; k < ans.size(); k++) {
		if (ans[k].second == true)
			cnt++;
	}
	return cnt;
}
// Driver code
int main()
{
	vector<string> S;
	S.push_back("there is a cow");
	S.push_back("cow is our mother");
	S.push_back("cow gives us milk and milk is sweet");
	S.push_back("there is a boy who loves cow");
	cout << commonWords(S);
	return 0;
}
