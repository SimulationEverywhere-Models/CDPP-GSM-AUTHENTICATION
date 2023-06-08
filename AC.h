/*******************************************************************
*
*  DESCRIPTION: Atomic Model for the Access Control (AC)
*
*  AUTHOR: Rachid Chreyh 
*
*  EMAIL: rchreyh@connect.carleton.ca  
*
*  DATE: 9/10/2005
*
*******************************************************************/

#ifndef __AC_H
#define __AC_H

//#include <list>
#include "atomic.h"     // class Atomic
#include "distri.h"        // class Distribution
class AC : public Atomic
{
public:
	AC( const string &name = "Access_Control" );	//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
    Port &Id;
	Port &MaxValidId;
	Port &Rand;
	Port &SRES_1;
	int  MaxValidIdNum;
	int  IdNum;
	int  RandNum;
	int  SRES1_Num;
	Distribution *dist;
	Distribution &distribution()
		{return *dist;}

};	// class AC

// ** inline ** // 
inline
string AC::className() const
{
	return "Access_Control" ;
}

#endif   //__AC_H
