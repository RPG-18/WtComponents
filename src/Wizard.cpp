#include <iostream>

#include <Wt/WLabel>
#include <Wt/WGroupBox>
#include <Wt/WPushButton>
#include <Wt/WVBoxLayout>
#include <Wt/WStackedWidget>

#include "Wizard.h"
#include "WizardPage.h"

namespace Wt
{

Wizard::Wizard(WObject* parent) :
        WDialog(parent),
        m_currentId(-1),
        m_stack(new WStackedWidget),
        m_title(new WLabel),
        m_subTitle(new WGroupBox),
        m_back(new WPushButton("< Back")),
        m_next(new WPushButton("Next>")),
        m_cancel(new WPushButton("Cancel")),
        m_finish(new WPushButton("Finish"))
{
    setModal(true);
    setResizable(true);

    titleBar()->addWidget(m_title);

    auto contentLayout = new WVBoxLayout;
    contents()->setLayout(contentLayout);
    contentLayout->addWidget(m_subTitle);
    m_subTitle->addWidget(m_stack);
    m_stack->addStyleClass("Wizard-stack");

    footer()->addWidget(m_back);
    footer()->addWidget(m_next);
    footer()->addWidget(m_finish);
    footer()->addWidget(m_cancel);

    m_back->clicked().connect(this, &Wizard::back);
    m_next->clicked().connect(this, &Wizard::next);
    m_cancel->clicked().connect(this, &Wizard::reject);
    m_finish->clicked().connect(this, &Wizard::finish);

    m_finish->setHidden(true);
}

void Wizard::setField(const Wt::WString& name, const boost::any& value)
{
    m_fields[name] = value;
}

bool Wizard::testField(const Wt::WString& name) const
{
    auto result = m_fields.find(name);
    return result != m_fields.end();
}

boost::any& Wizard::field(const Wt::WString& name)
{
    return m_fields.at(name);
}

void Wizard::addPage(WizardPage* page)
{

    m_pages.push_back(page);
    m_stack->addWidget(page);
    page->setWizard(this);

    if (m_currentId == -1)
    {
        setCurrentPage(0);
    }

    updateButtonState();
}

int Wizard::currentId() const
{
    return m_currentId;
}
WizardPage* Wizard::currentPage() const
{
    return m_pages.at(m_currentId);
}

void Wizard::setCurrentPage(int indx)
{
    m_currentId = indx;
    m_pages[indx]->initializePage();

    m_stack->setCurrentIndex(indx);
    m_title->setText(m_pages[indx]->title());
    m_subTitle->setTitle(m_pages[indx]->subTitle());

    updateButtonState();
}

void Wizard::back()
{
    if (m_currentId > 0)
    {
        m_pages[m_currentId]->cleanupPage();
        setCurrentPage(m_currentId - 1);
    }
}

void Wizard::next()
{
    if (currentPageIsComplete() && validateCurrentPage())
    {

        updateButtonState();
        int nId = nextId();

        if ((nId == -1) && (m_currentId < m_pages.size()))
        {
            setCurrentPage(m_currentId + 1);
        }

        if (nId > -1 && nId < m_pages.size())
        {
            setCurrentPage(nId);
        }
    }
}

void Wizard::finish()
{
    if (currentPageIsComplete() && validateCurrentPage())
    {
        accept();
    }
}

int Wizard::nextId() const
{
    if (m_currentId == -1)
    {
        return -1;
    }

    return m_pages[m_currentId]->nextId();
}

bool Wizard::validateCurrentPage() const
{
    if (m_currentId == -1)
    {
        return false;
    }

    return m_pages[m_currentId]->validatePage();
}

bool Wizard::currentPageIsComplete() const
{
    if (m_currentId == -1)
    {
        return false;
    }
    return m_pages[m_currentId]->isComplete();

}

void Wizard::updateButtonState()
{
    if (m_currentId == -1)
    {
        return;
    }

    if (m_currentId == 0)
    {
        m_back->setEnabled(false);
    }

    if (m_currentId > 0)
    {
        m_back->setEnabled(true);
    }

    if (m_currentId < (m_pages.size() - 1))
    {
        m_next->setHidden(false);
    }
    else
    {
        m_next->setHidden(true);
    }

    m_finish->setHidden(!m_pages[m_currentId]->isFinalPage());
}

void Wizard::removeField(const Wt::WString& name)
{
    m_fields.erase(name);
}

}
