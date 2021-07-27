#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

/* NEW_BUS bus stop_count stop1 stop2 ... —  добавить маршрут автобуса с 
     названием bus и stop_count остановками с названиями stop1, stop2 ...
 * BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через остановку stop.
 * STOPS_FOR_BUS bus — вывести все остановоки маршрута bus 
 * со списком автобусов, на которые можно пересесть на каждой из остановок.
 * ALL_BUSES — вывести список всех маршрутов с остановками. */

enum class QueryType 
{
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query 
{
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

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


struct BusesForStopResponse 
{
  string stop;
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) 
{
  if (r.buses.size () == 0)
    os << "No stop" << endl;
  else
  {
    for (const string& bus : r.buses) 
      os << bus << " ";
    os << endl;
  }
  
  return os;
}

struct StopsForBusResponse 
{
  string bus;
  vector<string> stops;
  map<string, vector<string>> stops_to_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) 
{
  if (r.stops.size () == 0)
    os << "No bus" << endl;
  else
  {
    for (const string& stop : r.stops)
    {
      os << "Stop " << stop << ": ";

      if (r.stops_to_buses.at (stop).size () == 1)
        os << "no interchange";
      else
      {
        for (const string& other_bus : r.stops_to_buses.at (stop))
          if (r.bus != other_bus)
            os << other_bus << " ";
      }

      os << endl;
    }
  }

  return os;
}

struct AllBusesResponse 
{
  map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) 
{
  if (r.buses_to_stops.empty ()) 
    os << "No buses" << endl;
  else 
  {
    for (const auto& bus_item : r.buses_to_stops) 
    {
      os << "Bus " << bus_item.first << ": ";
      for (const string& stop : bus_item.second) 
        os << stop << " ";
      
      os << endl;
    }
  }

  return os;
}

class BusManager {
  map<string, vector<string>> buses_to_stops;
  map<string, vector<string>> stops_to_buses;

public:
  void AddBus (const string& bus, const vector<string>& stops) 
  {
    //size_t stop_count = stops.size ();
    buses_to_stops[bus] = stops;

    for (const string& stop : stops)
      stops_to_buses[stop].push_back (bus);      
  }

  BusesForStopResponse GetBusesForStop (const string& stop) const 
  {
    BusesForStopResponse r;
    r.stop = stop;

    size_t size = stops_to_buses.count (stop);
    r.buses.resize (size);
    if (size != 0) 
      r.buses = stops_to_buses.at (stop);
 
    return r;
  }

  StopsForBusResponse GetStopsForBus (const string& bus) const 
  {
    StopsForBusResponse r;
    r.bus = bus;

    size_t size = buses_to_stops.count (bus);
    r.stops.resize (size);
    if (size != 0) 
      r.stops = buses_to_stops.at (bus);

    r.stops_to_buses = stops_to_buses;

    return r;
  }

  AllBusesResponse GetAllBuses() const 
  {
    AllBusesResponse r;
    r.buses_to_stops = buses_to_stops;
    return r;
  }
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
