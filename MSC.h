/*******************************************************************
*
*  DESCRIPTION: Atomic Model for the Mobile Switching Center (MSC)
*
*  AUTHOR: Rachid Chreyh 
*
*  EMAIL: rchreyh@connect.carleton.ca  
*
*  DATE: 9/10/2005
*
*******************************************************************/

#ifndef __MSC_H
#define __MSC_H

//#include <list>
#include "atomic.h"     // class Atomic

class MSC : public Atomic
{
public:
	MSC( const string &name = "Mobile_Switching_Center" );	//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
    Port &SRES_1;
	Port &SRES_2;
	Port &Ok;
	int  Num_Inputs;
	int  SRES1_Num;
	int  SRES2_Num;
	bool OkValue;

};	// class MSC

// ** inline ** // 
inline
string MSC::className() const
{
	return "Mobile_Switching_Center" ;
}

#endif   //__MSC_H
