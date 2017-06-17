/*
* Copyright (c) 2017 Jean-Sébastien Fauteux
*
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the authors be held liable for any damages arising from
* the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it freely,
* subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not claim
*    that you wrote the original software. If you use this software in a product,
*    an acknowledgment in the product documentation would be appreciated but is
*    not required.
*
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

#pragma once

#include <memory>

namespace rsm {

	////////////////////////////////////////////////////////////
	/// \brief Templated generic container class
	///		   
	/// This class ensure type-erasure and allows to store any kind of data.
	/// Useful for storing different kind of data in a generic way
	////////////////////////////////////////////////////////////
	class Any {
	public:
		////////////////////////////////////////////////////////////
		/// \brief Constructor
		///
		/// Construct an empty Any
		////////////////////////////////////////////////////////////
		Any()
			: m_holder(nullptr) {}

		////////////////////////////////////////////////////////////
		/// \brief Templated Constructor
		///
		/// Construct the Any object with the given data
		///
		/// \param data Data to store
		////////////////////////////////////////////////////////////
		template<class Type>
		Any(const Type& data)
			: m_holder(std::make_unique<Impl<Type>>(data)) {}

		////////////////////////////////////////////////////////////
		/// \brief Copy Constructor
		///
		/// Construct the Any object with the content of the other Any object
		///
		/// \param other The Any object to copy construct from
		////////////////////////////////////////////////////////////
		Any(const Any& other)
			: m_holder(other.m_holder ? other.m_holder->copy() : nullptr) {}

		////////////////////////////////////////////////////////////
		/// \brief Templated copy assignment
		///
		/// Copy assign the templated data in the Any object for storage
		///
		/// \param data Templated data to copy
		///
		/// \return Reference to this Any object
		////////////////////////////////////////////////////////////
		template<class Type>
		Any& operator=(const Type& data) {
			Any(data).swap(*this);
			return *this;
		}

		////////////////////////////////////////////////////////////
		/// \brief Copy assignment
		///
		/// Copy assign the stored data in the Any object for storage
		///
		/// \param other Any object to copy from
		///
		/// \return Reference to this Any object
		////////////////////////////////////////////////////////////
		Any& operator=(Any other) {
			Any(other).swap(*this);
			return *this;
		}

		////////////////////////////////////////////////////////////
		/// \brief Move constructor
		///
		/// Construct the Any object from the passed Any object
		/// The passed Any object will be invalidated after construction
		///
		/// \param other Any object to move contruct from
		////////////////////////////////////////////////////////////
		Any(Any&& other)
			: m_holder(std::move(other.m_holder))
		{
			other.m_holder.reset();
		}

		////////////////////////////////////////////////////////////
		/// \brief Templated move assignment
		///
		/// Move assign the templated data in the Any object for storage
		///
		/// \param data Templated data to move from
		///
		/// \return Reference to this Any object
		////////////////////////////////////////////////////////////
		template<class Type>
		Any& operator=(Type&& data) {
			Any(data).swap(*this);
			return *this;
		}

		////////////////////////////////////////////////////////////
		/// \brief Move assignment
		///
		/// Move assign the stored data in the Any object for storage
		/// The passed Any object will be invalidated after assignment
		///
		/// \param other Any object to move data from
		///
		/// \return Reference to this Any object
		////////////////////////////////////////////////////////////
		Any& operator=(Any&& other) {
			other.swap(*this);
			Any().swap(other);
			return *this;
		}

		///////////////////////////////////////////////////////////
		/// \brief Destructor
		////////////////////////////////////////////////////////////
		~Any() {}

		///////////////////////////////////////////////////////////
		/// \brief Validity of the object
		///
		/// Return if the object contains data or not
		///
		/// \return True if the object is valid, false otherwise
		////////////////////////////////////////////////////////////
		bool isValid() const {
			return m_holder != nullptr;
		}

		///////////////////////////////////////////////////////////
		/// \brief Reference to the stored content
		///
		/// Returns a reference to the content stored in the object
		/// This is done through a templated cast
		/// Note: Giving a wrong template will result in undefined behavior
		///
		/// \return Reference to the content
		////////////////////////////////////////////////////////////
		template<class Type>
		Type& get() const {
			return reinterpret_cast<Impl<Type>*>(m_holder.get())->val;
		}

	private:
		Any& swap(Any& other) {
			std::swap(m_holder, other.m_holder);
			return *this;
		}

		struct Holder {
			virtual ~Holder() {}
			virtual Holder* copy() = 0;
		};

		template<class Type>
		struct Impl : Holder {
			Impl(const Type& t)
				: val(t) {}

			Holder* copy() {
				return new Impl(val);
			}

			Type val;
		};

		std::unique_ptr<Holder> m_holder;
	};

}