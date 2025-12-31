#include "storage/duckforce_catalog.hpp"
#include "duckdb/catalog/catalog_set.hpp"
#include "duckdb/catalog/catalog_entry/schema_catalog_entry.hpp"
#include "duckdb/common/exception.hpp"
#include "duckdb/parser/parsed_data/create_schema_info.hpp"
#include "duckdb/parser/parsed_data/drop_info.hpp"
#include "duckdb/planner/operator/logical_create_table.hpp"
#include "duckdb/planner/operator/logical_insert.hpp"
#include "duckdb/planner/operator/logical_delete.hpp"
#include "duckdb/planner/operator/logical_update.hpp"
#include "duckdb/execution/physical_operator.hpp"
#include "duckdb/execution/physical_plan_generator.hpp"
#include "duckdb/catalog/entry_lookup_info.hpp"
#include "duckdb/common/enums/on_entry_not_found.hpp"
#include "duckdb/main/client_context.hpp"

namespace duckdb {

DuckforceCatalog::DuckforceCatalog(AttachedDatabase &db) : Catalog(db) {
	// Initialize the catalog set for schemas
	schemas = make_uniq<CatalogSet>(*this);
	db_path = "";
	std::cout << "Initializing DuckforceCatalog" << std::endl;
}

DuckforceCatalog::~DuckforceCatalog() = default;

void DuckforceCatalog::Initialize(bool load_builtin) {
	// Initialize built-in schemas if needed
	if (load_builtin) {
		// Get a system catalog transaction
		auto data = CatalogTransaction::GetSystemTransaction(GetDatabase());

		// Create default 'main' schema
		CreateSchemaInfo info;
		info.schema = "main";
		info.internal = true;

		CreateSchema(data, info);

		std::cout << "DuckforceCatalog initialized with builtin schemas" << std::endl;
	}
}

string DuckforceCatalog::GetCatalogType() {
	return "duckforce";
}

optional_ptr<CatalogEntry> DuckforceCatalog::CreateSchema(CatalogTransaction transaction, CreateSchemaInfo &info) {
	throw CatalogException("Not Implemented");
}

optional_ptr<SchemaCatalogEntry> DuckforceCatalog::LookupSchema(CatalogTransaction transaction,
                                                                const EntryLookupInfo &schema_lookup,
                                                                OnEntryNotFound if_not_found) {
	throw CatalogException("Not Implemented");
}

void DuckforceCatalog::ScanSchemas(ClientContext &context, std::function<void(SchemaCatalogEntry &)> callback) {
	std::cout << " IN Scan Schemas" << std::endl;
	throw CatalogException("Not Implemented");
}

PhysicalOperator &DuckforceCatalog::PlanCreateTableAs(ClientContext &context, PhysicalPlanGenerator &planner,
                                                      LogicalCreateTable &op, PhysicalOperator &plan) {
	// Delegate to the physical plan generator
	// This is typically handled by the planner itself, so we just return the plan as-is
	return plan;
}

PhysicalOperator &DuckforceCatalog::PlanInsert(ClientContext &context, PhysicalPlanGenerator &planner,
                                               LogicalInsert &op, optional_ptr<PhysicalOperator> plan) {
	// Delegate to the physical plan generator
	if (plan) {
		return *plan;
	}
	throw CatalogException("Insert plan cannot be null");
}

PhysicalOperator &DuckforceCatalog::PlanDelete(ClientContext &context, PhysicalPlanGenerator &planner,
                                               LogicalDelete &op, PhysicalOperator &plan) {
	// Delegate to the physical plan generator
	// For now, just return the plan as provided
	return plan;
}

PhysicalOperator &DuckforceCatalog::PlanUpdate(ClientContext &context, PhysicalPlanGenerator &planner,
                                               LogicalUpdate &op, PhysicalOperator &plan) {
	// Delegate to the physical plan generator
	// For now, just return the plan as provided
	return plan;
}

DatabaseSize DuckforceCatalog::GetDatabaseSize(ClientContext &context) {
	// Return database size information
	DatabaseSize size;
	size.free_blocks = 0;
	size.total_blocks = 0;
	size.used_blocks = 0;
	size.wal_size = 0;
	size.block_size = 0;
	size.bytes = 0;
	return size;
}

bool DuckforceCatalog::InMemory() {
	// DuckForce is an in-memory storage extension
	return true;
}

string DuckforceCatalog::GetDBPath() {
	// Return the database path
	return db_path;
}

void DuckforceCatalog::DropSchema(ClientContext &context, DropInfo &info) {
	throw CatalogException("Not Implemented");
}

} // namespace duckdb
