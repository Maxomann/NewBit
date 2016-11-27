#pragma once
#include "stdafx.h"
#include "Component.h"
#include "ComponentAlreadyExistsException.h"
#include "ComponentDoesNotExistException.h"
#include "EntityAlreadyInitializedException.h"

namespace nb
{
	namespace entity
	{
		class Entity
		{
			std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
			bool m_isInit = false;

		public:
			Entity() = default;
			Entity( const Entity& entity ) = delete;
			Entity( Entity&& entity ) = default;

			Component* addComponent( std::unique_ptr<Component>&& component )
			{
				if ( m_isInit )
					component->init( *this );
				auto componentPointer = component.get();

				const auto& type = component->type;

				auto insertResult = m_components.insert( std::make_pair( type, std::move( component ) ) );
				if ( !insertResult.second )
				{
					throw exception::ComponentAlreadyExistsException( type.name() );
				}
				return insertResult.first->second.get();
			};

			template < class T >
			T* getComponent()const
			{
				const auto typeIndex = std::type_index( typeid( T ) );
				try
				{
					return (T*) m_components.at( typeIndex ).get();
				}
				catch ( std::out_of_range )
				{
					throw exception::ComponentDoesNotExistException( typeIndex.name() );
				}
			};

			template < class T >
			void removeComponent()
			{
				const auto typeIndex = std::type_index( typeid( T ) );
				try
				{
					auto& component = m_components.at( typeIndex );
					component->destroy( *this );
					m_components.erase( typeIndex );
				}
				catch ( std::out_of_range )
				{
					throw exception::ComponentDoesNotExistException( typeIndex.name() );
				}
			};

			void init();
			/* Not called on World::~World() */
			void destroy();
		};
	}
}