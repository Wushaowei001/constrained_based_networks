#ifndef GECODE_COMPOSITION_MANAGEMENT_QUERY_H
#define GECODE_COMPOSITION_MANAGEMENT_QUERY_H

#include<map>
#include<vector>

#include "component.h"
#include "port.h"

using namespace Gecode;

namespace composition_management {

class Query{
protected:
  std::vector<Component> components;
  
  std::map<IncomingPort, OutgoingPort> connections;
public:
    Query(std::vector<Component> components, std::map<IncomingPort, OutgoingPort> connections)
        : components(components)
        , connections(connections)
    {
    }
};

} // end namespace composition_management

#endif // GECODE_COMPOSITION_MANAGEMENT_QUERY_H