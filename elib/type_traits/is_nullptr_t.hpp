/* 
 * Copyright (C) 2013  Eric Fiselier
 * 
 * This file is part of elib.
 *
 * elib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * elib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with elib.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ELIB_TYPE_TRAITS_IS_NULLPTR_T_HPP
#define ELIB_TYPE_TRAITS_IS_NULLPTR_T_HPP

#include <elib/type_traits/integral_constant.hpp>
#include <elib/type_traits/remove_cv.hpp>

#include <cstddef>

namespace elib {
namespace type_traits {
namespace detail {

    
template <typename T>
struct is_nullptr_t : public false_type
{ };

template <>
struct is_nullptr_t<std::nullptr_t> : public true_type
{ };


} /* namespace detail */


template <typename T>
struct is_nullptr_t : public detail::is_nullptr_t<typename remove_cv<T>::type>
{ };


} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_NULLPTR_T_HPP */