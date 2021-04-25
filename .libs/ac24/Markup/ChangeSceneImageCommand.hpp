// *********************************************************************************************************************
// Description:		ChangeSceneImageCommand class
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	FEs
//
// *********************************************************************************************************************

#ifndef CHANGESCENEIMAGECOMMAND_HPP
#define CHANGESCENEIMAGECOMMAND_HPP

#pragma once

#include "MarkupExport.hpp"

#include "MarkupTypes.hpp"

#include "Ref.hpp"
#include "MarkupCommandBase.hpp"

namespace GX {
class Image;
typedef GS::Ref<Image> ImageRef;
}

namespace PRMU {

class MARKUP_DLL_EXPORT ChangeSceneImageCommand : public MarkupCommandBase {
	DECLARE_DYNAMIC_CLASS_INFO (ChangeSceneImageCommand)

private:
	PRMU::EntryViewRef  entryView;
	GX::ImageRef		img;

private:
	ChangeSceneImageCommand ();
	ChangeSceneImageCommand (const ChangeSceneImageCommand& source); //disabled
	ChangeSceneImageCommand& operator= (const ChangeSceneImageCommand& source); //disabled

public:
	ChangeSceneImageCommand (const IMarkupEditabilityChecker* checker, 
							 PRMU::EntryViewRef  entryView,
							 GX::ImageRef img);

	virtual GS::ErrorStatus ExecuteInternal (void) override;
};

}

#endif