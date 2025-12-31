#define DUCKDB_EXTENSION_MAIN

#include "duckforce_extension.hpp"
#include "duckforce_storage.hpp"
#include "duckdb.hpp"
#include "duckdb/common/exception.hpp"
#include "duckdb/function/scalar_function.hpp"
#include <duckdb/parser/parsed_data/create_scalar_function_info.hpp>
#include "duckdb/main/extension/extension_loader.hpp"
#include "duckdb/common/helper.hpp"
#include "duckdb/planner/extension_callback.hpp"

namespace duckdb {

class DuckforceExtensionCallback : public ExtensionCallback {
public:
	void OnExtensionLoaded(DatabaseInstance &db, const string &name) override {
		std::cout << "Extension " << name << " loaded successfully." << std::endl;
	}
};

static void LoadInternal(ExtensionLoader &loader) {
	auto &config = DBConfig::GetConfig(loader.GetDatabaseInstance());

	config.extension_callbacks.push_back(make_uniq<DuckforceExtensionCallback>());
	config.storage_extensions["duckforce"] = make_uniq<DuckforceStorageExtension>();
}

void DuckforceExtension::Load(ExtensionLoader &loader) {
	std::cout << "Loading Duckforce Extension..." << std::endl;
	LoadInternal(loader);
}

} // namespace duckdb

extern "C" {

DUCKDB_CPP_EXTENSION_ENTRY(duckforce, loader) {
	duckdb::LoadInternal(loader);
}
}
