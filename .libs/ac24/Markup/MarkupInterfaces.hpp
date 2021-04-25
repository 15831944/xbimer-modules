// *********************************************************************************************************************
// Markup Interfaces
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	FEs
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef MARKUPINTERFACES_HPP
#define MARKUPINTERFACES_HPP

#pragma once

// from Markup
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"

// from TWClient
#include "TWClient/Mailbox/UserContact.hpp"


// --- predeclarations ---------------------------------------------------------------------------

namespace EDB {
class GeneralElem;
typedef ODB::Ref<EDB::GeneralElem> GeneralElemRef;
typedef ODB::ConstRef<EDB::GeneralElem> GeneralElemConstRef;
typedef ODB::RefList<EDB::GeneralElem> GeneralElemRefList;
typedef ODB::ConstRefList<EDB::GeneralElem> GeneralElemConstRefList;

class Project;
typedef ODB::Ref<EDB::Project> ProjectRef;
}

// --- Function Pointer Definition --------------------------------------------------------------------------------------

typedef std::function<GS::HashTable<GS::UniString, TWC::Mailbox::ConstUserContactRef> ()>	GetUserContactsFunctionPtr;
typedef std::function<bool ()>																IsTeamworkFunctionPtr;
typedef std::function<bool (const GS::UniString&)>											IsTWUserOnlineFunctionPtr;
typedef std::function<short ()>																GetCurrentTWUserIdFunctionPtr;
typedef std::function<GS::Guid ()>															GetCurrentTWUserGuidFunctionPtr;
typedef std::function<GS::UniString ()>														GetCurrentTWUserNameFunctionPtr;
typedef std::function<GS::UniString ()>														GetCurrentTWLoginNameFunctionPtr;
typedef std::function<short (const GS::Guid& userGuid)>										GetUserIdFromGuidFunctionPtr;
typedef std::function<GS::Guid (short userId)>												GetUserGuidFromIdFunctionPtr;
typedef std::function<GS::UniString (const ODB::ConstRef<ODB::Object>& object)>				GetOwnerUserNameFunctionPtr;
typedef std::function<GS::ErrorStatus (PRMU::MarkupEntryRefList entry, short ownerUserId)>	ReserveMarkupFunctionPtr;
typedef std::function<bool (short userId)>													HasRightsFunctionPtr;


namespace PRMU {
// --- enum definitions ---------------------------------------------------------------------------------------------
enum class Diff3DElemExistenceAndStateInfo {
	Exclusive1,
	Exclusive2,
	Both_Unchanged,
	Both_Changed
};

enum IssueRelatedOperation {
	NotSet,
	Create,
	CreateWithComponent,
	Edit,
	EditAssignee,
	Delete,
	Rename,
	Import,
	Export,
	SetParent,
	AddComponent,
	AddComponentOnDiff3D,
	AcceptComponent,
	RemoveComponent,
	AddEntryView,
	AddEntryViewWithComponent,
	AddEntryViewWithComponentsDiff3D,
	DeleteEntryView,
	RedefineEntryViewByCurrentView,
	RenameEntryView,
	ViewEntryViewImage,
	ExportEntryViewImage,
	ImportImageOntoEntryView,
	EditEntryViewImageExternal,
	AddComment,
	ModifyEntryComment,
	ManageTags
};

typedef std::function<Diff3DElemExistenceAndStateInfo (const ODB::Id& idInSource)> GetDiff3DElemExistenceAndStateInfoFunctionPtr;

// --- Struct definitions -----------------------------------------------------------------------------------------------

enum class MARKUP_DLL_EXPORT MarkupEntryTWOperations 
{
	Nothing			= 0x0000, // - 0
	AssignEntries	= 0x0001, // - 1
	RequestEntries	= 0x0010, // - 2
	ReleaseEntries	= 0x0100, // - 4
	ReserveEntries	= 0x1000, // - 8
	All				= 0x1111  // - 15
};

inline MarkupEntryTWOperations	operator|	(const MarkupEntryTWOperations& a, const MarkupEntryTWOperations& b)	{ return (MarkupEntryTWOperations)((UInt32)a | (UInt32)b); }
inline MarkupEntryTWOperations	operator&	(const MarkupEntryTWOperations& a, const MarkupEntryTWOperations& b)	{ return (MarkupEntryTWOperations)((UInt32)a & (UInt32)b); }
inline MarkupEntryTWOperations	operator^	(const MarkupEntryTWOperations& a, const MarkupEntryTWOperations& b)	{ return (MarkupEntryTWOperations)((UInt32)a ^ (UInt32)b); }
inline MarkupEntryTWOperations& operator|=	(const MarkupEntryTWOperations& a, const MarkupEntryTWOperations& b)	{ return (MarkupEntryTWOperations&)((UInt32&)a |= (UInt32)b); }
inline MarkupEntryTWOperations& operator&=	(const MarkupEntryTWOperations& a, const MarkupEntryTWOperations& b)	{ return (MarkupEntryTWOperations&)((UInt32&)a &= (UInt32)b); }
inline bool						operator==	(const MarkupEntryTWOperations& a, const UInt32& b)						{ return (UInt32&)a == b; }
inline bool						operator!=	(const MarkupEntryTWOperations& a, const UInt32& b)						{ return !(a == b); }


struct MARKUP_DLL_EXPORT TWUserParams {

	TWUserParams ();
	TWUserParams (const TWUserParams& other);

	TWUserParams*								Clone () const;
	GetUserContactsFunctionPtr					GetUserContacts;
	IsTeamworkFunctionPtr						IsTeamwork;
	IsTWUserOnlineFunctionPtr					IsTWUserOnline;
	GetCurrentTWUserIdFunctionPtr				GetCurrentTWUserId;
	GetCurrentTWUserGuidFunctionPtr				GetCurrentTWUserGuid;
	GetCurrentTWUserNameFunctionPtr				GetCurrentTWUserName;
	GetCurrentTWLoginNameFunctionPtr			GetCurrentTWLoginName;
	GetUserIdFromGuidFunctionPtr				GetUserIdFromGuid;
	GetUserGuidFromIdFunctionPtr				GetUserGuidFromId;
	GetOwnerUserNameFunctionPtr					GetOwnerUserName;
	MarkupEntryTWOperations						GetTWOperationsForUserOnEntries (short userId, const PRMU::MarkupEntryConstRefList& entries) const;

	HasRightsFunctionPtr						HasRightForIssueCreation;
	HasRightsFunctionPtr						HasRightForIssueModification;
	HasRightsFunctionPtr						HasRightForIssueDeletion;
	HasRightsFunctionPtr						HasRightForIssueTagManagement;

	virtual ~TWUserParams ();
};


struct MARKUP_DLL_EXPORT Diff3DElemIdToCurrentModelElemIdMapUpdater {
	using Callback = std::function<void (const GS::HashTable<ODB::Id, ODB::Id>& idMapTable)>;

	Callback updateIdMap;

	Diff3DElemIdToCurrentModelElemIdMapUpdater (Callback updateIdMap) : updateIdMap (updateIdMap) {}
	Diff3DElemIdToCurrentModelElemIdMapUpdater () : updateIdMap (nullptr) {}
	virtual void UpdateIdMap (const GS::HashTable<ODB::Id, ODB::Id>& idMapTable) const;
};

// --- Interfaces definitions -----------------------------------------------------------------------------------------------


class MARKUP_DLL_EXPORT IEditabilityChecker {
public:
	virtual ~IEditabilityChecker ();
	virtual IEditabilityChecker* Clone () const = 0;
	virtual bool IsEditable (EDB::GeneralElemConstRef elem, bool isAutoReservable = false, short* testResult_Out = nullptr) const = 0;
	virtual bool IsEditableMarkup (PRMU::MarkupEntryConstRef entry) const = 0;
	virtual bool IsEditableComment (PRMU::EntryCommentConstRef comment) const = 0;
};


class MARKUP_DLL_EXPORT ITeamWorkHelper {
public:
	virtual ~ITeamWorkHelper ();
	virtual bool IsTeamwork (void) const = 0;
	virtual ITeamWorkHelper* Clone () const = 0;
	virtual bool IsElemReservedByTwUser (short twUserId, EDB::GeneralElemConstRef elem) const = 0;
	virtual bool IsAutoReserveEnabled () const = 0;
	virtual bool IsElemAutoReservable (EDB::GeneralElemConstRef elem) const = 0;
	virtual GS::ErrorStatus ReserveMarkupEntries (PRMU::MarkupEntryRefList entries, short ownerUserId) const = 0;
	virtual GS::ErrorStatus	RequestMarkupEntries (PRMU::MarkupEntryRefList entries) const = 0;
	virtual GS::ErrorStatus ReleaseMarkupEntries (PRMU::MarkupEntryRefList entries, bool comment = false) const = 0;
	virtual GS::ErrCode AutoReserve (ODB::ObjectRefList objects, USize* nAutoReservedElems = nullptr, bool notify = true) const = 0;
};


class MARKUP_DLL_EXPORT IMarkupEditabilityChecker {
private:
	GS::Owner<IEditabilityChecker>	editabilityChecker;
	GS::Owner<ITeamWorkHelper>		twHelper;
	GS::Owner<TWUserParams>			twUserParams;

protected:
	IMarkupEditabilityChecker (IEditabilityChecker* editabilityChecker, ITeamWorkHelper* twHelper, TWUserParams* twUserParams);

public:
	virtual ~IMarkupEditabilityChecker ();

	bool TWUserHasPermissions (GS::Array<TWCB::PermissionID> permissions, short userId = 0) const;
	bool AreIssuesEditable (PRMU::MarkupEntryConstRefList entries) const;
	bool IsIssueOperationClearedForCurrentUser (const PRMU::MarkupEntryConstRefList& entries, IssueRelatedOperation operation) const;

	const IEditabilityChecker* GetEditabilityChecker () const;
	const ITeamWorkHelper* GetTeamWorkHelper () const;
	const TWUserParams* GetTWUserParams () const;
};


class MARKUP_DLL_EXPORT IAcceptedIssueElemPreparator {
public:
	virtual ~IAcceptedIssueElemPreparator ();

	virtual GSErrCode ProcessElement (const EDB::GeneralElemRef& issueElem, const EDB::GeneralElemConstRef& targetElem) const = 0;
};

} // namespace PRMU
#endif