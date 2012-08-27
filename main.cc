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

using namespace std;
using namespace yarp;
using namespace yarp::os;

int main(){
	eBottle eb1("1 2 3 4 (5 6.2 7 8 {64 5 6 7} Hello)(World 1 2 3    ) { 4 5 6 7 87} (5 6 3.2) 1 2 4 {5 6 7} (3 4 5) 1");
	fprintf(stderr,"TOSTRING: eb1: %s\n",eb1.toString().c_str());
	int size;
	const char * p=eb1.toBinary(&size);	
		
	eBottle eb2;
	eb2.fromBinary(p,size);
	fprintf(stderr,"TOSTRING: eb2: %s\n",eb2.toString().c_str());
	
	int eb1_size=eb1.getBinarySize();
	char * buff=new char[eb1_size];
	eb1.toBinary(buff);
	
	eBottle eb3;
	eb3.fromBinary(buff,eb1_size);
	fprintf(stderr,"TOSTRING: eb3: %s\n",eb3.toString().c_str());
		
	Network::init();
	BufferedPort<eBottle> bp1;
	BufferedPort<eBottle> bp2;
	bp1.open("/out");
	bp2.open("/in");
	Network::connect("/out","/in");
	
	eBottle &eb4=bp1.prepare();
	eb4=eb1;
	fprintf(stderr,"TOSTRING: eb4: %s\n",eb4.toString().c_str());
	bp1.write();
	eBottle * eb5= bp2.read();
	fprintf(stderr,"TOSTRING: eb5: %s\n",eb5->toString().c_str());
}
