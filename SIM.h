/*******************************************************************
*
*  DESCRIPTION: Atomic Model for the SIM Card (SIM)
*
*  AUTHOR: Rachid Chreyh 
*
*  EMAIL: rchreyh@connect.carleton.ca  
*
*  DATE: 15/10/2005
*
*******************************************************************/

#ifndef __SIM_H
#define __SIM_H

//#include <list>
#include "atomic.h"     // class Atomic
#include "distri.h"        // class Distribution
class SIM : public Atomic
{
public:
	SIM( const string &name = "SIM_CARD" );	//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
    Port &Id;
	Port &On;
	Port &Rand;
	Port &SRES_2;
	bool Authenticating;
	int  IdNum;
	int  RandNum;
	int  SRES2_Num;
	Time  preparationTime;
	Distribution *dist;

};	// class SIM

// ** inline ** // 
inline
string SIM::className() const
{
	return "SIM_CARD" ;
}

#endif   //__SIM_H
