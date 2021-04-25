#ifndef GS_VBEO_ROOM_ADD_PAR_UPDATER_HPP
#define GS_VBEO_ROOM_ADD_PAR_UPDATER_HPP

#include "VBElemOperationsExport.hpp"
#include "RoomTypes.hpp"

namespace GDL {
	class ParameterAccessor;
}

namespace VBEO {

VB_ELEM_OPERATIONS_DLL_EXPORT
void ModifyAddParHdlAtIndex (GDL::ParameterAccessor&	parameterAccessor,
							 Int32						parIndex,
							 double						par,
							 const char*				name);

class VB_ELEM_OPERATIONS_DLL_EXPORT RoomAddParUpdater {
private:
	template<class ValueType>
	struct Parameter {
		const char*		name;
		ValueType		value;
		Int32			index;
	};
	
	using NumericParameter = Parameter<double>;
	using IntegerParameter = Parameter<Int32>;

	VBElem::RoomRef					room;
	GS::Array<NumericParameter>		numericParameterChangeRequests;
	GS::Array<IntegerParameter>		integerParameterChangeRequests;

	bool IsValidParameterIndex (Int32 parameterIndex, const GDL::ParameterGetter& stampParameterGetter);

public:
	RoomAddParUpdater (const VBElem::RoomRef& inRoom);
	void AddParameterUpdateRequest (const char* parameterName, double newValue);
	void AddParameterUpdateRequest (const char* parameterName, Int32 newValue);
	bool ExecuteUpdate ();
};

}

#endif
