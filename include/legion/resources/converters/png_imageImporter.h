#pragma once

#include <hive/importer/importer.h>
#include <silhouette/image.h>

namespace le {

class PNGImageImporter : public hi::Importer<si::Image> {
  NU_DELETE_COPY_AND_MOVE(PNGImageImporter);

public:
  PNGImageImporter() = default;
  ~PNGImageImporter() override = default;

  bool import(nu::InputStream* stream, si::Image* storage) override;
};

}  // namespace le
