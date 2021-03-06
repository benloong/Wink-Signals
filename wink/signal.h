///
/// Wink Signals
/// Copyright (C) 2012 Anax Creations. All rights reserved.
///
///
/// This software is provided 'as-is', without any express or implied warranty.
/// In no event will the authors be held liable for any damages arising from the
/// use of this software.
///
/// Permission is hereby granted, free of charge, to any person
/// obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// 1. The origin of this software must not be misrepresented;
///    you must not claim that you wrote the original software.
///    If you use this software in a product, an acknowledgment
///    in the product documentation would be appreciated but is not required.
///
/// 2. Altered source versions must be plainly marked as such,
///	   and must not be misrepresented as being the original software.
///
/// 3. The above copyright notice and this permission notice shall be included in
///    all copies or substantial portions of the Software.
///

#ifndef __WINK_SIGNAL_H__
#define __WINK_SIGNAL_H__

#include <vector>

#include "slot.h"

namespace wink
{
	template <class Slot>
	struct signal
	{
	private:
		
		typedef signal<Slot> __this_type;
		
	public:
		
		typedef Slot slot_type;
				
		/// Connects a slot to the signal
		/// \param slot The slot you wish to connect
		/// \see bind To bind a slot to a function
		void connect(const slot_type& slot)
		{
			_slots.push_back(slot);
		}
		
		/// Disconnects a slot from the signal
		/// \param slot The slot you wish to disconnect
		/// \see bind To bind a slot to a function
		void disconnect(const slot_type& slot)
		{
			_slots.erase(std::find(_slots.begin(), _slots.end(), slot));
		}
		
		/// Emits the events you wish to send to the call-backs
		/// \param args The arguments to emit to the slots connected to the signal
		template <class ...Args>
		void emit(Args&&... args) const
		{
			for(typename __slot_array::const_iterator i = _slots.begin(); i != _slots.end(); ++i)
			{
				(*i)(args...);
			}
		}
		
		/// Emits events you wish to send to call-backs
		/// \param args The arguments to emit to the slots connected to the signal
		/// \note
		/// This is equvialent to emit.
		template <class ...Args>
		void operator()(Args&&... args) const
		{
			emit(args...);
		}
		
		// comparision operators for sorting and comparing
		
		bool operator==(const __this_type& signal) const
		{ return _slots == signal._slots; }
		
		bool operator!=(const __this_type& signal) const
		{ return !operator==(signal); }
		
	private:
		
		/// defines an array of slots
		typedef std::vector<slot_type> __slot_array;
		
		/// The slots connected to the signal
		__slot_array _slots;
	};
}

#endif // __WINK_SIGNAL_H__