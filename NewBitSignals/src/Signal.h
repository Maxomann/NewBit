#pragma once
#include "stdafx.h"
#include "Trackable.h"

namespace nb
{
	template <class R, class ... Args>
	class Signal
	{
		std::vector<std::function<R( Args... )>> m_slots;
		std::vector<std::pair<std::function<R( Args... )>, std::weak_ptr<bool>>> m_trackedSlots;

	public:
		// slot needs to be callable
		// for member functions see below or use std::bind()
		void connect( std::function < R( Args... > slot )
		{
			m_slots.push_back( std::move( slot ) );
		};

		// binds args to slot
		// example usage: Signal.connect(std::mem_fn(&Foo::bar), foo))
		template <class ... BindArgs>
		void connect( std::function < R( Args... > slot, BindArgs&&... args )
		{
			m_slots.push_back( easy_bind( slot, args... ) );
		};

		// slot needs to be callable
		// will remove connection when foo gets destroyed
		// example usage: Signal.connect(std::bind(std::mem_fn(&Foo::bar), &foo), foo)
		template<class T>
		void connect_track( std::function < R( Args... > slot,
											   const Trackable& foo )
		{
			m_trackedSlots.push_back( std::make_pair( std::move( slot ),
													  foo.getTrackablePtr() ) );
		};

		// binds foo to slot
		// foo needs to be a child of nb::Trackable
		// will remove connection when foo gets destroyed
		// example usage: Signal.connect(std::mem_fn(&Foo::bar), foo))
		template<class T>
		void connect_track_auto( std::function < R( Args... > slot,
													const T& foo )
		{
			m_trackedSlots.push_back( std::make_pair( std::move( easy_bind( slot, foo ) ),
													  foo.getTrackablePtr() ) );
		};

		template<class ... PassArgs>
		void call( PassArgs&&... args )
		{
			for( auto& func : m_slots )
			{
				//call
				func( args... );
			}

			m_trackedSlots.erase( std::remove( m_trackedSlots.begin(), m_trackedSlots.end(), [&] ( std::pair<std::function<R( Args... )>, std::weak_ptr<bool>>& el ){
				if( !el.second.expired() )
				{
					//call
					el.first( args... );
					return false;
				}
				else
					return true;
			} ), m_trackedSlots.end() );
		}
	};
}
