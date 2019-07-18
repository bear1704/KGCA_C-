#include "PUserManager.h"

PUserManager::PUserManager()
{
}

bool PUserManager::Init()
{
	return false;
}

bool PUserManager::Frame()
{
	return false;
}

bool PUserManager::Render()
{
	return false;
}

bool PUserManager::Release()
{
	return false;
}

void PUserManager::AddUser(PUser* user)
{
	std::lock_guard<std::mutex> lock(mutex_);

	std::random_device r;
	std::mt19937 engine(r());
	std::uniform_int_distribution<int> distribution(-100000, 100000);
	auto generator = std::bind(distribution, engine); //데미지 난수화 
	int random = generator();


	user->set_connected(true);
	user->set_event(WSACreateEvent());
	user->set_id(random);
	//user->set_name필요 
	
	user_list_.push_back(user);



	

	printf("\n접속 [%s][%d] , -%d-",
		inet_ntoa(user->get_client_addr().sin_addr),
		ntohs(user->get_client_addr().sin_port),
		user_list_.size());

}

void PUserManager::DeleteUser(PUser* user)
{
	std::vector<PUser*>::iterator iter;
	iter = find(user_list_.begin(), user_list_.end(), user);
	closesocket(user->get_socket());
	user->set_connected(false);
	printf("\n접속 종료됨 [%s][%d] , -%d-",
		inet_ntoa(user->get_client_addr().sin_addr),
		ntohs(user->get_client_addr().sin_port),
		user_list_.size());

	delete* iter;
	user_list_.erase(iter);


}

PUserManager::~PUserManager()
{
}

PUser::PUser()
{
}

PUser::~PUser()
{
}

void PUser::set_connected(bool connect)
{
	connected_ = connect;
}

void PUser::set_name(std::string name)
{
	name_ = name;
}

void PUser::set_event(HANDLE event)
{
	user_event_ = event;
}

void PUser::set_socket(SOCKET socket)
{
	user_socket_ = socket;
}

void PUser::set_id(int id)
{
	unique_id_ = id;
}

bool PUser::get_connected()
{
	return connected_;
}

std::string& PUser::get_name()
{
	return name_;
}

HANDLE& PUser::get_event()
{
	return user_event_;
}

SOCKET& PUser::get_socket()
{
	return user_socket_;
}

SOCKADDR_IN& PUser::get_client_addr()
{
	return client_addr_;
}

int PUser::get_id()
{
	return unique_id_;
}
