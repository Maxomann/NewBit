#pragma once
#include "stdafx.h"
#include "Connection.h"

namespace nb
{
	template <class T>
	class Signal;

	template< class RetVal, class ... Args >
	class Signal<RetVal( Args... )>
	{
		std::shared_ptr<bool> m_trackablePtr;
		std::vector<std::pair<std::weak_ptr<bool>, std::function<RetVal( Args... )>>> m_connectionTracker;

		void removeInvalidConnections()
		{
			m_connectionTracker.erase( std::remove_if( m_connectionTracker.begin(),
													   m_connectionTracker.end(),
													   []( const auto& el ) {
				return el.first.expired();
			} ), m_connectionTracker.end() );
		}

	public:
		Signal()
			: m_trackablePtr( std::make_shared<bool>( true ) )
		{}

		Signal( const Signal& ) = delete;
		Signal( Signal&& ) = default;

		Connection connect( std::function<RetVal( Args... )> func )
		{
			Connection con( m_trackablePtr );

			auto toEmplace =
				std::make_pair<std::weak_ptr<bool>,
				std::function<RetVal( Args... )>>(con.getTrackablePtr(),
												   std::move( func ));

			m_connectionTracker.emplace_back( move( toEmplace ) );

			return con;
		}

		template < class T >
		Connection connect( T* obj, RetVal( T::* mem_fn_ptr )(Args...) )
		{
			return connect( [=]( Args... args ) -> decltype(mem_fn_ptr( obj, args... )) {return mem_fn_ptr( obj, args... )} );
		}

		void call( Args& ... args )
		{
			removeInvalidConnections();

			for (const auto& con : m_connectionTracker)
			{
				con.second( args ... );
			}
		}

		Signal& operator=( const Signal& ) = delete;
		Signal& operator=( Signal&& ) = default;
	};
}
