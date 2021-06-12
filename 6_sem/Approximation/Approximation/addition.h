#ifndef ADDITION_H
#define ADDITION_H

#define LEN 1234

#include <memory>

constexpr double EPS = 1.e-15;

enum class Method_type
{
  shift_newton,
  cubic_spline,
};

enum class Message_type
{
  warning,
  information
};

void print_message (Message_type msg_t, const char *title_msg, const char *format, ...);

#endif // ADDITION_H
