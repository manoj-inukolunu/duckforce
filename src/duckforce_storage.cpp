#include "duckdb.hpp"
#include "storage/duckforce_catalog.hpp"
#include "duckforce_storage.hpp"
#include "duckdb/parser/parsed_data/attach_info.hpp"
#include "storage/duckforce_transaction_manager.hpp"

#include <iostream>

namespace duckdb {

static unique_ptr<Catalog> DuckforceAttachFunction(optional_ptr<StorageExtensionInfo> storage_info,
                                                   ClientContext &context, AttachedDatabase &db, const string &name,
                                                   AttachInfo &info, AttachOptions &options) {

	// Placeholder implementation

	std::cout << " DuckforceAttachFunction called for database: " << name << std::endl;
	auto duckforce_catalog = make_uniq<DuckforceCatalog>(db);
	return duckforce_catalog;
}

static unique_ptr<TransactionManager> DuckforceCreateTransactionManager(optional_ptr<StorageExtensionInfo> storage_info,
                                                                        AttachedDatabase &db, Catalog &catalog) {
	// Placeholder implementation
	std::cout << " DuckforceCreateTransactionManager called for database: " << db.GetName() << std::endl;

	auto &duckforce_catalog = catalog.Cast<DuckforceCatalog>();
	return make_uniq<DuckforceTransactionManager>(db, duckforce_catalog);
}

DuckforceStorageExtension::DuckforceStorageExtension() {
	attach = DuckforceAttachFunction;
	create_transaction_manager = DuckforceCreateTransactionManager;
}
} // namespace duckdb