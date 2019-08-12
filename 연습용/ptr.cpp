#include <memory>
#include <utility>
#include <string>
#include <iostream>

#define TEST
#ifdef TEST

std::unique_ptr<int> func()
{
	std::unique_ptr<int> pstr = std::make_unique<int>();
	return pstr;

}


int main()
{
	//std::unique_ptr<std::string> pstr = std::make_unique<std::string>(1,'c');

	//std::string* a = pstr.get();
	//std::string* b = pstr.get();
	//std::string* c = pstr.get();
	//std::string* d = pstr.get();

	//std::unique_ptr<std::string> pstr2 = std::move(pstr);
	//std::unique_ptr<std::string> pstr3 = std::move(pstr);
	//std::cout << *a << *b << *c << *d << std::endl;
	//std::cout << *pstr << *pstr2 << *pstr3 << std::endl;
	void getridof();
	


	int len = 4;
	
	int* aa = new int;
	*aa = 4;
	std::unique_ptr<int> uptr{ aa };
	std::unique_ptr<int> uptr2 = std::move(uptr);
	
	
	std::shared_ptr<int> pdata{aa};
	std::shared_ptr<int> pdata2{ pdata };
	//uptr.reset();
	//std::shared_ptr<double> pdata{ new double(999.0) };

	std::cout << *uptr << std::endl;
	system("pause");
}

#endif