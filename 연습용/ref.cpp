#include <iostream>
#include <vector>
#include <string>

#ifdef TEST

using namespace std;

template<typename T>
class o
{
public:

	o(std::string name, T value)
	{
		name = nameValue;
		value = objectValue;
		std::cout << "�Ϲ� ������ ȣ��" << std::endl;
	}

	/*o(const o& ref)
	{
		nameValue = ref.nameValue;
		objectValue = ref.objectValue;
		std::cout << "��������� ȣ��" << std::endl;
	}
*/
	o& operator=(const o& oooos)
	{
		nameValue = oooos.nameValue;
		objectValue = oooos.objectValue;
		std::cout << "���Կ����� ȣ��" << std::endl;
		return *this;
	}
	/*o(const o&& mov)
	{
		nameValue = mov.nameValue;
		objectValue = mov.objectValue;
		std::cout << "�̵������� ȣ��" << std::endl;
	}*/

	o operator+(const o& ooos)
	{
		o os("ccc", 4);
		os.nameValue = ooos.nameValue + nameValue;
		os.objectValue = ooos.objectValue + objectValue;

		return os;
	}
	private:
		std::string nameValue;
		T objectValue;

};


int main()
{
	std::string  a("pers");
	std::string b("sat");
	o<int> p(a, 4);
	o<int> s(b, 6);
	
	p = s;
	
	o<int> g = s;
	o<int>f(s);
	p = s + g;
	

	system("pause");
}

#endif