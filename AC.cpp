/*******************************************************************
*
*  DESCRIPTION: Atomic Model for Access Control (AC)
*
*  AUTHOR: Rachid Chreyh 
*
*  EMAIL: rchreyh@connect.carleton.ca
*
*  DATE: 9/10/2005
*
*******************************************************************/

/** include files **/
#include "AC.h"      // class Access Control
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: AC
* Description: 
********************************************************************/
AC::AC( const string &name )
: Atomic( name )
, Id( addInputPort( "Id" ) )
, MaxValidId( addInputPort( "MaxValidId" ) )
, Rand( addOutputPort( "Rand" ) )
, SRES_1( addOutputPort( "SRES_1" ) )
{

	try
	{
		dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );

		MASSERT( dist );

		for ( register int i = 0 ; i < dist->varCount() ; i++ )
		{
			string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar(i) ) ) ;
			dist->setVar( i, str2float( parameter ) ) ;
		}
	} catch( InvalidDistribution &e )
	{
		e.addText( "The model " + description() + " has distribution problems!" ) ;
		e.print(cerr);
		MTHROW( e ) ;
	} catch( MException &e )
	{
		MTHROW( e ) ;
	}

}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &AC::initFunction()
{
	this-> passivate();
	IdNum = 0;
	MaxValidIdNum = -1; 
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &AC::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == Id ) 
	{
		IdNum = static_cast < int > (msg.value());
		
		RandNum = fabs( this->distribution().get() ); 
		if (IdNum <= MaxValidIdNum)
			SRES1_Num = RandNum + IdNum;
		else
			SRES1_Num = 0;
		
		holdIn( active, Time::Zero );
	}
	else if( msg.port() == MaxValidId )
	{
		MaxValidIdNum = static_cast < int > (msg.value());
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &AC::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &AC::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), Rand, RandNum) ;
	sendOutput( msg.time(), SRES_1, SRES1_Num) ;
	return *this ;
}
