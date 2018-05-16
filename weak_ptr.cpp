#include<iostream>
#include<memory>
#include<string>
using namespace std;
class PlayWithSharedCircularRef {
private:
	string me = "default";
	shared_ptr<PlayWithSharedCircularRef> sp_friend;
public:
	PlayWithSharedCircularRef(string str) { 
		cout << "PlayWithSharedCircularRef created: " << str << endl; 
		this->me = str;
	};

	void makeFriend(shared_ptr<PlayWithSharedCircularRef> myFriend) {
		cout << "PlayWithSharedCircularRef makeFriend for:" << me << endl;
		this->sp_friend =  myFriend;
	}
	~PlayWithSharedCircularRef() {
		cout << "PlayWithSharedCircularRef destroyed: " << this->me << endl;
	}
};
class PlayWithSharedCircularRefFix {
private:
	string me = "default";
	weak_ptr<PlayWithSharedCircularRefFix> sp_friend; //lighter as unique pointer but with more safety of lock and expired
public:
	PlayWithSharedCircularRefFix(string str) {
		cout << "PlayWithSharedCircularRefFix created: " << str << endl;
		this->me = str;
	};

	void makeFriend(shared_ptr<PlayWithSharedCircularRefFix> myFriend) {
		cout << "PlayWithSharedCircularRefFix makeFriend for:" << me << endl;
		this->sp_friend = myFriend;
	}

	void printMe() const {
		cout << "PlayWithSharedCircularRefFix print:" << this->me << endl;
	}

	void printFriend() {
		if (!this->sp_friend.expired()) {
			cout << "PlayWithSharedCircularRefFix friend is owned by: "<< this->sp_friend.lock().use_count() << endl;
			this->sp_friend.lock()->printMe();
		}
	}

	~PlayWithSharedCircularRefFix() {
		cout << "PlayWithSharedCircularRefFix destroyed: " << this->me << endl;
	}
};
int main() {
	shared_ptr<PlayWithSharedCircularRef> sp1 = make_shared<PlayWithSharedCircularRef>("f1");
	shared_ptr<PlayWithSharedCircularRef> sp2 = make_shared<PlayWithSharedCircularRef>("f2");
	sp1->makeFriend(sp2); // will not destroy
	sp2->makeFriend(sp1); // will not destroy
	shared_ptr<PlayWithSharedCircularRefFix> sp3 = make_shared<PlayWithSharedCircularRefFix>("f3");
	shared_ptr<PlayWithSharedCircularRefFix> sp4 = make_shared<PlayWithSharedCircularRefFix>("f4");
	sp4->makeFriend(sp3);
	sp3->makeFriend(sp4);
	sp3->printFriend();
	sp4->printFriend();
}


/** output:
PlayWithSharedCircularRef created: f1
PlayWithSharedCircularRef created: f2
PlayWithSharedCircularRef makeFriend for:f1
PlayWithSharedCircularRef makeFriend for:f2
PlayWithSharedCircularRefFix created: f3
PlayWithSharedCircularRefFix created: f4
PlayWithSharedCircularRefFix makeFriend for:f4
PlayWithSharedCircularRefFix makeFriend for:f3
PlayWithSharedCircularRefFix friend is owned by: 2
PlayWithSharedCircularRefFix print:f4
PlayWithSharedCircularRefFix friend is owned by: 2
PlayWithSharedCircularRefFix print:f3
PlayWithSharedCircularRefFix destroyed: f4
PlayWithSharedCircularRefFix destroyed: f3
Press any key to continue . . .
**/
