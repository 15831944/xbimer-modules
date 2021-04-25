// *****************************************************************************
// File:			DGWPFTexts.hpp
//
//
// Namespace:		DG
//
// Contact person:	DGY
//
// SG compatible
// *****************************************************************************

#ifndef	DGWPFTexts_HPP
#define	DGWPFTexts_HPP

// --- Includes ----------------------------------------------------------------

#include "WPFText.hpp"
#include "DG.h"

namespace TE {
class Font;
class IRichText;
class IParagraph;
class IRun;
}

namespace Gfx {
class Color;
}

namespace DGWPFText {

class DG_DLL_EXPORT ParagraphFilter
{
public:
	virtual const TE::IParagraph* Get (const TE::IParagraph* src) { return src; }
};

class DG_DLL_EXPORT RunFilter
{
public:
	virtual const TE::IRun* Get (const TE::IRun* src) { return src; }
};

DG_DLL_EXPORT WPFText::ISimpleText* CreateSimpleText (const GS::UniString& text, const TE::Font& font, const Gfx::Color& color);
DG_DLL_EXPORT WPFText::IRichText* CreateRichText (const TE::IRichText& rtext, ParagraphFilter* pFilter = nullptr, RunFilter* rFilter = nullptr);



}	// namespace DGWPFText


#endif
