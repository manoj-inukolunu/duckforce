#pragma once

#include "duckdb.hpp"

namespace duckdb {

class DuckforceExtension : public Extension {
public:
	void Load(ExtensionLoader &db) override;
	std::string Name() override {
		return "duckforce";
	}
	std::string Version() const override {
		return "0.1.0";
	};
};

} // namespace duckdb
