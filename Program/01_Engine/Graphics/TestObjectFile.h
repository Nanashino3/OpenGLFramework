#pragma once

#include <memory>
#include <vector>
namespace tkl{ class Mesh; }

namespace tkl
{
class TestObjectFile
{
public:
	static std::vector<std::shared_ptr<Mesh>> CreateFromObjFile(const char* filepath);
};

} // namespace tkl