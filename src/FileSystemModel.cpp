#include <map>
#include <iostream>
#include <algorithm>
#include <boost/filesystem.hpp>

#include "FileSystemModel.h"
using namespace boost::filesystem;

namespace
{
struct TreeNode
{
    enum Type
    {
        File, Directory
    };

    std::string filename;
    std::string path;
    TreeNode* parent;
    std::vector<TreeNode*> children;
    Type type;
    bool childrenLoaded;

    TreeNode(TreeNode* prnt = nullptr) :
            parent(prnt),
            type(Directory),
            childrenLoaded(false)
    {
        if (parent)
        {
            parent->children.push_back(this);
        }
    }

    ~TreeNode()
    {
        parent = nullptr;
        for (TreeNode* child : children)
        {
            delete child;
        }
        children.clear();
    }

    size_t loadChildren()
    {
        if (childrenLoaded)
        {
            return children.size();
        }

        boost::filesystem::path p(path);

        childrenLoaded = true;
        size_t count = 0;

        try
        {
            for (directory_iterator iter(p), end; iter != end; ++iter)
            {
                auto itm = new TreeNode(this);
                itm->filename = iter->path().filename().string();
                itm->path = iter->path().string();
                itm->type =
                        is_directory(iter->path()) ?
                                TreeNode::Directory : TreeNode::File;
                ++count;
            }

            std::sort(children.begin(), children.end(),
                    [](const TreeNode* a, const TreeNode* b)
                    {
                        return a->filename<b->filename;
                    });

            return count;
        } catch (const filesystem_error&)
        {
            return 0;
        }
    }
};

std::map<TreeNode::Type, std::string> FILE_SYSTEM_ICONS =
{
{ TreeNode::File, "icons/document.png" },
{ TreeNode::Directory, "icons/yellow-folder-open.png" } };

}
namespace Wt
{

struct FileSystemModelPrivate
{
    FileSystemModelPrivate() :
            root(new TreeNode)
    {
        root->filename = "/";
        root->path = "/";
    }

    std::unique_ptr<TreeNode> root;
};

FileSystemModel::FileSystemModel(WObject* parent) :
        WAbstractItemModel(parent),
        m_impl(new FileSystemModelPrivate)
{
}

int FileSystemModel::columnCount(const WModelIndex& parent) const
{
    return 1;
}

int FileSystemModel::rowCount(const WModelIndex& parent) const
{
    if (parent.isValid())
    {

        TreeNode* node = static_cast<TreeNode*>(parent.internalPointer());
        if (node == nullptr || node->type == TreeNode::File)
        {
            return 0;
        }

        return node->childrenLoaded ?
                node->children.size() : node->loadChildren();

    }
    else
    {
        //Unix root '/'
        return 1;
    }

    return 0;
}

WModelIndex FileSystemModel::parent(const WModelIndex& index) const
{
    if (!index.isValid())
    {
        return WModelIndex();
    }

    auto node = static_cast<TreeNode*>(index.internalPointer());
    if (node->parent == nullptr)
    {
        return WModelIndex();
    }

    if (node->parent->parent == nullptr)
    {
        return createIndex(0, 0, m_impl->root.get());
    }

    const auto grand = node->parent->parent;
    const auto parent = node->parent;

    const auto res = std::lower_bound(grand->children.cbegin(),
            grand->children.cend(), parent);

    const size_t row = std::distance(grand->children.cbegin(), res);

    return createIndex(row, 0, parent);
}

boost::any FileSystemModel::data(const WModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return boost::any();
    }

    auto node = static_cast<TreeNode*>(index.internalPointer());
    if (node == nullptr)
    {
        return boost::any();
    }

    switch (role)
    {
    case DisplayRole:
    {
        return node->filename;
    }
    case Path:
    {
        return node->path;
    }
    case DecorationRole:
    {
        try
        {
            return FILE_SYSTEM_ICONS.at(node->type);
        } catch (...)
        {

            return boost::any();
        }
    }
        break;
    default:
        return boost::any();
    }
}

WModelIndex FileSystemModel::index(int row, int column,
        const Wt::WModelIndex& parent) const
{
    if (!parent.isValid())
    {
        return createIndex(0, 0, m_impl->root.get());
    }
    TreeNode* pNode = static_cast<TreeNode*>(parent.internalPointer());
    if (pNode == nullptr)
    {
        return WModelIndex();
    }

    return createIndex(row, column, pNode->children[row]);
}
boost::any FileSystemModel::headerData(int section, Orientation orientation,
        int role) const
{
    if (role == DisplayRole && orientation == Horizontal)
    {
        return "File name";
    }

    return boost::any();
}
}
