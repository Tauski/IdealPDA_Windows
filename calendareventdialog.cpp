#include "calendareventdialog.h"
#include "ui_calendareventdialog.h"

CalendarEventDialog::CalendarEventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalendarEventDialog)
{
    ui->setupUi(this);
}

CalendarEventDialog::~CalendarEventDialog()
{
    delete ui;
}
