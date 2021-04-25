#if !defined __GDL_GDLIPDICTIONARYPATHCACHE_HPP__
#define __GDL_GDLIPDICTIONARYPATHCACHE_HPP__

#include "GDLExport.h"

#include "GSUnID.hpp"
#include "Ref.hpp"
#include "HashTable.hpp"
#include "GDLDictionaryPath.hpp"
#include "GDLFile.h"


namespace GDL
{
class DictionaryPathStructureSerializer;

struct GDL_DLL_EXPORT DictionaryPathStructure
{
	friend class DictionaryPathStructureSerializer;
public:
	explicit DictionaryPathStructure (const FieldName& firstFieldName);

	const GS::Array<Int32>&		GetIndicesToRead () const;
	void						ModifyArrayIndex (UInt32 itemIndex, UIndex arrayIndex);
	const DictionaryPath&		GetPath () const;

private:
	DictionaryPath		pathScheme;
	GS::Array<Int32>	indicesToRead;
};


class GDL_DLL_EXPORT DictionaryPathStructureSerializer
{
public:
	GSErr		AddFieldName (const char* name);
	GSErr		AddIndex ();

	const GS::String&						SerializedPath ();
	static GS::Ref<DictionaryPathStructure>	DeSerializePath (GS::String serializedPath);

private:
	struct ParsedPathItem
	{
		FieldName	fieldName;
		bool		hasIndex;

		explicit ParsedPathItem (FieldName fieldName, bool hasIndex);
	};
	static ParsedPathItem		ParseNextPathItem (const char** remainingPath);
	static FieldName			ParseNextFieldName (const char** remainingPath);
	static bool					ParseNextHasIndex (const char** remainingPath);


	static const char PathId_BeginFieldChar		= '.';
	static const char PathId_IndexPlaceholder	= '#';

	GS::String	serializedPath;
};


class GDL_DLL_EXPORT CodeAreaRuntimeCache
{
public:
	typedef UInt32	CodeAreaIndex;

	DictionaryPathStructure*	GetVolatileEditableDictionaryPathStructure (CodeAreaIndex codeAreaIndex, const std::function<GS::String (CodeAreaIndex)>& resolveIdIndexFn);
	UIndex						GetIdTableIndex (CodeAreaIndex codeAreaIndex, const std::function<UIndex (CodeAreaIndex)>& insertAndResolveFn);
	UIndex						GetStringTableIndex (CodeAreaIndex codeAreaIndex, const std::function<UIndex (CodeAreaIndex)>& insertAndResolveFn);
	UIndex						GetParNamesListTableIndex (CodeAreaIndex codeAreaIndex, const std::function<UIndex (CodeAreaIndex)>& insertAndResolveFn);

private:
	UIndex						GetCachedIndex (GS::Array<Int32>& cache, CodeAreaIndex codeAreaIndex, const std::function<UIndex (CodeAreaIndex)>& insertAndResolveFn);

	GS::Array<GS::Ref<DictionaryPathStructure>>		pathInfos;
	GS::Array<Int32>								idTableIndices;
	GS::Array<Int32>								stringTableIndices;
	GS::Array<Int32>								parNamesListTableIndices;
};

class GDL_DLL_EXPORT CodeAreaRuntimeCacheContainer
{
public:
	CodeAreaRuntimeCacheContainer ();
	CodeAreaRuntimeCacheContainer (const CodeAreaRuntimeCacheContainer&) = delete;
	CodeAreaRuntimeCacheContainer& operator= (const CodeAreaRuntimeCacheContainer&) = delete;

	CodeAreaRuntimeCache&	RetrieveCache (const ConstBinCodePtr& ptr);

	GS::HashTable<ConstBinCodePtr, GS::Owner<CodeAreaRuntimeCache>>	instances;
};

}


#endif