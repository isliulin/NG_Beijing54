
#include "CellDescBase.h"
#include "MacroDef.h"

float CellDescBase::GetCenterFreqMHz()
{
 float center=0;
 switch(m_netType)
 {
   case GSM: //2g
       /*if(m_channelNo>=1&&m_channelNo<=124)
	   {
		   center= 890+m_channelNo*0.2+45; //gsm 900
	   }
	   else if(m_channelNo>=512&&m_channelNo<=885)
	   {
		   center=1710.2+(m_channelNo-512)*0.2+95;//gsm 1800
	   }
	   else
	   {
		   center=900;
	   }*/
	   center = m_frequency;
	 	break;
   case UMTS://3g
       	// center=(float)m_channelNo/5;
		center = m_frequency;
		break;
   case LTE://4g
	   /*{
   	    //center=(float)m_channelNo/5;
   	    float fDLLow=1900;
		int NoffsetDL=36000;
   	    if(m_channelNo>=36000&&m_channelNo<=36199)
   	    {
          fDLLow=1900;
		  NoffsetDL=36000;
   	    }
		else if(m_channelNo>=36200&&m_channelNo<=36349)
		{
          fDLLow=2010;
		  NoffsetDL=36200;
		}
		else if(m_channelNo>=36350&&m_channelNo<=36949)
		{
           fDLLow=1850;
		  NoffsetDL=36350;
		}
		else if(m_channelNo>=36950&&m_channelNo<=37549)
		{
          fDLLow=1930;
		  NoffsetDL=36950;
		}
		else if(m_channelNo>=37550&&m_channelNo<=37749)
		{
           fDLLow=1910;
		  NoffsetDL=37550;
		}
		else if(m_channelNo>=37750&&m_channelNo<=38249)
		{
          fDLLow=2570;
		  NoffsetDL=37750;
		}
		else if(m_channelNo>=38250&&m_channelNo<=38649)
		{
		  fDLLow=1880;
		  NoffsetDL=38250;

		}
		else if(m_channelNo>=38650&&m_channelNo<=39649)
		{
            fDLLow=2300;
		    NoffsetDL=38650;
		}
		else if(m_channelNo>=39650&&m_channelNo<=41589)
		{
		   fDLLow=2496;
		  NoffsetDL=39650;
		}
        else if(m_channelNo>=41590&&m_channelNo<=43589)
		{
          fDLLow=3400;
		  NoffsetDL=41590;
		}
		else if(m_channelNo>=43590&&m_channelNo<=45589)
		{
          fDLLow=3600;
		  NoffsetDL=43590;
		}
		else if(m_channelNo>=45590&&m_channelNo<=46589)
		{
		  fDLLow=703;
		  NoffsetDL=45590;
		}
        else
        {
          return 2000;
        }

		center=fDLLow+0.1*(m_channelNo-NoffsetDL);
	   } */
	    center = m_frequency;
		break;
   case STATION_5G:
	   center=m_frequency;
	   break;
   case DTV:
	   center=m_frequency;
	   break;
   case WIFI:
	   center = m_frequency;
	   break;
   default:
	   break;
 }

 return center;

}


