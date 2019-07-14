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
 *  @file         XercesWrapper.h
 *  @version      0.1
 *  @author       Marcin Malczewski
 *  @department   Com SDC NA B3
 *  @mail         marcin.malczewski_ext@siemens.com
 *  @date         22.2.2006
 *
 *  @brief        XercesWrapper includes.
 *
 *************************************************************/

#ifndef INCLUDED_XERCESWRAPPER_H
#define INCLUDED_XERCESWRAPPER_H

#if defined(XERCESWRAPPER_LIB)|| defined(_LIB)
	#define XML_API
#else
	#if defined(_WIN32) || defined(__WIN32__)
		#ifdef XERCESWRAPPER_EXPORTS
			#define XML_API __declspec(dllexport)
		#else
			#define XML_API __declspec(dllimport)
		#endif 
	#else 
		#if defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
			#define XML_API __attribute__ ((visibility("default")))
		#else
			#define XML_API
		#endif	// __GNUC__		
	#endif		// WIN32 / !WIN32
#endif

// local includes
#include "XMLDocument.h"
#include "XMLNode.h"
#include "XMLValue.h"
#include "XMLDataException.h"
#include "XMLDefs.h"

#endif