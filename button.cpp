#include "button.h"



Button::Button(const std::string &iconPath, const QSize &buttonSize, QWidget *parent):
    QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setIcon(QIcon((basePath + iconPath).c_str()));
    setMinimumSize(buttonSize);
}
