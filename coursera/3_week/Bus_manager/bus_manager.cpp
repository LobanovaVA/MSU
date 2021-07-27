#include "bus_manager.h"

void BusManager::AddBus (const string& bus, const vector<string>& stops) 
{
  buses_to_stops[bus] = stops;

  for (const string& stop : stops)
    stops_to_buses[stop].push_back (bus);      
}

BusesForStopResponse BusManager::GetBusesForStop (const string& stop) const 
{
  BusesForStopResponse r;
  r.stop = stop;

  size_t size = stops_to_buses.count (stop);
  r.buses.resize (size);
  if (size != 0) 
    r.buses = stops_to_buses.at (stop);

  return r;
}

StopsForBusResponse BusManager::GetStopsForBus (const string& bus) const 
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

AllBusesResponse BusManager::GetAllBuses() const 
{
  AllBusesResponse r;
  r.buses_to_stops = buses_to_stops;
  return r;
}
