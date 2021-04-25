// *********************************************************************************************************************
// Create Markup Entry Command
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef CREATEMARKUPENTYCOMMAND_HPP
#define CREATEMARKUPENTYCOMMAND_HPP

#pragma once


// from Markup
#include "MarkupTypes.hpp"
#include "MarkupCommandsUtils.hpp"
#include "IMarkupCreatorCommand.hpp"

// from GSRoot
#include "ClassInfo.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT CreateMarkupEntryCommand : public PRMU::IMarkupCreatorCommand
{
	DECLARE_DYNAMIC_CLASS_INFO (CreateMarkupEntryCommand)

private:
	CreateMarkupEntryCommand& operator= (const CreateMarkupEntryCommand& source);

protected:
	CreateMarkupEntryCommand ();
	explicit CreateMarkupEntryCommand (const CreateMarkupEntryCommand& source);

public:
	CreateMarkupEntryCommand (const IMarkupEditabilityChecker*  checker, 
							  GS::UniString						name,
							  GS::Guid							ownerId,
							  GS::UniString						ownerFullName, 
							  PRMU::MarkupEntrySetRef			entrySet,
							  PRMU::MarkupEntryRef				parentEntry = nullptr);

	virtual GS::ErrorStatus ExecuteInternal (void) override;

	virtual GS::ErrorStatus	RestoreValidated (const GS::ObjectState& os, const ODB::ObjectRef& context) override;

	GS::ObjectState			GetResult (void) const override;

};

}


#endif