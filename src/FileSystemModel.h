#ifndef SRC_UI_COMPONENTS_FILESYSTEMMODEL_H_
#define SRC_UI_COMPONENTS_FILESYSTEMMODEL_H_

#include <memory>

#include <Wt/WAbstractItemModel>

namespace Wt
{

struct FileSystemModelPrivate;

/*!
 * @brief FileSystemModel class.
 *
 *The FileSystemModel class provides a data model for the local filesystem.
 */
class FileSystemModel: public Wt::WAbstractItemModel
{
public:

    enum Roles
    {
        Name = Wt::UserRole + 1, Path = Wt::UserRole
    };

    FileSystemModel(Wt::WObject* parent = nullptr);

    bool isFile(const Wt::WModelIndex& index) const;
    bool isDir(const Wt::WModelIndex& index) const;

    virtual int columnCount(const Wt::WModelIndex& parent =
            Wt::WModelIndex()) const;

    virtual int rowCount(const Wt::WModelIndex& parent =
            Wt::WModelIndex()) const;

    virtual Wt::WModelIndex parent(const Wt::WModelIndex& index) const;

    virtual boost::any data(const Wt::WModelIndex& index, int role =
            Wt::DisplayRole) const;

    virtual Wt::WModelIndex index(int row, int column,
            const Wt::WModelIndex& parent = Wt::WModelIndex()) const;

    virtual boost::any headerData(int section, Orientation orientation =
            Horizontal, int role = DisplayRole) const;
private:

    std::unique_ptr<FileSystemModelPrivate> m_impl;
};

}

#endif
