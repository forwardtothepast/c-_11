#include<iostream>
#include<string>
#include<vector>
using namespace std;

void passThisValue(int && x) {
	cout << "in passThisValuex r value: "<< x <<endl;
}
void passThisValue(int & x) {
	cout << "in passThisValuex l value: " << x << endl;
}
template <typename T>
void funcNotPerfectFwd(T arg) {
	cout << "in funcNotPerfectFwd: " << arg << endl;
	return passThisValue(arg);
}

template <typename T>
void funcPerfectFwd(T&& arg) {
	cout << "in funcPerfectFwd : " << arg << endl;
	return passThisValue(std::forward<T> (arg));
}

/**internal implementation
template <typename T>
T&& forward(typename remove_reference<T>:type& arg) {
return static_cast<T&&>(arg);

T&& is universal type when used in :
1) template typename
2) its a function template, i.e. reference collapsing has happend

**/
int main() {
	int p = 10;
	int n = 9;
	funcNotPerfectFwd(5);
	funcNotPerfectFwd(p);
	funcPerfectFwd(8);
	funcPerfectFwd(n);
}

/**output:
in funcNotPerfectFwd: 5
in passThisValuex l value: 5
in funcNotPerfectFwd: 10
in passThisValuex l value: 10
in funcPerfectFwd : 8
in passThisValuex r value: 8
in funcPerfectFwd : 9
in passThisValuex l value: 9
Press any key to continue . . .
**/