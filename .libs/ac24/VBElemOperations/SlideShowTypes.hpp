// ****************************************************************************
//                            Common SlideShow/SunStudy types
//
// Module:			ACOperations
// Namespace:		-
// Contact person:	PP
//
// [SG compatible]
// ****************************************************************************


#ifndef	VBELEMOPERATIONS_SLIDESHOWTYPES_HPP
#define	VBELEMOPERATIONS_SLIDESHOWTYPES_HPP

#pragma once

#include	"VBElemOperationsExport.hpp"

// from Geometry
#include	"Coord3d.h"

#include "TextEngine.hpp"
#include "Color.hpp"


namespace GS {
	class IChannel;
	class OChannel;
}

namespace SlideShow {


	enum class SlidesFrom : short {
		SlidesFrom3D,
		SlidesFromSymbol3D,
		SlidesFromRendering
	};

	struct VB_ELEM_OPERATIONS_DLL_EXPORT SlideType {
		Coord3D		viewPt;
		Coord3D		objPt;
		double		lightHor;
		double		lightVert;
		double		slotAng;
		double		rollAng;

		SlideType ();
	};

	struct VB_ELEM_OPERATIONS_DLL_EXPORT Wind3DSetsRec {	// Record for 3D View && Window parameters
		short		nDivSlide;		// if > 0, divide whole trajet to nDivSlide pieces else divide each interval to -nDivSlide pieces
		short		frameSizeV;		// vertical frame size of the 3d window. This is a screen measured value (native screen units).
		short		frameSizeH;		// horizontal frame size of the 3d window. This is a screen measured value (native screen units).
		short		slideMethod;	// 0 = polygon, 1 = Bezier
		bool		slideCyclic;	// after last view go to first
		bool		polygonTarget;	// polygon interp. between target points


		Wind3DSetsRec ();

		void		Clear ();

		GSErrCode	Read (GS::IChannel& ic);
		GSErrCode	Write (GS::OChannel& oc) const;
	};

	enum class SubtitlePosition : short {
		BottomLeft = 1,
		BottomCenter = 2,
		BottomRight = 3,
		TopLeft = 4,
		TopCenter = 5,
		TopRight = 6
	};

	enum class SubtitleFontSize : short {
		Small = 1,
		Medium = 2,
		Large = 3
	};

	struct	VB_ELEM_OPERATIONS_DLL_EXPORT	SlideParams {
		UInt32		startFrame;
		UInt32		endFrame;
		UInt32		startTime;	// seconds from 00:00, [0 .. 24*60*60)
		UInt32		endTime;	// seconds from 00:00, [0 .. 24*60*60)
		UInt32		diffTime;	// seconds
		bool		fromSunRiseToSunset;
		bool		allFrames;

		//Subtitle
		bool				addSubtitle;
		bool				addLocation;
		bool				addDate;
		bool				addTime;
		TE::Font			font;
		SubtitleFontSize	fontSize;
		Gfx::Color			fontColor;
		SubtitlePosition	textPosition;

		SlideParams ();
	};


}	// namespace SlideShow


#endif // VBELEMOPERATIONS_SLIDESHOWTYPES_HPP