#include "FrameworkPch.h"
#include "Framework/EntityDefinition.h"

#include "Framework/Slice.h"
#include "Framework/Entity.h"
#include "Framework/ParameterSet.h"

using namespace Helium;

HELIUM_IMPLEMENT_ASSET( Helium::EntityDefinition, Framework, 0 );

void Helium::EntityDefinition::PopulateMetaType( Reflect::MetaStruct& comp )
{
	comp.AddField( &EntityDefinition::m_ComponentDefinitionSet, "m_ComponentDefinitionSet" );
	comp.AddField( &EntityDefinition::m_Components, "m_Components" );
}

/// Constructor.
EntityDefinition::EntityDefinition()
{
}

/// Destructor.
EntityDefinition::~EntityDefinition()
{
}

void Helium::EntityDefinition::AddComponentDefinition( Helium::Name name, Helium::ComponentDefinition *pComponentDefinition )
{
	if (!m_ComponentDefinitionSet)
	{
		InitComponentDefinitionSet();
	}

	m_ComponentDefinitionSet->AddComponentDefinition(name, pComponentDefinition);
}

Helium::EntityPtr Helium::EntityDefinition::CreateEntity()
{
	return Reflect::AssertCast<Entity>(Entity::CreateObject());
}

void Helium::EntityDefinition::FinalizeEntity( Entity *pEntity, const ParameterSet *pParameterSet )
{
	HELIUM_ASSERT(pEntity);

	if (m_ComponentDefinitionSet.Get())
	{
		static const ParameterSet NULL_PARAMETERS;
		pEntity->DeployComponents(*m_ComponentDefinitionSet, pParameterSet ? *pParameterSet : NULL_PARAMETERS);
	}
	else
	{
		pEntity->DeployComponents(m_Components);
	}
}
