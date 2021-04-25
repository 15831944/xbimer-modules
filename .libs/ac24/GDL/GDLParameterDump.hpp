#ifndef GS_GDLPARAMETERDUMP_HPP
#define GS_GDLPARAMETERDUMP_HPP

#include "GDLExport.h"
#include "comProc.h" 
#include "Pair.hpp"
#include "Array.hpp"
#include "UniString.hpp"
#include "Optional.hpp"

namespace GDL {

class ParameterGetter;

class GDL_DLL_EXPORT IGDLDumper {
public:
	enum class Section {
		General,
		UserGDLParamList,
		CurrentGDLParamList,
		Global,
		LocalizedDefaultGDLParamList,
		Other
	};

	virtual void DumpMessage (const GS::UniString& message) = 0;
	virtual void DumpKeyValuePair (const GS::UniString& key, const GS::UniString& value) = 0;
	virtual void DumpParameter (Section section, const GS::ObjectState& parameterState) = 0;
	virtual void AddEmptyLine () = 0;
	virtual void NextElem (const GS::UniString& description) = 0;

	virtual bool ShouldDump (Section section) = 0;
	virtual ~IGDLDumper ();
};

class GDL_DLL_EXPORT DefaultGDLDumper : public IGDLDumper {
public:
	virtual void DumpKeyValuePair (const GS::UniString& key, const GS::UniString& value) override;
	virtual void DumpParameter (Section section, const GS::ObjectState& parameterState) override;
	virtual void AddEmptyLine () override;
	virtual void NextElem (const GS::UniString& description) override;

	virtual bool ShouldDump (Section section) override;
};

GDL_DLL_EXPORT void GDL_CALL DumpGDLParameters (IGDLDumper::Section section, const ParameterGetter& parameters, IGDLDumper& messageProc);

}


GDL_DLL_EXPORT void GDL_CALL GDLDumpVariable (const GDL::ParameterGetter& parameters, Int32 index, MessageProc_UStr* messageProc);
GDL_DLL_EXPORT void GDL_CALL GDLDumpVariableHdl (const GDL::ParameterGetter& variableHdl, MessageProc_UStr* messageProc);


#endif
