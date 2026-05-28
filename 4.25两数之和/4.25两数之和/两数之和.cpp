#include <iostream>
#include <vector>
#include<string>
#include <utility>
using namespace std;

int main()
{
	/*pair<int, string> p;
	p.first = 1;
	p.second = "Tom";
	string a = "Happy ";
	string b = "Newyear";
	cout << a.length()<< "\n";
	cout << b.length() << "\n";
	cout << a.size() << "\n";
	cout << b.size() << "\n";
	cout << a[0] << "\n";
	cout << b[0] << "\n";
	if (b.find("year") != string::npos)
	{
		cout << "find year:" << b.find("year") << "\n";
	}
	else
	{
		cout<<"not find" << "\n";
	}
	string ab = a + b;
	cout << ab << "\n";

	ab.replace(6, 3, "aaa");
	cout << ab << "\n";

	cout << ab.substr(6, 7) << "\n";

	ab.insert(5, " China!");
	cout << ab << "\n";

	ab.erase(5, 2);
	cout << ab << "\n";*/

	vector<pair<int, string>>l;
	l.resize(3);
	l[0] = { 1,"Fang" };
	l[1] = { 2,"Zai" };
	l[2] = { 3,"Qiang" };
	for (auto x : l)
	{
		cout << x.first << " " << x.second<<endl;
	}
	return 0;
}


