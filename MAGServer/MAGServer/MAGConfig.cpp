#include "stdafx.h"
#include "MAGConfig.h"


MAGConfig::MAGConfig(void)
{

}


MAGConfig::~MAGConfig(void)
{

}

unsigned int MAGConfig::get_ConnectionCount()
{
	return mConnectionCount;
}
std::string MAGConfig::get_LoginID(int index)
{
	return mLoginID[index];
}