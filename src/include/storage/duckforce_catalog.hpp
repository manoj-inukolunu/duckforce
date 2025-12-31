#pragma once

#include "duckdb/catalog/catalog.hpp"
#include "duckdb/storage/storage_extension.hpp"
#include "duckdb/common/map.hpp"
#include "duckdb/common/mutex.hpp"
#include <iostream>

namespace duckdb {
class DuckforceCatalog : public Catalog {
public:
	explicit DuckforceCatalog(AttachedDatabase &db);

	~DuckforceCatalog() override;

	// Pure virtual function implementations from Catalog
	void Initialize(bool load_builtin) override;
	string GetCatalogType() override;
	optional_ptr<CatalogEntry> CreateSchema(CatalogTransaction transaction, CreateSchemaInfo &info) override;
	optional_ptr<SchemaCatalogEntry> LookupSchema(CatalogTransaction transaction,
	                                               const EntryLookupInfo &schema_lookup,
	                                               OnEntryNotFound if_not_found) override;
	void ScanSchemas(ClientContext &context, std::function<void(SchemaCatalogEntry &)> callback) override;
	
	PhysicalOperator &PlanCreateTableAs(ClientContext &context, PhysicalPlanGenerator &planner,
	                                     LogicalCreateTable &op, PhysicalOperator &plan) override;
	PhysicalOperator &PlanInsert(ClientContext &context, PhysicalPlanGenerator &planner, LogicalInsert &op,
	                             optional_ptr<PhysicalOperator> plan) override;
	PhysicalOperator &PlanDelete(ClientContext &context, PhysicalPlanGenerator &planner, LogicalDelete &op,
	                             PhysicalOperator &plan) override;
	PhysicalOperator &PlanUpdate(ClientContext &context, PhysicalPlanGenerator &planner, LogicalUpdate &op,
	                             PhysicalOperator &plan) override;
	
	DatabaseSize GetDatabaseSize(ClientContext &context) override;
	bool InMemory() override;
	string GetDBPath() override;
	
	void DropSchema(ClientContext &context, DropInfo &info) override;

private:
	//! Catalog set holding schemas
	unique_ptr<CatalogSet> schemas;
	//! Write lock for thread-safe access
	mutex write_lock;
	//! Database path
	string db_path;
};

} // namespace duckdb