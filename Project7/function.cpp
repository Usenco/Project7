#include "function.h"

std::string m_sha256(std::string text)
{
	for (std::string::iterator i = text.begin(); i < text.end(); i++)
	{
		(*i)+=3;
	}
	return text;
}
