#include <vector>
#include <iostream>
using namespace std;

void bubbleSort(vector<int> &a){
	int n=a.size();
	for(int i=0;i<n;i++){
		bool swapped = false;
		for(int j=0;j<n-1-i;j++){
			if(a[j]>a[j+1]){
				swap(a[j],a[j+1]);
				swapped = true;
			}
		}
		if(!swapped) break;
	}
}
 
int main(void)
{
vector<int> arr = {5, 1, 4, 2, 8};
    bubbleSort(arr);

    for (int x : arr) {
        cout << x << " ";
    } 
}
