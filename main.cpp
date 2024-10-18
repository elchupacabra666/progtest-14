#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;
#endif /* __PROGTEST__ */


class MyVector;

class MyString {
      public:
	char * m_str;
	MyString(const char * src);
	MyString(const MyString & src);
	~MyString();
	MyString & operator=(const MyString & str);
      friend ostream & operator<<(ostream & os, const MyString & str);
      friend bool operator==(const MyString & s1, const MyString & s2);
};

ostream & operator<<(ostream & os, const MyString & str ) {
	cout << str.m_str;	return os;
}


bool operator==(const MyString & s1, const MyString & s2) {

	if (strlen(s1.m_str) != strlen(s2.m_str))
		return false;

	size_t size = strlen(s1.m_str);
	for (size_t i = 0; i <= size; i++) {
		if (s1.m_str[i] != s2.m_str[i])
			return false;
	}
	return true;
}

MyString::MyString(const char *src) {


	if (src == nullptr) {
		m_str = new char[1];
		m_str[0] = '\0';
	}

	else {
		m_str = new char [strlen(src) + 1];
		strcpy(m_str, src);
		m_str[strlen(src)] = '\0';
	}
}

MyString::~MyString() {
	delete[] m_str;
}

MyString::MyString(const MyString &src) {
	m_str = new char[strlen(src.m_str) + 1];
	strcpy(m_str, src.m_str);
	m_str[strlen(src.m_str)] = '\0';
}

MyString &MyString::operator=(const MyString &str) {

	if (&str == this) return *this;
	delete [] this->m_str;
	size_t size = strlen(str.m_str);
	m_str = new char [size + 1];
	for (size_t i = 0; i < size; i++) {
		this->m_str[i] = str.m_str[i];
	}

	this->m_str[size] = '\0';

	return *this;
}

class CMail {
      public:
	CMail(const char *from = "",
	      const char *to = "",
	      const char *body = "") : m_from(from), m_to(to), m_body(body){};
	bool operator==(const CMail &x) const;
	friend ostream &operator<<(ostream &os,
				   const CMail &m);

	MyString m_from;
	MyString m_to;
	MyString m_body;
      private:
};

class MyVector {
      public:
	MyVector(): m_array(nullptr), m_capacity(0), m_count(0){};
	MyVector(const MyVector & src);
	MyVector & operator=(const MyVector & src);
	~MyVector();
	void push_back(const CMail & mail);
	void addCapacity();
	void printVec();

	CMail * m_array;
	size_t m_capacity;
	size_t m_count;
};




class CMailIterator {
      public:
	explicit                 operator bool() const;

	bool operator!() const;

	const CMail &operator*() const;

	CMailIterator &operator++(void);

	MyVector m_vector;

	size_t m_index = 0;
};

CMailIterator &CMailIterator::operator++(void) {
	(this->m_index)++;
	return *this;
}

const CMail &CMailIterator::operator*(void) const {
	return (m_vector.m_array[m_index]);
}

CMailIterator::operator bool(void) const {
	if (m_index + 1 <= m_vector.m_count)
		return true;
	return false;
}

bool CMailIterator::operator!(void) const {

	if (m_index + 1 <= m_vector.m_count)
		return false;
	return true;
}

void MyVector::printVec() {

	for (size_t i = 0; i < m_count - 1; i++) {
		cout << m_array[i];
	}
	cout << m_array[m_count - 1];
}

class CMailServer {
      public:
	void sendMail(const CMail &m);

	CMailIterator outbox(const char *email) const;

	CMailIterator inbox(const char *email) const;

	MyVector vect;
};


void CMailServer::sendMail(const CMail &m) {
	vect.push_back(m);
}

CMailIterator CMailServer::outbox(const char *email) const {

	CMailIterator it;
	for (size_t i = 0; i < vect.m_count; i++) {
		if (email == vect.m_array[i].m_from)
			it.m_vector.push_back(vect.m_array[i]);
	}
	return it;
}

CMailIterator CMailServer::inbox(const char *email) const {
	CMailIterator it;
	for (size_t i = 0; i < vect.m_count; i++) {
		if (email == vect.m_array[i].m_to)
			it.m_vector.push_back(vect.m_array[i]);
	}
	return it;
}

bool CMail::operator==(const CMail &x) const {

	if (this->m_from == x.m_from && this->m_to == x.m_to && this->m_body == x.m_body)
		return true;
	return false;
}


ostream &operator<<(ostream &os, const CMail &m) {
	os << "From: " << m.m_from.m_str << ", To: " << m.m_to.m_str << ", Body: " << m.m_body.m_str;
	return os;
}

//From: john, To: alice, Body: deadline notice



void MyVector::push_back(const CMail & mail) {

	if (m_count == m_capacity)
		addCapacity();
	m_array[m_count] = mail;
	m_count++;
}

void MyVector::addCapacity() {
	size_t oldCap = m_capacity;
	m_capacity = m_capacity * 2 + 1;
	CMail * newArray = new CMail [m_capacity];

	for (size_t i = 0; i < oldCap; i++) {
		newArray[i] = {nullptr, nullptr, nullptr};
	}

	for (size_t i = 0; i < m_count; i++) {
		newArray[i] = m_array[i];
	}
	delete[] m_array;
	m_array = newArray;
}

MyVector::~MyVector() {

	delete[] m_array;

}

MyVector & MyVector::operator=(const MyVector &src) {
	if (&src == this)
		return *this;
	delete[] this->m_array;
	this->m_capacity = src.m_capacity;
	this->m_count = src.m_count;
	this->m_array = new CMail [this->m_capacity];
	for (size_t i = 0; i < m_count; i++) {
		this->m_array[i] = src.m_array[i];
	}
	return *this;
}

MyVector::MyVector(const MyVector &src){

	m_capacity = src.m_capacity;
	m_count = src.m_count;
	m_array = new CMail [m_capacity];
	for (size_t i = 0; i < m_count; i++) {
		this->m_array[i] = src.m_array[i];
	}
}




#ifndef __PROGTEST__

bool matchOutput(const CMail &m,
		 const char *str) {
	ostringstream oss;
	oss << m;
	return oss.str() == str;
}

int main(void) {
	char from[100], to[100], body[1024];


	/*CMailIterator it;
	CMailServer a;
	a.vect.push_back(CMail("john", "peter", "progtest deadline"));
	a.vect.push_back(CMail("petr", "patrik", "ahoj zmrde"));
	a.vect.push_back(CMail("petr", "pepa", "jak se mas"));
	a.vect.push_back(CMail("petr", "viki", "spamuju te"));
	a.vect.push_back(CMail("petr", "maminka", "ahoj mami"));
	a.vect.printVec();

	it = a.outbox("petr");
	cout << "Outbox:" << endl;
	it.m_vector.printVec();

	cout << "Inbox:" << endl;
	it = a.inbox("pepa");
	it.m_vector.printVec();

	cout << endl;
	++it;
	++it;
	++it;
	++it;
	++it;
	++it;
	++it;
	++it;
	++it;
	++it;
	++it;
	++it;



	if (it) cout << "Pravda";
	else cout << "Lež";*/


	assert(CMail("john", "peter", "progtest deadline") == CMail("john", "peter", "progtest deadline"));
	assert(!(CMail("john", "peter", "progtest deadline") == CMail("john", "progtest deadline", "peter")));
	assert(!(CMail("john", "peter", "progtest deadline") == CMail("peter", "john", "progtest deadline")));
	assert(!(CMail("john", "peter", "progtest deadline") == CMail("peter", "progtest deadline", "john")));
	assert(!(CMail("john", "peter", "progtest deadline") == CMail("progtest deadline", "john", "peter")));
	assert(!(CMail("john", "peter", "progtest deadline") == CMail("progtest deadline", "peter", "john")));
	CMailServer s0;
	s0.sendMail(CMail("john", "peter", "some important mail"));
	strncpy(from, "john", sizeof(from));
	strncpy(to, "thomas", sizeof(to));
	strncpy(body, "another important mail", sizeof(body));
	s0.sendMail(CMail(from, to, body));
	strncpy(from, "john", sizeof(from));
	strncpy(to, "alice", sizeof(to));
	strncpy(body, "deadline notice", sizeof(body));
	s0.sendMail(CMail(from, to, body));
	s0.sendMail(CMail("alice", "john", "deadline confirmation"));
	s0.sendMail(CMail("peter", "alice", "PR bullshit"));
	CMailIterator i0 = s0.inbox("alice");
	assert(i0 && *i0 == CMail("john", "alice", "deadline notice"));
	assert(matchOutput(*i0, "From: john, To: alice, Body: deadline notice"));
	assert(++i0 && *i0 == CMail("peter", "alice", "PR bullshit"));

	assert(matchOutput(*i0, "From: peter, To: alice, Body: PR bullshit"));
	assert(!++i0);

	CMailIterator i1 = s0.inbox("john");
	assert(i1 && *i1 == CMail("alice", "john", "deadline confirmation"));
	assert(matchOutput(*i1, "From: alice, To: john, Body: deadline confirmation"));
	assert(!++i1);

	CMailIterator i2 = s0.outbox("john");
	assert(i2 && *i2 == CMail("john", "peter", "some important mail"));
	assert(matchOutput(*i2, "From: john, To: peter, Body: some important mail"));
	assert(++i2 && *i2 == CMail("john", "thomas", "another important mail"));
	assert(matchOutput(*i2, "From: john, To: thomas, Body: another important mail"));
	assert(++i2 && *i2 == CMail("john", "alice", "deadline notice"));
	assert(matchOutput(*i2, "From: john, To: alice, Body: deadline notice"));
	assert(!++i2);


	CMailIterator i3 = s0.outbox("thomas");
	assert(!i3);

	CMailIterator i4 = s0.outbox("steve");
	assert(!i4);

	CMailIterator i5 = s0.outbox("thomas");
	s0.sendMail(CMail("thomas", "boss", "daily report"));
	assert(!i5);

	CMailIterator i6 = s0.outbox("thomas");
	assert(i6 && *i6 == CMail("thomas", "boss", "daily report"));
	assert(matchOutput(*i6, "From: thomas, To: boss, Body: daily report"));
	assert(!++i6);

	CMailIterator i7 = s0.inbox("alice");
	s0.sendMail(CMail("thomas", "alice", "meeting details"));
	assert(i7 && *i7 == CMail("john", "alice", "deadline notice"));
	assert(matchOutput(*i7, "From: john, To: alice, Body: deadline notice"));
	assert(++i7 && *i7 == CMail("peter", "alice", "PR bullshit"));
	assert(matchOutput(*i7, "From: peter, To: alice, Body: PR bullshit"));
	assert(!++i7);

	CMailIterator i8 = s0.inbox("alice");
	assert(i8 && *i8 == CMail("john", "alice", "deadline notice"));
	assert(matchOutput(*i8, "From: john, To: alice, Body: deadline notice"));
	assert(++i8 && *i8 == CMail("peter", "alice", "PR bullshit"));
	assert(matchOutput(*i8, "From: peter, To: alice, Body: PR bullshit"));
	assert(++i8 && *i8 == CMail("thomas", "alice", "meeting details"));
	assert(matchOutput(*i8, "From: thomas, To: alice, Body: meeting details"));
	assert(!++i8);

	CMailServer s1(s0);
	s0.sendMail(CMail("joe", "alice", "delivery details"));
	s1.sendMail(CMail("sam", "alice", "order confirmation"));
	CMailIterator i9 = s0.inbox("alice");
	assert(i9 && *i9 == CMail("john", "alice", "deadline notice"));
	assert(matchOutput(*i9, "From: john, To: alice, Body: deadline notice"));
	assert(++i9 && *i9 == CMail("peter", "alice", "PR bullshit"));
	assert(matchOutput(*i9, "From: peter, To: alice, Body: PR bullshit"));
	assert(++i9 && *i9 == CMail("thomas", "alice", "meeting details"));
	assert(matchOutput(*i9, "From: thomas, To: alice, Body: meeting details"));
	assert(++i9 && *i9 == CMail("joe", "alice", "delivery details"));
	assert(matchOutput(*i9, "From: joe, To: alice, Body: delivery details"));
	assert(!++i9);

	CMailIterator i10 = s1.inbox("alice");
	assert(i10 && *i10 == CMail("john", "alice", "deadline notice"));
	assert(matchOutput(*i10, "From: john, To: alice, Body: deadline notice"));
	assert(++i10 && *i10 == CMail("peter", "alice", "PR bullshit"));
	assert(matchOutput(*i10, "From: peter, To: alice, Body: PR bullshit"));
	assert(++i10 && *i10 == CMail("thomas", "alice", "meeting details"));
	assert(matchOutput(*i10, "From: thomas, To: alice, Body: meeting details"));
	assert(++i10 && *i10 == CMail("sam", "alice", "order confirmation"));
	assert(matchOutput(*i10, "From: sam, To: alice, Body: order confirmation"));
	assert(!++i10);

	CMailServer s2;
	s2.sendMail(CMail("alice", "alice", "mailbox test"));
	CMailIterator i11 = s2.inbox("alice");
	assert(i11 && *i11 == CMail("alice", "alice", "mailbox test"));
	assert(matchOutput(*i11, "From: alice, To: alice, Body: mailbox test"));
	assert(!++i11);

	s2 = s0;
	s0.sendMail(CMail("steve", "alice", "newsletter"));
	s2.sendMail(CMail("paul", "alice", "invalid invoice"));
	CMailIterator i12 = s0.inbox("alice");
	assert(i12 && *i12 == CMail("john", "alice", "deadline notice"));
	assert(matchOutput(*i12, "From: john, To: alice, Body: deadline notice"));
	assert(++i12 && *i12 == CMail("peter", "alice", "PR bullshit"));
	assert(matchOutput(*i12, "From: peter, To: alice, Body: PR bullshit"));
	assert(++i12 && *i12 == CMail("thomas", "alice", "meeting details"));
	assert(matchOutput(*i12, "From: thomas, To: alice, Body: meeting details"));
	assert(++i12 && *i12 == CMail("joe", "alice", "delivery details"));
	assert(matchOutput(*i12, "From: joe, To: alice, Body: delivery details"));
	assert(++i12 && *i12 == CMail("steve", "alice", "newsletter"));
	assert(matchOutput(*i12, "From: steve, To: alice, Body: newsletter"));
	assert(!++i12);

	CMailIterator i13 = s2.inbox("alice");
	assert(i13 && *i13 == CMail("john", "alice", "deadline notice"));
	assert(matchOutput(*i13, "From: john, To: alice, Body: deadline notice"));
	assert(++i13 && *i13 == CMail("peter", "alice", "PR bullshit"));
	assert(matchOutput(*i13, "From: peter, To: alice, Body: PR bullshit"));
	assert(++i13 && *i13 == CMail("thomas", "alice", "meeting details"));
	assert(matchOutput(*i13, "From: thomas, To: alice, Body: meeting details"));
	assert(++i13 && *i13 == CMail("joe", "alice", "delivery details"));
	assert(matchOutput(*i13, "From: joe, To: alice, Body: delivery details"));
	assert(++i13 && *i13 == CMail("paul", "alice", "invalid invoice"));
	assert(matchOutput(*i13, "From: paul, To: alice, Body: invalid invoice"));
	assert(!++i13);

	return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
