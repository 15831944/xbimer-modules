// *********************************************************************************************************************
// File:			SeparatedListBoxUtils.hpp
//
// Description:		-
//
// Project:			A-183
//
// Namespace:		DG
//
// Contact person:	KKr
//
// *********************************************************************************************************************

#ifndef UDSEPARATEDLISTBOXUTILS_HPP
#define UDSEPARATEDLISTBOXUTILS_HPP

#pragma once

// from DG
#include "DGListBox.hpp"
#include "UDDefinitions.hpp"

// from GSRoot
#include "RSTypes.hpp"
#include "SkipSet.hpp"
#include "Array.hpp"
#include "Algorithms.hpp"


namespace UD {

struct UD_DLL_EXPORT SeparatedListBoxData
{
	GS::Array<DG::Icon>				tabItemIcons;
	GS::Array<GS::UniString>		tabItemTexts;
	DGUserData						itemValue;
	GS::Ref<GS::Object>				itemObjectData;

	virtual ~SeparatedListBoxData ();
};

//TODO az observerben is le kellene kezelni a separatorok miatti indexvaltozast
class UD_DLL_EXPORT SeparatedListBoxObserver : public GS::EventObserver
{
public:
	virtual void	ListBoxClicked (const DG::ListBoxClickEvent& ev);
	virtual void	ListBoxSelectionChanged (const DG::ListBoxSelectionEvent& ev);
	virtual void	ListBoxItemDragged (const DG::ListBoxDragEvent& ev);
	virtual void	ListBoxHeaderItemClicked (const DG::ListBoxHeaderItemClickEvent& ev);
	virtual short	ListBoxHeaderItemResized (const DG::ListBoxHeaderItemResizeEvent& ev);
	virtual void	ListBoxDoubleClicked (const DG::ListBoxDoubleClickEvent& ev);
	virtual void	ListBoxContextMenuRequested (const DG::ListBoxContextMenuEvent& ev, bool* processed);
	virtual void	ListBoxTabFieldUpdate (const DG::ListBoxTabItemUpdateEvent& ev);
	virtual void	ItemFocusGained	(const DG::ItemFocusEvent& ev);
	virtual void	ItemToolTipRequested (const DG::ItemHelpEvent& ev, GS::UniString* toolTipText);
	
	virtual			~SeparatedListBoxObserver ();
};

template <class ListBoxType>
class SeparatedListBox : DG::ListBoxObserver,
	GS::EventSource
{
	static_assert (GS::IsCompatible<ListBoxType, DG::ListBox>, "ListBoxType should be derived from DG::ListBox");
private:
	short				lastSelectedItem;
	GS::SkipSet<short>	separators;
	ListBoxType			listBox;

	bool				isCheckBoxEnabled;
	short				checkBoxTab;

	bool				isDragEnabled;
	short				dragIconTab;

	virtual void 		ListBoxClicked (const DG::ListBoxClickEvent& ev) override;
	virtual void		ListBoxItemDragged (const DG::ListBoxDragEvent& ev) override;
	virtual void		ListBoxMouseMoved (const DG::ListBoxMouseMoveEvent& ev, short* inArea) override;
	virtual void		ListBoxHeaderItemClicked (const DG::ListBoxHeaderItemClickEvent& ev) override;
	virtual short		ListBoxHeaderItemResized (const DG::ListBoxHeaderItemResizeEvent& ev) override;
	virtual void		ListBoxDoubleClicked (const DG::ListBoxDoubleClickEvent& ev) override;
	virtual void		ListBoxSelectionChanged (const DG::ListBoxSelectionEvent& ev) override;
	virtual void		ListBoxContextMenuRequested (const DG::ListBoxContextMenuEvent& ev, bool* processed) override;
	virtual void		ListBoxTabFieldUpdate (const DG::ListBoxTabItemUpdateEvent& ev) override;
	virtual void		ItemFocusGained	(const DG::ItemFocusEvent& ev) override;
	virtual void		ItemToolTipRequested (const DG::ItemHelpEvent& ev, GS::UniString* toolTipText) override;


	short	AddSeparatorsToIndex (short listItem) const;
	short	DeleteSeparatorsFromIndex (short selected) const;
	void	RefreshListBox ();

	GS::Array<SeparatedListBoxData> 	CreateDataTable () const;
	void RebuildListBoxFromDataTable (const GS::Array<SeparatedListBoxData> &dataArray);

public:
	SeparatedListBox (const DG::Panel& panel, short item);
	SeparatedListBox (const DG::Panel& panel, const DG::Rect& rect, DG::ListBox::ScrollType scroll = DG::ListBox::VScroll,
					  DG::ListBox::PartialItemType part = DG::ListBox::PartialItems, DG::ListBox::HeaderFlag headerFlag = DG::ListBox::NoHeader,
					  short headerSize = 0, DG::ListBox::FrameType frameType = DG::ListBox::NoFrame);
	virtual			~SeparatedListBox ();

	short						GetSelectedItem (bool ignoreLastSelected = false) const;
	GS::Array<short>			GetSelectedItems () const;
	GS::Array<short>			GetSelectedItemsHandleSeparators () const;	//TODO altalanos megoldas
	short						GetItemCount () const;

	short						GetItemIndexWithoutSeparators (short indexWithSeparator) const;

	bool						AppendItem ();
	bool						InsertItem (short insertIdx);

	void						SetTabItemText (short listItem, short tabIndex, const GS::UniString& text);
	GS::UniString				GetTabItemText (short listItem, short tabIndex) const;

	void						SelectItem (short listItem);
	void						DeselectItem (short listItem);

	void						DeleteItem (short listItem);
	void						DeleteItems (GS::Array<short> items);

	void						Resize (short hGrow, short vGrow);
	void						Move (short hDisp, short vDisp);

	void						Attach (SeparatedListBoxObserver& observer);
	void						Detach (SeparatedListBoxObserver& observer);

	bool						SetTabFieldCount (short nTabFields);
	short						GetTabFieldCount () const { return listBox.GetTabFieldCount (); }

	void						SetTabItemIcon (short listItem, short tabIndex, const DG::Icon& icon);
	DG::Icon					GetTabItemIcon (short listItem, short tabIndex) const;

	void						SetTabFieldProperties (short tabIndex, short begPos, short endPos, DG::ListBox::Justification just, DG::ListBox::Truncation trunc,
													   bool hasSeparator = false, bool status = true);
	short						GetTabFieldEndPosition (short column) const { return listBox.GetTabFieldEndPosition (column); }
	short						GetTabFieldBeginPosition (short column) const { return listBox.GetTabFieldBeginPosition (column); }

	short						GetItemWidth () const;

	void						InsertSeparator (short listItem);

	bool						WasCheckBoxTabClicked (const DG::ListBoxClickEvent& ev) const;
	bool						WasCheckBoxTabDoubleClicked (const DG::ListBoxDoubleClickEvent& ev) const;

	void						EnableCheckBox (short column);
	bool						IsCheckBoxEnabled () const { return isCheckBoxEnabled; }
	bool						GetCheckBoxState (short row) const;
	void						SetCheckBoxState (short row, bool state);

	void						EnableDrag (short iconColumn);
	bool						IsDragEnabled () const { return isDragEnabled; }

	void						SetItemObjectData (short row, GS::Ref<GS::Object> object);
	GS::Object&					GetItemObjectData (short row) const;

	void						SetHeaderItemCount (short itemCount);
	short						GetHeaderItemCount () const;

	void						SetOnTabItem (short tabIndex, const DG::Item& item);
	void						RemoveOnTabItem (short tabIndex);
	DG::Item*					GetOnTabItem (short tabIndex) const;

	void						SetItemStatus (short listItem, DG::ListBox::ItemStatus status);
	DG::ListBox::ItemStatus		GetItemStatus (short listItem) const;

	void						SetHeaderItemArrowType (short headerItem, DG::ListBox::ArrowType arrowType);
	DG::ListBox::ArrowType		GetHeaderItemArrowType (short headerItem) const;

	void						SetHeaderSynchronState (bool isSynchron);
	bool						IsHeaderInSynchronState () const;

	void						SetHeaderItemText (short headerItem, const GS::UniString& text);
	GS::UniString				GetHeaderItemText (short headerItem) const;

	void						SetHeaderPushableButtons (bool hasPushableButtons);
	bool						HasHeaderPushableButtons () const;

	void						SetHeaderDragableButtons (bool hasDragableButtons);
	void						EnableHeaderButton ();

	void						RedrawItem (short listItem);
	void						RedrawTabItem (short listItem, short tabIndex);

	void						SetFocus ();

	void						SetItemHeight (short height);
	short						GetItemHeight () const;

	void						SetItemValue (short listItem, DGUserData value);
	DGUserData					GetItemValue (short listItem) const;

	void						SetTabFieldTruncation (short tabIndex, DG::ListBox::Truncation trunc);
	void						SetTabFieldJustification (short tabIndex, DG::ListBox::Justification just);

	void						SetTabFieldBeginEndPosition (short tabIndex, short begPos, short endPos);

	void						Clear ();
	void						EnableDraw ();
	void						DisableDraw ();
	void						Redraw ();
	void						OrderListBox (short column, bool isIncreasing, bool iconOrder = false);

	void						Enable () { listBox.Enable (); }
	void						Disable () { listBox.Disable (); }

	void						SetHeaderItemSizeableFlag (short item, bool flag) { listBox.SetHeaderItemSizeableFlag (item, flag); }
	
	void						SetTabFieldOwnerDrawFlag (short tabIndex, bool ownerDraw);

	const ListBoxType&			GetListBox () const;

	void						Show (void);
	void						Hide (void);
};


template <class ListBoxType>
SeparatedListBox<ListBoxType>::SeparatedListBox (const DG::Panel& panel, short item) :
	listBox (panel, item),
	isCheckBoxEnabled (false),
	checkBoxTab (-1),
	isDragEnabled (false),
	dragIconTab (-1),
	lastSelectedItem (-1)
{
	listBox.Attach (*this);
	listBox.SetHelpStyle (DG::ListBox::HSForItem);
}	


template <class ListBoxType>
SeparatedListBox<ListBoxType>::SeparatedListBox (const DG::Panel& panel,
												 const DG::Rect& rect,
												 DG::ListBox::ScrollType scroll /*= VScroll*/,
												 DG::ListBox::PartialItemType part /*= PartialItems*/,
												 DG::ListBox::HeaderFlag headerFlag /*= NoHeader*/,
												 short headerSize /*= 0*/,
												 DG::ListBox::FrameType frameType /*= NoFrame*/) :
	listBox (panel, rect, scroll, part, headerFlag, headerSize, frameType),
	isCheckBoxEnabled (false),
	checkBoxTab (-1),
	isDragEnabled (false),
	dragIconTab (-1),
	lastSelectedItem (-1)
{
	listBox.Attach (*this);
	listBox.SetHelpStyle (DG::ListBox::HSForItem);
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::Show (void)
{
	listBox.Show ();
}	


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::Hide (void)
{
	listBox.Hide ();
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetTabFieldTruncation (short tabIndex, DG::ListBox::Truncation trunc)
{
	listBox.SetTabFieldTruncation (tabIndex, trunc);
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetTabFieldJustification (short tabIndex, DG::ListBox::Justification just)
{
	listBox.SetTabFieldJustification (tabIndex, just);
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetTabFieldBeginEndPosition (short tabIndex, short begPos, short endPos)
{
	listBox.SetTabFieldBeginEndPosition (tabIndex, begPos, endPos);
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::EnableDraw (void)
{
	listBox.EnableDraw ();
}		


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::DisableDraw (void)
{
	listBox.DisableDraw ();
}	


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::Redraw (void)
{
	listBox.Redraw ();
}	


template <class ListBoxType>
bool SeparatedListBox<ListBoxType>::WasCheckBoxTabDoubleClicked (const DG::ListBoxDoubleClickEvent& ev) const
{
	DBVERIFY (isCheckBoxEnabled);

	short pos = ev.GetMouseOffset ().GetX ();
	short beg = ev.GetSource ()->GetTabFieldBeginPosition (checkBoxTab);
	short end = ev.GetSource ()->GetTabFieldEndPosition (checkBoxTab);

	if (pos >= beg && pos <= end)
		return true;
	else
		return false;
}	


template <class ListBoxType>
bool SeparatedListBox<ListBoxType>::IsHeaderInSynchronState (void) const
{
	return listBox.IsHeaderInSynchronState ();
}	


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetHeaderSynchronState (bool isSynchron)
{
	listBox.SetHeaderSynchronState (isSynchron);
}		


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetItemHeight (short height)
{
	listBox.SetItemHeight (height);
}		


template <class ListBoxType>
short SeparatedListBox<ListBoxType>::GetItemHeight (void) const
{
	return listBox.GetItemHeight ();
}		


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetFocus (void)
{
	listBox.SetFocus ();
}		


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::RedrawTabItem (short listItem, short tabIndex)
{
	listItem = AddSeparatorsToIndex (listItem);
	listBox.RedrawTabItem (listItem, tabIndex);
}		


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::RedrawItem (short listItem)
{
	listItem = AddSeparatorsToIndex (listItem);
	listBox.RedrawItem (listItem);
}	


template <class ListBoxType>
DG::Item* SeparatedListBox<ListBoxType>::GetOnTabItem (short tabIndex) const
{
	return listBox.GetOnTabItem (tabIndex);
}		


template <class ListBoxType>
void UD::SeparatedListBox<ListBoxType>::RemoveOnTabItem (short tabIndex)
{
	listBox.RemoveOnTabItem (tabIndex);
}


template <class ListBoxType>
void UD::SeparatedListBox<ListBoxType>::DeselectItem (short listItem)
{
	listItem = AddSeparatorsToIndex (listItem);
	listBox.DeselectItem (listItem);
}

template <class ListBoxType>
void UD::SeparatedListBox<ListBoxType>::DeleteItems (GS::Array<short> items)
{
	GS::Sort (items.Begin (), items.End (), [&] (short i1, short i2) -> bool {
		return i1 > i2;
	});
	for (const auto& i : items) {
		short listItem = AddSeparatorsToIndex (i);
		listBox.DeleteItem (listItem);
	}
	RefreshListBox ();
}

template <class ListBoxType>
GS::Array<short> SeparatedListBox<ListBoxType>::GetSelectedItems (void) const
{
	return listBox.GetSelectedItems ();
}	


template <class ListBoxType>
GS::Array<short> SeparatedListBox<ListBoxType>::GetSelectedItemsHandleSeparators (void) const
{
	GS::Array<short> selectedIndices = listBox.GetSelectedItems ();

	GS::HashSet<short> separatorsIndicies;
	for (short index = 0; index < (short)selectedIndices.GetSize (); index++) {
		if (listBox.IsSeparator (selectedIndices[index]))
			separatorsIndicies.Add (index);
	}
	
	for (const auto& separatorIndex : separatorsIndicies) {
		selectedIndices.Delete (separatorIndex);
	}

	GS::Array<short> selectedIndicesWithoutSeparators;
	for (const auto& index : selectedIndices) {
		selectedIndicesWithoutSeparators.Push (DeleteSeparatorsFromIndex (index));
	}

	return selectedIndicesWithoutSeparators;
}


template <class ListBoxType>
bool SeparatedListBox<ListBoxType>::HasHeaderPushableButtons (void) const
{
	return listBox.HasHeaderPushableButtons ();
}		


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetHeaderPushableButtons (bool hasPushableButtons)
{
	listBox.SetHeaderPushableButtons (hasPushableButtons);
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::EnableHeaderButton ()
{
	listBox.EnableHeaderButton ();
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetHeaderDragableButtons (bool hasDragableButton)
{
	listBox.SetHeaderDragableButtons (hasDragableButton);
}


template <class ListBoxType>
SeparatedListBox<ListBoxType>::~SeparatedListBox ()
{
	listBox.Detach (*this);
}		


template <class ListBoxType>
short SeparatedListBox<ListBoxType>::GetSelectedItem (bool ignoreLastSelected /*= false*/) const
{
	short selected = listBox.GetSelectedItem ();

	if (selected == 0 && !ignoreLastSelected)
		return lastSelectedItem;

	return DeleteSeparatorsFromIndex (selected);

}		


template <class ListBoxType>
short SeparatedListBox<ListBoxType>::GetItemCount () const
{
	return DeleteSeparatorsFromIndex (listBox.GetItemCount ());
}
 

template <class ListBoxType>
short UD::SeparatedListBox<ListBoxType>::GetItemIndexWithoutSeparators (short indexWithSeparator) const
{
	return DeleteSeparatorsFromIndex (indexWithSeparator); 
}


template <class ListBoxType>
bool SeparatedListBox<ListBoxType>::AppendItem ()
{
	bool result = listBox.AppendItem ();
	short placeSeparatorBelowItem = 1;
	if (DBVERIFY (result)) {
		if (isCheckBoxEnabled)
			listBox.SetTabItemIcon (listBox.GetItemCount (), checkBoxTab, DG::Icon (SysResModule, DG_LIST_CHECKEDICON));

		if (isDragEnabled)
			listBox.SetTabItemIcon (listBox.GetItemCount (), dragIconTab, DG::Icon (SysResModule, DG_LIST_DRAGICON));

		while (separators.Contains (listBox.GetItemCount () + placeSeparatorBelowItem))
			listBox.InsertSeparator (listBox.GetItemCount () + placeSeparatorBelowItem);
	}

	return result;
}	



template <class ListBoxType>
bool SeparatedListBox<ListBoxType>::InsertItem (short insertIdx)
{
	bool result = listBox.InsertItem (insertIdx);
	short placeSeparatorBelowItem = 1;
	if (DBVERIFY (result)) {
		if (isCheckBoxEnabled)
			listBox.SetTabItemIcon (insertIdx, checkBoxTab, DG::Icon (SysResModule, DG_LIST_CHECKEDICON));

		if (isDragEnabled)
			listBox.SetTabItemIcon (insertIdx, dragIconTab, DG::Icon (SysResModule, DG_LIST_DRAGICON));

		while (separators.Contains (insertIdx + placeSeparatorBelowItem)) {
			listBox.InsertSeparator (insertIdx + placeSeparatorBelowItem);
			insertIdx++;
		}
	}

	return result;
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetTabItemText (short listItem, short tabIndex, const GS::UniString& text)
{
	if (DBVERIFY (!(isCheckBoxEnabled && checkBoxTab == tabIndex) || (!(isDragEnabled && dragIconTab == tabIndex)))) {
		listItem = AddSeparatorsToIndex (listItem);

		listBox.SetTabItemText (listItem, tabIndex, text);
	}
}	


template <class ListBoxType>
GS::UniString SeparatedListBox<ListBoxType>::GetTabItemText (short listItem, short tabIndex) const
{
	listItem = AddSeparatorsToIndex (listItem);

	return listBox.GetTabItemText (listItem, tabIndex);
}	


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SelectItem (short listItem)
{
	listItem = AddSeparatorsToIndex (listItem);

	listBox.SelectItem (listItem);
}	


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::DeleteItem (short listItem)
{
	listItem = AddSeparatorsToIndex (listItem);

	listBox.DeleteItem (listItem);
	RefreshListBox ();
}	


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::ListBoxClicked (const DG::ListBoxClickEvent& ev)
{
	lastSelectedItem = ev.GetSource ()->GetSelectedItem ();

	if (GS::IsSame<ListBoxType, DG::SingleSelListBox>) {
		if (isCheckBoxEnabled) {
			if (WasCheckBoxTabClicked (ev) && listBox.GetItemStatus (lastSelectedItem) == DG::ListBox::ItemStatus::Enabled) {
				bool isItemChecked = listBox.GetTabItemIcon (listBox.GetSelectedItem (), checkBoxTab).GetResourceId () == DG_LIST_CHECKEDICON;
				listBox.SetTabItemIcon (listBox.GetSelectedItem (), checkBoxTab, DG::Icon (SysResModule, isItemChecked ? DG_LIST_UNCHECKEDICON : DG_LIST_CHECKEDICON));
			}
		}
	} else {
		if (isCheckBoxEnabled) {
			if (WasCheckBoxTabClicked (ev)) {
				GS::Array<short> selectedItems = listBox.GetSelectedItems ();

				bool allItemsEnabled = true;
				bool allItemsDisabled = true;

				for (short i : selectedItems) {
					if (listBox.GetTabItemIcon (i, checkBoxTab).GetResourceId () == DG_LIST_CHECKEDICON)
						allItemsDisabled = false;
					if (listBox.GetTabItemIcon (i, checkBoxTab).GetResourceId () == DG_LIST_UNCHECKEDICON)
						allItemsEnabled = false;
				}

				for (short i : selectedItems) {
					if (!allItemsDisabled && !allItemsEnabled) {
						listBox.SetTabItemIcon (i, checkBoxTab, DG::Icon (SysResModule, DG_LIST_CHECKEDICON));
					} else if (listBox.GetItemStatus (i) == DG::ListBox::ItemStatus::Enabled) {
						bool isItemChecked = listBox.GetTabItemIcon (i, checkBoxTab).GetResourceId () == DG_LIST_CHECKEDICON;
						listBox.SetTabItemIcon (i, checkBoxTab, DG::Icon (SysResModule, isItemChecked ? DG_LIST_UNCHECKEDICON : DG_LIST_CHECKEDICON));
					}
				}
			}
		}
	}

	for (auto it = EnumerateObservers (); it != nullptr; ++it) {
		SeparatedListBoxObserver* observer = static_cast<SeparatedListBoxObserver*>(&*it);
		observer->ListBoxClicked (ev);
	}
}		


template <class ListBoxType>
bool	SeparatedListBox<ListBoxType>::WasCheckBoxTabClicked (const DG::ListBoxClickEvent& ev) const
{
	DBVERIFY (isCheckBoxEnabled);

	short pos = ev.GetMouseOffset ().GetX ();
	short beg = ev.GetSource ()->GetTabFieldBeginPosition (checkBoxTab);
	short end = ev.GetSource ()->GetTabFieldEndPosition (checkBoxTab);

	return (pos >= beg && pos <= end);
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::ListBoxItemDragged (const DG::ListBoxDragEvent& ev)
{
	for (auto it = EnumerateObservers (); it != nullptr; ++it) {
		SeparatedListBoxObserver* observer = static_cast<SeparatedListBoxObserver*>(&*it);
		observer->ListBoxItemDragged (ev);

	}
}	


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::ListBoxSelectionChanged (const DG::ListBoxSelectionEvent& ev)
{
	for (auto it = EnumerateObservers (); it != nullptr; ++it) {
		SeparatedListBoxObserver* observer = static_cast<SeparatedListBoxObserver*>(&*it);
		observer->ListBoxSelectionChanged (ev);

	}
}	


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::ListBoxContextMenuRequested (const DG::ListBoxContextMenuEvent& ev, bool* processed)
{
	for (auto it = EnumerateObservers (); it != nullptr; ++it) {
		SeparatedListBoxObserver* observer = static_cast<SeparatedListBoxObserver*>(&*it);
		observer->ListBoxContextMenuRequested (ev, processed);
	}
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::ListBoxTabFieldUpdate (const DG::ListBoxTabItemUpdateEvent& ev)
{
	for (auto it = EnumerateObservers (); it != nullptr; ++it) {
		SeparatedListBoxObserver* observer = static_cast<SeparatedListBoxObserver*>(&*it);
		observer->ListBoxTabFieldUpdate (ev);
	}
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::ItemFocusGained (const DG::ItemFocusEvent& ev)
{
	for (auto it = EnumerateObservers (); it != nullptr; ++it) {
		SeparatedListBoxObserver* observer = static_cast<SeparatedListBoxObserver*>(&*it);
		observer->ItemFocusGained (ev);
	}
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::ItemToolTipRequested (const DG::ItemHelpEvent& ev, GS::UniString* toolTipText)
{
	for (auto it = EnumerateObservers (); it != nullptr; ++it) {
		SeparatedListBoxObserver* observer = static_cast<SeparatedListBoxObserver*>(&*it);
		observer->ItemToolTipRequested (ev, toolTipText);
	}
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::ListBoxMouseMoved (const DG::ListBoxMouseMoveEvent& ev, short* inArea)
{
	if (!isDragEnabled)
		return;

	short left = listBox.GetTabFieldBeginPosition (dragIconTab);
	short right = listBox.GetTabFieldEndPosition (dragIconTab);
	if (ev.GetMouseOffset ().GetX () >= left && ev.GetMouseOffset ().GetX () <= right) {
		if (!listBox.IsSeparator (ev.GetListItem ())) {
			DG::Icon icon = listBox.GetTabItemIcon (ev.GetListItem (), 1);
			if (icon.GetResourceId () == DG::ListBox::DragIcon)
				*inArea = DG::ListBox::DragArea;
			else
				*inArea = DG::ListBox::NoSpecArea;
		}
	}
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::ListBoxHeaderItemClicked (const DG::ListBoxHeaderItemClickEvent& ev)
{
	for (auto it = EnumerateObservers (); it != nullptr; ++it) {
		SeparatedListBoxObserver* observer = static_cast<SeparatedListBoxObserver*>(&*it);
		observer->ListBoxHeaderItemClicked (ev);

	}
}	


template <class ListBoxType>
short SeparatedListBox<ListBoxType>::ListBoxHeaderItemResized (const DG::ListBoxHeaderItemResizeEvent& ev)
{
	for (auto it = EnumerateObservers (); it != nullptr; ++it) {
		SeparatedListBoxObserver* observer = static_cast<SeparatedListBoxObserver*>(&*it);
		observer->ListBoxHeaderItemResized (ev);

	}
	return 0;
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::ListBoxDoubleClicked (const DG::ListBoxDoubleClickEvent& ev)
{
	for (auto it = EnumerateObservers (); it != nullptr; ++it) {
		SeparatedListBoxObserver* observer = static_cast<SeparatedListBoxObserver*>(&*it);
		observer->ListBoxDoubleClicked (ev);

	}
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::EnableCheckBox (short column)
{
	if (DBVERIFY (listBox.GetItemCount () == 0 && column <= listBox.GetTabFieldCount ())) {
		isCheckBoxEnabled = true;
		checkBoxTab = column;
	}
}


template <class ListBoxType>
bool SeparatedListBox<ListBoxType>::GetCheckBoxState (short row) const
{
	short separatorsAddedToIndex = AddSeparatorsToIndex (row);
	if (DBVERIFY (isCheckBoxEnabled) && listBox.GetItemStatus (separatorsAddedToIndex) == DG::ListBox::ItemStatus::Enabled)
		return listBox.GetTabItemIcon (separatorsAddedToIndex, checkBoxTab).GetResourceId () == DG_LIST_CHECKEDICON;

	return false;
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetCheckBoxState (short row, bool state)
{
	if (DBVERIFY (isCheckBoxEnabled))
		listBox.SetTabItemIcon (AddSeparatorsToIndex (row), checkBoxTab, DG::Icon (SysResModule, state ? DG_LIST_CHECKEDICON : DG_LIST_UNCHECKEDICON));
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::EnableDrag (short iconColumn)
{
	if (DBVERIFY (listBox.GetItemCount () == 0 && iconColumn <= listBox.GetTabFieldCount ())) {
		listBox.EnableMouseMoveEvent ();
		dragIconTab = iconColumn;
		isDragEnabled = true;
	}

}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetItemObjectData (short row, GS::Ref<GS::Object> object)
{
	listBox.SetItemObjectData (AddSeparatorsToIndex (row), object);
}


template <class ListBoxType>
GS::Object& SeparatedListBox<ListBoxType>::GetItemObjectData (short row) const
{
	return *listBox.GetItemObjectData (AddSeparatorsToIndex (row));
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetHeaderItemCount (short itemCount)
{
	listBox.SetHeaderItemCount (itemCount);
}


template <class ListBoxType>
DGUserData SeparatedListBox<ListBoxType>::GetItemValue (short listItem) const
{
	return listBox.GetItemValue (AddSeparatorsToIndex (listItem));
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetItemValue (short listItem, DGUserData value)
{
	listBox.SetItemValue (AddSeparatorsToIndex (listItem), value);
}


template <class ListBoxType>
short SeparatedListBox<ListBoxType>::GetHeaderItemCount (void) const
{
	return listBox.GetHeaderItemCount ();
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetOnTabItem (short tabIndex, const DG::Item& item)
{
	listBox.SetOnTabItem (tabIndex, item);
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetItemStatus (short listItem, DG::ListBox::ItemStatus status)
{
	listBox.SetItemStatus (AddSeparatorsToIndex (listItem), status);
}


template <class ListBoxType>
DG::ListBox::ItemStatus SeparatedListBox<ListBoxType>::GetItemStatus (short listItem) const
{
	return listBox.GetItemStatus (AddSeparatorsToIndex (listItem));
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetHeaderItemArrowType (short headerItem, DG::ListBox::ArrowType arrowType)
{
	listBox.SetHeaderItemArrowType (headerItem, arrowType);
}	


template <class ListBoxType>
DG::ListBox::ArrowType SeparatedListBox<ListBoxType>::GetHeaderItemArrowType (short headerItem) const
{
	return listBox.GetHeaderItemArrowType (headerItem);
}		


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetHeaderItemText (short headerItem, const GS::UniString& text)
{
	listBox.SetHeaderItemText (headerItem, text);
}	


template <class ListBoxType>
GS::UniString SeparatedListBox<ListBoxType>::GetHeaderItemText (short headerItem) const
{
	return listBox.GetHeaderItemText (headerItem);
}	


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::Clear ()
{
	separators.Clear ();
	listBox.DeleteItem (DG::ListBox::AllItems);
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::InsertSeparator (short listItem)
{
	separators.Add (listItem);
	RefreshListBox ();
}		


template <class ListBoxType>
short SeparatedListBox<ListBoxType>::AddSeparatorsToIndex (short listItem) const
{
	for (const auto& separator : separators) {
		if (separator > listItem) {
			break;
		}
		++listItem;
	}
	return listItem;
}	


template <class ListBoxType>
short SeparatedListBox<ListBoxType>::DeleteSeparatorsFromIndex (short selected) const
{
	short offset = 0;
	for (const auto& separator : separators) {
		if (separator > selected) {
			break;
		}
		++offset;
	}

	return selected - offset;
}	


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::Resize (short hGrow, short vGrow)
{
	listBox.Resize (hGrow, vGrow);
}	


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::Move (short hDisp, short vDisp)
{
	listBox.Move (hDisp, vDisp);
}		


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::Attach (SeparatedListBoxObserver& observer)
{
	GS::EventSource::Attach (observer);
}		


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::Detach (SeparatedListBoxObserver& observer)
{
	GS::EventSource::Detach (observer);
}		


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetTabItemIcon (short listItem, short tabIndex, const DG::Icon& icon)
{
	if (DBVERIFY (!(isCheckBoxEnabled && checkBoxTab == tabIndex)))
		listBox.SetTabItemIcon (AddSeparatorsToIndex (listItem), tabIndex, icon);
}		


template <class ListBoxType>
bool SeparatedListBox<ListBoxType>::SetTabFieldCount (short nTabFields)
{
	return listBox.SetTabFieldCount (nTabFields);
}	


template <class ListBoxType>
DG::Icon SeparatedListBox<ListBoxType>::GetTabItemIcon (short listItem, short tabIndex) const
{
	if (DBVERIFY (!(isCheckBoxEnabled && checkBoxTab == tabIndex)))
		return listBox.GetTabItemIcon (AddSeparatorsToIndex (listItem), tabIndex);

	return DG::Icon ();
}	


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetTabFieldProperties (short tabIndex, short begPos, short endPos, DG::ListBox::Justification just, DG::ListBox::Truncation trunc, bool hasSeparator /*= false*/, bool status /*= true*/)
{
	listBox.SetTabFieldProperties (tabIndex, begPos, endPos, just, trunc, hasSeparator, status);
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::SetTabFieldOwnerDrawFlag (short tabIndex, bool ownerDraw)
{
	listBox.SetTabFieldOwnerDrawFlag (tabIndex, ownerDraw);
}


template <class ListBoxType>
short SeparatedListBox<ListBoxType>::GetItemWidth (void) const
{
	return listBox.GetItemWidth ();
}	


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::RefreshListBox ()
{
	if (listBox.GetItemCount () == 0)
		return;

	RebuildListBoxFromDataTable (CreateDataTable ());

}


template <class ListBoxType>
const ListBoxType&	 SeparatedListBox<ListBoxType>::GetListBox () const
{
	return listBox;
}


template <class ListBoxType>
GS::Array<SeparatedListBoxData> SeparatedListBox<ListBoxType>::CreateDataTable () const
{
	GS::Array<SeparatedListBoxData> result;
	for (short row = 1; row <= listBox.GetItemCount (); ++row) {
		if (listBox.IsSeparator (row))
			continue;

		SeparatedListBoxData data;
		for (short column = 1; column <= listBox.GetTabFieldCount (); ++column) {
			data.tabItemTexts.Push (listBox.GetTabItemText (row, column));
			data.tabItemIcons.Push (listBox.GetTabItemIcon (row, column));
		}
		data.itemValue = listBox.GetItemValue (row);
		data.itemObjectData = listBox.GetItemObjectData (row);

		result.Push (data);
	}

	return result;
}

template <class ListBoxType>
void SeparatedListBox<ListBoxType>::OrderListBox (short column, bool isIncreasing, bool iconOrder /*= false*/)
{
	--column;
	GS::Array<SeparatedListBoxData> data = CreateDataTable ();
	auto orderFunction = [&] (SeparatedListBoxData data1, SeparatedListBoxData data2) -> bool {
		if (iconOrder) {
			return data1.tabItemIcons[column] == data2.tabItemIcons[column] ? false : !((data1.tabItemIcons[column].GetResourceId () > data2.tabItemIcons[column].GetResourceId ()) ^ !isIncreasing);
		} else {
			return data1.tabItemTexts[column] == data2.tabItemTexts[column] ? false : !((data1.tabItemTexts[column] > data2.tabItemTexts[column]) ^ !isIncreasing);
		}
	};

	GS::Sort (data.Begin (), data.End (), orderFunction);
	RebuildListBoxFromDataTable (data);
}


template <class ListBoxType>
void SeparatedListBox<ListBoxType>::RebuildListBoxFromDataTable (const GS::Array<SeparatedListBoxData> &dataArray)
{
	listBox.DisableDraw ();
	listBox.DeleteItem (DG_ALL_ITEMS);

	short index = 1;
	for (short row = 1; row <= static_cast<short>(dataArray.GetSize ()); ++row) {
		short oldItemCount = listBox.GetItemCount ();
		AppendItem ();

		for (short column = 1; column <= listBox.GetTabFieldCount (); ++column) {
			listBox.SetTabItemIcon (index, column, dataArray[row - 1].tabItemIcons[column - 1]);
			listBox.SetTabItemText (index, column, dataArray[row - 1].tabItemTexts[column - 1]);
		}
		listBox.SetItemValue (index, dataArray[row - 1].itemValue);
		listBox.SetItemObjectData (index, dataArray[row - 1].itemObjectData);

		index += (listBox.GetItemCount () - oldItemCount);
	}

	listBox.EnableDraw ();
	listBox.Redraw ();
}



}		//namespace UD


#endif
