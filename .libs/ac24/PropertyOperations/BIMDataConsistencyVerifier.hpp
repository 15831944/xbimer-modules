#ifndef BIMDATACONSISTENCYVERIFIER_HPP
#define BIMDATACONSISTENCYVERIFIER_HPP

#include "PropertyOperationsExport.hpp"


namespace ODB {
class Database;
class DependencyNode;
}


namespace BIMData {

PROPERTY_OPERATIONS_DLL_EXPORT	ODB::DependencyNode*	GetBIMDataConsistencyVerifierNode ();

PROPERTY_OPERATIONS_DLL_EXPORT	void					VerifyBIMDataConsistency (const ODB::Database* projectDatabase);

PROPERTY_OPERATIONS_DLL_EXPORT	void					FixBIMDataInconsistencies (ODB::Database* projectDatabase);

}


#endif