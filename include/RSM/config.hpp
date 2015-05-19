/*
 * Copyright (C) - Jean-Sébastien Fauteux 2015
 * This work is licensed under the Creative Commons Attribution 4.0 International License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by/4.0/ 
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 */

#pragma once

#if (defined(_WIN32) || defined(__WIN32__)) && !defined(RSM_STATIC)

	//Export Library (DLL Side)
	#ifdef RSM_EXPORTS
		#define RSM_API __declspec(dllexport)
	//Import Library (Dev Side)
	#else
		#define RSM_API __declspec(dllimport)
	#endif // ORA_EXPORTS

	#ifdef _MSC_VER
		#pragma warning(disable: 4251)
		#pragma warning(disable: 4396) //Deactivates warning for inline of friend function
	#endif // _MSV_VER

//No DLL for other platform
#else
	#define RSM_API
#endif
