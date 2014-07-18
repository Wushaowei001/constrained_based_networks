#include "rice/Class.hpp"
#include "rice/Constructor.hpp"
#include "rice/String.hpp"
#include "rice/Array.hpp"
#include "rice/Enum.hpp"

#include <stdint.h>
#include <vector>
#include <deque>
#include <iostream>

#include <gecode_composition_management/port.h>
#include <gecode_composition_management/component.h>
#include <gecode_composition_management/query.h>
#include <gecode_composition_management/solution.h>


using namespace Rice;
using namespace composition_management;

typedef std::vector< std::string > StringVector;
typedef std::vector< IncomingPort > IncomingPortVector;
typedef std::vector< OutgoingPort > OutgoingPortVector;

Data_Type<StringVector> stringVector;
Data_Type<IncomingPortVector> incomingPortVector;
Data_Type<OutgoingPortVector> outgoingPortVector;

Data_Type<IncomingPort> rb_cIncomingPort;
Data_Type<OutgoingPort> rb_cOutgoingPort;
Data_Type<Component> rb_cComponent;
Data_Type<Query> rb_cQuery;
Data_Type<Solution> rb_cSolution;

static Module rb_mGecodeCompMgmt;

// Conversion templates
template<>
StringVector from_ruby< StringVector >(Object obj)
{
    Data_Object<StringVector> strings(obj, stringVector);
    return *strings;
}

template<>
Object to_ruby<StringVector>(const StringVector& v)
{
    Array strings;
    StringVector::const_iterator it;
    for(it = v.begin(); it != v.end(); it++)
    {
            strings.push(String(*it));
    }

    return strings;
}

template<>
Object to_ruby< IncomingPortVector >(const IncomingPortVector& v)
{
    Array ports;
    IncomingPortVector::const_iterator it;
    for( it = v.begin(); it != v.end(); it++)
    {
            ports.push(Data_Object<IncomingPort>( new IncomingPort(*it)));
    }

    return ports;
}

template<>
Object to_ruby< OutgoingPortVector >(const OutgoingPortVector& v)
{
    Array ports;
    OutgoingPortVector::const_iterator it;
    for( it = v.begin(); it != v.end(); it++)
    {
            ports.push(Data_Object<OutgoingPort>(new OutgoingPort(*it) ));
    }

    return ports;
}

// Wrappers
Array wrap_component_getConfiguration(Object self)
{
    Data_Object<Component> component(self, rb_cComponent);
    StringVector conf = component->getConfiguration();
    return to_ruby<StringVector>(conf);
}

void wrap_component_setConfiguration(Object self, Array configuration)
{
    Data_Object<Component> component(self, rb_cComponent);
    StringVector conf = from_ruby< StringVector >(configuration);
    component->setConfiguration(conf);
}

Array wrap_component_getInPorts(Object self)
{
    Data_Object<Component> component(self, rb_cComponent);
    IncomingPortVector ports = component->getInPorts();
    return to_ruby<IncomingPortVector>(ports);
}

Array wrap_component_getOutPorts(Object self)
{
    Data_Object<Component> component(self, rb_cComponent);
    OutgoingPortVector ports = component->getOutPorts();
    return to_ruby<OutgoingPortVector>(ports);
}

/**
 *
 */
extern "C"
void Init_gecodecompositionmanagement_ruby()
{

    // Define module FIPA
    rb_mGecodeCompMgmt = define_module("gecode_composition_management");
    
    rb_cIncomingPort = define_class_under<IncomingPort>(rb_mGecodeCompMgmt, "IncomingPort")
        .define_constructor(Constructor<IncomingPort, const std::string&, const std::string&>(), (Arg("datatype"), Arg("name")))
        .define_method("toString", &IncomingPort::toString)
    ;
    
    rb_cOutgoingPort = define_class_under<OutgoingPort>(rb_mGecodeCompMgmt, "OutgoingPort")
        .define_constructor(Constructor<OutgoingPort, const std::string&, const std::string&>(), (Arg("datatype"), Arg("name")))
        .define_method("toString", &OutgoingPort::toString)
    ;
    
    rb_cComponent = define_class_under<Component>(rb_mGecodeCompMgmt, "Component")
        .define_constructor(Constructor<Component, int, const std::string&>(), (Arg("type"), Arg("name")))
        .define_constructor(Constructor<Component>() )
        .define_method("toString", &Component::toString)
        .define_method("getType", &Component::getType)
        .define_method("getName", &Component::getName)
        .define_method("setName", &Component::getName, Arg("name"))
        .define_method("pushBackInPort", &Component::pushBackInPort, Arg("inPort"))
        .define_method("pushBackOutPort", &Component::pushBackOutPort, Arg("outPort"))
        .define_method("putIncomingConnection", &Component::putIncomingConnection, (Arg("inPort"), Arg("componentName")))
        .define_method("putOutgoingConnection", &Component::putOutgoingConnection, (Arg("outPort"), Arg("componentName")))
        .define_method("getConfiguration", &wrap_component_getConfiguration)
        .define_method("setConfiguration", &wrap_component_setConfiguration, Arg("confguration"))
        .define_method("getInPort", &wrap_component_getInPorts)
        .define_method("getOutPorts", &wrap_component_getOutPorts)
    ;
    
    rb_cQuery = define_class_under<Query>(rb_mGecodeCompMgmt, "Query")
        .define_constructor(Constructor<Query, const std::string&>(), Arg("name"))
        .define_method("toString", &Query::toString)
        .define_method("getComponent", &Query::getComponent, Arg("name"))
        .define_method("getComponentIndex", &Query::getComponentIndex, Arg("name"))
        .define_method("getName", &Query::getName)
        .define_method("addComponent", &Query::addComponent, Arg("component"))
        .define_method("integrateSubQuery", &Query::integrateSubQuery, Arg("subQuery"))
        .define_method("addConnection", &Query::addConnection, (Arg("outCompName"), Arg("out"), Arg("inCompName"), Arg("in")))
    ;
    
    rb_cSolution = define_class_under<Solution>(rb_mGecodeCompMgmt, "Solution")
        .define_method("babSearch", &Solution::babSearch, (Arg("query"), Arg("pool"))) // static method
        .define_method("print", &Solution::print)
    ;
}
