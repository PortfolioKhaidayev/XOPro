#include <WApplication>
#include "xowindow.h"

int WINAPI WinMain(HINSTANCE hInstace, HINSTANCE hPrevInst, LPSTR lpCmdString, int nCmdShow)
{
    WApplication *app = WApplication::instance(hInstace, hPrevInst, lpCmdString, nCmdShow);

    XOWindow *w = new XOWindow(nullptr);
    w->show();
    w->initUi();

    return app->run();
}
