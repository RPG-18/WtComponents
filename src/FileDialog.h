#ifndef SRC_UI_COMPONENTS_FILEDIALOG_H_
#define SRC_UI_COMPONENTS_FILEDIALOG_H_

#include <Wt/WDialog>

#include "WStringList.h"

namespace Wt
{
class WTreeView;
class FileSystemModel;

class FileDialog: public Wt::WDialog
{
public:

    FileDialog(WObject* parent = nullptr);
    virtual void accept();

    /*!
     * Get selected files and folders
     */
    Wt::WStringList selected() const;

private:

    Wt::WTreeView* m_view;
    FileSystemModel* m_fs;
};

}

#endif
