/*------------------------------------------------------------------------
 *  Copyright (C) 2000-2008, Universidad de Zaragoza, SPAIN
 *
 *  Contact Addresses: Danilo Tardioli                   dantard@unizar.es
 *
 *  eBottle is free software;  you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation;  either version 2, or (at your option) any
 *  later version.
 *
 *  eBottle is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY;  without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  distributed with eBottle; see file COPYING. If not,  write to the
 *  Free Software  Foundation, 59 Temple Place - Suite 330, Boston, MA
 *  02111-1307, USA.
 *
 *  As a special exception, if you link this unit with other files to
 *  produce an executable, this unit does not by itself cause the resulting
 *  executable to be covered by the GNU General Public License.  This
 *  exception does not however invalidate any other reasons why the
 *  executable file might be covered by the GNU Public License.
 *
 *-------------------------------------------------------------------------*/

#include "eBottle.h"
#include <yarp/os/all.h>
#include <string>
#include <sstream>
#include <vector>

using yarp::os::eValue;
using yarp::os::eBottle;
using yarp::os::ConstString;

eValue::eValue() {
}
eValue::eValue(const int i) {
	value=new int(i);
	type=INT;
}

eValue::eValue(const char * text) {
	value=new std::string(text);
	type=STRING;
}

eValue::eValue(const std::string& s) {
	value=new std::string(s);
	type=STRING;
}

eValue::eValue(const double d) {
	value=new double(d);
	type=DOUBLE;
}
eValue::eValue(const char * p, const unsigned int size_p) {
	type = CHARP;
	size = size_p;
	value = (char *) new char[size];
	memcpy(value, p, size);
}

eValue::eValue(const eBottle * p) {
	this->value = (char *)p;
	type = BOTTLE;
}
int eValue::asInt() const {
	return *(int*) this->value;
}
double eValue::asDouble() const {
	return *(double*)value;
}

char * eValue::asBlob() {
	return (char*) value;
}

char * eValue::asBlob() const {
	return (char*) value;
}

eBottle * eValue::asList() const {
	return (eBottle*) value;
}

eBottle * eValue::asList() {
	return (eBottle*) value;
}

yarp::os::ConstString eValue::asString() const {
	ConstString cs( ((std::string*) value)->c_str());
	return cs;
}

int* eValue::asIntPtr()  {
	return (int*) value;
}

int* eValue::asIntPtr()  const {
	return (int*) value;
}

double* eValue::asDoublePtr()  {
	return (double*) value;
}

double* eValue::asDoublePtr() const {
	return (double*) value;
}

std::string* eValue::asStringPtr()  {
	return (std::string*) value;
}

/*ConstString* eValue::asStringPtr() const {
	return (ConstString*) value;
}*/

unsigned int eValue::asBlobLength() const {
	return size;
}

eValue::ValueType eValue::getType() const {
	return type;
}

unsigned int eValue::getSize() const {
	return size;
}

eValue::~eValue() {
	switch (type) {
		case CHARP:
			delete [] ((char*) value);
			break;
		case INT:
			delete (int*) value;
			break;
		case DOUBLE:
			delete (double*) value;
			break;
		case BOTTLE:
			delete (eBottle*) value;
			break;
		case STRING:
			delete (std::string*) value;
			break;
	}
}

bool eValue::isString() const {
	return type==STRING;
}
bool eValue::isInt() const {
	return type==INT;
}

bool eValue::isList() const {
	return type==BOTTLE;
}

bool eValue::isBlob() const {
	return type==CHARP;
}
bool eValue::isDouble() const {
	return type==DOUBLE;
}

eValue * eValue::makeBlob(const char* p, const unsigned int size) {
	return new eValue(p,size);
}

eValue & eValue::operator=(const eValue & p) {
	this->type=p.getType();
	this->size=p.getSize();
	switch(this->type) {
		case INT:
		value = new int(p.asInt());
		break;
		case BOTTLE:
		value = new eBottle();
		(*(eBottle*)value) = *(p.asList());
		break;
		case DOUBLE:
		value = new double(p.asDouble());
		break;
		case CHARP:
		value = new char[this->size];
		memcpy((char*)value,p.asBlob(),p.getSize());
		break;
		case STRING:
		value = new std::string(p.asString());
		break;
	}
	return *this;
}

std::string eBottle::content() const {
	std::string cont;
	for (unsigned int i = 0; i<values.size(); i++) {
		cont += (int) values[i]->getType();
		fprintf(stderr,"->%d  \n",values[i]->getType());
		cont += ":s";
	}
	return cont;
}

eBottle::eBottle() {
	toBinaryPointer=NULL;
}

void eBottle::clear() {
	for (unsigned int i=0; i<values.size(); i++) {
		delete values.at(i);
	}
	delete toBinaryPointer;
	values.clear();
}
unsigned int eBottle::count() const {
	return values.size();
}
unsigned int eBottle::size() const {
	return values.size();
}

eBottle::~eBottle() {
	for (unsigned int i=0; i<values.size(); i++) {
		delete values.at(i);
	}
	delete toBinaryPointer;
}
void eBottle::addInt(const int i) {
	eValue * p = new eValue(i);
	values.push_back(p);
}

void eBottle::addString(const std::string& s) {
	eValue * p = new eValue(s.c_str());
	values.push_back(p);
}

void eBottle::addString(const ConstString& s) {
	eValue * p = new eValue(s.c_str());
	values.push_back(p);
}

void eBottle::addString(const char * s) {
	eValue * p = new eValue(s);
	values.push_back(p);
}
void eBottle::addDouble(const double d) {
	eValue * p = new eValue(d);
	values.push_back(p);
}
void eBottle::addBlob(const char * q, const unsigned int size) {
	eValue * p = new eValue(q,size);
	values.push_back(p);
}
eBottle * eBottle::addListPtr() {
	eBottle* yb= new eBottle();
	eValue * p = new eValue(yb);
	values.push_back(p);
	return (eBottle*) yb;
}

eBottle & eBottle::addList() {
	eBottle* yb= new eBottle();
	eValue * p = new eValue(yb);
	values.push_back(p);
	return *yb;
}

void eBottle::add(const eValue* yv) {
	eValue * p = new eValue();
	(*p)=*yv;
	values.push_back(p);
}

void eBottle::add(const eValue & yv) {
	eValue * p = new eValue();
	(*p)=yv;
	values.push_back(p);
}

eValue * eBottle::getPtr(const unsigned int i) {
	return values.at(i);
}

eValue * eBottle::getPtr(const unsigned int i) const {
	return values.at(i);
}

eValue & eBottle::get(const unsigned int i) {
	return *values.at(i);
}

eValue & eBottle::get(const unsigned int i) const {
	return *values.at(i);
}

bool eBottle::write(ConnectionWriter& connection) {
	int size=getBinarySize();
	connection.appendInt(size);
//	fprintf(stderr,"TX SIZE: %d\n",size);
	char * tmp=new char[size];
	toBinary(tmp);
	connection.appendBlock(tmp, size);
	delete[] tmp;
	return true;
}

bool eBottle::read(ConnectionReader& connection) {
	this->clear();
	int size=connection.expectInt();
//	fprintf(stderr,"RX SIZE: %d\n",size);
	const char * tmp=new char[size];
	connection.expectBlock(tmp, size);
	fromBinary(tmp, size);
	delete[] tmp;
	return !connection.isError();
}

void eBottle::remove(const unsigned int i) {
	delete values.at(i);
	values.erase(values.begin()+i);
}

void eBottle::insert(const eValue *p, const unsigned int i) {
	eValue * yv=new eValue();
	*yv=*p;
	values.insert(values.begin()+i, yv);
}
eBottle & eBottle::operator=(const eBottle & p) {
	this->clear();
	for (unsigned int i=0;i<p.values.size();i++) {
		switch (p.getPtr(i)->getType()) {
			case eValue::INT:
			this->addInt(p.getPtr(i)->asInt());
			break;
			case eValue::DOUBLE:
			this->addDouble(p.getPtr(i)->asDouble());
			break;
			case eValue::CHARP:
			this->addBlob(p.getPtr(i)->asBlob(),p.getPtr(i)->getSize());
			break;
			case eValue::BOTTLE: {
				eBottle * yb= this->addListPtr();
				yb->operator=(*(p.getPtr(i)->asList()));
				break;
			}
			case eValue::STRING: {
				this->addString(p.getPtr(i)->asString().c_str());
				break;
			}
		}
	}
	return *this;
}

void eBottle::copy(const eBottle *p) {
	this->clear();
	for (unsigned int i=0; i<p->count(); i++) {
		switch (p->getPtr(i)->getType()) {
			case eValue::INT:
				this->addInt(p->getPtr(i)->asInt());
				break;
			case eValue::DOUBLE:
				this->addDouble(p->getPtr(i)->asDouble());
				break;
			case eValue::CHARP:
				this->addBlob(p->getPtr(i)->asBlob(), p->getPtr(i)->getSize());
				break;
			case eValue::BOTTLE: {
				eBottle * yb= this->addListPtr();
				yb->copy(p->getPtr(i)->asList());
				break;
			}
			case eValue::STRING:
				this->addString(p->getPtr(i)->asString());
				break;
		}
	}
}

const char * const eBottle::toBinary(int *size) const {
	int global_size=0;
	fill(this, global_size);
	toBinaryPointer = new char[global_size];
	global_size=0;
	fill(this, global_size, toBinaryPointer);
	*size=global_size;
	return toBinaryPointer;
}

unsigned int eBottle::getBinarySize() const {
	int size=0;
	fill(this, size);
	return size;

}
void eBottle::toBinary(char * p) const {
	int global_size=0;
	fill(this, global_size, p);
}

void eBottle::fromBinary(const char * p, const int size) {
	int s=0;
	reconstruct(this, s, (char *) p);
	if (size!=s) {
		fprintf(stderr,"Reconstruct error\n");
	}
}

void eBottle::append(const eBottle & yb) {
	for (unsigned int i=0; i<yb.count(); i++) {
		this->add(yb.getPtr(i));
	}
}

void eBottle::fill(const eBottle * b, int &s, char * p) const {
	if (p!=NULL)
		* (int*) (p+s) =b->count();
	s+=sizeof(int);
	for (unsigned int i=0; i<b->count(); i++) {
		if (p!=NULL) {
			* (int*) (p+s) = b->getPtr(i)->getType();
		}
		s+=sizeof(int);
		switch (b->getPtr(i)->getType()) {
			case eValue::INT: {
				if (p!=NULL) {
					*(int*) (p+s) =b->getPtr(i)->asInt();
				}
				s+=sizeof(int);
				break;
			}
			case eValue::DOUBLE: {
				if (p!=NULL)
					* (double*) (p+s)=b->getPtr(i)->asDouble();
				s+=sizeof(double);
				break;
			}
			case eValue::CHARP: {
				if (p!=NULL)
					* (int*) (p+s)=b->getPtr(i)->getSize();
				s+=sizeof(int);
				if (p!=NULL)
					memcpy(p+s, b->getPtr(i)->asBlob(), b->getPtr(i)->getSize());
				s+=b->getPtr(i)->getSize();
				break;
			}
			case eValue::BOTTLE: {
				eBottle * q=b->getPtr(i)->asList();
				fill(q, s, p);
				break;
			}
			case eValue::STRING: {
				int str_len=strlen(b->getPtr(i)->asString().c_str())+1;
				if (p!=NULL)
					* (int*) (p+s)=str_len;
				s+=sizeof(int);
				if (p!=NULL)
					memcpy(p+s, b->getPtr(i)->asString().c_str(), str_len);
				s+=str_len;
				break;
			}
		}
	}
}

void eBottle::reconstruct(eBottle * b, int & s, char * p) const {
	unsigned int n_elem_bottle = * (int*) (p+s);
	s+=sizeof(int);
	for (unsigned int i=0; i<n_elem_bottle; i++) {
		int * j = (int*) (p+s); //type
		s+=sizeof(int);
		switch (*j) {
			case eValue::INT: {
				b->addInt(* (int*) (p+s) );
				s+=sizeof(int);
				break;
			}
			case eValue::DOUBLE: {
				b->addDouble(* (double*) (p+s));
				s+=sizeof(double);
				break;
			}
			case eValue::CHARP: {
				int dim=(* (int*) (p+s));
				s+=sizeof(int);
				b->addBlob(p+s, dim);
				s+=dim;
				break;
			}
			case eValue::BOTTLE: {
				eBottle * q=b->addListPtr();
				reconstruct(q, s, p);
				break;
			}
			case eValue::STRING: {
				int strlen=( * (int*) (p+s) );
				s+=sizeof(int);
				b->addString(p+s);
				s+=strlen;
				break;
			}
		}
	}
}

std::string eBottle::toString() const {
	std::ostringstream s;
	fillString(&s, this);
	return s.str();
}
void eBottle::fromString(const std::string& s) {
	fromString(s.c_str());
}

void eBottle::fromString(const ConstString& s) {
	fromString(s.c_str());
}

void eBottle::fromString(const char * txt) {
	std::string s;
	s+="EBOTTLE ";
	bool addSpace=false;
	for (unsigned int i=0; i< strlen(txt); i++) {
		if (txt[i]=='(' || txt[i]==')' || txt[i]=='{' || txt[i]=='}') {
			addSpace=true;
		}
		if (addSpace)
			s+=" ";
		s+=(char) txt[i];
		if (addSpace)
			s+=" ";
		addSpace=false;
	}
	char s2[] = " ";
	char *ptr;
	ptr = strtok( (char*) s.c_str(), s2);
	fromStr(this, s2);
}

eValue & eBottle::operator[](const unsigned int i) const {
	return *values.at(i);
}

eValue & eBottle::operator[](const unsigned int i) {
	return *values.at(i);
}

eBottle::eBottle(const std::string& s){
	toBinaryPointer=NULL;
	this->fromString(s.c_str());
}

eBottle::eBottle(const ConstString& s) {
	toBinaryPointer=NULL;
	this->fromString(s.c_str());

}

eBottle::eBottle(const char * txt) {
	toBinaryPointer=NULL;
	this->fromString(txt);
}

eBottle::eBottle(const eBottle & eb) {
	toBinaryPointer=NULL;
	this->copy(&eb);

}
void eBottle::fromStr(eBottle *b, const char * s2) const {
	char * ptr = strtok(NULL, s2);
	bool beginBlob=false;
	std::vector<char> v;
	while (ptr != NULL) {
		if (*ptr >= 'A' && *ptr <= 'z') {
			b->addString(ptr);
		} else if (*ptr=='(') {
			eBottle * p = b->addListPtr();
			fromStr(p, s2);
		} else if (*ptr==')') {
			return;
		} else if (*ptr=='{') {
			beginBlob=true;
		} else if (*ptr=='}') {
			beginBlob=false;
			char tmp[v.size()];
			for (unsigned int i=0; i<v.size(); i++) {
				tmp[i]=v.at(i);
			}
			b->addBlob((char *)tmp, v.size());
		} else {
			if (beginBlob) {
				v.push_back(atoi(ptr));
			} else {
				if (strstr(ptr, ".")==NULL) {
					b->addInt(atoi(ptr));
				} else {
					b->addDouble(atof(ptr));
				}
			}
		}
		ptr = strtok(NULL, s2);
	}
}

void eBottle::fillString(std::ostringstream * s, const eBottle *b) const {
	for (unsigned int i=0; i<b->values.size(); i++) {
		switch (b->getPtr(i)->getType()) {
			case eValue::INT: {
				int v=b->getPtr(i)->asInt();
				*s << v;
				break;
			}
			case eValue::DOUBLE: {
				double v = b->getPtr(i)->asDouble();
				*s << v;
				break;
			}
			case eValue::CHARP: {
				*s << "{";
				char * elem=b->getPtr(i)->asBlob();
				unsigned int j;
				for (j=0; j<b->getPtr(i)->getSize()-1; j++) {
					*s << (int) elem[j] << " ";
				}
				*s << (int) elem[j] << "}";
				break;
			}
			case eValue::BOTTLE: {
				*s << "(";
				eBottle *c= b->getPtr(i)->asList();
				b->fillString(s, c);
				*s << ")";
				break;
			}
			case eValue::STRING: {
				*s << b->getPtr(i)->asString().c_str();
				break;
			}
		}
		if (i!=b->count()-1)
			*s<< " ";
	}
}

