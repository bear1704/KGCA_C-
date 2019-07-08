#include "PNormalSelect.h"
#include "PNetwork.h"


bool PNormalSelect::Init()
{
	return true;
}

bool PNormalSelect::Frame()
{
	FD_ZERO(&read_set_);
	FD_ZERO(&write_set_);
	FD_SET(socket_, &read_set_);
	FD_SET(socket_, &write_set_);

	timeval time;
	time.tv_sec = 10;
	time.tv_usec = 0;

	int ret = select(0, &read_set_, &write_set_, NULL, &time);

	if (ret == SOCKET_ERROR)
		return false;
	if (ret == 0)
		return true; //timeout

	if (FD_ISSET(socket_, &read_set_))
	{
		if (RecvPacket() == false)
		{
			PNetwork::set_connect(false);
		}
	}
	if (FD_ISSET(socket_, &write_set_))
	{
		//
	}


	return true;
}

PNormalSelect::PNormalSelect(SOCKET sock) : PSelectModel(sock)
{
	socket_ = sock;
}

PNormalSelect::~PNormalSelect()
{
}
