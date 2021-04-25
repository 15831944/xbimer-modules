// *********************************************************************************************************************
// MarkupEntry: Record to manage a set of elements in redlining
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (MARKUPENTRY_HPP)
#define MARKUPENTRY_HPP


// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "EventSource.hpp"

// from ObjectDatabase
#include "ODBDependencyNode.hpp"
#include "ODBDynamicObject.hpp"

// VBElements
#include "EDBGeneralDefinitions.hpp"

// from Markup
#include "EntryComment.hpp"
#include "EntryComponent.hpp"
#include "EntryComponentTypes.hpp"
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"

// --- Forward declarations	------------------------------------------------------------------------------------------------

namespace EDB {
class IElemDatabase;
class GeneralElem;
typedef ODB::Ref<GeneralElem>		GeneralElemRef;
typedef ODB::ConstRef<GeneralElem>	GeneralElemConstRef;
class Floor;
typedef ODB::Ref<Floor>		FloorRef;
}

namespace PRMU {
class ITeamWorkHelper;
class IMarkupEditabilityChecker;
}

namespace VBElem {
class Word;
typedef ODB::Ref<Word>	WordRef;
}

namespace VBES {
class ElemSet;
typedef ODB::Ref<ElemSet>		ElemSetRef;
typedef ODB::ConstRef<ElemSet>	ElemSetConstRef;
}

namespace PRMU {

// === MarkupEntryClientData class ===============================================================================================


class MARKUP_DLL_EXPORT MarkupEntryClientData : public ODB::DynamicObject
{
	DECLARE_DYNAMIC_CLASS (MarkupEntryClientData)

public:
	MarkupEntryClientData ();
	MarkupEntryClientData (bool _turnedOn);
	~MarkupEntryClientData ();

	bool					IsTurnedOn (void) const;
	void					SetTurnedOn (bool _turnedOn);

	MarkupEntryConstRef		GetMarkupEntry (void) const;

protected:
	virtual GSErrCode		WriteIsolatedState (GS::OChannel& oc) const override;
	virtual GSErrCode		ReadIsolatedState (GS::IChannel& ic) override;

private:
	GSErrCode				WriteIsolatedStateVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode				ReadIsolatedStateVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);


};


class MARKUP_DLL_EXPORT MarkupEntryConstructionData {
public:
	GS::UniString					name;
	ODB::ConstRef<MarkupEntry>		parent;

	GS::UniString					ownerFullName;
	GS::Guid						ownerId;

	MarkupEntrySetRef				entrySet;

	PRMU::TagValueRef				priority;
	PRMU::TagValueRef				status;

	bool							onOffSwitch;
	GS::Optional<GSTime>			dueDate;
	GS::HashSet<GS::UniString>		labels;
	GS::UniString					description;
	GS::HashSet<GS::UniString>		responsibles;

	MarkupEntryConstructionData (const GS::UniString&					name,
								 const GS::Guid&						ownerId,
								 const GS::UniString&					ownerFullName,
								 const MarkupEntrySetRef&				entrySet = nullptr,
								 const ODB::ConstRef<MarkupEntry>&		parent = nullptr,
								 const TagValueRef&						priority = nullptr,
								 const TagValueRef&						status = nullptr,
								 bool									onOffSwitch = true,
								 const GS::Optional <GSTime>&			dueDate = GS::Optional <GSTime> (),
								 const GS::UniString&					description = GS::EmptyUniString,
								 const GS::HashSet<GS::UniString>&		labels = GS::HashSet<GS::UniString> (),
								 const GS::HashSet<GS::UniString>&		responsibles = GS::HashSet<GS::UniString> ());

	MarkupEntryConstructionData (const MarkupEntryConstructionData& source) = delete;
	void* operator new(size_t size) = delete;
	void operator delete(void*) = delete;


};

// === MarkupEntry class ===============================================================================================

class MARKUP_DLL_EXPORT MarkupEntry : public TW::Object,
	public GS::EventSource
{
	DECLARE_DYNAMIC_CLASS (MarkupEntry)

	friend class MarkupEntryReflection;


private:
	static GS::Guid markupEntryViewAssocId;
	static GS::Guid commentAssociationId;
	static GS::Guid markupComponentsAssocId;
	// ... Constructors / destructor ...................................................................................
	MarkupEntry (const MarkupEntry&		source);

	MarkupEntry ();

	MarkupEntry (const GS::UniString&			name,
				 ODB::ConstRef<MarkupEntry>		parent,
				 const GS::Optional <GSTime>&	dueDate);
public:
	~MarkupEntry ();

	static MarkupEntryRef		CreateEntry (const MarkupEntryConstructionData& constructionData, const ITeamWorkHelper* twHelper);
	static MarkupEntryRef		CreateUnreservedEntry (const MarkupEntryConstructionData& constructionData);

	bool		operator== (const MarkupEntry& entry) const;

	// ... Accessors	................................................................................................

	static HistoryEntryConstRefList GetHistory (const MarkupEntryConstRef& entry);
	static void AddHistory (const MarkupEntryRef& entry, const HistoryEntryRefList& newHistory);

	MarkupEntryConstRef			GetParentEntry () const;

	const GS::UniString			GetName () const;

	bool						HasPriority () const;
	PRMU::TagValueConstRef		GetPriority () const;
	static void					SetPriority (const MarkupEntryRef& entry, const PRMU::TagValueRef& newPriority);

	bool						HasStatus () const;
	PRMU::TagValueConstRef		GetStatus () const;
	static void					SetStatus (const MarkupEntryRef& entry, const PRMU::TagValueRef& newStatus);

	GS::UniString				GetType () const;
	void						SetType (const GS::UniString& newType);

	GS::Array<GS::UniString>	GetReferenceLinks () const;
	void						SetReferenceLinks (const GS::Array<GS::UniString>& newReference);

	void						AddLabel (const GS::UniString& newLabel);
	void						RemoveLabels ();
	void						RemoveLabels (const GS::UniString& labelToRemove);
	void						RemoveLabels (const GS::Array<GS::UniString>& labelsToRemove);
	void						SetLabels (const GS::HashSet<GS::UniString>& newLabels);
	GS::HashSet<GS::UniString>	GetLabels () const;
	GS::UniString				GetLabelsToString () const;

	void						AddResponsible (const GS::UniString& newResponsible);
	void						RemoveResponsibles ();
	void						RemoveResponsible (const GS::UniString& responsibleToRemove);
	void						RemoveResponsibles (const GS::HashSet<GS::UniString> responsiblesToRemove);
	void						SetResponsibles (const GS::HashSet<GS::UniString>& newResponsibles);
	void						SetResponsiblesFromString (const GS::UniString& newResponsibles, const GS::UniString& separatorChars);
	GS::HashSet<GS::UniString>	GetResponsibles () const;
	GS::UniString				GetResponsiblesAsString () const;

	GS::UniString				GetDescription () const;
	void						SetDescription (const GS::UniString& newDescription);

	GS::Optional<GSTime>		GetDueDate () const;
	void						SetDueDate (const GS::Optional <GSTime>& newDate);
	GS::UniString				GetDueDateString () const;

	GS::UniString				GetStage () const;
	void						SetStage (const GS::UniString& newStage);

	GSTime						GetCreationTime () const;
	GSTime						GetModificationTime () const;

	GS::Guid					GetCreatorGuid () const;
	GS::UniString				GetCreatorFullName () const;
	void						SetCreator (const GS::Guid& pCreatorId, const GS::UniString& pCreatorFullName);
	GS::Guid					GetLastModifierGuid () const;
	GS::UniString				GetLastModifierFullName () const;
	void						SetLastModifier (const GS::Guid& pLastModifierId, const GS::UniString& pLastModifierFullName);

	static GS::Guid							GetEntryViewAssociationId ();
	static GS::Guid							GetCommentAssociationId ();
	static GS::Guid							GetComponentsAssociationId ();
	bool									ContainsCommentGuid (const GS::Guid& commentGuid) const;
	EntryCommentConstRefList				GetCommentList () const;
	static EntryCommentRefList				GetCommentList (MarkupEntryRef entry);
	EntryCommentConstRef					GetLastComment () const;
	EntryCommentRef							GetLastCommentRef ();
	static EntryCommentRef					AddComment (const PRMU::MarkupEntryRef&			markupEntry,
														const GS::Guid&						userId,
														const GS::UniString&				str,
														PRMU::EntryComment::CommentStatus	status = PRMU::EntryComment::Unknown,
														const GS::UniString&				verbalStatus = "",
														const GS::Guid&						commentId = GS::NULLGuid,
														const GS::UniString&				author = "",
														GSTime								commentCreaTime = TIGetTime ());

	const GS::Guid						GetHandlerGuid () const;
	GS::Guid							GetIdForBCF () const;

	GSErrCode							AddEntryView (const EntryViewRef& view);
	GSErrCode							DeleteEntryView (const EntryViewRef& view);
	EntryViewConstRefList				GetEntryViews () const;
	EntryViewConstRef					GetEntryViewByName (const GS::UniString& entryViewName) const;
	PRMU::EntryCommentRef				GetCommentByExternalGuidString (const GS::UniString& guidString) const;
	PRMU::EntryViewRef					GetEntryViewByExternalGuidString (const GS::UniString& guidString) const;
	EntryViewConstRef					GetFirstEntryView () const;
	static	EntryViewRefList			GetEntryViews (const PRMU::MarkupEntryRef& entry);
	static  EntryViewConstRef			GetEntryViewByName (const PRMU::MarkupEntryConstRef& entry, const GS::UniString& entryViewName);
	static	MarkupEntryRef				GetMarkupEntryByEntryView (const PRMU::EntryViewRef& entryView);
	static	MarkupEntryConstRef			GetMarkupEntryByEntryView (const PRMU::EntryViewConstRef& entryView);
	static	MarkupEntryRef				GetMarkupEntryByEntryComment (const PRMU::EntryCommentRef& entryComment);
	static	MarkupEntryConstRef			GetMarkupEntryByEntryComment (const PRMU::EntryCommentConstRef& entryComment);
	static	MarkupEntryRef				GetMarkupEntryByRemark (const RemarkRef& remark);
	static  MarkupEntryConstRef			GetConstMarkupEntryByEntryComponent (const EntryComponentConstRef& entryComponent);
	static  MarkupEntryRef				GetMarkupEntryByEntryComponent (const EntryComponentRef& entryComponent);
	static  MarkupEntryRefList			GetMarkupEntriesByEntryComponents (const PRMU::EntryComponentRefList& entryComponents);
	static	MarkupEntryConstRefList		GetMarkupEntriesByElem (const EDB::GeneralElemConstRef& elem);
	static  MarkupEntryRefList			GetMarkupEntriesByEntryViews (const PRMU::EntryViewRefList& entryViews);

	static void							FillTagValuesWithDefaults (const MarkupEntrySetRef& entrySet, PRMU::MarkupEntryRef entry);
	static void							FillStatusWithDefault (const TagSetConstRef& statusTagSet, PRMU::MarkupEntryRef entry);
	static void							FillPriorityWithDefault (const TagSetConstRef& priorityTagSet, PRMU::MarkupEntryRef entry);

	static void							AddComponents (const MarkupEntryRef& entry, const EntryComponentRefList& components);
	static void							AddComponents (const MarkupEntryRef& entry, const EntryComponentRefList& components, EntryViewRef entryView);
	static void							RemoveComponent (const MarkupEntryRef& entry, const EntryComponentRef& component);
	static bool							IsRelatedComponent (const MarkupEntryRef& entry, const EntryComponentRef& component);
	static bool							IsRelatedComponent (const MarkupEntryConstRef& entry, const EntryComponentConstRef& component);
	EntryComponentConstRefList			GetComponents () const;
	static EntryComponentRefList		GetComponents (const MarkupEntryRef& entry);
	static EntryComponentConstRefList	GetComponentsByElems (const EDB::GeneralElemConstRefList& elem);
	static EntryComponentRefList		GetComponentsByElems (const EDB::GeneralElemRefList& elem);
	static EntryComponentConstRefList	GetComponentsByElem (const MarkupEntryConstRef& entry, const EDB::GeneralElemConstRef& elem);
	static EntryComponentRefList		GetComponentsByElem (const MarkupEntryRef& entry, const EDB::GeneralElemConstRef& elem);
	static EntryComponentConstRefList	GetComponentsByElemInModel (const EDB::GeneralElemConstRef& elem);
	static EntryComponentConstRefList	GetComponentsByElemOutOfModel (const EDB::GeneralElemConstRef& elem);
	static EDB::GeneralElemConstRef		GetCorrespondingElem (const PRMU::MarkupEntryConstRef& entry, EDB::GeneralElemConstRef elem);
	EntryComponentConstRefList			GetComponentsByType (EntryComponent::Type type) const;
	EntryComponentConstRefList			GetSuggestions () const;

	static bool							IsMarkupOutOfModelElement (const EDB::GeneralElemConstRef& elem);

protected:
	EntryComponentRefList				GetComponents ();

public:
	struct ConstMethods : public ODB::ConstMethods<MarkupEntry> {
		EntryComponentRefList			GetComponents () {	return GetPtr()->GetComponents (); }
	};
	
	EDB::GeneralElemConstRefList		GetRelatedElements () const;
	static	EDB::GeneralElemRefList		GetRelatedElements (const PRMU::MarkupEntryRef& entry);
	EDB::GeneralElemConstRefList		GetAllRelatedElements () const;
	static	EDB::GeneralElemRefList		GetAllRelatedElements (const PRMU::MarkupEntryRef& entry);

	EDB::GeneralElemConstRefList		GetElementsByComponentType (EntryComponent::Type type) const;

	EDB::GeneralElemConstRefList		GetModificationInElement () const;
	EDB::GeneralElemConstRefList		GetModificationOutElement () const;
	EDB::GeneralElemConstRefList		GetSuggestionElements () const;
	bool								HasElementsOutOfModel () const;
	EDB::GeneralElemConstRefList		GetElementsOutOfModel () const;
	static EDB::GeneralElemRefList		GetElementsOutOfModel (const PRMU::MarkupEntryRef& entry);
	EDB::GeneralElemConstRefList		GetElementsInModel () const;
	static EntryComponent::Type			GetComponentType (const EDB::GeneralElemConstRef& elem);
	static EntryComponent::Type			GetComponentType (const PRMU::EntryComponentConstRef& component);

	bool								IsRelatedElement (const EDB::GeneralElemConstRef& elem) const;
	static bool							IsRelatedElementStatic (const EDB::GeneralElemConstRef& elem);
	bool								IsHighlightedElement (const EDB::GeneralElemConstRef& elem) const;
	bool								IsModificationElement (const EDB::GeneralElemConstRef& elem) const;
	bool								IsModificationInElement (const EDB::GeneralElemConstRef& elem) const;
	bool								IsModificationOutElement (const EDB::GeneralElemConstRef& elem) const;
	bool								IsCreationElement (const EDB::GeneralElemConstRef& elem) const;
	bool								IsDeletionElement (const EDB::GeneralElemConstRef& elem) const;
	bool								IsInModelElement (const EDB::GeneralElemConstRef& elem) const;
	bool								IsOutOfModelElement (const EDB::GeneralElemConstRef& elem) const;
	bool								IsConnectedComment (const EntryCommentRef& comment) const;

	bool						IsTurnedOn () const;

	void						PostChanges (const MarkupEntry& originalEntry);

	// Modifiers
	void						SetParentEntry (const MarkupEntryConstRef& parent);

	void						SetName (const GS::UniString& str);

	void						SetCreationTime (const GSTime& time);
	void						SetModificationTime (const GSTime& time);

	void						SetHandlerGuid (const GS::Guid& guid);
	void						SetExternalId (const GS::Guid& guid);

	static void					TWReceivePostProcess (const MarkupEntryRef& markupEntry);
	static void					SetTurnedOn (const MarkupEntryRef& markupEntry, bool newState);

	void						ConvertToOldAssociations (const PRMU::MarkupEntrySetRef& entrySet, const VBES::ElemSetRef& elemSet, const EDB::FloorRef& floor);
	void						ConvertToNewAssociations (const PRMU::MarkupEntrySetRef& entrySet);
	EDB::GeneralElemRefList		FilterOldPaintedElems () const;
	void						ConvertToOldRemark ();
	void						ConvertToNewRemark ();
	void						ConvertToOldParentEntry ();
	void						ConvertToNewParentEntry ();

	void						Share ();

	PRMUAC22::AssignInfoRef			CreateAssignInfo ();
	PRMUAC22::AssignInfoConstRef	GetAssignInfo () const;
	static PRMUAC22::AssignInfoRef	GetAssignInfo (const MarkupEntryRef& markupEntry);
	static MarkupEntryRef			GetEntryFromAssignInfo (const PRMUAC22::AssignInfoRef& assignInfo);

	// Object realization
	virtual GSErrCode			Read (GS::IChannel& ic) override;

	void 						Debug (void) const;

	static void					RemoveElemFromGroup (const EDB::GeneralElemRef& elem);

private:
	static void		AddCommentSorted (const PRMU::MarkupEntryRef& markupEntry, EntryCommentRef commentRef);
	void 			PostNameChangedEvent ();
	void			PostRemarkChangedEvent ();
	void			PostRemarkPlacementChangedEvent ();
	void			PostRemarkVisibilityChangedEvent ();
	void			PostCommentAddedEvent () const;
	void			PostElemlistChangedEvent ();
	void			PostEntryOnOffSwitchChangedEvent () const;

	EntryViewRef		GetFirstAvailableEntryView ();
	bool				ElemIsOwnedByGroup (const EDB::GeneralElemRef& elem);

protected:
	virtual GSErrCode	WriteIsolatedState (GS::OChannel& oc) const override;
	virtual GSErrCode	ReadIsolatedState (GS::IChannel& ic) override;
	virtual	GSErrCode	WriteTWIsolatedState (GS::OChannel& oc) const override;
	virtual	GSErrCode	ReadTWIsolatedState (GS::IChannel& ic) override;

private:
	GSErrCode	ReadIsolatedStateVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode	ReadCoreIsolatedStateVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode	ReadIsolatedStateVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode	ReadIsolatedStateVersion3 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode	WriteCoreIsolatedStateVersion4 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode	ReadCoreIsolatedStateVersion4 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode	WriteIsolatedStateVersion4 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode	ReadIsolatedStateVersion4 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode	ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode	ReadVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);
};

// === Helper functions ================================================================================================

MARKUP_DLL_EXPORT void							DeleteMarkupEntry (const MarkupEntryRef& entry);
MARKUP_DLL_EXPORT MarkupEntryRefList			GetMarkUpEntriesByOldElemSet (const VBES::ElemSetRef& elemSet);

MARKUP_DLL_EXPORT GS::Guid						GetOwnedElementsAssocId ();
MARKUP_DLL_EXPORT GS::Guid						GetPaintedElementsAssocId ();
MARKUP_DLL_EXPORT GS::Guid						GetOwnedCommentsAssocId ();
MARKUP_DLL_EXPORT GS::Guid						GetAssignInfoAssocId ();

MARKUP_DLL_EXPORT bool							IsMarkupedElement (const EDB::GeneralElemConstRef& elem);
MARKUP_DLL_EXPORT bool							IsMarkupedElementOutOfModel (const EDB::GeneralElemConstRef& elem);
MARKUP_DLL_EXPORT bool							IsMarkupedElementInModel (const EDB::GeneralElemConstRef& elem);

MARKUP_DLL_EXPORT MarkupEntryConstRef			GetMarkupEntryByElemOutOfModel (const EDB::GeneralElemConstRef& elem);
MARKUP_DLL_EXPORT MarkupEntryRef				GetMarkupEntryByElemOutOfModel (const EDB::GeneralElemRef& elem);
MARKUP_DLL_EXPORT MarkupEntryConstRefList		GetMarkupEntryByElemInModel (const EDB::GeneralElemConstRef& elem);
MARKUP_DLL_EXPORT MarkupEntryRefList			GetMarkupEntryByElemInModel (const EDB::GeneralElemRef& elem);
MARKUP_DLL_EXPORT MarkupEntryConstRefList		GetMarkupEntryByElem (const EDB::GeneralElemConstRef& elem);
MARKUP_DLL_EXPORT MarkupEntryRefList			GetMarkupEntryByElem (const EDB::GeneralElemRef& elem);

MARKUP_DLL_EXPORT MarkupEntryRef				GetIFCCompareEntry (const EDB::GeneralElemRef& elemRef, const GS::UniString&	nameFormat);

MARKUP_DLL_EXPORT MarkupEntryRef				GetMarkUpEntryByAssignInfo (const PRMUAC22::AssignInfoRef& assignInfoRef);

MARKUP_DLL_EXPORT void							ShowMarkUpEntriesByElem (const EDB::GeneralElemRef& elem);

MARKUP_DLL_EXPORT void							ConvertMarkupFromAC11 (EDB::IElemDatabase* db, const VBES::ElemSetRef& elemSet);

MARKUP_DLL_EXPORT MarkupClientConversionData* 	ConvertMarkupFromAC19 (MarkupEntryConstRef& markupEntry);
MARKUP_DLL_EXPORT void							ConvertMarkupToAC19 (MarkupEntryRef& markupEntry, const MarkupClientConversionData* conversionData);

extern MARKUP_DLL_EXPORT ODB::DependencyNode	clientDataToEntryPropagator;
extern MARKUP_DLL_EXPORT ODB::DependencyNode	markupToNewOutOfModelElemPropagator;
extern MARKUP_DLL_EXPORT ODB::DependencyNode	entyCompomentToElementChangePropagator;

}	// namespace PRMU


#endif
