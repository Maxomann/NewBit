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
		struct Callback
		{
			std::optional<std::weak_ptr<bool>> optionalTrackingPtr;
			std::function<RetVal( Args... )> func;
		};

		std::shared_ptr<bool> m_trackablePtr;
		std::vector<Callback> m_callbacks;

		void removeInvalidConnections()
		{
			m_callbacks.erase( std::remove_if( m_callbacks.begin(),
											   m_callbacks.end(),
											   [] ( const Callback& el ){
				if( el.optionalTrackingPtr.has_value() )
					return el.optionalTrackingPtr->expired();
				else
					return false;
			} ), m_callbacks.end() );
		}

	public:
		Signal()
			: m_trackablePtr( std::make_shared<bool>( true ) )
		{}

		Signal( const Signal& ) = delete;
		Signal( Signal&& ) = default;

		void connect( std::function<RetVal( Args... )> func )
		{
			Callback cb;
			cb.func = std::move( func );

			m_callbacks.emplace_back( std::move( cb ) );
		}

		template < class T >
		void connect( T* obj, RetVal( T::* mem_fn_ptr )( Args... ) )
		{
			connect( [=] ( Args... args ) -> RetVal{ return ( obj->*mem_fn_ptr )( args... ); } );
		}

		void connect_track( Connections& connections, std::function<RetVal( Args... )> func )
		{
			Connection con( m_trackablePtr );

			Callback cb;
			cb.func = std::move( func );
			cb.optionalTrackingPtr = con.getTrackablePtr();

			m_callbacks.emplace_back( std::move( cb ) );

			connections.push_back( std::move( con ) );
		}

		template < class T >
		void connect_track( Connections& connections, T* obj, RetVal( T::* mem_fn_ptr )( Args... ) )
		{
			connect_track( connections, [=] ( Args... args ) -> RetVal{ return ( obj->*mem_fn_ptr )( args... ); } );
		}

		void call( Args const& ... args )
		{
			removeInvalidConnections();

			for( const auto& el : m_callbacks )
			{
				el.func( args ... );
			}
		}

		void operator() ( Args const& ... args )
		{
			call( std::forward( args )... );
		}

		Signal& operator=( const Signal& ) = delete;
		Signal& operator=( Signal&& ) = default;
	};
}
