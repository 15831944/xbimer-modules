// *********************************************************************************************************************
// Edit TagSet To Entry Command
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef EDITTAGSETCOMMAND_HPP
#define EDITTAGSETCOMMAND_HPP

#pragma once

// from ODB
#include "MVCCommand.hpp"
#include "ODBIdSpace.hpp"
#include "ODBMD5DifferenceGenerator.hpp"

// from Markup
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"
#include "TagSet.hpp"

// from GSRoot
#include "AutoPtr.hpp"
#include "ClassInfo.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT EditTagSetCommand : public MVC::CommandImp {
	DECLARE_DYNAMIC_CLASS_INFO (EditTagSetCommand)

private:
	class IdSpaceContentEnumerator : public ODB::MD5DifferenceGenerator::ObjectSet {
	private:
		ODB::IdSpace* idSpace;
	public:
		explicit IdSpaceContentEnumerator (ODB::IdSpace* idSpace);

		virtual void	EnumerateObjects (ODB::MD5DifferenceGenerator::ObjectSet::ConstObjectEnumerator* enumerator) const override;
	};

	ODB::IdSpace*					idSpace;
	TagSetRef						originalTagSet;
	TagSetRef						editedTagSet;
	ODB::MD5DifferenceGenerator*	differenceGenerator;
	IdSpaceContentEnumerator*		idSpaceContentEnumerator;


	EditTagSetCommand ();
	EditTagSetCommand (const EditTagSetCommand& source);
	EditTagSetCommand& operator= (const EditTagSetCommand& source);

	GS::ErrorStatus FillAndTraceNewIdSpace ();
public:
	EditTagSetCommand (TagSetRef tagSet);
	~EditTagSetCommand ();


	virtual GS::ErrorStatus Execute (void) override;

	TagSetRef GetTagSet () const;
};

}


#endif