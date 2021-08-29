#pragma once

#include "test_runner.h"
#include "node.h"
#include "database.h"
#include "condition_parser.h"

#include <sstream>

using namespace std;

void TestAll ();

void TestParseEvent ();

void TestDbAdd ();
void TestDbFind ();
void TestDbLast ();
void TestDbRemoveIf ();

void TestInsertionOrder ();
void TestsMyCustom ();
void TestDatabase ();

void TestDateComparisonNode ();
void TestEventComparisonNode ();

void TestLogicalOperationNode ();

void TestEmptyNode ();
