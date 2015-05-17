/*
* Copyright (C) - Jean-Sébastien Fauteux 2015
* This work is licensed under the Creative Commons Attribution 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by/4.0/
* or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#pragma once

#include <RSM/config.hpp>

namespace Eve {

	////////////////////////////////////////////////////////////
	/// \brief NonCopyable class from which class that should be not copyable will inherit
	///
	////////////////////////////////////////////////////////////
	class RSM_API NonCopyable {
	protected:
		////////////////////////////////////////////////////////////
		/// \brief Default Constructor
		///
		/// We must explicitly declare a default constructor because
		/// of the copy constructor.
		///
		////////////////////////////////////////////////////////////
		NonCopyable(){}
	private:
		//Private copy constructor and assignment operator. No copy.
		NonCopyable(const NonCopyable&);
		NonCopyable& operator=(const NonCopyable&);
	};

}