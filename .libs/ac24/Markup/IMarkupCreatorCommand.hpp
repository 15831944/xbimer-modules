// *********************************************************************************************************************
// Markup Creator Commands interface
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	FLT
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef IMARKUPCREATORCOMMAND_HPP
#define IMARKUPCREATORCOMMAND_HPP

#pragma once

// from Markup
#include "MarkupCommandBase.hpp"
#include "TraceAndMergeEntrySetChanges.hpp"
#include "MarkupTypes.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT IMarkupCreatorCommand : public PRMU::MarkupCommandBase,
												public PRMU::TraceAndMergeEntrySetChanges
{
private:
	GS::UniString			name;
	GS::Guid				ownerId;
	GS::UniString			ownerFullName;

protected:
	PRMU::MarkupEntryRefList newEntries;

protected:
	IMarkupCreatorCommand () = delete;
	IMarkupCreatorCommand (const IMarkupEditabilityChecker* checker, 
						   const GS::UniString& name,
						   const GS::Guid&	ownerId,
						   const GS::UniString& ownerFullName,
						   const GS::Array<TWCB::PermissionID>& necessaryPermissions,  
						   const PRMU::MarkupEntrySetConstRef& originalEntrySet,
						   const PRMU::MarkupEntryRef& parentEntryToCopy);

	explicit IMarkupCreatorCommand (const IMarkupCreatorCommand& source);

public:
	virtual ~IMarkupCreatorCommand ();
	virtual MarkupEntryRefList GetTemporaryNewMarkupEntries () final;
	virtual MarkupEntryRefList GetMergedNewMarkupEntries () final;
};
}	// PRMU namespace

#endif