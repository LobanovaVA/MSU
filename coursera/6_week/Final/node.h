#pragma once

#include <sstream>
#include <memory>

#include "date.h"

using namespace std;

enum class Comparison
{
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual
};

enum class LogicalOperation
{
  Or,
  And
};

class Node
{
public:
  virtual bool Evaluate (const Date & date, const string & event) const = 0;
  virtual ~Node () = default;
};

class EmptyNode : public Node
{
public:
  bool Evaluate (const Date & date, const string & event) const override;
};

class DateComparisonNode : public Node
{
private:
  const Comparison cmp;
  const Date value;

public:
   DateComparisonNode (const Comparison cmp_, const Date & value_)
    : cmp (cmp_), value (value_) {}

  bool Evaluate (const Date & date, const string & event) const override;
};


class EventComparisonNode : public Node
{
private:
  const Comparison cmp;
  const string value;

public:
  EventComparisonNode (const Comparison cmp_, const string & value_)
    : cmp (cmp_), value (value_) {}

  bool Evaluate (const Date & date, const string & event) const override;
};


class LogicalOperationNode : public Node
{
private:
  const LogicalOperation log_op;
  shared_ptr <Node> left, right;

public:
  LogicalOperationNode (const LogicalOperation log_op_,
                        shared_ptr <Node> left_, shared_ptr <Node> right_)
    : log_op (log_op_), left (left_), right (right_) {}

  bool Evaluate (const Date & date, const string & event) const override;
};
