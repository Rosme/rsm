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

	class Any {
	public:
		Any()
			: m_holder(nullptr) {}

		template<class Type>
		Any(const Type& data)
			: m_holder(std::make_unique<Impl<Type>>(data)) {}

		Any(const Any& other)
			: m_holder(other.m_holder ? other.m_holder->copy() : nullptr) {}

		template<class Type>
		Any& operator=(const Type& other) {
			Any(other).swap(*this);
			return *this;
		}

		Any& operator=(Any other) {
			Any(other).swap(*this);
			return *this;
		}

		Any(Any&& other)
			: m_holder(std::move(other.m_holder))
		{
			other.m_holder.reset();
		}

		template<class Type>
		Any& operator=(Type&& data) {
			Any(data).swap(*this);
			return *this;
		}

		Any& operator=(Any&& other) {
			other.swap(*this);
			Any().swap(other);
			return *this;
		}

		~Any() {}

		bool isValid() const {
			return m_holder != nullptr;
		}

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