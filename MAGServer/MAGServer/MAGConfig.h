#pragma once

#include <string>

class MAGConfig
{
public:
	MAGConfig(void);
	virtual ~MAGConfig(void);

	unsigned int get_ConnectionCount();
	std::string	 get_LoginID(int index);

private:
	unsigned int mConnectionCount;
	std::string	 mLoginID[10];
};

