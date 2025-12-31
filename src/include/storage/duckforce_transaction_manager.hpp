//===----------------------------------------------------------------------===//
//                         DuckDB
//
// storage/postgres_transaction_manager.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/transaction/transaction_manager.hpp"
#include "duckdb/common/reference_map.hpp"
#include "storage/duckforce_catalog.hpp"

namespace duckdb {

class DuckforceTransactionManager : public TransactionManager {
public:
	DuckforceTransactionManager(AttachedDatabase &db_p, DuckforceCatalog &duckforce_catalog);

	Transaction &StartTransaction(ClientContext &context) override;
	ErrorData CommitTransaction(ClientContext &context, Transaction &transaction) override;
	void RollbackTransaction(Transaction &transaction) override;

	void Checkpoint(ClientContext &context, bool force = false) override;

private:
	DuckforceCatalog &duckforce_catalog;
	mutex transaction_lock;
	// reference_map_t<Transaction, unique_ptr<DuckforceTransaction>> transactions;
};

} // namespace duckdb
