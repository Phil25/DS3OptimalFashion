#pragma once

#include <wx/wx.h>

template <typename T>
class ListPanel final : public wxScrolledWindow
{
	wxBoxSizer* sizer{nullptr};
	wxButton* adder{nullptr};
	uint32_t limit{999};

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
		if (GetListItemCount() >= limit)
			return nullptr;

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

	auto GetListItemCount() const
	{
		return sizer->GetItemCount() - 1; // button at the end
	}

	auto GetItemAtIndex(size_t index) const
	{
		return static_cast<T*>(sizer->GetItem(index)->GetWindow());
	}

	void SetLimit(uint32_t limit)
	{
		this->limit = limit;
	}

private:
	void AddListItemSelf(wxCommandEvent&)
	{
		AddListItem();
	}
};
