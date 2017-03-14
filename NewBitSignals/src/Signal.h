#pragma once
#include <signals-cpp\signals.hpp>

namespace nb
{
	template< typename Signature >
	class Signal : public signals::signal<Signature>
	{
	public:
		template<typename... Args>
		inline void call( Args&&... args ) const
		{
			fire( std::forward<Args>( args )... );
		}
	};

	using Connection = signals::connection;
	using Connections = signals::connections;
}
