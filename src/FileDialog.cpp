#include <iostream>

#include <Wt/WTreeView>
#include <Wt/WVBoxLayout>
#include <Wt/WPushButton>

#include "FileDialog.h"
#include "FileSystemModel.h"

namespace Wt
{
using namespace Wt;

FileDialog::FileDialog(WObject* parent) :
        WDialog(parent),
        m_view(new WTreeView()),
        m_fs(new FileSystemModel(this))

{
    setWindowTitle("Selecting files and directories");

    auto cancel = new WPushButton("Cancel", footer());
    cancel->clicked().connect(this, &WDialog::reject);

    auto select = new WPushButton("Select", footer());
    select->clicked().connect(this, &FileDialog::accept);

    m_view->setModel(m_fs);
    m_view->setSelectionBehavior(SelectItems);
    m_view->setSelectionMode(ExtendedSelection);
    m_view->setSortingEnabled(false);
    m_view->setHeaderHeight(0);
    m_view->expandToDepth(1);

    auto layout = new WVBoxLayout;
    layout->addWidget(m_view);
    contents()->setLayout(layout);

    resize(600, 500);
}

void FileDialog::accept()
{
    const auto indxs = m_view->selectedIndexes();
    if (indxs.size() > 0)
    {
        WDialog::accept();
    }
}

Wt::WStringList FileDialog::selected() const
{
    WStringList list;
    const auto indxs = m_view->selectedIndexes();
    for (auto indx : indxs)
    {
        const WString pt = boost::any_cast<std::string>(
                indx.data(FileSystemModel::Path));
        list << pt;
    }

    return list;
}

}
