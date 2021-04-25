// *********************************************************************************************************************
// Converts Remark data of the MarkupEntry
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (REMARKCONVERSIONDATA_HPP)
#define REMARKCONVERSIONDATA_HPP

#pragma once
// --- Includes --------------------------------------------------------------------------------------------------------

// from Markup
#include "EntryRemark.hpp"

// from ODB
#include "ODBConversionData.hpp"

namespace PRMU {
class MARKUP_DLL_EXPORT RemarkConversionData : public ODB::ConversionData
{
	DECLARE_DYNAMIC_CLASS_INFO (RemarkConversionData);
private:
	EntryRemark remark;
public:
	RemarkConversionData () = default;
	RemarkConversionData (const EntryRemark& oldRemark);
	RemarkConversionData (const RemarkConversionData& source);
	virtual ~RemarkConversionData () = default;

	virtual GS::Object* Clone	(void) const override;
	virtual GSErrCode	Write	(GS::OChannel& oc) const override;
	virtual GSErrCode	Read	(GS::IChannel& ic) override;	

	inline const EntryRemark &GetOldRemark () const { return remark; }
};


} // namespace PRMU

#endif
