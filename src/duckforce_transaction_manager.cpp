//===----------------------------------------------------------------------===//
//                         DuckDB
//
// storage/postgres_transaction_manager.hpp
//
//
//===----------------------------------------------------------------------===//

#include "storage/duckforce_catalog.hpp"
#include "storage/duckforce_transaction_manager.hpp"

namespace duckdb {

DuckforceTransactionManager::DuckforceTransactionManager(AttachedDatabase &db_p, DuckforceCatalog &duckforce_catalog)
    : TransactionManager(db_p), duckforce_catalog(duckforce_catalog) {
	std::cout << "INit Ductforce transaction Manager" << std::endl;
}

Transaction &DuckforceTransactionManager::StartTransaction(ClientContext &context) {
	throw NotImplementedException("DuckforceTransactionManager::StartTransaction not implemented yet");
}

ErrorData DuckforceTransactionManager::CommitTransaction(ClientContext &context, Transaction &transaction) {
	throw NotImplementedException("DuckforceTransactionManager::CommitTransaction not implemented yet");
}

void DuckforceTransactionManager::RollbackTransaction(Transaction &transaction) {
	throw NotImplementedException("DuckforceTransactionManager::RollbackTransaction not implemented yet");
}

void DuckforceTransactionManager::Checkpoint(ClientContext &context, bool force) {
	throw NotImplementedException("DuckforceTransactionManager::Checkpoint not implemented yet");
}

} // namespace duckdb
