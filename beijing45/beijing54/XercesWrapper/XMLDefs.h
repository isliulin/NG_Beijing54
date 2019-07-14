/**
 * <!--
 *  Copyright (C) Siemens AG 2006. All Rights Reserved. Confidential.
 *
 *  Distribution only to people who need to know this information in
 *  order to do their job.(Need-to-know principle).
 *  Distribution to persons outside the company, only if these persons
 *  signed a non-disclosure agreement.
 *  Electronic transmission, e.g. via electronic mail, must be made in
 *  encrypted form.
 *  -->
 *  @file         XMLDefs.h
 *  @version      0.1
 *  @author       Marcin Malczewski
 *  @department   Com SDC NA B3
 *  @mail         marcin.malczewski_ext@siemens.com
 *  @date         5.5.2006
 *
 *  @brief        XMLDefs includes.
 *
 *************************************************************/

#ifndef INCLUDED_XMLDEFS_H
#define INCLUDED_XMLDEFS_H


#define USE_LOG 0
#include <iostream>
#if USE_LOG
#define XMLLOGOUT(x) {std::cout<<x<<std::endl;}
#else
#define XMLLOGOUT(x)
#endif

#endif