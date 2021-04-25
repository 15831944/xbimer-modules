
// *********************************************************************************************************************
// Holds all TagSets
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (MARKUPTAGSETCONTAINER_HPP)
#define MARKUPTAGSETCONTAINER_HPP
#endif

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from Markup
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"

// from TWRoot
#include "IResolvableObjectSet.hpp"
#include "TWObject.hpp"

// --- Forward declarations	------------------------------------------------------------------------------------------------


// --- Type definitions -------------------------------------------------------------------------------------------

namespace PRMU {

class MARKUP_DLL_EXPORT TagSetContainer : public TW::Object,
										  public TW::IResolvableObjectSet
{
	DECLARE_DYNAMIC_CLASS (TagSetContainer)

private:
	void SetStatusTagSet (TagSetRef tagSet);
	void SetPriorityTagSet (TagSetRef tagSet);

public:
	TagSetContainer ();
	TagSetContainer (const TagSetContainer& source);
	virtual ~TagSetContainer ();

	virtual TagSetContainer* Clone () const override;

	static TagSetContainerConstRef GetTagSetContainer (TagSetConstRef tagSet);
	static TagSetContainerRef GetTagSetContainer (TagSetRef tagSet);

	static TagSetRef GetStatusTagSet (TagSetContainerRef container);
	TagSetConstRef GetStatusTagSet () const;

	static TagSetRef GetPriorityTagSet (TagSetContainerRef container);
	TagSetConstRef GetPriorityTagSet () const;

		// TW::IResolvableObjectSet methods

	virtual TWCB::PermissionID			GetCreatePermissionID					() const override;
	virtual TWCB::PermissionID			GetDeleteModifyPermissionID				() const override;
	virtual GS::PagedArray<GS::Guid>	GetAssociationsForModificationDetection	() const override;

	virtual void						ResolveConflicts (const TW::IResolvableObjectSetConstIRef& resolvableObjectSet) override;
};
}	//namespace PRMU