#include "tstring.h"
#include <bits/ostream_insert.h>

namespace tld
{
	string::string() : text{}, size(0)
	{}
	
	string::string(const string& that) : text{}, size(that.size)
	{
		for (size_t i = 0; i < max_strlen; i++)
			this->text[i] = that.text[i];
	}
	
	string& string::operator =(const string& that)
	{
		if (this != &that)
		{
			for (size_t i = 0; i < max_strlen; i++)
				this->text[i] = that.text[i];
			
			this->size = that.size;
		}
		
		return *this;
	}
	
	string operator +(const string& lht, const string& rht)
	{
		string tmp(lht);
		
		tmp.size += rht.size;
		
		size_t j = 0;
		for (size_t i = lht.size; i < tmp.size; i++)
		{
			tmp.text[i] = rht.text[j];
			j++;
		}
		
		return tmp;
	}
	
	bool operator ==(const string& lht, const string& rht)
	{
		if (lht.size != rht.size)
			return false;
		
		for (size_t i = 0; i < lht.size; i++)
			if (lht.text[i] != rht.text[i])
				return false;
		
		return true;
	}
	
	bool operator >(const string& lht, const string& rht)
	{
		if (lht.size < rht.size)
		{
			for (size_t i = 0; i < lht.size; i++)
				if (lht.text[i] > rht.text[i])
					return true;
			
			return false;
		} else
		{
			for (size_t i = 0; i < rht.size; i++)
				if (lht.text[i] < rht.text[i])
					return false;
			
			return true;
		}
	}
	
	bool operator <(const string& lht, const string& rht)
	{
		if (lht.size < rht.size)
		{
			for (size_t i = 0; i < lht.size; i++)
				if (lht.text[i] > rht.text[i])
					return false;
			
			return true;
		} else
		{
			for (size_t i = 0; i < rht.size; i++)
				if (lht.text[i] < rht.text[i])
					return true;
			
			return false;
		}
	}
	
	bool operator !=(const string& lht, const string& rht)
	{
		return !(lht == rht);
	}
	
	bool operator >=(const string& lht, const string& rht)
	{
		return !(lht < rht);
	}
	
	bool operator <=(const string& lht, const string& rht)
	{
		return !(lht > rht);
	}
	
	string& operator +=(string& lht, const string& rht)
	{
		size_t j = 0;
		
		while ((rht.text[j] != '\0') && (lht.size < max_strlen))
		{
			lht.text[lht.size] = rht.text[j];
			lht.size++;
			j++;
		}
		
		lht.text[lht.size++] = '\0';
		
		return lht;
	}
	
	std::ostream& operator <<(std::ostream& os, const string& str)
	{
		return __ostream_insert(os, str.text, str.size);
	}
	
	string::string(const char* str) : text{0}, size(0)
	{
		while ((str[size] != '\0') && (size < max_strlen))
		{
			text[size] = str[size];
			size++;
		}
	}
	
	string& string::operator =(const char* str)
	{
		this->size = 0;
		
		while ((str[size] != '\0') && (size < max_strlen))
		{
			text[size] = str[size];
			size++;
		}
		
		text[size] = '\0';
		
		return *this;
	}
	
	string& operator +=(string& lht, const char* str)
	{
		
		size_t j = 0;
		
		while ((str[j] != '\0') && (lht.size < max_strlen))
		{
			lht.text[lht.size] = str[j];
			lht.size++;
			j++;
		}
		
		lht.text[lht.size++] = '\0';
		
		return lht;
	}
	
	string& operator +=(string& lht, const char rht)
	{
		if (lht.size < max_strlen)
		{
			lht.text[lht.size++] = rht;
			lht.text[lht.size] = '\0';
		}
		
		return lht;
	}
	
	
	string::~string() = default;
	
} //namespace tld