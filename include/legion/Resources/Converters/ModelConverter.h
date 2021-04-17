#ifndef LEGION_RESOURCES_CONVERTERS_MODEL_CONVERTER_H_
#define LEGION_RESOURCES_CONVERTERS_MODEL_CONVERTER_H_

#include "canvas/Renderer/Renderer.h"
#include "legion/Resources/Converters/RendererConverter.h"
#include "legion/Resources/Model.h"
#include "silhouette/scene.h"

namespace le {

class ModelConverter : public RendererConverter<Model> {
public:
  ModelConverter();

private:
  bool load(hi::ResourceManager* resourceManager, nu::StringView name, nu::InputStream* inputStream,
            Model* model) override;

  ca::VertexDefinition m_vertexDefinition;
};

}  // namespace le

#endif  // LEGION_RESOURCES_CONVERTERS_MODEL_CONVERTER_H_
