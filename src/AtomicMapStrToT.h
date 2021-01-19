#pragma once

#include <map>
#include <string>
#include <atomic>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>

template<class T>
class AtomicMapStrToT
{
public:
   AtomicMapStrToT() : _mutex(new sf::Mutex()), _is_locked(false){};

   const T& get(std::string key)
   {
      sf::Lock lock(*_mutex);
      return _map[key];
   }

   T& getWhenLocked(std::string key)
   {
      sf::Lock lock(*_mutex);
      if (!_is_locked)
         throw "You must lock the AtomicMap before calling this function";
      else
         return _map[key];
   }

   std::map<std::string,T>& getMapWhenLocked()
   {
      sf::Lock lock(*_mutex);
      if (!_is_locked)
         throw "You must lock the AtomicMap before calling this function";
      else
         return _map;
   }

   void set(std::string key, T &val)
   {
      sf::Lock lock(*_mutex);
      _map[key] = val;
   }

   void clear()
   {
      sf::Lock lock(*_mutex);
      _map.clear();
   }

   void erase(std::string key)
   {
      sf::Lock lock(*_mutex);
      _map.erase(key);
   }

   bool empty()
   {
      sf::Lock lock(*_mutex);
      return _map.empty();
   }

   void lock() 
   { 
      sf::Lock lock(*_mutex);
      _mutex->lock(); 
      _is_locked = true; 
   }

   void unlock() 
   {
      sf::Lock lock(*_mutex); 
      _mutex->unlock(); 
      _is_locked = false; 
   }

private:
   std::map<std::string, T> _map;
   sf::Mutex* _mutex;
   std::atomic<bool> _is_locked;
};

