#pragma once

#include <wx/wx.h>

template <typename T>
class ListPanel final : public wxScrolledWindow
{
	wxBoxSizer* sizer{nullptr};
	wxButton* adder{nullptr};

public:
	ListPanel(wxWindow* parent)
		: wxScrolledWindow(parent)
		, sizer(new wxBoxSizer(wxVERTICAL))
		, adder(new wxButton(this, wxID_ANY, wxT("New")))
	{
		adder->Bind(wxEVT_BUTTON, &ListPanel<T>::AddListItemSelf, this);

		sizer->Add(adder, 0, wxALIGN_CENTER | wxTOP, 10);

		this->SetScrollRate(5, 5);
		this->SetSizerAndFit(sizer);
	}

	auto AddListItem() -> T*
	{
		auto* item = new T(this);

		sizer->Insert(sizer->GetItemCount() - 1, item, 1, wxALIGN_CENTER);
		sizer->Layout();

		this->SetSizerAndFit(sizer);
		this->GetParent()->GetSizer()->Layout();

		this->Scroll(0, 9999);

		return item;
	}

	void RemoveListItem(wxWindow* item)
	{
		const bool detachSuccess = sizer->Detach(item);
		assert(detachSuccess);

		item->Destroy();
		sizer->Layout();

		this->SetSizerAndFit(sizer);
		this->GetParent()->GetSizer()->Layout();
	}

private:
	void AddListItemSelf(wxCommandEvent&)
	{
		AddListItem();
	}
};
