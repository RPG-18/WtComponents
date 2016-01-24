#ifndef SRC_UI_WIZARDPAGE_H_
#define SRC_UI_WIZARDPAGE_H_

#include <Wt/WContainerWidget>

namespace Wt
{

class Wizard;
class WizardPage: public Wt::WContainerWidget
{
    friend class Wizard;

public:

    WizardPage(Wt::WContainerWidget* parent = nullptr);

    virtual void cleanupPage();
    virtual void initializePage();
    virtual bool isComplete() const;
    virtual bool validatePage();
    virtual int nextId() const;

    bool isFinalPage() const;
    void setFinalPage(bool isFinal);

    const Wt::WString& title() const;
    void setTitle(const Wt::WString& title);

    const Wt::WString& subTitle() const;
    void setSubTitle(const Wt::WString& subTitle);

protected:

    Wizard* wizard() const;

private:

    void setWizard(Wizard* wizard);

private:
    Wt::WString m_title;
    Wt::WString m_subTitle;
    Wizard* m_wizard;
    bool m_isFilanPage;
};

}

#endif
