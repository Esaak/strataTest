#ifndef BUTTON_H
#define BUTTON_H

#include <QToolButton>

class Button : public QToolButton
{
    Q_OBJECT

public:
    Button(const std::string &iconPath,const QSize &buttonSize, QWidget *parent = nullptr);
private:
    const std::string basePath = "/home/esaak/my_folder/CProjects/QTstrata_test/scatterchart/";
};

#endif // BUTTON_H
