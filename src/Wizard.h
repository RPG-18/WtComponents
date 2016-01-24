#ifndef SRC_UI_WIZARD_H_
#define SRC_UI_WIZARD_H_

#include <map>
#include <vector>

#include <boost/any.hpp>

#include <Wt/WDialog>

namespace Wt
{
class WLabel;
class WGroupBox;
class WPushButton;
class WStackedWidget;
class WizardPage;

class Wizard: public Wt::WDialog
{
public:

    Wizard(WObject* parent = nullptr);

    void addPage(WizardPage* page);

    int currentId() const;
    WizardPage* currentPage() const;

    void setCurrentPage(int indx);

    void back();
    void next();
    void finish();

    bool validateCurrentPage() const;
    bool currentPageIsComplete() const;

    int nextId() const;

    void setField(const Wt::WString& name, const boost::any& value);
    bool testField(const Wt::WString& name) const;
    boost::any& field(const Wt::WString& name);

    void removeField(const Wt::WString& name);

private:

    void updateButtonState();

private:

    int m_currentId;
    std::vector<WizardPage*> m_pages;
    Wt::WStackedWidget* m_stack;
    Wt::WLabel* m_title;
    Wt::WGroupBox* m_subTitle;

    Wt::WPushButton* m_back;
    Wt::WPushButton* m_next;
    Wt::WPushButton* m_cancel;
    Wt::WPushButton* m_finish;

    std::map<Wt::WString, boost::any> m_fields;
};

}

#endif
