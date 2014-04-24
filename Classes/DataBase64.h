#ifndef DATABASE64_H_
#define DATABASE64_H_

#include <string>

std::string SaveData(unsigned char const* , unsigned int len);
std::string ParseData(std::string const& s);

#endif /* DATABASE64_H_ */