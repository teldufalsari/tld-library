#ifndef TLD_TSTRING_H
#define TLD_TSTRING_H

/*This string class may seem week now. But only now.
 * This is going to be a project showing development in progress.
 * This class shall grow and and gain its might to replace std::string one day.
 */

#include <iostream>


namespace tld
{

	const size_t max_strlen = 1023;
	
	class string
	
	{
	
	private:
		char text[max_strlen + 1];
		size_t size;
	
	private:
	
	public:
		string();
		
		string(const string& that);
		
		~string();
		
		string(const char* str);
		
		string& operator =(const string& that);
		
		string& operator =(const char* str);
		
		friend string operator +(const string& lht, const string& rht);
		
		friend string& operator +=(string& lht, const string& rht);
		
		friend inline bool operator ==(const string& lht, const string& rht);
		
		friend inline bool operator >(const string& lht, const string& rht);
		
		friend inline bool operator <(const string& lht, const string& rht);
		
		friend inline bool operator !=(const string& lht, const string& rht);
		
		friend inline bool operator >=(const string& lht, const string& rht);
		
		friend inline bool operator <=(const string& lht, const string& rht);
		
		friend std::ostream& operator <<(std::ostream& os, const string& str);
		
		friend string& operator +=(string& lht, const char* rht);
		
		friend string& operator +=(string& lht, char rht);
		
	};


} //namespace tld
#endif //TLD_TSTRING_H
