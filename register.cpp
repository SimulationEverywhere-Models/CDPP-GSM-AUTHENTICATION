/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Rujun Hu
*
*  STUDENT#: 258902
*
*  EMAIL: rujun_hu@yahoo.ca
*
*  DATE: 16/10/2001
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "AC.h"        // class AC
#include "MSC.h"        // class MSC
#include "SIM.h"        // class SIM

void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<SIM>(), "SIMCard" ) ; 
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<MSC>(), "MobileSwitchingCenter" ) ; 
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<AC>(), "AccessControl" ) ;
} 

