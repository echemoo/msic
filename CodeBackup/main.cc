#include <iostream>
using namespace std;

int main(){
	double score = 0;
	cout << "请输出分数(0-150)，输入-1退出程序:" ;
	cin >> score;
	while( score != -1){
		if (score >=0 && score <=150){
			if (score >= 120)
				cout << "优秀" << endl ;
			else if(score >=105 && score <120)
				cout << "良好" << endl;
			else if(score >=90 && score <105)
				cout << "及格" << endl;
			else {
				cout << "不及格" << endl;
			}
			cout << "请再次输出分数(0-150)，输入-1退出程序:" ;
			cin >> score ;
		}else{
			cout << "请输入合理分数范围(0-150)，输入-1退出程序:" ;
			cin >> score ;
		}
	}
	return 0;
}
