#include "mobj.h"




void Mobj::deleteIt ()
{
	if (myType == 's') delete reinterpret_cast<std::string*> (p);
	else if (myType == 'm') delete reinterpret_cast<jmap*> (p);
	else if (myType == 'a') delete[] reinterpret_cast<Mobj*> (p);
	else if (myType != '_') free (p);
}

Mobj::Mobj () {}

Mobj::Mobj (const int& i) : p(malloc(sizeof(int)))
{
	*reinterpret_cast<int*> (p) = i;
	myType = 'i';
}
// float
Mobj::Mobj (const float& f) : p(malloc(sizeof(float)))
{
	*reinterpret_cast<float*> (p) = f;
	myType = 'f';
}
// char
Mobj::Mobj (const char& ch) : p(malloc(sizeof(char)))
{
	*reinterpret_cast<char*> (p) = ch;
	myType = 'c';
}
// string
Mobj::Mobj (const std::string& s) : p(new std::string)
{
	*reinterpret_cast<std::string*> (p) = s;
	myType = 's';
}
Mobj::Mobj (const char* s) : p(new std::string)
{
	*reinterpret_cast<std::string*> (p) = s; myType = 's';
}
// map
Mobj::Mobj (const std::initializer_list<std::pair<std::string, Mobj> >& pr)
	: p (new jmap)
{
	for (auto it = pr.begin(); it!= pr.end(); ++it)
		(*reinterpret_cast<jmap*> (p))[it->first] = it->second;

	myType = 'm';
}

Mobj::Mobj (const short& _, const std::initializer_list<Mobj>& o) // array
: p(new Mobj[o.size ()])
{
	for (auto it = o.begin (); sz < o.size(); ++it, ++sz) {
		reinterpret_cast<Mobj*>(p)[sz] = *it;
	}
	sz = o.size ();
	myType = 'a';
}

unsigned long long Mobj::size () const { return sz; }

// конструктор с копированием
Mobj::Mobj (const Mobj& o)
{
	deleteIt ();
	switch (myType = o.type ())
	{
	case '_': p = nullptr; return;
	case 'i': p = malloc (sizeof (int));   *reinterpret_cast<int*>(p) = o.geti ();         return;
	case 'f': p = malloc (sizeof (float)); *reinterpret_cast<float*>(p) = o.getf ();       return;
	case 'c': p = malloc (sizeof (char));  *reinterpret_cast<char*>(p) = o.getc ();        return;
	case 's': p = new std::string;         *reinterpret_cast<std::string*>(p) = o.gets (); return;
	case 'm': p = new jmap;                *reinterpret_cast<jmap*> (p) = o.getm ();       return;
	case 'a':
		sz=o.sz;
		p = new Mobj[sz];
		for (unsigned long long idx = 0; idx<sz;++idx)
			reinterpret_cast<Mobj*>(p)[idx] = reinterpret_cast<Mobj*>(o.p)[idx];
	}
}

// конструктор с перемещением
Mobj::Mobj(Mobj&& other) noexcept
		: p(std::exchange (other.p, nullptr)),
			myType(std::exchange (other.myType, '_')),
			sz(std::exchange (other.sz, 0))
{}

// присвоения
Mobj& Mobj::operator=(const Mobj& o)
{
	if (o.p == p) {return *this;}
	if (myType!='a'|| (myType=='a' && sz!=o.sz)) {deleteIt ();}
	myType = o.type ();

	if (myType=='_')
	{
		p = nullptr;
		return *this;
	}

	if (myType=='i')
	{
		p = malloc(sizeof(int));
		*reinterpret_cast<int*>(p) = o.geti ();
		return *this;
	}

	if (myType=='f')
	{
		p = malloc(sizeof(float));
		*reinterpret_cast<float*>(p) = o.getf ();
		return *this;
	}

	if (myType=='c')
	{
		p = malloc(sizeof(char));
		*reinterpret_cast<char*>(p) = o.getc ();
		return *this;
	}

	if (myType=='s')
	{
		p = new std::string;
		*reinterpret_cast<std::string*>(p) = o.gets ();
		return *this;
	}

	if (myType=='m')
	{
		p = new jmap;
		*reinterpret_cast<jmap*>(p) = o.getm ();
		return *this;
	}

	if (myType=='a')
	{
		if (sz != o.sz)
		{
			p = new Mobj[o.sz];
			sz = o.sz;
		}

		for (unsigned long long idx = 0; idx < sz; ++idx)
		{
			reinterpret_cast<Mobj*>(p)[idx] = reinterpret_cast<Mobj*>(o.p)[idx];
		}
	}

	return *this;
}

// с перемещением
Mobj& Mobj::operator=(Mobj&& other) noexcept
{
	std::swap (p, other.p);
	std::swap (myType, other.myType);
	std::swap (sz, other.sz);
	return *this;
}

Mobj& Mobj::operator=(const int& i)
{
	if (myType != 'i')
	{
		deleteIt ();
		myType = 'i';
		p = malloc(sizeof(int));
	}
	*reinterpret_cast<int*>(p) = i;
	return *this;
}

Mobj& Mobj::operator=(const float& f)
{
	if (myType != 'f')
	{
		deleteIt ();
		myType = 'f';
		p = malloc(sizeof(float));
	}
	*reinterpret_cast<float*>(p) = f;
	return *this;
}

Mobj& Mobj::operator=(const char& c)
{
	if (myType != 'c')
	{
		deleteIt ();
		myType = 'c';
		p = malloc(sizeof(char));
	}
	*reinterpret_cast<char*>(p) = c;
	return *this;
}

Mobj& Mobj::operator=(const std::string& s)
{
	if (myType != 's')
	{
		if (myType == 'm') delete reinterpret_cast<jmap*>(p);
		else if (myType == 'a') delete[] reinterpret_cast<Mobj*>(p);
		else if (myType != '_') free (p);
		myType = 's';
		p = new std::string;
	}
	*reinterpret_cast<std::string*>(p) = s;
	return *this;
}

Mobj& Mobj::operator=(const char* s)
{
	if (myType != 's')
	{
		if (myType == 'm') delete reinterpret_cast<jmap*>(p);
		else if (myType == 'a') delete[] reinterpret_cast<Mobj*>(p);
		else if (myType != '_') free (p);
		myType = 's';
		p = new std::string;
	}
	*reinterpret_cast<std::string*>(p) = s;
	return *this;
}

Mobj& Mobj::operator=(const jmap& m)
{
	if (myType != 'm')
	{
		if (myType == 's') delete reinterpret_cast<std::string*>(p);
		else if (myType == 'a') delete[] reinterpret_cast<Mobj*>(p);
		else if (myType != '_') free (p);
		myType = 'm';
		p = new std::string;
	}
	*reinterpret_cast<jmap*>(p) = m;
	return *this;
}

Mobj& Mobj::operator=(const std::initializer_list<Mobj>& a)
{
	if (myType != 'a')
	{
		if (myType == 's') delete reinterpret_cast<std::string*>(p);
		else if (myType == 'm') delete reinterpret_cast<jmap*>(p);
		else if (myType != '_') free (p);
		sz = a.size ();
		p = new Mobj[sz];
	}
	else if (a.size() != sz)
	{
		delete[] reinterpret_cast<Mobj*>(p);
		sz = a.size ();
		p = new Mobj[sz];
	}
	myType = 'a';
	unsigned long long idx = 0;
	for (auto it = a.begin (); idx < sz; ++idx, ++it) {
		reinterpret_cast<Mobj*>(p)[idx] = *it;
	}
	return *this;
}

Mobj::~Mobj () { deleteIt (); }

Mobj& Mobj::operator[](const char* s) const
{
	if (myType == 'm')
	{
		return (*reinterpret_cast<jmap*>(p))[s];
	}
	throw "Mobj& operator[](const char* s)const is only for maps";
}

Mobj& Mobj::operator[](const std::string& s) const
{
	if (myType == 'm')
	{
		return (*reinterpret_cast<jmap*>(p))[s];
	}
	throw "Mobj& operator[](const std::string& s)const is only for maps";
}

Mobj& Mobj::operator[](const long long& idx) const
{
	if (myType == 'a')
	{
		if (idx>=0)
		{
			return reinterpret_cast<Mobj*>(p)[static_cast<unsigned long long>(idx)%sz];
		}
		// работает для относительно маленьких индексов
		return reinterpret_cast<Mobj*>(p)[(-idx) % static_cast<long long>(sz)];
	}
	throw "Error::Mobj::operator[](const int& idx)const is only for arrays";
}

int Mobj::geti () const
{
	return myType == 'i' ? *reinterpret_cast<int*>(p) : 0;
}

float Mobj::getf () const
{
	return myType == 'f' ? *reinterpret_cast<float*>(p) : 0.f;
}

char Mobj::getc () const
{
	return myType == 'c' ? *reinterpret_cast<char*>(p) : '_';
}

jmap& Mobj::getm () const
{
	if (myType == 'm') return *reinterpret_cast<jmap*>(p);
	throw "jmap& getm()const is only for maps";
}

const std::string& Mobj::gets () const
{
	if (myType == 's') return *reinterpret_cast<std::string*>(p);
	throw "const std::string& gets()const is only for strings";
}

void Mobj::seti (int i)
{
	if (myType!='i') {deleteIt (); p=malloc (sizeof (int)); myType = 'i';}
	*reinterpret_cast<int*>(p) = i;
}

void Mobj::setf (float f)
{
	if (myType!='f') {deleteIt (); p=malloc (sizeof (float)); myType = 'f';}
	*reinterpret_cast<float*>(p) = f;
}

void Mobj::setc (char c)
{
	if (myType!='c') {deleteIt (); p=malloc (sizeof (char)); myType = 'c';}
	*reinterpret_cast<char*>(p) = c;
}

void Mobj::setm (const std::initializer_list<std::pair<std::string, Mobj> >& pr)
{
	if (myType!='m')
	{
		deleteIt ();
		p = new jmap;
		myType = 'm';
	}

	for (auto it = pr.begin(); it!= pr.end(); ++it)
	{
		(*reinterpret_cast<jmap*>(p))[it->first] = it->second;
	}
}

void Mobj::setm (const std::map<std::string, Mobj>& pr)
{
	if (myType!='m')
	{
		deleteIt ();
		p = new jmap;
		myType = 'm';
	}

	for (auto it = pr.begin(); it!= pr.end(); ++it)
	{
		(*reinterpret_cast<jmap*>(p))[it->first] = it->second;
	}
}

void Mobj::seta (const std::initializer_list<Mobj>& pr)
{
	if (myType!='a'||(myType=='a'&&sz!=pr.size ()))
	{
		deleteIt ();
		sz = pr.size ();
		p = new Mobj[sz];
	}
	myType = 'a';
	unsigned long long idx = 0;
	for (auto it = pr.begin(); it!= pr.end(); ++idx, ++it)
	{
		reinterpret_cast<Mobj*>(p)[idx] = *it;
	}
}

void Mobj::seta (const std::vector<Mobj>& pr)
{
	if (myType!='a'||(myType=='a'&&sz!=pr.size ()))
	{
		deleteIt ();
		sz = pr.size ();
		p = new Mobj[sz];
	}
	myType = 'a';
	unsigned long long idx = 0;
	for (auto it = pr.begin(); it!= pr.end(); ++idx, ++it)
	{
		reinterpret_cast<Mobj*>(p)[idx] = *it;
	}
}

void Mobj::seta (unsigned long long size)
{
	if (myType!='a'||(myType=='a' && sz != size ))
	{
		deleteIt ();
		sz = size;
		p = new Mobj[size]();
	}
	myType = 'a';
}

char Mobj::type () const {return myType;}







namespace mobjReadFromFile
{
	enum class tokinType {STRING,FLOAT,INT,OMAP,CMAP,OARR,CARR,COMMA,COLON};
	struct Tokin
	{
		tokinType type;
		unsigned idx, len=1;
		Tokin (tokinType type_, unsigned& idx_) : type(type_),idx(idx_){}
		~Tokin () = default;
	};

	// достаёт токены из строки
	void strToTok (unsigned& idx, std::string& s, std::vector<Tokin>& v)
	{
		bool notstring = true, notnum = true;
		std::string num = "+-0123456789";
		auto prew = v.size ();
		std::vector<bool> isArray;
		std::vector<unsigned long long> posArray;
		for (;idx < s.length();++idx)
		{
			if(notstring)
			{
				if (!notnum && s[idx]=='.') {v.back ().type = tokinType::FLOAT; continue;}
				if (s[idx]=='{') {v.push_back (Tokin(tokinType::OMAP, idx)); isArray.push_back (false); continue;}
				if (s[idx]=='}') {v.push_back (Tokin(tokinType::CMAP, idx)); isArray.pop_back(); continue;}
				if (s[idx]=='[') {v.push_back (Tokin(tokinType::OARR, idx)); isArray.push_back (true); posArray.push_back(v.size () - 1); continue;}
				if (s[idx]==']') {v.push_back (Tokin(tokinType::CARR, idx)); isArray.pop_back(); posArray.pop_back(); continue;}
				if (s[idx]==',') {v.push_back (Tokin(tokinType::COMMA, idx)); if (isArray.back ()) {++(v[posArray.back()].len);} continue;}
				if (s[idx]==':') {v.push_back (Tokin(tokinType::COLON, idx)); continue;}

				if (s[idx]=='"')
				{
					v.push_back (Tokin(tokinType::STRING, ++idx));
					notstring = false;

					continue;
				}

				if (notnum && num.find_last_of(s[idx])!=std::string::npos)
				{
					v.push_back(Tokin(tokinType::INT, idx));
					notnum = false;
					prew = v.size();
					continue;
				}
				if (!notnum && prew != v.size())
				{
					(v.end()-2)->len = idx - (v.end()-2)->idx;
					notnum = true;
				}
			}
			else if (s[idx]=='"')
			{
				v.back ().len = idx - v.back().idx;
				notstring = true;
			}

		}
	}


	namespace tok
	{
		enum class add {NOTHING, VAL, ARRAY}; // работаем ли над json-объектом

		void OMAP (std::vector<Mobj*>& d, std::vector<add>& work)
		{
			d.back ()->setm ({});// пустое множество
			work.push_back (add::NOTHING); // требуем заказать место в множестве
		}

		void CMAP (std::vector<Mobj*>& d, std::vector<add>& work)
		{
			work.pop_back ();
			d.pop_back ();
		}

		void OARR (
			unsigned long long& idx,
			std::vector<Tokin>& v,
			std::vector<Mobj*>& d,
			std::vector<add>& work,
			std::vector<unsigned>& arrayIdx)
		{
			d.back ()->seta (v[idx].len); // добавили массив
			arrayIdx.push_back (0);
			d.push_back (&(  (*(d.back()))[arrayIdx.back ()]  )); // перешли к первому элементу
			work.push_back (add::ARRAY);
		}

		void CARR (std::vector<Mobj*>& d, std::vector<add>& work, std::vector<unsigned>& arrayIdx)
		{
			d.pop_back ();
			work.pop_back ();
			arrayIdx.pop_back ();
		}

		void NUM (
			unsigned long long& idx,
			std::string& str,
			std::vector<Tokin>& v,
			std::vector<Mobj*>& d,
			std::vector<add>& work)
		{
			if (work.back () != add::NOTHING)
			{
				if (v[idx].type==tokinType::INT)
				{
					(*(d.back ())) = std::stoi (str.substr(v[idx].idx, v[idx+1].idx-v[idx].idx));
				}
				else
				{
					(*(d.back ())) = std::stof (str.substr(v[idx].idx, v[idx+1].idx-v[idx].idx));
				}
			}
		}

		void STRING (
			unsigned long long& idx,
			std::string& str,
			std::vector<Tokin>& v,
			std::vector<Mobj*>& d,
			std::vector<add>& work)
		{
			if (work.back () != add::NOTHING)
			{
				(*(d.back ())) = str.substr (v[idx].idx, v[idx].len);
			}
		}

		void COLON (
			unsigned long long& idx,
			std::string& str,
			std::vector<Tokin>& v,
			std::vector<Mobj*>& d,
			std::vector<add>& work)
		{
			if (work.back () == add::NOTHING) // Если инициализация поля json-объекта,
			{
				// => раньше была строка => готовим место для объекта
				Mobj* op = &( (*(d.back ()))[str.substr(v[idx-1].idx, v[idx-1].len)] = Mobj () );

				d.push_back (op);
				work.back () = add::VAL;// требуем добавить значение
			}
		}

		void COMMA (
			std::vector<Mobj*>& d,
			std::vector<add>& work,
			std::vector<unsigned>& arrayIdx)
		{
			d.pop_back ();

			if (work.back () == add::VAL) // для json-объектов, откладываем переход к следующему объекту
			{
				work.back () = add::NOTHING;
			}
			else if (work.back () == add::ARRAY) // а для массива, переходим сразу
			{
				++(arrayIdx.back ());
				d.push_back (&( (*(d.back ()))[arrayIdx.back ()] ));
			}
		}

		void switcher (
			std::string& str,
			std::vector<Tokin>& v,
			std::vector<Mobj*>& d,
			std::vector<add>& work,
			std::vector<unsigned>& arrayIdx)
		{
			for (unsigned long long idx = 0; idx < v.size (); ++idx)
				switch(v[idx].type)
				{
					case tokinType::INT:
					case tokinType::FLOAT: 	NUM    (idx, str, v, d, work);      continue;
					case tokinType::STRING: STRING (idx, str, v, d, work);      continue;
					case tokinType::COLON:  COLON  (idx, str, v, d, work);      continue;
					case tokinType::OARR:   OARR   (idx, v, d, work, arrayIdx); continue;
					case tokinType::CARR:   CARR   (d, work, arrayIdx);         continue;
					case tokinType::COMMA:  COMMA  (d, work, arrayIdx);         continue;
					case tokinType::OMAP:   OMAP   (d, work);                   continue;
					case tokinType::CMAP:   CMAP   (d, work);                   continue;
				}
		}
	}


	// заносит токены в json-объект (с неправильной последовательностью токенов -- undefined поведение)
	void tokToMobj (std::vector<Tokin>& v, std::string& str, Mobj& root)
	{
		using namespace tok;
		std::vector<Mobj*> d; // deepness
		d.push_back (&root);

		std::vector<add> work;
		work.push_back (add::NOTHING);
		std::vector<unsigned> arrayIdx; // индекс в массиве

		switcher (str, v, d, work, arrayIdx);
	}




	// переводит json данные в объект Mobj
	void read (std::istream& is, Mobj& o)
	{
		std::vector<Tokin> v;
		std::string str;
		{
			char buff[400];
			while (!is.eof ())
			{
				is.getline (buff, 400);
				str += buff;
			}
		}
		unsigned idx = 0;
		strToTok (idx, str, v);
		tokToMobj (v, str, o);
	}
}









void Mobj::readFromFile (const char path[])
{
	using namespace mobjReadFromFile;
	std::ifstream fin (path);
	read (fin, *this);
	fin.close ();
}



















static unsigned mapprint = 0;
static unsigned long long deep = 0;
void tabs(std::ostream& os,unsigned long long& n)
{
	for (unsigned long long idx=0; idx < n; ++idx) { os << '\t'; }
}

std::ostream& operator<< (std::ostream& os, const Mobj& o)
{
	switch (o.type ())
	{
	case 'i':
		os << o.geti ();
		break;
	case 'f':
		os << o.getf ();
		break;
	case 'c':
		os << o.getc ();
		break;
	case 's':
		if (mapprint != 0)
		{
			os << '"' << o.gets () << '"';
			break;
		}
		os << o.gets ();
		break;
	case 'm':
		{
			++mapprint;
			jmap& mp = o.getm ();
			bool tr = false;
			//tabs (os, deep);
			os << '{';
			++deep;
			for (auto& it : mp)
			{
				if (tr) {os << ", ";}
				else {tr = !tr;}
				os << "\n";
				tabs (os, deep);
				os << '"' << it.first << "\" : " << it.second << "";
			}
			os << '\n';
			--deep;
			tabs (os, deep);
			os << '}';
			--mapprint;
		}
		break;
	case 'a':
		{
			++mapprint;
			auto sz = o.size ();
			os << '[';
			++deep;
			for (unsigned idx = 0; idx < sz; ++idx)
			{
				if (idx != 0) {os << ", ";}
				os << '\n';
				tabs(os,deep);
				os << o[idx];
			}
			os << '\n';
			--deep;
			tabs(os,deep);
			os << ']';
			--mapprint;
		}
		break;
	default:
		os << "_empty_";
		break;
	}

	return os;
}





std::istream& operator>> (std::istream& is, Mobj& o)
{
	std::string s;
	{
		char buff[300];
		is.getline(buff, 300);
		s = buff;
	}
	unsigned l = static_cast<unsigned>(s.length ());
	if (l==0) {o = Mobj (); return is;}
	if (l==3 && s[0]=='\'' && s[2]=='\'') {o = s[1]; return is;}
	if (s[0] == '"' && s.back()=='"')
	{
		o = s.substr (1, s.length () - 2);
		return is;
	}
	if (s.find_first_not_of( "+-0123456789" ) == std::string::npos)
	{
		o = std::stoi(s);
		return is;
	}
	if (s.find_first_not_of( "+-0123456789." ) == std::string::npos)
	{
		o = std::stof(s);
		return is;
	}
	if ( l==1 ) {o = s[0]; return is;}
	o = s;

	return is;
}
