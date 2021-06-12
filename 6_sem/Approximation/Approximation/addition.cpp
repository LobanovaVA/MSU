#include <QtWidgets/QMessageBox>
#include <QDebug>

#include "addition.h"

void
print_message (Message_type msg_t, const char *title_msg, const char *format, ...)
{
  va_list args;
  va_start (args, format);

  char msg[LEN];
  vsprintf (msg, format, args);
  qDebug() << msg;

  switch (msg_t)
    {
    case Message_type::warning:
      QMessageBox::warning (0, title_msg, msg);
      break;
    case Message_type::information:
      QMessageBox::information (0, title_msg, msg);
      break;
    }

  va_end (args);
}
