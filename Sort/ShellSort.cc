#include <iostream>
#include <vector>
#include <string>
using namespace std;


void shellSort(vector<int> & arr){
	int n=static_cast<int>(arr.size());
	for(int gap=n/2;gap>0;gap/=2){
		for(int i=gap;i<n;i++){
			int temp=arr[i];
			int j=i;
			while(j-gap>=0&&arr[j-gap]>temp){
				arr[j]=arr[j-gap];
				j-=gap;
			}
			arr[j]=temp;
		}
	}
}

int main(){
	// 测试用例
    vector<int> arr = {12, 34, 54, 2, 3, 20, 18, 7, 90, 1};

    cout << "原数组: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // 调用 Shell 排序
    shellSort(arr);

    cout << "排序后: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}
