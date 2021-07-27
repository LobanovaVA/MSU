#include "query.h"

istream& operator >> (istream& is, Query& q) 
{
  string operation_code;
  is >> operation_code;

  if (operation_code == "NEW_BUS")
  {
    q.type = QueryType::NewBus;
    is >> q.bus;

    int stop_count;
    is >> stop_count;

    q.stops.resize (stop_count);
    for (string& stop : q.stops) 
      is >> stop;

    return is;
  }

  if (operation_code == "BUSES_FOR_STOP")
  {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
    return is;
  }

  if (operation_code == "STOPS_FOR_BUS")
  {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
    return is;
  }

  if (operation_code == "ALL_BUSES")
  {
    q.type = QueryType::AllBuses;
    return is;
  }

  throw invalid_argument ("Cannot read command");
  return is;
}