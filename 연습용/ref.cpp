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
		std::cout << "일반 연산자 호출" << std::endl;
	}

	/*o(const o& ref)
	{
		nameValue = ref.nameValue;
		objectValue = ref.objectValue;
		std::cout << "복사생성자 호출" << std::endl;
	}
*/
	o& operator=(const o& oooos)
	{
		nameValue = oooos.nameValue;
		objectValue = oooos.objectValue;
		std::cout << "대입연산자 호출" << std::endl;
		return *this;
	}
	/*o(const o&& mov)
	{
		nameValue = mov.nameValue;
		objectValue = mov.objectValue;
		std::cout << "이동생성자 호출" << std::endl;
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