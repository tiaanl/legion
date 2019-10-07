#ifndef LEGION_RESOURCES_RESOURCE_MANAGER_H_
#define LEGION_RESOURCES_RESOURCE_MANAGER_H_

#include "hive/ResourceManager.h"
#include "legion/Resources/Converters/ImageConverter.h"
#include "legion/Resources/Converters/ModelConverter.h"
#include "legion/Resources/Converters/ShaderSourceConverter.h"
#include "legion/Resources/Converters/TextureConverter.h"

namespace le {

class ResourceManager : public hi::ResourceManager {
public:
  ResourceManager();

  void setRenderer(ca::Renderer* renderer);

private:
  ImageConverter m_imageConverter;
  ModelConverter m_modelConverter;
  ShaderSourceConverter m_shaderSourceConverter;
  TextureConverter m_textureConverter;
};

}  // namespace le

#endif  // LEGION_RESOURCES_RESOURCE_MANAGER_H_
