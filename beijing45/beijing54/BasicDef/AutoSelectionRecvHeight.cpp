
#include "AutoSelectionRecvHeight.h"

double GetAutoRecvHeight(double OldRecvHeight,double FreqMHz,ETransModel ModelID)
{

 if(OldRecvHeight!=-1)
 {
    return  OldRecvHeight;
 }

 if(ModelID==eAeroNautical)
 {
     return 20;
 }
 
 if(FreqMHz>=88&&FreqMHz<=108)
 {
    return 10;

 }

 return 1.5;



}












