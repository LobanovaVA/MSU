#include "node.h"

using namespace std;

bool
EmptyNode::Evaluate (const Date & /*date*/, const string & /*event*/) const
{
  return true;
}


bool
DateComparisonNode::Evaluate (const Date & date, const string & /*event*/) const
{
  switch (cmp)
    {
    case Comparison::Less:
      return date < value;
    case Comparison::LessOrEqual:
      return date <= value;
    case Comparison::Greater:
      return date > value;
    case Comparison::GreaterOrEqual:
      return date >= value;
    case Comparison::Equal:
      return date == value;
    case Comparison::NotEqual:
      return date != value;
    }
  return true;
}

bool
EventComparisonNode::Evaluate (const Date & /*date*/, const string & event) const
{
  switch (cmp)
    {
    case Comparison::Less:
      return event < value;
    case Comparison::LessOrEqual:
      return event <= value;
    case Comparison::Greater:
      return event > value;
    case Comparison::GreaterOrEqual:
      return event >= value;
    case Comparison::Equal:
      return event == value;
    case Comparison::NotEqual:
      return event != value;
    }
  return true;
}


bool
LogicalOperationNode::Evaluate (const Date & date, const string & event) const
{
  switch (log_op)
    {
    case LogicalOperation::Or:
      return left->Evaluate (date, event) || right->Evaluate (date, event);
    case LogicalOperation::And:
      return left->Evaluate (date, event) && right->Evaluate (date, event);
    }
  return true;
}
