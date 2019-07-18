#pragma once
#include "TServerStd.h"
#include "PProtocol.h"
#include <string>
#include <vector>



class PUser
{
private:
	SOCKET user_socket_;
	HANDLE user_event_;
	bool connected_;
	std::string name_;
	std::string unique_id_;
	SOCKADDR_IN client_addr_;
public:
	PUser();
	~PUser();
	
	//setter

	void set_connected(bool connect);
	void set_name(std::string name);
	void set_event(HANDLE event);
	void set_socket(SOCKET socket);
	
	//getter

	bool get_connected();
	std::string& get_name();
	HANDLE& get_event();
	SOCKET& get_socket();
	SOCKADDR_IN& get_client_addr();
};


class PUserManager : public PSingleton<PUserManager>
{
private:
	friend class PSingleton<PUserManager>;
private:
	PUserManager();
public:
	std::vector<PUser*> user_list_;
	std::mutex mutex_;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();


	void AddUser(PUser* user);


public:
	~PUserManager();
};

