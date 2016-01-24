#include "Wizard.h"
#include "WizardPage.h"

namespace Wt
{
using namespace Wt;

WizardPage::WizardPage(Wt::WContainerWidget* parent) :
        WContainerWidget(parent),
        m_wizard(nullptr),
        m_isFilanPage(false)
{
}

const Wt::WString& WizardPage::title() const
{
    return m_title;
}

void WizardPage::setTitle(const Wt::WString& title)
{
    m_title = title;
}

const Wt::WString& WizardPage::subTitle() const
{
    return m_subTitle;
}

void WizardPage::setSubTitle(const Wt::WString& subTitle)
{
    m_subTitle = subTitle;
}

void WizardPage::cleanupPage()
{

}

void WizardPage::initializePage()
{

}

bool WizardPage::isComplete() const
{
    return true;
}

bool WizardPage::validatePage()
{
    return true;
}

int WizardPage::nextId() const
{
    return -1;
}

void WizardPage::setWizard(Wizard* wizard)
{
    m_wizard = wizard;
}

Wizard* WizardPage::wizard() const
{
    return m_wizard;
}

bool WizardPage::isFinalPage() const
{
    return m_isFilanPage;
}

void WizardPage::setFinalPage(bool isFinal)
{
    m_isFilanPage = isFinal;
}

}
