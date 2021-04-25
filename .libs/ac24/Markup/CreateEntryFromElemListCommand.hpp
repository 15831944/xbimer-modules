// *********************************************************************************************************************
// Create Markup Entry Command
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB, FEs
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef CREATEMARKUPENTYFORMODELCHECKING_HPP
#define CREATEMARKUPENTYFORMODELCHECKING_HPP

#pragma once

// from Markup
#include "ComponentChecker.hpp"
#include "ElementAttacher.hpp"
#include "IMarkupCreatorCommand.hpp"
#include "MarkupCommandsUtils.hpp"
#include "MarkupModuleUtils.hpp"
#include "ElementDuplicator.hpp"

// from ProjectNavigator
#include "CaptureData.hpp"

// from GSRoot
#include "ClassInfo.hpp"

namespace PRMU { struct CreateEntryFromElemListCreationData; }

namespace PRMU {

class MARKUP_DLL_EXPORT CreateEntryFromElemListCommand : public PRMU::IMarkupCreatorCommand
{
	DECLARE_DYNAMIC_CLASS_INFO (CreateEntryFromElemListCommand)

private:
	PN::CaptureInterface* captureInterface;
	GS::UniString sceneName;
	
	PRMU::MarkupEntrySetRef entrySet;
	GS::Array<CreateEntryFromElemListCreationData> creationDatas;

	CreateEntryFromElemListCommand& operator= (const CreateEntryFromElemListCommand& source);

protected:
	bool separateEntriesForEachElemPair;

	CreateEntryFromElemListCommand ();
	CreateEntryFromElemListCommand (const CreateEntryFromElemListCommand& source);

public:
	CreateEntryFromElemListCommand (const IMarkupEditabilityChecker* checker, 
									const GS::UniString&			 name,
									const GS::Guid&					 ownerId,
									const GS::UniString&			 ownerFullName,
									const PRMU::MarkupEntrySetRef&	 entrySet,
									PN::CaptureInterface*			 captureInterface = nullptr,
									GS::Array<CreateEntryFromElemListCreationData>&& creationDatas = { },
									const GS::UniString&			 sceneName = GS::EmptyUniString,
									const PRMU::MarkupEntryRef&		 parentEntry = nullptr);

	virtual GS::ErrorStatus ExecuteInternal (void) override;

	void					SetSeparateEntries (bool separate) {separateEntriesForEachElemPair = separate; };
	void					SetCreationDatas	(GS::Array<CreateEntryFromElemListCreationData>&& creationDatas);
};


class MARKUP_DLL_EXPORT CreateMultipleEntriesFromElemListCommand : public PRMU::IMarkupCreatorCommand,
																   public ElementAttacher
{
	DECLARE_DYNAMIC_CLASS_INFO (CreateMultipleEntriesFromElemListCommand)

private:
	bool separateEntriesForEachElem;

	EDB::ProjectRef targetProject;
	ElementsFromDiff3DByComponentTypes elementsByComponentTypes;

	ElemDuplicator* elemDuplicator;
	ComponentChecker componentChecker;

	GS::UniString	issueName;
protected:
	CreateMultipleEntriesFromElemListCommand ();
	CreateMultipleEntriesFromElemListCommand (const CreateMultipleEntriesFromElemListCommand& source);
public:
	CreateMultipleEntriesFromElemListCommand (const PRMU::IMarkupEditabilityChecker* checker, 
											  EDB::ProjectRef targetProject,
											  const GS::UniString& name,
											  const GS::Guid& ownerId,
											  const GS::UniString& ownerFullName,
											  const PRMU::MarkupEntryRef& parentEntry,
											  const PRMU::ElementsFromDiff3DByComponentTypes& elementsByComponentTypes,
											  ElemDuplicator* elemDuplicator,
											  const ComponentChecker& componentChecker);

	virtual GS::ErrorStatus ExecuteInternal (void) override;
	void					SetIssueName (GS::UniString name) { issueName = name; }
	void					SetSeparateEntries (bool separate) { separateEntriesForEachElem = separate; };
	void					SetElementsByComponentTypes(const PRMU::ElementsFromDiff3DByComponentTypes& elements) {elementsByComponentTypes = elements;}
};


struct MARKUP_DLL_EXPORT CreateEntryFromElemListCreationData
{
	GS::UniString								name;
	GS::UniString								description;
	GS::HashSet<GS::UniString>					labels;
	GS::Array<EDB::GeneralElemRefList>			elems;
};

}


#endif