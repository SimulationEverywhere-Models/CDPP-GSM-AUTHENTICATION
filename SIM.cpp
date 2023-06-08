/*******************************************************************
*
*  DESCRIPTION: Atomic Model for SIM Card (SIM)
*
*  AUTHOR: Rachid Chreyh 
*
*  EMAIL: rchreyh@connect.carleton.ca
*
*  DATE: 15/10/2005
*
*******************************************************************/

/** include files **/
#include "SIM.h"      // class Access Control
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: SIM
* Description: 
********************************************************************/
SIM::SIM( const string &name )
: Atomic( name )
, On( addInputPort( "On" ) )
, Rand( addInputPort( "Rand" ) )
, Id( addOutputPort( "Id" ) )
, SRES_2( addOutputPort( "SRES_2" ) )
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;

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
Model &SIM::initFunction()
{
	this-> passivate();
	IdNum = 0;
	Authenticating = false; 
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &SIM::externalFunction( const ExternalMessage &msg )
{
	if (this->state() == passive)
	{
		if (( msg.port() == On ) && 
			(!Authenticating))
		{
			IdNum =  static_cast < int > (msg.value()); //fabs( dist->get() );
  
			holdIn( active, preparationTime );

		}
		else if  (( msg.port() == Rand ) && 
			      (Authenticating))
		{
			RandNum = static_cast < int > (msg.value());
			SRES2_Num = RandNum + IdNum;

			holdIn( active, preparationTime ); 
		}
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &SIM::internalFunction( const InternalMessage & )
{
	Authenticating = !Authenticating;
		
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &SIM::outputFunction( const InternalMessage &msg )
{
	if (!Authenticating) 
		sendOutput( msg.time(), Id, IdNum) ;
	else
		sendOutput( msg.time(), SRES_2, SRES2_Num) ;
	return *this ;
}
