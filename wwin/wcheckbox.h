#ifndef WCHECKBOX_H
#define WCHECKBOX_H

#include "wwin/wabstractbutton.h"

class WCheckBox : public WAbstractButton
{
public:
    WCheckBox(WWidget *parent = nullptr);
    WCheckBox(const WString title, WWidget *parent = nullptr);

    // WWidget interface
protected:
    virtual int style() override;
};

#endif // WCHECKBOX_H
