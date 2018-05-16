#include<iostream>
#include<memory>
#include<string>
using namespace std;
class PlayWithUnique {
	string name = "default";
public:
	PlayWithUnique() { cout << "PlayWithUnique created with default:" << this->name << endl; };
	PlayWithUnique(string str) {
		cout << "PlayWithUnique created with parameter:" << str << endl;
		this->name = str;
	}
	~PlayWithUnique() {
		cout << "PlayWithUnique destroyed: " << this->name << endl;
	}
};
int main() {
	unique_ptr<PlayWithUnique> up1(new PlayWithUnique("created_with_new_1"));
	unique_ptr<PlayWithUnique> up2(new PlayWithUnique("created_with_new_2"));
	unique_ptr<PlayWithUnique> up3(new PlayWithUnique("created_with_new_3"));
	// unique_ptr<PlayWithUnique> up3(up1); not possible function deleted
	PlayWithUnique * up4 = up1.get();
	if (!up1) {
		cout << "up1 deleted" << endl;
	}
	PlayWithUnique * up5 = up2.release();
	if (!up2) {
		cout << "up2 deleted" << endl;
	}
	up3.reset();
	if (!up3) {
		cout << "up3 deleted" << endl;
	}

	// no custome deleter
	unique_ptr<PlayWithUnique[]> up6(new PlayWithUnique[2]);
}
/** Output:
 PlayWithUnique created with parameter:created_with_new_1
PlayWithUnique created with parameter:created_with_new_2
PlayWithUnique created with parameter:created_with_new_3
up2 deleted
PlayWithUnique destroyed: created_with_new_3
up3 deleted
PlayWithUnique created with default:default
PlayWithUnique created with default:default
PlayWithUnique destroyed: default
PlayWithUnique destroyed: default
PlayWithUnique destroyed: created_with_new_1
Press any key to continue . . .
**/
