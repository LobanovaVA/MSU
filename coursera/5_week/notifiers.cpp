#include <iostream>
#include <string>

using namespace std;

void 
SendSms (const string& number, const string& message) 
{
  cout << "Send '" << message << "' to number " << number << endl;
}

void 
SendEmail (const string& email, const string& message) 
{
  cout << "Send '" << message << "' to e-mail "  << email << endl;
}

class INotifier
{
public:
  virtual void Notify (const string& message) = 0;
  virtual ~INotifier () = default;
};


class SmsNotifier : public INotifier
{
private:
  const string m_phone_number;

public:
  SmsNotifier (string phone_number) : m_phone_number (phone_number) {}

  void Notify (const string& message) override 
  {
    return SendSms (m_phone_number, message);
  }
};


class EmailNotifier : public INotifier
{
private:
  const string m_mail_address;

public:
  EmailNotifier (string mail_address) : m_mail_address (mail_address) {}

  void Notify (const string& message) override 
  {
    return SendEmail (m_mail_address, message);
  }
};


void 
Notify (INotifier& notifier, const string& message) 
{
  notifier.Notify (message);
}

int 
main () 
{
  SmsNotifier sms {"+7-495-777-77-77"};
  EmailNotifier email {"na-derevnyu@dedushke.ru"};

  Notify (sms, "I have White belt in C++");
  Notify (email, "And want a Yellow one");

  return 0;
}
