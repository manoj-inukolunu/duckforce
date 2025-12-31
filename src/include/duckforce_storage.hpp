#pragma once

#include "duckdb/storage/storage_extension.hpp"

namespace duckdb {
class DuckforceStorageExtension : public StorageExtension {

public:
	DuckforceStorageExtension();
};
} // namespace duckdb
