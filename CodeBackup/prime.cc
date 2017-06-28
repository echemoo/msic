#include <iostream>
using namespace std;

unsigned long maxPrime(unsigned long);
bool isPrime(unsigned long);

bool isPrime2(unsigned long n) {
    for(unsigned short i=2; i < n ; i++){
		if ( n % i == 0) {
			return false;
		}
	}
	return true;
}

int main(){
	unsigned long limitNum = 0;
	cout << "请输入大于0的正整数限定值，输入0退出程序:" ;
	cin >> limitNum;
	while( limitNum != 0){
		if (limitNum >= 1){
			cout << limitNum << "以内最大的质数为:" << maxPrime(limitNum) << endl;
			cout << "请输入大于0的正整数限定值，输入0退出程序:" ;
			cin >> limitNum ;
		}else{
			cout << "输入错误！\n请输入大于0的正整数限定值，输入0退出程序:" ;
			cin >> limitNum ;
		}
	}
	return 0;
}

unsigned long maxPrime(unsigned long limit){
	for (unsigned long i = limit; i > 0; i--){
		if(isPrime2(i)) return i;
	}
	return 0;
}

bool isPrime(unsigned long n) {
    if (n <= 3) {
        return n > 1;
    } else if (n % 2 == 0 || n % 3 == 0) {
        return false;
    } else {
        for (unsigned short i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }
}
