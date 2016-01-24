#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <Wt/WApplication>

namespace Wt
{
class WMenu;
class WTextArea;
class FileDialog;
class WNavigationBar;
class WStackedWidget;
class WContainerWidget;
}

class Application: public Wt::WApplication
{
public:
    Application(const Wt::WEnvironment& environment);

private:

    void init();
    Wt::WContainerWidget* createModelPage();
    Wt::WContainerWidget* createDialogPage();

private:

    Wt::WNavigationBar* m_navigation;
    Wt::WStackedWidget* m_contentsStack;
    Wt::WMenu* m_menu;
    Wt::FileDialog* m_fileDialog;
    Wt::WTextArea* m_textArea;

};

#endif /* APPLICATION_H_ */
