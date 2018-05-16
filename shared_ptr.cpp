#include<iostream>
#include<memory>
#include<string>
using namespace std;
class PlayWithShared {
	string name = "default";
public:
	PlayWithShared() { cout << "PlayWithShared created with default:" << this->name << endl; };
	PlayWithShared(string str) {
		cout << "PlayWithShared created with parameter:" << str << endl;
		this->name = str;
	}
	~PlayWithShared() {
		cout<< "PlayWithShared destroyed: " << this->name << endl;
	}
};
int main() {
	shared_ptr<PlayWithShared> sp1 = make_shared<PlayWithShared>("created_with_make_shared");
	shared_ptr<PlayWithShared> sp2(new PlayWithShared("created_with_new")); // not good, if exception is thrown after new the assignment to sp2 will not happen and memory will be leaked
	shared_ptr<PlayWithShared> sp3 = sp1;
	shared_ptr<PlayWithShared> sp4(sp1);
	cout << "sp1.use_count() : " << sp1.use_count() << endl;
	cout << "sp1.unique() : " << sp1.unique() << endl;
	PlayWithShared* raw = sp1.get(); //never do this, one smart pointer is created avoid using raw pointer
	sp1.reset(); // will release sp1
	if (sp1) {
		cout << "sp1.use_count() : " << sp1.use_count() << endl;
	}
	// invoke with new if you need a custom deleter
	shared_ptr<PlayWithShared> sp5(new PlayWithShared[2], [](PlayWithShared *p) {delete[] p; });
}
/**output:
 * PlayWithShared created with parameter:created_with_make_shared
PlayWithShared created with parameter:created_with_new
sp1.use_count() : 3
sp1.unique() : 0
PlayWithShared created with default:default
PlayWithShared created with default:default
PlayWithShared destroyed: default
PlayWithShared destroyed: default
PlayWithShared destroyed: created_with_make_shared
PlayWithShared destroyed: created_with_new
Press any key to continue .
 **/
