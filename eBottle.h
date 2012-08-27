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

/** \file eBottle.h
 * 
 * \brief eBottle and eValue definitions
 * 
 * \author Danilo Tardioli et al. (UniZar) \<dantard@unizar.es\>
 * 
 * \version 0.1 beta
 * 
 * \date May 2008
 * 
 * This file presents an efficient implementation of YARP communication classes <a href='http://eris.liralab.it/yarp/specs/dox/user/html/d3/d3e/classyarp_1_1os_1_1Bottle.html'> Bottle</a> 
 * and <a href='http://eris.liralab.it/yarp/specs/dox/user/html/d9/dad/classyarp_1_1os_1_1Value.html'>Value</a> 
 * to allow a faster communication using YARP.  
 * 
 * The interface is designed to ensure the compatibility with the YARP default 
 * classes overrided here which makes it easier to swap between YARP and UniZar 
 * Bottle and Value implementations.
 */

#ifndef YARPBOTTLE_H_
#define YARPBOTTLE_H_

#include <yarp/os/all.h>
#include <string>
#include <sstream>
#include <vector>

/** 
 * \brief YARP namespace
 * 
 * The eBottle and eValue classes are defined here to make them compatible
 */
namespace yarp {

	/** 
	 * \brief OS namespace
	 * 
	 * The eBottle and eValue classes are defined here to make them compatible
	 */
	namespace os {

		class eBottle;

		/**
		 * \brief Single efficient Value class
		 * 
		 * This class replaces the behaviour and functionality of the Value YARP 
		 * class.  It is the base class that allows simple data transmission.
		 * To transmit more complex data, list eValues can be used.
		 * 
		 */
		class eValue {
			public:
				/**
				 * \brief Basic types allowed in data transmission
				 * 
				 * These are the simple value types that can be transmitted
				 */
				enum ValueType {
					INT = 1, ///< Integer data  
					DOUBLE, ///< Double precission floating point data  
					CHARP, ///< Blob of bytes
					BOTTLE, ///< List of eValues 
					STRING ///< String of characters
				};

			public:

				/**
				 * \brief blob type eValue factory
				 * 
				 * Creates a dynamically allocated eValue with a blob inside.
				 * The blob is copied before stored.
				 * 
				 * \param[in] p A pointer to the memory to store
				 * \param[in] size The size of the memory blob in bytes
				 * 
				 * \return A pointer to the new eValue
				 */
				static eValue
						* makeBlob(const char* p, const unsigned int size);

				/**
				 * \brief Default constructor
				 * 
				 * Creates an empty eValue
				 */
				eValue();

				/**
				 * \brief Integer eValue constructor
				 * 
				 * Creates an eValue with an integer
				 * \param[in] i The integer to store
				 */
				eValue(const int i);

				/**
				 * \brief Double eValue constructor
				 * 
				 * Creates an eValue with a double
				 * \param[in] d The double to store
				 */
				eValue(const double d);

				/**
				 * \brief Blob eValue constructor
				 * 
				 * Creates an eValue with a blob of bytes.
				 * It Reserves its own memory and makes a copy of the blob.  
				 * 
				 * \param[in] p A pointer to the memory to store
				 * \param[in] size_p The size of the memory blob in bytes
				 */
				eValue(const char * p, const unsigned int size_p);

				/**
				 * \brief List eValue constructor
				 * 
				 * Creates an eValue with a list.
				 * The eValue <b>do not copy</b> the eBottle before storing it.
				 * \param[in] p The pointer to the list to store
				 */
				eValue(const eBottle * p);

				/**
				 * \brief String eValue constructor
				 * 
				 * Creates an eValue with a string, making a copy of the char array.
				 * \param[in] text The pointer to the null teminated string to store
				 */
				eValue(const char * text);

				/**
				 * \brief String eValue constructor
				 * 
				 * Creates an eValue with a string.
				 * It stores a copy of the string given.
				 * \param[in] s The string to store
				 */
				eValue(const std::string& s);

				/**
				 * \brief Class destructor
				 * 
				 * Frees all the memory used
				 */
				~eValue();

				/**
				 * Assignation operator
				 * 
				 * \param p The source  eValue to copy 
				 */
				eValue & operator=(const eValue & p);

				/**
				 * Access to eValue type
				 * 
				 * \return The type of the data in the eValue
				 */
				ValueType getType() const;

				/**
				 * Access to eValue size
				 * 
				 * \return The size of the data in the eValue in bytes
				 */
				unsigned int getSize() const;

				/**
				 * Checks wheather the eValue holds a integer or not
				 * 
				 * \return True if the eValue type is eValue::INT. Otherwise, false.
				 */
				bool isInt() const;

				/**
				 * Checks wheather the eValue holds a double or not
				 * 
				 * \return True if the eValue type is eValue::DOUBLE. Otherwise, false.
				 */
				bool isDouble() const;

				/**
				 * Checks wheather the eValue holds a blob or not
				 * 
				 * \return True if the eValue type is eValue::CHARP. Otherwise, false.
				 */
				bool isBlob() const;

				/**
				 * Checks wheather the eValue holds a list or not
				 * 
				 * \return True if the eValue type is eValue::BOTTLE. Otherwise, false.
				 */
				bool isList() const;

				/**
				 * Checks wheather the eValue holds a string or not
				 * 
				 * \return True if the eValue type is eValue::STRING. Otherwise, false.
				 */
				bool isString() const;

				/**
				 * Access to the eValue data as an integer
				 * 
				 * \return A copy of the integer stored in the eValue
				 */
				int asInt() const;

				/**
				 * Access to the eValue data as an integer
				 * 
				 * \return A pointer to the integer inside the eValue
				 */
				int* asIntPtr();

				/**
				 * Access to the eValue data as an integer
				 * 
				 * \return A constant pointer to the integer inside the eValue
				 */
				int* asIntPtr() const;

				/**
				 * Access to the eValue data as an double
				 * 
				 * \return A copy of the double stored in the eValue
				 */
				double asDouble() const;

				/**
				 * Access to the eValue data as an double
				 * 
				 * \return A pointer to the double inside the eValue
				 */
				double* asDoublePtr();

				/**
				 * Access to the eValue data as an double
				 * 
				 * \return A constant pointer to the double inside the eValue
				 */
				double* asDoublePtr() const;

				/**
				 * Access to the eValue data as an blob
				 * 
				 * \return A pointer to the blob inside the eValue
				 */
				char * asBlob();

				/**
				 * Access to the eValue data as an blob
				 * 
				 * \return A constant pointer to the blob inside the eValue
				 */
				char * asBlob() const;

				/**
				 * Access to the eValue data size as a blob
				 * 
				 * \return The size of the blob inside the eValue in bytes 
				 */
				unsigned int asBlobLength() const;

				/**
				 * Access to the eValue data as a list
				 * 
				 * \return A pointer to the list inside the eValue
				 */
				eBottle * asList();

				/**
				 * Access to the eValue data as a list
				 * 
				 * \return A constant pointer to the list inside the eValue
				 */
				eBottle * asList() const;

				/**
				 * Access to the eValue data as a string
				 * 
				 * \return A copy of the string stored in the eValue
				 */
				ConstString asString() const;

				/**
				 * Access to the eValue data as a string
				 * 
				 * \return A pointer to the string inside the eValue
				 */
				std::string* asStringPtr();

				/*
				 * Access to the eValue data as a string
				 * 
				 * \return A constant pointer to the string inside the eValue
				 
				ConstString* asStringPtr() const;*/

			private:
				ValueType type;
				unsigned int size;
				void * value;
		};

		/**
		 * \brief Efficient eValue list class
		 * 
		 * This class is able to store an ordered list of eValues of different
		 * types, including nested lists, and to transmit it using YARP.
		 * 
		 * The main difference between this implementation and the YARP default 
		 * one is that this is not strictly human readable, which permits a faster 
		 * and more efficient memory copy and yarp transmission.
		 * 
		 * Furthermore, using the efficient copy operator, most of the memory 
		 * leaks that pointers may cause are avoided.
		 */
		class eBottle : public yarp::os::Portable {
			public:
				/**
				 * \brief Default constructor
				 * 
				 * Creates an empty eBottle.
				 */
				eBottle();

				/**
				 * \brief String contructor
				 * 
				 * Creates an eBottle from a human readable string 
				 * (in the same way YARP does).
				 * 
				 * \param txt A pointer to the null terminated char array
				 */
				eBottle(const char * txt);

				/**
				 * \brief String contructor
				 * 
				 * Creates an eBottle from a human readable string 
				 * (in the same way YARP does).
				 * 
				 * \param s The string that represents the eBottle
				 */
				eBottle(const std::string& s);

				/**
				 * \brief String contructor
				 * 
				 * Creates an eBottle from a human readable string 
				 * (in the same way YARP does).
				 * 
				 * \param s The string that represents the eBottle
				 */
				eBottle(const ConstString& s);

				/**
				 * \brief Copy constructor
				 * 
				 * Creates an eBottle as a copy of another one
				 * 
				 * \param[in] eb The source eBottle to copy
				 */
				eBottle(const eBottle & eb);

				/**
				 * \brief Class destructor
				 * 
				 * Frees al the memory used in the object.
				 */
				virtual ~eBottle();

				/**
				 * \brief Copy function
				 * 
				 * Rebuilds the eBottle as a copy of another one
				 * 
				 * \param[in]  p A pointer to the eBottle to copy from.
				 */
				void copy(const eBottle *p);

				/**
				 * \brief Assignation operator
				 * 
				 * Rebuilds the eBottle as a copy of another one
				 * 
				 * \param[in]  p A reference to the eBottle to copy from.
				 */
				eBottle & operator=(const eBottle & p);

				/**
				 * Removes all the eValues inside the eBottle.
				 */
				virtual void clear();

				/**
				 * Inserts a copy of the an eValue at the end of the eBottle
				 * 
				 * \param[in] e A pointer to the eValue to insert
				 */
				void add(const eValue * e);

				/**
				 * Inserts a copy of the an eValue at the end of the eBottle
				 * 
				 * \param[in] e A reference to the eValue to insert
				 */
				void add(const eValue & e);

				/**
				 * Inserts an integer type eValue at the end of the eBottle
				 * 
				 * \param[in] i The integer to insert
				 */
				void addInt(const int i);

				/**
				 * Inserts a double type eValue at the end of the eBottle
				 * 
				 * \param[in] d The double to insert
				 */
				void addDouble(const double d);

				/**
				 * Inserts a blob type eValue at the end of the eBottle,
				 * making first a local copy of the memory
				 * 
				 * \param[in] q A pointer to the blob
				 * \param[in] size The size of the blob in bytes
				 */
				void addBlob(const char * q, const unsigned int size);

				/**
				 * Inserts a string eValue at the end of the eBottle
				 * 
				 * \param[in] s The string to insert
				 */
				void addString(const std::string& s);

				/**
				 * Inserts a string eValue at the end of the eBottle
				 * 
				 * \param[in] s The string to insert
				 */
				void addString(const ConstString& s);

				/**
				 * Inserts a string eValue at the end of the eBottle,
				 * making first a copy local memory
				 * 
				 * \param[in] s A pointer to the null terminated char array to insert
				 */
				void addString(const char * s);

				/**
				 * Reserves the memory for inserting a list at the end of the eBottle
				 * 
				 * \return A reference to the empty list inserted in the eBottle 
				 */
				eBottle & addList();

				/**
				 * Reserves the memory for inserting a list at the end of the eBottle
				 * 
				 * \return A pointer to the empty list inserted in the eBottle 
				 */
				eBottle * addListPtr();

				/**
				 * Inserts a copy of an eValue into the eBottle at a given position
				 * 
				 * \param[in] p A pointer to the eValue to insert
				 * \param[in] i The position where the eValue will be inserted
				 */
				void insert(const eValue* p, const unsigned int i);

				/**
				 * Inserts all the values inside a given eBottle at the end of the eBottle.
				 * The given eBottle is not inserted as a nested eBottle.
				 * 
				 * \param[in] yb The eBottle whose eValues will be appended
				 */
				void append(const eBottle & yb);

				/**
				 * Removes the eValue at a certain position
				 * 
				 * \param[in] i The position of the eValue to remove
				 */
				void remove(const unsigned int i);

				/**
				 * Access to the eBottle size
				 * 
				 * \return The amount of eValues inside the eBottle (nested eBottles are considered as one eValue)
				 */
				unsigned int count() const;

				/**
				 * Access to the eBottle size
				 * 
				 * \return The amount of eValues inside the eBottle (nested eBottles are considered as one eValue)
				 */
				unsigned int size() const;

				/**
				 * Access to the eBottle contents
				 * 
				 * \param[in] i A position inside the eBottle
				 * \return The eValue at the \p i position
				 */
				eValue & operator[](const unsigned int i);

				/**
				 * Access to the eBottle contents
				 * 
				 * \param[in] i A position inside the eBottle
				 * \return The eValue at the \p i position
				 */
				eValue & operator[](const unsigned int i) const;

				/**
				 * Access to the eBottle contents
				 * 
				 * \param[in] i A position inside the eBottle
				 * \return The eValue at the \p i position
				 */
				eValue & get(const unsigned int i);

				/**
				 * Access to the eBottle contents
				 * 
				 * \param[in] i A position inside the eBottle
				 * \return The eValue at the \p i position
				 */
				eValue & get(const unsigned int i) const;

				/**
				 * Access to the eBottle contents
				 * 
				 * \param[in] i A position inside the eBottle
				 * \return A constant pointer to the eValue at the \p i position
				 */
				eValue * getPtr(const unsigned int i) const;

				/**
				 * Access to the eBottle contents
				 * 
				 * \param[in] i A position inside the eBottle
				 * \return A pointer to the eValue at the \p i position
				 */
				eValue * getPtr(const unsigned int i);

				/**
				 * Builds a string that represents all the contents of the eBottle
				 * 
				 * \return The string representing the eBottle
				 */
				std::string toString() const;

				/**
				 * Builds an eBottle from its string representation
				 * 
				 * \param[in] s A pointer to a null terminated char array 
				 * representing an eBottle
				 */
				void fromString(const char * s);

				/**
				 * Builds an eBottle from its string representation
				 * 
				 * \param[in] s The string representing the eBottle
				 */
				void fromString(const std::string& s);

				/**
				 * Builds an eBottle from its string representation
				 * 
				 * \param[in] s The string representing the eBottle
				 */
				void fromString(const ConstString& s);

				/**
				 * Builds an eBottle from its binary representation
				 * 
				 * \param[in] p A pointer to the byte array with the binary representation
				 * \param[in] size The size of the binary representation in bytes
				 */
				void fromBinary(const char * p, const int size);

				/**
				 * Creates a binary representation of the eBottle
				 * 
				 * \param[out] size The size of the binary representation in bytes
				 * \return A constant pointer owned by the eBottle to the binary representation
				 */
				const char * const toBinary(int *size) const;

				/**
				 * Creates a binary representation of the eBottle
				 * 
				 * \param[out] p A pointer to a zone of memory owned by the 
				 * caller which is big enough to receive a copy of the binary 
				 * representation of the eBottle. The size of the binary 
				 * representation can be computed using eBottle::getBinarySize method.
				 *				   				 
				 */
				void toBinary(char * p) const;

				/**
				 * Computes the size of the binary representation of the eBottle
				 * 
				 * \return The size in bytes of the binary representation of th eBottle.
				 * 
				 * \sa toBinary
				 */
				unsigned int getBinarySize() const;

				/**
				 * This function is inherited from <a href='http://eris.liralab.it/yarp/specs/dox/user/html/d4/d41/classyarp_1_1os_1_1Portable.html'>Portable interface</a>
				 * and is used in data transmission.
				 */
				virtual bool read(ConnectionReader& connection);

				/**
				 * This function is inherited from <a href='http://eris.liralab.it/yarp/specs/dox/user/html/d4/d41/classyarp_1_1os_1_1Portable.html'>Portable interface</a>
				 * and is used in data transmission.
				 */
				virtual bool write(ConnectionWriter& connection);

			protected:
				std::vector< eValue *> values;
				unsigned int global_size;
				mutable char * toBinaryPointer;

				// private methods
				void fillString(std::ostringstream * s, const eBottle *b) const;
				void fill(const eBottle * b, int &s, char * p = NULL) const;
				void reconstruct(eBottle * b, int & s, char * p) const;
				void fromStr(eBottle *b, const char * s2) const;

				// for debug only 
				std::string content() const;
		};

	}
}

#endif /*YARPBOTTLE_H_*/
