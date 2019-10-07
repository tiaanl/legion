#include "legion/Resources/ResourceManager.h"

namespace le {

ResourceManager::ResourceManager() {
  registerConverter(&m_imageConverter);
  registerConverter(&m_modelConverter);
  registerConverter(&m_shaderSourceConverter);
  registerConverter(&m_textureConverter);
}

void ResourceManager::setRenderer(ca::Renderer* renderer) {
  m_modelConverter.setRenderer(renderer);
  m_shaderSourceConverter.setRenderer(renderer);
  m_textureConverter.setRenderer(renderer);
}

}  // namespace le
