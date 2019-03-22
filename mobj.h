#ifndef MOBJ_H
#define MOBJ_H
#include <string>
#include <fstream>
#include <utility>
#include <memory>
#include <initializer_list>
#include <vector>
#include <map>

class Mobj;

typedef std::map<std::string, Mobj> jmap;

class Mobj // mutable object
{
public:
	Mobj ();
	Mobj (const int& i);
	Mobj (const float& f);
	Mobj (const char& ch);
	Mobj (const std::string& s);
	Mobj (const char* s);
	Mobj (const std::initializer_list<std::pair<std::string, Mobj> >& pr); // map
	Mobj (const short& _, const std::initializer_list<Mobj>& o); // array
	Mobj (const Mobj& o); // конструктор с копированием [1]
	Mobj (Mobj&& other) noexcept; // с перемещением [2]

	Mobj& operator=(const Mobj& o); // присвоение с копированием [3]
	Mobj& operator=(Mobj&& other) noexcept;// с перемещением [4]
	Mobj& operator=(const int& i);
	Mobj& operator=(const float& f);
	Mobj& operator=(const char& c);
	Mobj& operator=(const std::string& s);
	Mobj& operator=(const char* s);
	Mobj& operator=(const jmap& m);
	Mobj& operator=(const std::initializer_list<Mobj>& a);

	~Mobj (); // деструктор [5]

	Mobj& operator[](const char* s) const;
	Mobj& operator[](const std::string& s) const;
	Mobj& operator[](const long long& idx) const;

	int geti () const;
	float getf () const;
	char getc () const;
	jmap& getm () const;
	const std::string& gets () const;

	void seti (int i);
	void setf (float f);
	void setc (char c);
	void setm (const std::initializer_list<std::pair<std::string, Mobj> >& pr);
	void setm (const std::map<std::string, Mobj>& pr);
	void seta (const std::initializer_list<Mobj>& pr);
	void seta (const std::vector<Mobj>& pr);
	void seta (unsigned long long size);

	unsigned long long size () const;
	char type () const;
	void readFromFile (const char path[]);
	void readFromStrData (std::string&& data);

private:
	void* p = nullptr;
	char myType = '_';
	unsigned long long sz = 0;
	void deleteIt ();
};






std::ostream& operator<< (std::ostream& os, const Mobj& o);
std::istream& operator>> (std::istream& is, Mobj& o);





#endif // MOBJ_H
