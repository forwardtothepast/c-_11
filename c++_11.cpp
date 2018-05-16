#include<iostream>
#include<vector>
#include<ostream>
#include<string>
using namespace std;

// uniform initialization 1. initializer list, 2. Regular constructor, 3. Aggregated initialization
// initializer list and regular initialization
class InitializerListClass {
private:
	std::vector<int> _m_vector;
public:
	InitializerListClass(const std::initializer_list<int> inputInitializerList) {
		std::cout << "InitializerListClass: parameter constructor for initializer list" << endl;
		for (auto itr : inputInitializerList) {
			this->_m_vector.push_back(itr);
		}
	}

	InitializerListClass(const std::vector<int> inputVector) {
		std::cout << "InitializerListClass: parameter constructor for vector" << endl;
		for (auto itr : inputVector) {
			this->_m_vector.push_back(itr);
		}
	}


	void print() {
		std::cout << "InitializerListClass: printing vector" << endl;
		for (auto itr : this->_m_vector) {
			std::cout << itr << " ";
		}
		std::cout << endl;
	}
	~InitializerListClass() {
		std::cout << "InitializerListClass: destructor" << endl;
	}
};

// aggregated initialization
class AggregatedIntialization {
public:
	int _m_member1;
	string _m_member2;
	void print() {
		cout << "AggregatedIntialization: _m_member1: " << this->_m_member1 << "	_m_member2: " << this->_m_member2 << endl;
	}
};

// nullptr usage
void functionOverLoad(int i) {
	cout << "functionOverLoad: intiger function" << endl;
}
void functionOverLoad(char * charPtr) {
	cout << "functionOverLoad: char* function" << endl;
}

// enum class usage
enum class employee { employeeName, employeeNumber };
enum class employer { employerName, employerNumber };

bool testEnumClass() {
	employee employeeObj = employee::employeeName;
	employer employerObj = employer::employerNumber;
	// return (employeeObj == employerObj), compile time error, in c++03 this would have not given any error
	return true;
}

// constexpr function and member
class constantExpressionClass {
public:
	constexpr static int constexprMember = 5;
	constexpr int constantExpression() {
		return 3 * constexprMember;
	}
};

////static assert
//template <typename func>
//void staticAssert(func lambdaFunction) {
//	std::cout << "staticAssert: called returns static_assert(4 == lambdaFunction" << endl;
//	static_assert(4 == lambdaFunction);
//}

// delegation constructor
class DelegatingConstructorBase {
	string _m_stringMember;
	int _m_intigerMember = 2;
public:
	DelegatingConstructorBase() {
		this->_m_stringMember = "default value";
		std::cout << "DelegatingConstructorBase: default constructor" << endl;
	}

	DelegatingConstructorBase(int arg) : DelegatingConstructorBase() {
		std::cout << "DelegatingConstructorBase: parameter constructor" << endl;
		this->_m_intigerMember = arg;
	}

	void print() {
		std::cout << "DelegatingConstructorBase: parameter constructor" << endl;
		std::cout << "DelegatingConstructorBase: value from parameter constructor: " << this->_m_intigerMember << endl;
		std::cout << "DelegatingConstructorBase: value from delegated constructor: " << this->_m_stringMember << endl;
	}

	~DelegatingConstructorBase() {
		std::cout << "DelegatingConstructorBase: destructor" << endl;
	}
};

//default and delete a constructor or function
class DefaultOrDeleteClassMember {
	string _m_stringMember = "default";
	int _m_intigerMember = 0;
public:
	DefaultOrDeleteClassMember() = default;

	DefaultOrDeleteClassMember(int arg) {
		std::cout << "DefaultOrDeleteClassMember: parameter constructor" << endl;
		this->_m_intigerMember = arg;
	}

	DefaultOrDeleteClassMember(const DefaultOrDeleteClassMember & copyObjectSource) = delete;

	void print() {
		std::cout << "DefaultOrDeleteClassMember: _m_intigerMember: " << this->_m_intigerMember << endl;
		std::cout << "DefaultOrDeleteClassMember: _m_stringMember: " << this->_m_stringMember << endl;
	}

	~DefaultOrDeleteClassMember() {
		std::cout << "DefaultOrDeleteClassMember: destructor" << endl;
	}
};


// final and override
class FinalAndOverrideBase {
public:
	virtual void overridenFunction(int arg) {
		cout << "FinalAndOverrideBase: overridenFunction";
	}
};
class FinalAndOverrideDerived : public FinalAndOverrideBase {
public:
	void overridenFunction(int arg) override final {
		cout << "FinalAndOverrideDerived: overridenFunction";
	}
};
class FinalAndOverrideSecondDerivation final : public FinalAndOverrideDerived {
public:
	// void overridenFunction(int arg) override {}, compilation error
};
// class FinalAndOverrideFinalDerivation : public FinalAndOverrideSecondDerivation{};, compilation error

// lambda function
void lambda1() {
	vector <int> vt = {1,2,3,4};
	int sum = 0;
	[&] (){
		for (auto i : vt) {
			sum += i;
		}
	}();
	cout << "sum calculated with lambda: " << sum << endl;
}

int main() {
	std::vector<int> lvalueVector = { 10, 12, 13, 14 }; //inbuild initializer list with collection in STL
	InitializerListClass objInitializedFromVector = { 1,2,3,4,5,6,7 }; // initializer list initialization
	InitializerListClass objInitializedFromLvalueVector = { lvalueVector }; // regular constructor initialization
	AggregatedIntialization objAggregatedIntialization = { 1, "test-AggregatedIntialization" }; // Aggregated initialization
	objInitializedFromVector.print();
	objInitializedFromLvalueVector.print();
	objAggregatedIntialization.print();
	functionOverLoad(NULL);
	functionOverLoad(nullptr);
	constantExpressionClass constantexprObj;
	cout<<"constant expr output"<<constantexprObj.constantExpression()<<endl;
	DelegatingConstructorBase delegatingConstructorBaseObj = { 4 };
	DefaultOrDeleteClassMember defaultOrDeleteClassMemberObj1 = { 5 };
	DefaultOrDeleteClassMember defaultOrDeleteClassMemberObj2;
	defaultOrDeleteClassMemberObj1.print();
	defaultOrDeleteClassMemberObj2.print();
	lambda1();

}