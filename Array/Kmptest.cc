#include <type_traits>
#include <vector>
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
using std::string;


vector<int> build_lps(const string &pat){
	int m = pat.size();
	vector<int> lps(m,0);
	if(m==0) return lps;

	int len=0;
	int i=1;

	while(i<m){
		if(pat[i]==pat[len]){
			len++;
			lps[i]=len;
			i++;
		}else{
			if(len!=0){
				len=lps[len-1];
			}else{
				lps[i]=0;
				i++;
			}
		}

	}
	return lps;
}

vector<int> kmp_search_all(const string &txt,const string &pat){
	vector<int> res;
	int n=(int)txt.size();
	int m=(int)pat.size();
	if(m==0){
		res.push_back(0);
		return res;
	}
	vector<int> lps = build_lps(pat);
	int i=0;
	int j=0;
	while(i<n){
		if(txt[i]==pat[j]){
			i++;
			j++;
			if(j==m){
				res.push_back(i-j);
				j=lps[j-1];
			}
		}else{
			if(j!=0){
				j=lps[j-1];
			}else{
				i++;
			}
		}
	}
	return res;
}



int main(void)
{
		string txt = "abcxabcdabcdabcyabcdabcy";
    string pat = "abcdabcy";

    // 1) 打印 lps 数组以便查看
    vector<int> lps = build_lps(pat);
    cout << "Pattern: " << pat << "\nLPS: "; 

	for(int x:lps){
		cout<<x<<' ';
	}
		cout<<endl;

	vector<int> matches = kmp_search_all(txt, pat);
    if (matches.empty()) {
        cout << "No matches found\n";
    } else {
        cout << "Matches found at indices: ";
        for (int idx : matches) cout << idx << ' ';
        cout << "\n";
    }

    return 0;
}
