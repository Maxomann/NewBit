#pragma once
#include "stdafx.h"
#include "Component.h"
#include "ComponentAlreadyExistsException.h"
#include "ComponentDoesNotExistException.h"
#include "EntityAlreadyInitializedException.h"

namespace nb
{
	class Entity
	{
		std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
		bool m_isInit = false;

	public:
		Entity() = default;
		Entity( const Entity& entity ) = delete;
		Entity( Entity&& entity ) = default;

		// T must inherit from Component
		template < class T >
		Component* addComponent( std::unique_ptr<T>&& component )
		{
			if (m_isInit)
				component->init( *this );
			auto componentPointer = component.get();

			const auto typeIndex = std::type_index( typeid(T) );
#ifdef _DEBUG
			if (typeIndex == std::type_index( typeid(Component) ))
				throw std::exception();
#endif // _DEBUG

			auto insertResult = m_components.insert( std::make_pair( typeIndex, std::move( component ) ) );
			if (!insertResult.second)
			{
				throw exception::ComponentAlreadyExistsException( typeIndex.name() );
			}
			return insertResult.first->second.get();
		};

		template < class T >
		T* getComponent()const
		{
			const auto typeIndex = std::type_index( typeid(T) );
			try
			{
				return (T*)m_components.at( typeIndex ).get();
			}
			catch (std::out_of_range)
			{
				throw exception::ComponentDoesNotExistException( typeIndex.name() );
			}
		};

		template < class T >
		T* getComponent_try()const
		{
			const auto typeIndex = std::type_index( typeid(T) );
			auto result = m_components.find( typeIndex );
			if (result != m_components.end())
				return (T*)result->second.get();
			else
				return nullptr;
		};

		template < class T >
		void removeComponent()
		{
			const auto typeIndex = std::type_index( typeid(T) );
			try
			{
				auto& component = m_components.at( typeIndex );
				component->destroy( *this );
				m_components.erase( typeIndex );
			}
			catch (std::out_of_range)
			{
				throw exception::ComponentDoesNotExistException( typeIndex.name() );
			}
		};

		/* init() is called by EntityManager::addEntities(). Do not call this manually! */
		void init();
		/* Not called on World::~World() */
		void destroy();
	};
}
