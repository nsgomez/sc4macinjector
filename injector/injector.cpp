/*
 *  injector.cpp
 *  injector
 *
 *  Created by Nelson Gomez on 12/23/17.
 *  Copyright © 2017 Nelson Gomez. All rights reserved.
 *
 */

#include <iostream>
#include "injector.hpp"
#include "injectorPriv.hpp"

void injector::HelloWorld(const char * s)
{
	 injectorPriv *theObj = new injectorPriv;
	 theObj->HelloWorldPriv(s);
	 delete theObj;
};

void injectorPriv::HelloWorldPriv(const char * s) 
{
	std::cout << s << std::endl;
};

