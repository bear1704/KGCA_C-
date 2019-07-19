#pragma once
#include "TServerStd.h"
#include "PProtocol.h"
#include <string>
#include <vector>
#include <random>
#include <functional>

class PPacketManager;


class PUser
{
private:
	SOCKET user_socket_;
	HANDLE user_event_;
	bool connected_;
	std::string name_;
	WORD unique_id_;
	SOCKADDR_IN client_addr_;
public:
	PUser();
	~PUser();
	
	//setter

	void set_connected(bool connect);
	void set_name(std::string name);
	void set_event(HANDLE event);
	void set_socket(SOCKET socket);
	void set_id(int id);
	
	//getter

	bool get_connected();
	std::string get_name();
	HANDLE get_event();
	SOCKET get_socket();
	HANDLE* get_event_by_ptr();
	SOCKADDR_IN* get_client_addr_by_ptr();
	SOCKET* get_socket_by_ptr();
	SOCKADDR_IN get_client_addr();
	int get_id();
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
	void DeleteUser(PUser* user);
	PUser* FindUserById(WORD id);


public:
	~PUserManager();
};

