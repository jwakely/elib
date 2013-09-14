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
#ifndef ELIB_TYPE_TRAITS_REMOVE_CV_HPP
#define ELIB_TYPE_TRAITS_REMOVE_CV_HPP

#include <elib/type_traits/remove_const.hpp>
#include <elib/type_traits/remove_volatile.hpp>

namespace elib {
namespace type_traits {

        
template <typename T>
struct remove_cv : public remove_const<typename remove_volatile<T>::type>
{ };
        
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_REMOVE_CV_HPP */