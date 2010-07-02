#pragma once

#include "ExportBase.h"
#include "Pipeline/Asset/Classes/Entity.h"

namespace MayaContent
{
  class MAYA_API ExportEntity : public ExportBase
  {
  public:
    ExportEntity( const MObject& mayaObject, Nocturnal::TUID id )
      : ExportBase( mayaObject )
    {
      m_ContentObject = new Asset::Entity( id );
    }

    // Gather the necessary maya data
    virtual void GatherMayaData( V_ExportBase &newExportObjects );
   };

  typedef Nocturnal::SmartPtr<ExportEntity> ExportEntityPtr;
}