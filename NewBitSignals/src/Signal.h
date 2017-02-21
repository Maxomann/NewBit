#pragma once
#include "stdafx.h"
#include "Trackable.h"

namespace nb
{
	template <class R, class... Args>
	class Signal
	{
		std::vector<std::function<R( Args... )>> m_slots;
		std::vector<std::pair<std::function<R( Args... )>, std::weak_ptr<bool>>> m_trackedSlots;

	public:
		// slot must be callable
		// for member functions see below or use std::bind()
		void connect( std::function < R( Args... ) > slot )
		{
			m_slots.push_back( std::move( slot ) );
		};

		// binds args to slot
		template <class T>
		void connect_mem_fn_auto( R( __thiscall T::* slot )(Args...),
								  T& instance )
		{
			std::function<R( T&, Args... )> func = slot;

			m_slots.push_back( easy_bind( func, std::ref( instance ) ) );
		};

		// slot must be callable
		// will remove connection when foo gets destroyed
		void connect_track( std::function < R( Args... ) > slot,
							const Trackable& foo )
		{
			m_trackedSlots.push_back( std::make_pair( std::move( slot ),
													  foo.getTrackablePtr() ) );
		};

		// binds foo to slot
		// foo needs to be a child of nb::Trackable
		// will remove connection when foo gets destroyed
		template<class T>
		void connect_mem_fn_auto_track( R( __thiscall T::* slot )(Args...),
										T& instance )
		{
			std::function<R( T&, Args... )> func = slot;

			m_trackedSlots.push_back( std::make_pair( std::move( easy_bind( func, std::ref( instance ) ) ),
													  instance.getTrackablePtr() ) );
		};

		void call( Args&... args )
		{
			for (auto& func : m_slots)
			{
				//call
				func( args... );
			}

			m_trackedSlots.erase( std::remove_if( m_trackedSlots.begin(), m_trackedSlots.end(), [&]( std::pair<std::function<R( Args... )>, std::weak_ptr<bool>>& el ) {
				if (!el.second.expired())
					return true;

				//call
				el.first( args... );
				return false;
			} ), m_trackedSlots.end() );
		}
	};
}
