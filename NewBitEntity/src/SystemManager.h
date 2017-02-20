#pragma once
#include "stdafx.h"
#include "System.h"
#include "SystemAlreadyExistsException.h"
#include "SystemDoesNotExistException.h"
#include "SystemManagerAlreadyInitializedException.h"

namespace nb
{
	class EntityManager;

	class SystemManager
	{
		EntityManager* r_entityManager;

		std::unordered_map<std::type_index, std::unique_ptr<System>> m_systems;
		std::vector<System*> m_systemsByUpdateOrder;

		bool m_isInit = false;

		bool m_isSorted = false;
		void sortSystemsByUpdateOrder();

	protected:
		void updateSystems();

	public:
		SystemManager( EntityManager& entityManager );

		template < class T >
		T* addSystem()
		{
			auto system = std::make_unique<T>();

			if (m_isInit)
				system->init( *this, *r_entityManager );

			const auto typeIndex = std::type_index( typeid(T) );

			auto insertResult = m_systems.insert( std::make_pair( typeIndex, std::move( system ) ) );
			if (!insertResult.second)
			{
				throw exception::SystemAlreadyExistsException( typeIndex.name() );
			}
			auto systemPointer = (T*)insertResult.first->second.get();

			m_systemsByUpdateOrder.push_back( systemPointer );
			m_isSorted = false;
			return systemPointer;
		};

		template < class T >
		T* getSystem()const
		{
			const auto typeIndex = std::type_index( typeid(T) );
			try
			{
				return (T*)m_systems.at( typeIndex ).get();
			}
			catch (std::out_of_range)
			{
				throw exception::SystemDoesNotExistException( typeIndex.name() );
			}
		};

		template < class T >
		void removeSystem()
		{
			const auto typeIndex = std::type_index( typeid(T) );
			try
			{
				auto& system = m_systems.at( typeIndex );
				system->destroy( *this, *r_entityManager );
				m_systemsByUpdateOrder.erase(
					std::remove( m_systemsByUpdateOrder.begin(),
								 m_systemsByUpdateOrder.end(),
								 system.get() )
				);
				m_systems.erase( typeIndex );
			}
			catch (std::out_of_range)
			{
				throw exception::SystemDoesNotExistException( typeIndex.name() );
			}
		};

		DLL_EXPORT void initSystems();
	};
}
