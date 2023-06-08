/*******************************************************************
*
*  DESCRIPTION: Atomic Model for Mobile Switching Center (MSC)
*
*  AUTHOR: Rachid Chreyh 
*
*  EMAIL: rchreyh@connect.carleton.ca
*
*  DATE: 9/10/2005
*
*******************************************************************/

/** include files **/
#include "MSC.h"      // class Mobile Switching Center
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: MSC
* Description: 
********************************************************************/
MSC::MSC( const string &name )
: Atomic( name )
, SRES_1( addInputPort( "SRES_1" ) )
, SRES_2( addInputPort( "SRES_2" ) )
, Ok( addOutputPort( "Ok" ) )
{
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &MSC::initFunction()
{
	this-> passivate();
    Num_Inputs = 0;

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &MSC::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == SRES_1 ) 
	{
		SRES1_Num = static_cast < int > (msg.value());
		if (Num_Inputs == 0)
		{
			Num_Inputs++;
		}
		else
		{
			OkValue = 0;
			holdIn( active, Time::Zero );
		}
	}
	else if( msg.port() == SRES_2 )
	{
		SRES2_Num = static_cast < int > (msg.value());
		if (Num_Inputs != 0)
		{
			OkValue = (SRES2_Num == SRES1_Num);
			Num_Inputs = 0;
			holdIn( active, Time::Zero );
		}
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &MSC::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &MSC::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), Ok, OkValue) ;
	return *this ;
}
