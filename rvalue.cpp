#include<iostream>
#include<string>
#include<vector>
using namespace std;
class ExplainRvalue {
private:
	int * _marray;
	int size = 3;
	string name = "default";
public:
	ExplainRvalue() {	
		cout << "ExplainRvalue(): name = "<< name<<endl;
		this->_marray = new int[size];
		for (auto i = 0; i < this->size; i++) {
			this->_marray[i] = i;
		}
	}

	ExplainRvalue(int sizeArg, string nameStr, const int *arr) {
		cout << "ExplainRvalue(int sizeArg, string nameStr, const int *arr): name = " << nameStr << endl;
		this->size = sizeArg;
		this->_marray = new int[this->size];
		this->name = nameStr;
		for (auto i = 0; i < this->size; i++) {
			this->_marray[i] = arr[i];
		}
	}

	ExplainRvalue(const ExplainRvalue & src) {
		cout << "(const ExplainRvalue & src) : name = " << src.name << endl;
		this->size = src.size;
		this->_marray = new int[this->size];
		this->name = src.name;
		for (auto i = 0; i < this->size; i++) {
			this->_marray[i] = src._marray[i];
		}
	}

	ExplainRvalue(ExplainRvalue && src) {
		cout << "(ExplainRvalue && src)  : name = " << src.name << endl;
		this->size = src.size;
		this->_marray = src._marray;
		this->name = src.name;
		src._marray = nullptr;
	}

	~ExplainRvalue() {
		delete this->_marray;
		this->_marray = nullptr;
	}

	void print() {
		auto printArray = [this] {		
			for (auto i = 0; i < this->size; i++) {
			cout << this->_marray[i] << " ";
		}
		cout << endl; };
		cout << "this->size: " << this->size << endl;
		cout << "this->_marray: " << endl;
		printArray();
		cout << "this->name: " << this->name << endl;
	}
};

int main() {
	int arr[] = {1, 2};
	int arr3[] = { 1, 2, 3, 4, 5};
	auto fun1 = [&] { return ExplainRvalue(5, "rValue overload", arr3); };
	// create lvalue object
	ExplainRvalue lObj = ExplainRvalue(2, "lValue",arr);
	vector<ExplainRvalue> vt;
	vt.push_back(fun1());
	vt.push_back(lObj);
	for (auto i : vt) {
		i.print();
	}
}

/** output:
explainrvalue(int sizearg, string namestr, const int *arr) : name = lvalue
explainrvalue(int sizearg, string namestr, const int *arr) : name = rvalue overload
(explainrvalue && src) : name = rvalue overload
(const explainrvalue & src) : name = lvalue
(const explainrvalue & src) : name = rvalue overload
(const explainrvalue & src) : name = rvalue overload
this->size : 5
this->_marray :
	1 2 3 4 5
	this->name : rvalue overload
	(const explainrvalue & src) : name = lvalue
	this->size : 2
	this->_marray :
	1 2
	this->name : lvalue
	press any key to continue . . .**/