#include <vector>
#include <iostream>
#include <numeric>
#include <iterator>


#ifdef MYSTRING
class MyString
{
private:
	char* string_content_;
	int string_length_;
	int memory_capacity_;

public:
	MyString();
	//문자열로부터 생성하는 생성자
	~MyString();
	MyString(const char* str);
	//복사 생성자
	MyString(const MyString& str);
	MyString(MyString&& str) noexcept;

	void reserve(int size);
	MyString operator+(const MyString& s);

	int length() const;

	void print();
	void println();

};

MyString::MyString()
{
	std::cout << "생성자 호출! \n" << std::endl;
	string_length_ = 0;
	memory_capacity_ = 0;
	string_content_ = nullptr;
}

MyString::MyString(const char* str)
{
	std::cout << "문자열을 인수로 한 생성자 호출! \n" << std::endl;
	string_length_ = strlen(str);
	memory_capacity_ = string_length_ + 1;
	string_content_ = new char[memory_capacity_];

	for (int i = 0; i < strlen(str); i++)
		string_content_[i] = str[i];

	string_content_[strlen(str)] = '\0';
}

MyString::MyString(const MyString& str)
{
	std::cout << "복사 생성자 호출! \n" << std::endl;
	string_length_ = str.string_length_;
	string_content_ = new char[string_length_ + 1];

	for (int i = 0;  i < string_length_; i++)  string_content_[i] = str.string_content_[i];
	string_content_[string_length_] = '\0';
}

MyString::MyString(MyString&& str) noexcept
{
	std::cout << "이동 생성자 호출!\n" << std::endl;
	string_length_ = str.string_length_;
	string_content_ = str.string_content_;
	memory_capacity_ = str.memory_capacity_;

	str.string_content_ = nullptr;
}
MyString::~MyString() { delete[] string_content_; std::cout << "소멸자 호출!" << std::endl; }


void MyString::reserve(int size)
{
	if (size > memory_capacity_)
	{
		char* prev_string_content = string_content_;
		
		string_content_ = new char[size];
		memory_capacity_ = size;

		for (int i = 0; i < string_length_; i++)
			string_content_[i] = prev_string_content[i];
		
		if (prev_string_content != nullptr) delete[] prev_string_content;

	}
}

MyString MyString::operator+(const MyString &s)
{
	MyString str;
	str.reserve(string_length_ + s.string_length_ + 1);

	for (int i = 0; i < string_length_; i++)
		str.string_content_[i] = string_content_[i];
	for (int i = 0; i < s.string_length_; i++)
		str.string_content_[string_length_ + i] = s.string_content_[i];

	str.string_length_ = string_length_ + s.string_length_;

	str.string_content_[str.string_length_] = '\0';

	return str;
}

int MyString::length() const { return string_length_; }
void MyString::print()
{
	for (int i = 0; i < string_length_; i++) std::cout << string_content_[i];
}
void MyString::println ()
{ 
	for (int i = 0; i < string_length_; i++) std::cout << string_content_[i];
	
	std::cout << std::endl;
}





int main()
{
	MyString str1("abc");
	MyString str2("def");
	std::cout << "------------" << std::endl;
	//MyString str3 = str1 + str2;
	MyString&& str3 = str1 + str2;
	//str3.println();
	
	//std::vector<MyString> vec;
	//std::cout << "1st" << std::endl;
	//vec.push_back(str3);
	//std::cout << "2nd" << std::endl;
	//vec.push_back(str3);
	//std::cout << "3rd" << std::endl;
	//vec.push_back(str3);


	system("pause");

}
#endif
#ifdef MOVECONSTRUCTOR
class A
{
private:

	int data_;

public:
	A(int data) : data_(data) { std::cout << "일반 생성자 호출! " << std::endl; }

	A(const A& a) : data_(a.data_)
	{
		//data_ = a.data_;
		std::cout << "복사 생성자 호출" << std::endl;
	}

};

int main()
{
	A a(1);
	A b(a);

	A c(A(2));
	system("pause");

}

#endif
