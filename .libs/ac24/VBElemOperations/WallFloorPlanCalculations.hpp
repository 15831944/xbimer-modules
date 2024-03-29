// *********************************************************************************************************************
// Description:		Wall calculation utilities
//
// Module:			VBElemOperations
// Namespace:		
// Contact person:	MA
//
// SG compatible
// *********************************************************************************************************************

#if !defined (WALL_FLOOR_PLAN_CALCULATIONS_HPP)
#define WALL_FLOOR_PLAN_CALCULATIONS_HPP

#pragma once

// from GSRoot
#include	"IAllocator.hpp"
#include	"HandleLikeClass.hpp"
#include	"GSGuid.hpp"

// from Geometry
#include	"Point2D.hpp"
#include	"IrregularPolygon2D.hpp"

// from VBElements
#include	"Data_bits.h"
#include	"VBElementsBase.hpp"
#include	"VBElements/LineBase.hpp"

// from Phasing
#include	"PhasingTypes.hpp"

// from VBElemOperations
#include	"VBElemOperationsExport.hpp"
#include	"CompositeInfo.hpp"
#include	"GDLGlobalCalculations.hpp"
#include	"VBElemSurfaceDescriptor.hpp"


/* Uj fal L kapcsolodasanak engedelyezese */
VB_ELEM_OPERATIONS_DLL_EXPORT extern bool	newWallLT;	/* RJ(W)194 */

/* Uj fal T kapcsolodasanak engedelyezese */
VB_ELEM_OPERATIONS_DLL_EXPORT extern bool	newWallT;	/* RJ */

/* Uj fal X kapcsolodasanak engedelyezese */
VB_ELEM_OPERATIONS_DLL_EXPORT extern bool	newWallX;	/* RJ */

/* Solidos falrajzolasi kiserletek */
VB_ELEM_OPERATIONS_DLL_EXPORT extern bool	newWallSolid;	/* RJ */

namespace Cache {
class GenericCache;
}

namespace GS {
	class IChannel;
	class OChannel;
}

class DetailHandler;

namespace VBD {
	class FloorPlanCutLevels;
	typedef ODB::Ref<FloorPlanCutLevels> FloorPlanCutLevelsRef;
	typedef ODB::ConstRef<FloorPlanCutLevels> FloorPlanCutLevelsConstRef;
}


namespace VBCalculations {

#define Eps_Conn	1E-5

enum ComplexResult {
	Complex_Missing		= 0,
	Complex_Invisible	= 1,
	Complex_OK			= 2
};


struct BHATCHCORNERS {
	short	wallIndx;
	short	wallEdge;
	Coord	c1, c2;
};


struct	CW2BordRec {
public:
	CW2BordRec () :
		bordLinePen (0),
		bordLineType (),
		bordDeter (0),	
		flagBits (0),
		skip (false)
	{
	}

	short				bordLinePen;		/* Index of the border frame pen			*/
	ADB::AttributeIndex	bordLineType;		/* Index of the border frame typr			*/
	short				bordDeter;			/* InnerLine or ContourLine					*/
	short				flagBits;
	bool				skip;
};

#define Empty_HatchId -1
#define Undef_HatchId -2

struct	CW2CompRec {
public:
	CW2CompRec () :
	  cutSurface (),
	  inBoundPen (0),	
	  inBoundType (),
	  endLinePen (0),	
	  endLineType (),
	  flagBits (0),
	  frame_Flags (0),
	  laneIndex (0),
	  fillThick (0),	
	  till (0),
	  priority (0),	
	  skinType (CompInfo::Skin_Normal),	
	  noFill (false),
	  hatchId (0)
	{
	}

	CutSurface				cutSurface;
	short					inBoundPen;		/* Index of the inside frame pen			*/
	ADB::AttributeIndex		inBoundType;	/* Index of the border frame type			*/
	short					endLinePen;		/* Index of the outside frame pen			*/
	ADB::AttributeIndex		endLineType;	/* Index of the border frame type			*/
	short					flagBits;		/* Index of the frame pen					*/
	short					frame_Flags;
	short					laneIndex;
	double					fillThick;		/* absolute thickness of the component in m	*/
	double					till;
	short					priority;		/* Priority of the composite skin			*/
	CompInfo::SkinType		skinType;		/* Skin_Normal, Skin_Upper, Skin_Down		*/
	bool					noFill;			/* No fill for this composite				*/
	Int32					hatchId;		/* Hatch Id (composite index, or profile hatch Id */
};


template <class T, USize Size>
class OptionalArray {
public:
	OptionalArray ()
	{
	}

	const T& operator[] (int index) const
	{
		return data[EnsureSize (index)];
	}

	T& operator[] (int index)
	{
		return data[EnsureSize (index)];
	}

private:
	UIndex EnsureSize (int requestedSize) const
	{
		if (requestedSize < 0 || requestedSize >= Size) {
			DBBREAK_STR (GS::UniString::Printf ("Invalid index used. Index is: %d while the array size is: %u", requestedSize, Size).ToCStr ());
			if (data.IsEmpty ()) {
				data.SetSize (1);
			}
			return 0;
		}

		if (data.GetSize () < USize (requestedSize) + 1) {
			data.SetSize (requestedSize + 1);
		}

		return USize (requestedSize);
	}

	mutable GS::ArrayFB<T, Size> data;
};


struct VB_ELEM_OPERATIONS_DLL_EXPORT CW2StructRec {
public:
	CW2StructRec ();

	void SetTrapezoidSkin (VBAttr::CompWallConstRef compWall);
	void SetTrapezoidSkin (short index);
	void ShiftTrapezoidSkin (short shift);
	short GetTrapezoidSkin () const;
	void SetFirstLastNotWrappingSkin (VBAttr::CompWallConstRef compWall);
	void SetFirstLastNotWrappingSkin (short firstIndex, short lastIndex);
	void ShiftFirstLastNotWrappingSkin (short firstShift, short lastShift);
	bool HasCoreSkin ();
	bool IsNotWrappingSkin (short index) const;

	short							plMode;				/* Drawing mode			*/
	short							nSkins;				/* number of skins		*/
	EDB::OrderIndex					drawingOrderIndex;	/* Only for BestComp	*/
	short							elemPriority;		/* Only for BestComp	*/
	double							totalThick;
	OptionalArray<CW2CompRec, MaxComp>		compRec;
	OptionalArray<CW2BordRec, MaxComp + 1>	bordRec;
	double							thickness;			/* Optim. for complex wall */
	double							offset;				/* Optim. for complex wall */
	double							thickcorr;			/* Optim. for complex wall */
	double							offscorr;			/* Optim. for complex wall */
	const VBElem::Wall*				wallRef;
	Phasing::RenovationStatusType	wallStatus;
private:
	short							trapezoidSkin;			/* Trapezoid composite skin */
	short							firstNotWrappingSkin;	/* First skin not wrap around column */
	short							lastNotWrappingSkin;	/* First skin not wrap around column */
};


struct COLUWALLX {
	short				edgeInd;
	short				wallEdge;
	VBElemSurfaceDescriptor	material;
	VBElemSurfaceDescriptor	oppMat;
	bool				wallFlipped;
	Int32				wallInd;
	GS::Guid			wallGuid;
	double				arrange;
	double				virtualarrange;
	double				compThick;
	Coord				dirVect;
};


struct VB_ELEM_OPERATIONS_DLL_EXPORT WallCutPlaneData {
	VBD::FloorPlanCutLevelsConstRef						floorCutLevels;
	VBElem::ElemDisplayOptions							displayOption;
	bool												stWAbstToSt;
	VBElem::ElemViewDepthLimitations 					viewDepth;
	bool												globViewDepth;
	bool												noUpdat;

	WallCutPlaneData ();
	WallCutPlaneData (VBD::FloorPlanCutLevelsConstRef		floorCut,
					  VBElem::ElemDisplayOptions			dOpt,
					  bool									toStand,
					  VBElem::ElemViewDepthLimitations 		vDepth,
					  bool									glDepth);

	bool operator== (const WallCutPlaneData& rhs) const;
	ULong GenerateHashValue () const;
	virtual ~WallCutPlaneData ();
};


enum WallBoundaryType {
	NoBoundary = 0,
	BoundaryFirstOnly = 1,
	BoundarySecondOnly = 2,
	BoundaryBoth = 3
};


enum OverlapType {
	Overlap_Column  = 0,
	Overlap_Door    = 1,
	Overlap_Window  = 2,
	Overlap_X       = 3,
	Overlap_WallEnd = 4
};


enum SideLine
{
	DoNotShow,
	ShowForWD,
	ShowForHole
};


struct VB_ELEM_OPERATIONS_DLL_EXPORT Wallhole2PolygonInfo {
	bool					isWallhole2;			// WALLHOLE2 or WALLBLOCK2 GDL command
	ADB::AttributeIndex		fillIndex;				// fill type, 0 -> no fill
	short					fillPen;				// fill pen
	short					bkgPen;					// fill background pen
	bool					alignLocalFill;			// align local fill orientation with begC->endC
	short					fillTypeDetermination;	// DraftingFills (0), CutFills (1) or CoverFills (2)
	GX::Pattern::HatchTran	hatchTrafo;

	Wallhole2PolygonInfo () : isWallhole2 (false), fillIndex (), fillPen (0), bkgPen (0), alignLocalFill (false), fillTypeDetermination (0) {}

	// SymbBinCache miatt, verziozni nem kell
	GSErrCode	Read	(GS::IChannel& ic);
	GSErrCode	Write	(GS::OChannel& oc) const;
};

typedef Geometry::CustomIrregularPolygon2D <Geometry::PolyId, Geometry::PolyId, Geometry::PolyId, Wallhole2PolygonInfo>			WallholePolygon;
typedef Geometry::CustomMultiIrregularPolygon2D <Geometry::PolyId, Geometry::PolyId, Geometry::PolyId, Wallhole2PolygonInfo>	WallholeMultiPolygon;

class VB_ELEM_OPERATIONS_DLL_EXPORT LineBase
{
private:
	ADB::AttributeIndex	m_layer;
	short				m_drawIndex;
	VBAttr::ExtendedPen	m_ContourPen;
	ADB::AttributeIndex	m_ContourLineType;
	short				m_Determination;

public:
	LineBase ();

	// accessors
	void						SetLayer						(const ADB::AttributeIndex& layer)	{ m_layer = layer;				}
	const ADB::AttributeIndex&	GetLayer						(void) const						{ return m_layer;				}

	void						SetDrawIndex					(DrawIndex drwIndex)				{ m_drawIndex = drwIndex;		}
	DrawIndex					GetDrawIndex					(void) const						{ DBASSERT (m_drawIndex >= 0 && m_drawIndex <= MaxInt8); return static_cast<DrawIndex> (m_drawIndex); }

	void						SetContourExtendedPen			(VBAttr::ExtendedPen pen)			{ m_ContourPen = pen;			}
	VBAttr::ExtendedPen			GetContourExtendedPen			(void) const						{ return m_ContourPen;			}

	void						SetContourLineType				(const ADB::AttributeIndex& lType)	{ m_ContourLineType = lType;	}
	const ADB::AttributeIndex&	GetContourLineType				(void) const						{ return m_ContourLineType;		}

	void									SetDetermination	(VBElem::LineBase::DeterminationType detValue)	{ m_Determination = static_cast<short> (detValue);								}
	VBElem::LineBase::DeterminationType		GetDetermination	(void) const									{ return static_cast<VBElem::LineBase::DeterminationType> (m_Determination);	}

	// SymbBinCache miatt, verziozni nem kell
	GSErrCode			Read							(GS::IChannel& ic);
	GSErrCode			Write							(GS::OChannel& oc) const;
};

class VB_ELEM_OPERATIONS_DLL_EXPORT Line : public LineBase
{
private:
	Sector				m_sector;
	bool				m_treatAsArc;				// used in XColumn.c

public:
	Line ();

	const Coord&		GetBegC							(void) const					{ return m_sector.c1;			}
	const Coord&		GetEndC							(void) const					{ return m_sector.c2;			}
	const Sector&		GetSector						(void) const					{ return m_sector;				}

	void				SetBegC							(const Coord& c)				{ m_sector.c1 = c;				}
	void				SetEndC							(const Coord& c) 				{ m_sector.c2 = c;				}
	void				SetSector						(const Sector& s)				{ m_sector = s;					}

	void				SetTreatAsArc					(bool isArc)					{ m_treatAsArc = isArc;			}
	bool				TreatAsArc						(void) const					{ return m_treatAsArc;			}

	void				Transform						(const TRANMAT*	tran);

	// SymbBinCache miatt, verziozni nem kell
	GSErrCode			Read							(GS::IChannel& ic);
	GSErrCode			Write							(GS::OChannel& oc) const;
};

class VB_ELEM_OPERATIONS_DLL_EXPORT Arc : public LineBase
{
private:	
	Coord origC;
	double r;
	double mainAxisDir;
	double ratio;
	double begAng;
	double endAng;
	Coord begC;
	Coord endC;
	bool elliptic;
	bool reflected;
	bool whole;				// TODO KiP GenArc-ra cserelni

public:
	Arc ();

	// accessors
	void				SetBegC							(const Coord& coord);			
	void				SetEndC							(const Coord& coord);			
	void				SetOrigC						(const Coord& coord);			
	void				SetRadius						(const double value);			
	void				SetMainAxisDir					(const double value);			
	void				SetRatio						(const double value);			
	void				SetBegAng						(const double value);			
	void				SetEndAng						(const double value);			
	void				SetElliptic						(const bool value);				
	void				SetReflected					(const bool value);				
	void				SetWhole						(const bool value);				

	void				SetBegCAndBegAng				(const Coord& coord);
	void				SetEndCAndEndAng				(const Coord& coord);
	void				CalcBegEndCo					(void);
	void				TraBackToArcSys					(Coord* c) const;
	bool				ValidArcPoint					(const Coord	*c) const;
	double				ComputeEllipsFi					(const Coord *pt) const;
	void				ComputeEllipsCoord				(double fi, Coord *pt) const;

	const Coord&		GetOrigC						(void) const;
	const double&		GetRadius						(void) const;
	const double&		GetMainAxisDir					(void) const;
	const double&		GetRatio						(void) const;
	const double&		GetBegAng						(void) const;
	const double&		GetEndAng						(void) const;
	const Coord&		GetBegC							(void) const;
	const Coord&		GetEndC							(void) const;
	const bool&			IsElliptic						(void) const;
	const bool&			GetReflected					(void) const;
	const bool&			GetWhole						(void) const;

	const GenArc		GetArc							(void) const;
	void				SetArc							(const GenArc& arc);

	void				Transform						(const TRANMAT*	tran);

	// SymbBinCache miatt, verziozni nem kell
	GSErrCode			Read							(GS::IChannel& ic);
	GSErrCode			Write							(GS::OChannel& oc) const;
};


struct VB_ELEM_OPERATIONS_DLL_EXPORT WD2SectType{
	double		sectMax;	/* Maximum ertek a referencia oldalon		*/
	double		sectMin;	/* Minimum ertek a referencia oldalon		*/
	double		sectOppMax;	/* Maximum ertek az ellentetes oldalon		*/
	double		sectOppMin;	/* Minimum ertek az ellentetes oldalon		*/
	Coord		sBord[4];	/* A kivagott hatarvonal					*/
	Int32		nBord;		/* A pontok szama az sBord-ban				*/
	Coord		sBord2[4];	/* A kivagott hatarvonal 2: OBB-bol vag-vszg*/
	Int32		nBord2;		/* A pontok szama az sBord2-ben	       -vszg*/
	Int32		indRef;		/* A szekciohoz tartozo referencia index	*/
	Int32		indOpp;		/* A szekcio masik vegehez tartozo index	*/
	Int32		dummyL;
	bool		reveal;		/* Reveal-os-e a szekcio					*/
	bool		maxIn;		/* A ref. oldalon van-e a maximum ertek 	*/
	char		outOfWall;	/* Kilogas, 0: bent van, 1: kilog, 2: hataron csak rev.  */
	OverlapType	overlapType;/* Tipus, oszlop:0, ablak:2, ajto:1, X:3, falveg:4  */
	bool		wrapCol;	/* Korbefolyos-e az oszlop								 */
	bool		toCore;		/* Korbefolyos oszlopnal nincs korbefolyas a core alatt	 */
	bool		fromCore;	/* Korbefolyos oszlopnal nincs korbefolyas a core felett */
	char		filler_0;
	Int32		compBits;	/* X eseten a hatar mely retegnel rajzolando (bitjeloles)*/
	short		pen;		/* A fal szine								*/
	SideLine	sideLine;	/* Kell-e rajzolni az adott ablaknal   -vszg*/
	bool		from3d;		/* A 3d rajzolja a kihagyott helyre			*/
	short		filler_1;
	EDB::GeneralElemConstRef	cdwHole;
	bool		wallhole;	/* 2D Wallhole								*/
	WallholeMultiPolygon					clippPolygonsWallHole;
	ProfileMultiPolygon						clippPolygonsColumn;
	GS::Array<Line>					wallLines;
	GS::Array<Arc>					wallArcs;


	Int32		GetNumPolygons		(void) const;

	void		CutElem				(Int32 polygonIndex, const Sector& cutSector, Geometry::Boundary cutBoundaries, GS::Array<Sector>& results) const;
	void		CutElem				(Int32 polygonIndex, const GenArc& cutArc, Geometry::Boundary cutBoundaries, GS::Array<GenArc>& results) const;

	void		ElemPolyDifference	(Int32 polygonIndex, const Sector& cutSector, Geometry::Boundary cutBoundaries, GS::Array<Sector>& results) const;
	void		ElemPolyDifference	(Int32 polygonIndex, const GenArc& cutArc, Geometry::Boundary cutBoundaries, GS::Array<GenArc>& results) const;
};


struct WallBeamConnectionEnvir {
	WallBeamConnectionEnvir () :
		sect (20),
		sectEnds (10),
		sectWD2 (20),
		sectHoleWD2 (20)
	{
		nSect   = 0;
		nEnd    = 0;
		nSectWD2 = 0;
		nSectHoleWD2 = 0;

		sect.SetSize (sect.GetCapacity ());
		sectEnds.SetSize (sectEnds.GetCapacity ());
		sectWD2.SetSize (sectWD2.GetCapacity ());
		sectHoleWD2.SetSize (sectHoleWD2.GetCapacity ());

		sectEnds[0] = 0;
	}
	~WallBeamConnectionEnvir()
	{
	}
	UIndex								nSect;			/* Number of sects					*/
	UIndex								nEnd;			/* Number of sectEnds				*/
	GS::Array<double>					sect;			/* Sect factors						*/
	GS::Array<Int32>					sectEnds;		/* Sect factors ends for one edge	*/
	UIndex								nSectWD2;		/* Number of sectWD  				*/
	GS::Array<WD2SectType>				sectWD2;		/* WD sects							*/
	UIndex								nSectHoleWD2;	/* Number of sectHoleWD  				*/
	GS::Array<WD2SectType>				sectHoleWD2;	/* WD2DWALLHOLE sects					*/
};


struct FlagBitsAndLine {
	short							flagBits;
	Line							line;
	VBElem::WallConstRef			wallRef;
	VBElem::WallConstRef			wallRefBoundOther;
	WallBoundaryType				wallBoundary;
};


struct FlagBitsAndArc {
	short							flagBits;
	Arc								arc;
	VBElem::WallConstRef			wallRef;
	VBElem::WallConstRef			wallRefBoundOther;
	WallBoundaryType					wallBoundary;
};


struct DirAndTransf {
	double	h_Angle;	/* Irnya a hatch irnyhoz			*/
	Coord	refP;		/* Ref. point a soft insul-hoz      */
	Coord	origP;		/* Origo a soft insul-hoz			*/
	double	fillThick;	/* Thickness a a soft insul-hoz     */
	short   dirFlags;
};


struct JointSectRec2 {
	double								ordB;		/* Rendezshez hasznlt kezdeti rtk a ref vonalon 	*/
	double								ordE;		/* Rendezshez hasznlt vg rtk a ref vonalon     	*/
	double								sectB;		/* A kapcsold rteg kezdeti T pontja (a vIndex len) 	*/
	double								sectE;		/* A kapcsold rteg vg T pontja (a vIndex len) 		*/
	double								vxB;		/* A kapcsold rteg kezdeti x irnya 					*/
	double								vyB;		/* A kapcsold rteg kezdeti y irnya 					*/
	double								vxE;		/* A kapcsold rteg vg x irnya 						*/
	double								vyE;		/* A kapcsold rteg vg y irnya 						*/
	double								rB;			/* A kapcsold rteg kezdeti arc sugara (-1, ha nincs)	*/
	double								rE;			/* A kapcsold rteg vg arc sugara (-1, ha nincs)		*/
	DirAndTransf						dirAndTransf;/* A kapcsold fal irnya es pars a hatch irnyhoz	*/
	Int32								vIndex;		/* Ehhez az lhez kapcsoldik T-ben a msik fal 				*/
	Int32								oIndex;		/* Ebbe a referencia lbe kapcsoldik. A rendezsnl hasznlja 	*/
	short								sIndex;		/* A rteg indexe											*/
	short								stoIndex;	/* Annak a rtegnek az indexe aminek a szine s fille kell	*/
	short								frameLRFlags;	/* Oldalrajzols flag: 1 s 2 bit: oldal, 3 bit: vizsz.	*/
	bool								side12;		/* Referencia vonalon van-e a csatlakozs vagy szemben		*/
	bool								conLT;		/* LT csatlakoz elem										*/
	CutSurface							cutSurface;
	short								bordLeft;
	short								bordRight;
	short								bordTop;
	short								bordBottom;
	GSAttributeIndex					bordLeftType;
	GSAttributeIndex					bordRightType;
	GSAttributeIndex					bordTopType;
	GSAttributeIndex					bordBottomType;
	short								bordLeftDeter;
	short								bordRightDeter;
	short								bordTopDeter;
	short								bordBottomDeter;
	short								bordLeftFlagBits;
	short								bordRightFlagBits;
	short								bordTopFlagBits;
	short								bordBottomFlagBits;
	short								bordLeftMaxPrior;
	short								bordRightMaxPrior;
	short								bordTopMaxPrior;
	short								bordBottomMaxPrior;
	bool								bordLeftBoundary;
	bool								bordRightBoundary;
	bool								bordTopBoundary;
	bool								bordBottomBoundary;
	const VBElem::Wall*					bordLeftWallRef;
	const VBElem::Wall*					bordRightWallRef;
	const VBElem::Wall*					bordTopWallRef;
	const VBElem::Wall*					bordBottomWallRef;
	const VBElem::Wall*					bordLeftWallRefBoundOther;
	const VBElem::Wall*					bordRightWallRefBoundOther;
	const VBElem::Wall*					bordTopWallRefBoundOther;
	const VBElem::Wall*					bordBottomWallRefBoundOther;
	short								flagBits;
	CompInfo::SkinType					skinType;
	short								priority;  
	bool								noFill;
	short								hatchCutLine;
	GSAttributeIndex					hatchCutLineType;
	Int32								hatchId;
	const VBElem::Wall*					wallRef;
};


struct SkinPointInf {
	short	sind;				/* Skin index						*/
	short	bind;				/* Skin index beg corner			*/
	short	eind;				/* Skin index end corner			*/
	short	pen;				/* Pen of the LT line				*/
	ADB::AttributeIndex	lType;	/* LType of the LT line				*/
	short	deter;				/* InnerLine or ContourLine			*/
	short	flagBits;
	short   prior;
	CutSurface	cutSurface;
	short	invis;				/* 0: visib, 1:invis (in column)	*/
	double  angle;				/* angle of the LT line				*/
	const VBElem::Wall*	wallRef;
};			/* Wall LT coords					*/


struct DirAnglePars {
	double	dirAngle;				/* Iranya a hatch iranyhoz					*/
	double  dirAngle1;				/* Iranya a hatch iranyhoz (trapezos)		*/
	Coord	begRefP[MaxComp + 1];	/* Ref. point a soft insul-hoz (retegenkent)*/
	Coord	origo;					/* Origo a soft insul-hoz					*/
	bool    circFlag;
	bool    begFlag;
	bool    xMirrorFlag;
};


struct WallComputingEnvir {
	WallComputingEnvir (GS::IAllocator& inallocator, Cache::GenericCache* const pGenericCache = nullptr) :
		nTJoin (0),
		maxTJoin (20),
		actDrawIndex (0),
		actCW2 ((VBCalculations::CW2StructRec*)inallocator.Alloc (sizeof (VBCalculations::CW2StructRec))),
		tJoin (inallocator, maxTJoin * sizeof (JointSectRec2), maxTJoin),
		allocator (inallocator),
		isPrinting (false),
		nCollectedSkin (0),
		begGerbeStatus (false),
		endGerbeStatus (false),
		begLT (false),
		endLT (false),
		numBPlus (0),
		numEPlus (0),
		dirAnglePars (),
		dirAndTransf (),
		collectedSkinFillPriority (0),
		collectedSkinCutLine (0),
		collectedSkinCutLineType (0),
		collectedSkinHatchId (0),
		pGenericCache (pGenericCache)
	{
		new (actCW2) VBCalculations::CW2StructRec ();
	}
	~WallComputingEnvir()
	{
		actCW2->VBCalculations::CW2StructRec::~CW2StructRec ();
		if (actCW2 != nullptr)
			allocator.Free(actCW2);
	}

	Cache::GenericCache* GetGenericCachePtr () const { return pGenericCache; }

/*------------------------------Member variables----------------------------*/

	VBElem::WallRef						actWall;	/* Actual wall						*/
	short								actDrawIndex; /* Actual wall draw index			*/
	VBCalculations::CW2StructRec*		actCW2;		/* Actual composite values			*/
/*-------------------------------Line buffering-----------------------------*/
	GS::Array<FlagBitsAndLine>			linst;		/* Lines							*/
/*-------------------------------Arc buffering------------------------------*/
	GS::Array<FlagBitsAndArc>			arcst;			/* Arcs							*/
/*-------------------------------TJoin handling-----------------------------*/
	short								nTJoin;			/* Number of T Joint sects			*/
	short								maxTJoin;		/* Number of T Joint sects records	*/
	GS::HandleLikeClass<JointSectRec2>	tJoin;			/* T Joint sects factors			*/
/*------------------------------LT skin handling----------------------------*/
	bool								begGerbeStatus;		/* Gerbevagas dimension and status at the beginning	*/
	bool								endGerbeStatus;		/* Gerbevagas dimension and status at the end		*/
	bool								begLT;			/* LT or T at the beginning			*/
	bool								endLT;			/* LT or T at the end				*/
	short								numBPlus;		/* Number of new begpoints			*/
	short								numEPlus;		/* Number of new endpoints			*/
	Coord								begPlus[3*MaxComp+4];	/* The new points to begin	*/
	Coord								endPlus[3*MaxComp+4];	/* The new points to end	*/
	OptionalArray<SkinPointInf, 3 * MaxComp + 4>	begInf;		/* Informations of the new  */
	OptionalArray<SkinPointInf, 3 * MaxComp + 4>	endInf;		/* Informations of the new  */
/*--------------------------------------------------------------------------*/
	DirAnglePars						dirAnglePars;
	DirAndTransf						dirAndTransf;

	GS::IAllocator& 					allocator;
	bool								isPrinting;

	Int32								nCollectedSkin;				/* # of skins in wall2Polys array		*/
	Geometry::MultiIrregularPolygon2D	collectedWall2Polys;		/* fills of wall to unify if it is overrided by renovation override style */
	CutSurface							collectedSkinCutSurface;
	short								collectedSkinFillPriority;	/* fill priority							*/
	short								collectedSkinCutLine;
	ADB::AttributeIndex					collectedSkinCutLineType;
	Int32								collectedSkinHatchId;
/*--------------------------------Cache pointer------------------------------*/
	Cache::GenericCache*	const		pGenericCache;
};


struct DrawSectCN2Data {
	static const Int32	nc = 5;
	Int32				skinIdx;
	Coord				hatchCol[6];
	Int32				na;
	PolyArcRec			hatchArcCol[4];
	DrawSectCN2Data (Int32 skinIdx, const Coord (&hatchColInput)[6], Int32 na, const PolyArcRec (&hatchArcColInput)[4]) : skinIdx (skinIdx), na (na)
	{
		hatchCol [0] = hatchColInput [0];
		hatchCol [1] = hatchColInput [1];
		hatchCol [2] = hatchColInput [2];
		hatchCol [3] = hatchColInput [3];
		hatchCol [4] = hatchColInput [4];
		hatchCol [5] = hatchColInput [5];

		hatchArcCol [0] = hatchArcColInput [0];
		hatchArcCol [1] = hatchArcColInput [1];
		hatchArcCol [2] = hatchArcColInput [2];
		hatchArcCol [3] = hatchArcColInput [3];
	}
};


enum DisplayOptionAndViewDepthSource {FillFromWCutPlaneData, FillFromElem};

void VB_ELEM_OPERATIONS_DLL_EXPORT GetDisplayOptionAndViewDepth (	VBElem::WallConstRef					pWall,
																	const WallCutPlaneData*					wCutPlane,
																	VBElem::ElemDisplayOptions&				displayOption,
																	VBElem::ElemViewDepthLimitations& 		viewDepth);


ComplexResult VB_ELEM_OPERATIONS_DLL_EXPORT	ComplexCalculateThicknessAndOffset (const VBElem::WallConstRef&					pWall,
																				double*										thickness,
																				double*										offset,
																				const short									showElemFloor,
																				EffectiveComposite::Structure				structureDisplay,
																				VBD::FloorPlanCutLevelsConstRef				floorPlanCutLevels,
																				VBElem::ElemDisplayOptions					displayOption,
																				VBElem::ElemViewDepthLimitations			viewDepth,
																				const EDB::FloorStructureConstRef&			floorStructure,
																				CompInfo::CompositeInfo*					compInfo  = nullptr,
																				double*										thickCorr = nullptr,
																				double*										offsCorr  = nullptr);


bool VB_ELEM_OPERATIONS_DLL_EXPORT /*TODO_D-116_MA: ConnectWalls lekoltoztetes utan static*/ StoreWallSector (bool								flippedWall,
													const Geometry::IrregularPolygon2D&	poly,
													Sector*								wallSector,
													GenArc*								wallArc);


bool VB_ELEM_OPERATIONS_DLL_EXPORT StoreWallSector (bool				flippedWall,
													const Coord*		wallCoord,
													Sector*				wallSector,
													const PolyArcRec*	wPolyArcsPtr,
													GenArc*				wallArc);


void VB_ELEM_OPERATIONS_DLL_EXPORT TestW2MatWidth (	VBCalculations::CW2StructRec* c_PLCWptr,
													EffectiveComposite::Structure structureDisplay,
													double*                       refWidth,
													double*                       oppWidth);


bool VB_ELEM_OPERATIONS_DLL_EXPORT CorrFacPoints (	VBElem::WallConstRef					pWall2,
													const Geometry::IrregularPolygon2D&		wPoly,
													double* const							mb,
													double* const							me,
													bool* const								begOut,
													bool* const								endOut,
													Coord* const							corner,
													const WallBeamConnectionEnvir* const	wbce);


Int32 VB_ELEM_OPERATIONS_DLL_EXPORT GetTrapezoidSkinInd (const VBCalculations::CW2StructRec* pCW2, bool turned);


Int32 VB_ELEM_OPERATIONS_DLL_EXPORT GetFirstLastCoreInd (	const VBCalculations::CW2StructRec*		pCW2,
															bool									firstCore);


double VB_ELEM_OPERATIONS_DLL_EXPORT ComputeAndCorrRotFi (	const bool                      begOut,
															const bool                      endOut,
															const Coord* const              wallOrigo,
															const Coord* const              begC,
															const Coord* const              endC,
															const bool                      chfl,
															const WallComputingEnvir* const wce);

void VB_ELEM_OPERATIONS_DLL_EXPORT GetMinMax_Sect  (const Int32								ind,
													double* const							min,
													double* const							max,
													const WallBeamConnectionEnvir* const	wbce);


void VB_ELEM_OPERATIONS_DLL_EXPORT CorrEBPlus (	bool                      begOut,
												bool                      endOut,
												const Int32               skinInd,
												const bool                normDir,
												Coord*                    hatchCol,
												Int32*                    nArcs,
												PolyArcRec*				  hatchArcCol,
												const bool                chfl,
												WallComputingEnvir* const wce);


static inline void SetCN2Skin (	const Int32					nc,
								const Coord					(&hatchCol)[6],
								const Int32					na,
								const PolyArcRec			(&hatchArcCol)[4],
								Int32*						nCoo,
								Coord*						skinCoo,
								Int32*						nCoa,
								PolyArcRec*					skinArc)
{
	Int32	i;


	for (*nCoo = nc, i = 0; i < nc && DBVERIFY (i < 6); ++i)
		skinCoo[i] = hatchCol[i];
	for (*nCoa = na, i = 0; i < na && DBVERIFY (i < 4); ++i)
		skinArc[i] = hatchArcCol[i];

	return;
}

void VB_ELEM_OPERATIONS_DLL_EXPORT	GetWall2Core (	short										showElemFloor,
													VBCalculations::WallCutPlaneData*			wCutPlane,
													VBElem::WallConstRef						pWall2,
													const Geometry::IrregularPolygon2D&			wPoly,
													VBCalculations::CW2StructRec*				wCW2,
													Int32*										nCoo,
													Coord*										coreCoo,
													Int32*										nCoa,
													PolyArcRec*									coreArc,
													SkinMergeMode								skinMergeMode,
													const DetailHandler*						detailHandler,
													const VBCalculations::GDLGlobalCalcEnvir&	gdlGlobals );



} // namespace VBCalculations

#endif