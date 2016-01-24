#include <Wt/WMenu>
#include <Wt/WLabel>
#include <Wt/WText>
#include <Wt/WTextArea>
#include <Wt/WTreeView>
#include <Wt/WVBoxLayout>
#include <Wt/WPushButton>
#include <Wt/WNavigationBar>
#include <Wt/WStackedWidget>
#include <Wt/WBootstrapTheme>

#include "FileDialog.h"
#include "Application.h"
#include "FileSystemModel.h"

using namespace Wt;

Application::Application(const Wt::WEnvironment& environment) :
        Wt::WApplication(environment),
        m_navigation(new WNavigationBar()),
        m_contentsStack(new WStackedWidget()),
        m_menu(nullptr),
        m_fileDialog(nullptr),
        m_textArea(new WTextArea())
{
    setTitle("Component gallery");

    init();
}

void Application::init()
{
    root()->addWidget(m_navigation);
    root()->addWidget(m_contentsStack);

    m_menu = new WMenu(m_contentsStack, root());

    auto theme = new WBootstrapTheme();
    theme->setVersion(WBootstrapTheme::Version3);
    setTheme(theme);

    m_navigation->setResponsive(true);
    m_contentsStack->addStyleClass("contents");

    m_navigation->addMenu(m_menu);
    m_menu->addItem("Model", createModelPage());
    m_menu->addItem("Dialogs", createDialogPage());
}

Wt::WContainerWidget* Application::createModelPage()
{
    auto container = new WContainerWidget;
    auto label = new WLabel();
    label->setTextFormat(XHTMLText);
    label->setText("<h3><b>File system model</b></h3>");
    container->addWidget(label);
    auto tree = new WTreeView(container);
    tree->setModel(new FileSystemModel(this));
    tree->resize(300, 400);
    tree->setMaximumSize(300, 400);
    tree->setSortingEnabled(false);

    return container;
}

Wt::WContainerWidget* Application::createDialogPage()
{
    auto container = new WContainerWidget;

    auto label = new WLabel();
    label->setTextFormat(XHTMLText);
    label->setText("<h3><b>File dialog</b></h3>");
    container->addWidget(label);

    auto button = new WPushButton("Select");
    container->addWidget(button);

    container->addWidget(m_textArea);
    m_textArea->resize(400, 300);

    button->clicked().connect(
            std::bind(
                    [&]()
                    {
                        if(m_fileDialog)
                        {
                            return;
                        }

                        m_fileDialog = new FileDialog(this);
                        m_fileDialog->show();
                        m_fileDialog->finished()
                        .connect(
                                std::bind([&]()
                                        {
                                            const auto files = m_fileDialog->selected().join("\n");
                                            m_textArea->setText(files);
                                            delete m_fileDialog;
                                            m_fileDialog = nullptr;
                                        }));
                    }));

    return container;
}
