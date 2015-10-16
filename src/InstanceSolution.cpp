#include "InstanceSolution.hpp"

#include <gecode/gist.hh>
#include <gecode/minimodel.hh>

#include <memory>
#include <vector>
#include <map>
#include <stdexcept>
#include "Pool.hpp"
#include "Task.hpp"
#include "Composition.hpp"
#include "DataService.hpp"
#include "SpecializedComponent.hpp"
#include <stdlib.h>
#include <fstream>
#include <graph_analysis/GraphIO.hpp>
#include <gecode/gist.hh>

using namespace Gecode;

namespace constrained_based_networks
{

void InstanceSolution::gatherAllStringConfigs()
{
    std::set<std::string> strings;
    strings.insert("");
    for (const auto& v : graph->getAllVertices()) {
        auto helper_node = boost::static_pointer_cast<ComponentInstanceHelper>(v);
        auto component = dynamic_cast<Component*>(helper_node->component.get());
        if (!component) throw std::runtime_error("Cannot get component from graph");
        auto spec_component = dynamic_cast<SpecializedComponentBase*>(component);

        for (const auto& prop : component->getProperties()) {
            if (prop.t == ConfigurationModel::STRING) {

                // Save all possible options from the config
                for (const auto& section : component->getSections()) {
                    try
                    {
                        strings.insert(component->getConfFileProperty(section, prop.name));
                    }
                    catch (std::out_of_range e)
                    {
                        // Do nothign because it is notmal that not all propertys exist in all sections
                    }
                }

                // If this is a specialized component it might have configuration request on it's own
                if (spec_component) {
                    auto it = spec_component->configuration.find(prop.name);

                    // If this specalized component has a requirement for a string property
                    // Otherwise it does not
                    if (it != spec_component->configuration.end()) {
                        strings.insert(it->second);
                    }
                }
            }
        }
    }
    string_helper = std::shared_ptr<std::map<std::string, unsigned int>>(new std::map<std::string, unsigned int>);
    unsigned int cnt = 0;
    for (auto s : strings) {
        string_helper->insert({s, cnt++});
    }
}

void InstanceSolution::buildInstanceGraph(graph_analysis::Vertex::Ptr parent_orig, graph_analysis::DirectedGraphInterface& orig, graph_analysis::Vertex::Ptr parent)
{
    for (auto v : orig.outEdges(parent_orig)) {
        auto target = ComponentInstanceHelper::make(v->getTargetVertex());
        graph_analysis::Edge::Ptr e(new graph_analysis::Edge());
        e->setSourceVertex(parent);
        e->setTargetVertex(target);
        graph->addEdge(e);
        buildInstanceGraph(v->getTargetVertex(), orig, target);
    }
}

graph_analysis::Vertex::Ptr InstanceSolution::getRoot(const graph_analysis::BaseGraph::Ptr& _graph)
{
    graph_analysis::Vertex::Ptr root;
    for (auto v : _graph->getAllVertices()) {
        auto component = dynamic_cast<Component*>(v.get());
        auto spec = dynamic_cast<ConfiguredComponent*>(v.get());
        if(spec){
            std::cout << "Got a configures component " << spec->toString() << std::endl;
            component = spec->component;
        }
        if(!component){
            if (v->toString() == "root-knot") {
                root = v;
                break;
            }
        }else{
            if (component->getName() == "root-knot") {
                root = v;
                break;
            }
        }
    }
    /*
    std::cerr << "Error output:" << std::endl;
    for (auto v : _graph->getAllVertices()) {
        std::cerr << "Got " << v->toString() <<  std::endl;
    }
    if (!root) {
        throw std::runtime_error("Could not get the root knot of the graph");
    }
    */
    return root;
}

InstanceSolution::InstanceSolution(graph_analysis::BaseGraph::Ptr _graph)  // : graph(_graph)
{
    graph_analysis::Vertex::Ptr root = getRoot(_graph);

    graph = boost::static_pointer_cast<graph_analysis::DirectedGraphInterface>(graph_analysis::BaseGraph::getInstance(graph_analysis::BaseGraph::LEMON_DIRECTED_GRAPH));
    auto orig = dynamic_cast<graph_analysis::DirectedGraphInterface*>(_graph.get());
    assert(orig);

    buildInstanceGraph(root, *orig, ComponentInstanceHelper::make(root));

    gatherAllStringConfigs();

    // Setup the configuration arrays
    verticies_in_tree = graph->getAllVertices().size();
    float_config.resize(verticies_in_tree);
    bool_config.resize(verticies_in_tree);
    int_config.resize(verticies_in_tree);
    string_config.resize(verticies_in_tree);

    // Setup all propagations and actual requirements for all configs we have
    // In case we have a specialized component, this is the only case
    // (currently) where a configuiration is actually filled
    // with values. Later a extension based on configurations is needed
    for (auto helper_node : graph->getAllVertices()) {
        auto helper_node2 = boost::static_pointer_cast<ComponentInstanceHelper>(helper_node);
        auto component = dynamic_cast<Component*>(helper_node2->component.get());
        if (!component) throw std::runtime_error("Cannot get component from graph");

        // We need only to separate between this types, al other types should not occur anymore in the graph
        // Like DataServices are replaced with actual task-contexts
        auto cmp = dynamic_cast<Composition*>(component);
        auto task = dynamic_cast<Task*>(component);
        auto spec_cmp = dynamic_cast<SpecializedComponentBase*>(component);
        if (!task && !cmp) throw std::runtime_error("We have some unresolved or unknown elements within the graph");

        if (cmp) {
            setupProperties(cmp, helper_node2, graph);

            // So we need to propagate all entries here
            auto edges = graph->getEdgeIterator(helper_node2);
            while (edges->next()) {

                // If our task is a child and we are NOT a specialized component
                // (which would assume that we are not support this?, maybe we we would set a specific configuration then?!
                auto task = dynamic_cast<Task*>(edges->current()->getTargetVertex().get());
                auto specialized_task = dynamic_cast<SpecializedComponentBase*>(edges->current()->getTargetVertex().get());

                if (task && specialized_task) {
                    throw std::runtime_error("We got a specialized task as child, this is not (Yet) supported");
                }

                if (task) {
                    // Okay we start to use a default config for not
                    // TODO this must be extended later to load instead of the default-configs somthing which
                    // can be set by somehting like a with_conf call within the compositions

                    // Make sure the properties exist
                    setupProperties(task, edges->current()->getTargetVertex(), graph);

                    for (auto prop : task->getProperties()) {
                        switch (prop.t) {
                            case(constrained_based_networks::ConfigurationModel::INT) : {
                                try
                                {
                                    rel(*this, int_config[graph->getVertexId(edges->current()->getTargetVertex())][prop.name], IRT_EQ, atoi(task->getConfFileProperty("default", prop.name).c_str()));
                                }
                                catch (std::out_of_range e)
                                {
                                    int val = 0;
                                    if (spec_cmp) {
                                        auto it = spec_cmp->configuration.find(prop.name);
                                        if (it != spec_cmp->configuration.end()) {
                                            val = atoi(it->second.c_str());
                                        } else {
                                            std::cerr << "Cannot get configuration " << prop.name << " for Task " << task->getName() << "Assuming 0" << std::endl;
                                        }
                                    } else {
                                        std::cerr << "Cannot get configuration " << prop.name << " for Task " << task->getName() << "Assuming 0" << std::endl;
                                    }
                                    rel(*this, int_config[graph->getVertexId(edges->current()->getTargetVertex())][prop.name], IRT_EQ, val);
                                }
                                break;
                            }
                            case(constrained_based_networks::ConfigurationModel::STRING) : {
                                try
                                {
                                    // This can fail
                                    std::string str = task->getConfFileProperty("default", prop.name);
                                    unsigned int id = 0;
                                    if (string_helper->find(str) == string_helper->end()) {
                                        throw std::runtime_error("String helper does not contain the needed string this should not happen");
                                    } else {
                                        id = string_helper->at(str);
                                    }
                                    rel(*this, string_config[graph->getVertexId(edges->current()->getTargetVertex())][prop.name], IRT_EQ, id);
                                }
                                catch (std::out_of_range e)
                                {
                                    int id = 0;
                                    if (spec_cmp) {
                                        auto it = spec_cmp->configuration.find(prop.name);
                                        if (it != spec_cmp->configuration.end()) {
                                            std::string str;
                                            if (string_helper->find(str) == string_helper->end()) {
                                                throw std::runtime_error("String helper does not contain the needed string this should not happen");
                                            } else {
                                                id = string_helper->at(str);
                                            }
                                        } else {
                                            std::cerr << "Cannot get configuration " << prop.name << " for Task " << task->getName() << "Assuming empty string" << std::endl;
                                        }
                                    } else {
                                        std::cerr << "Cannot get configuration " << prop.name << " for Task " << task->getName() << "Assuming empty string" << std::endl;
                                    }
                                    rel(*this, string_config[graph->getVertexId(edges->current()->getTargetVertex())][prop.name], IRT_EQ, id);
                                }
                                break;
                            }
                            case(constrained_based_networks::ConfigurationModel::DOUBLE) : {
                                try
                                {
                                    const float val = atof(task->getConfFileProperty("default", prop.name).c_str());
                                    rel(*this, float_config[graph->getVertexId(edges->current()->getTargetVertex())][prop.name], FRT_EQ, val);
                                }
                                catch (std::out_of_range e)
                                {
                                    double val = 0;
                                    if (spec_cmp) {
                                        auto it = spec_cmp->configuration.find(prop.name);
                                        if (it != spec_cmp->configuration.end()) {
                                            val = atof(it->second.c_str());
                                        } else {
                                            std::cerr << "Cannot get configuration " << prop.name << " for Task " << task->getName() << "Assuming 0.0" << std::endl;
                                        }
                                    } else {
                                        std::cerr << "Cannot get configuration " << prop.name << " for Task " << task->getName() << "Assuming 0.0" << std::endl;
                                    }
                                    rel(*this, float_config[graph->getVertexId(edges->current()->getTargetVertex())][prop.name], FRT_EQ, val);
                                }
                                break;
                            }
                            case(constrained_based_networks::ConfigurationModel::BOOL) : {
                                try
                                {

                                    rel(*this, bool_config[graph->getVertexId(edges->current()->getTargetVertex())][prop.name], IRT_EQ, atoi(task->getConfFileProperty("default", prop.name).c_str()));
                                }
                                catch (std::out_of_range e)
                                {
                                    bool val = false;
                                    if (spec_cmp) {
                                        auto it = spec_cmp->configuration.find(prop.name);
                                        if (it != spec_cmp->configuration.end()) {
                                            val = atoi(it->second.c_str());
                                        } else {
                                            std::cerr << "Cannot get configuration " << prop.name << " for Task " << task->getName() << "Assuming false" << std::endl;
                                        }
                                    } else {
                                        std::cerr << "Cannot get configuration " << prop.name << " for Task " << task->getName() << "Assuming false" << std::endl;
                                    }
                                    rel(*this, bool_config[graph->getVertexId(edges->current()->getTargetVertex())][prop.name], IRT_EQ, val);
                                }
                                break;
                            }
                        };
                    }
                }

                auto child = dynamic_cast<Component*>(edges->current()->getTargetVertex().get());
                for (auto forward : cmp->getArgumentForwards(child)) {

                    if (child->getProperty(forward.second) != cmp->getProperty(forward.first)) {
                        throw std::runtime_error("The properties of child and parend differ in type");
                    }
                    // Dont care which type we choose check is done before
                    switch (child->getProperty(forward.second)) {
                        case(constrained_based_networks::ConfigurationModel::INT) : {
                            auto var = Gecode::IntVar(*this, 0, Gecode::Int::Limits::max);
                            int_config[graph->getVertexId(edges->current()->getTargetVertex())][forward.second] = var;
                            auto var_source = int_config[graph->getVertexId(helper_node2)][forward.first];
                            rel(*this, var, IRT_EQ, var_source);
                            break;
                        }
                        case(constrained_based_networks::ConfigurationModel::STRING) : {
                            auto var = Gecode::IntVar(*this, 0, Gecode::Int::Limits::max);
                            string_config[graph->getVertexId(edges->current()->getTargetVertex())][forward.second] = var;
                            auto var_source = string_config[graph->getVertexId(helper_node2)][forward.first];
                            rel(*this, var, IRT_EQ, var_source);
                            break;
                        }
                        case(constrained_based_networks::ConfigurationModel::DOUBLE) : {
                            auto var = Gecode::FloatVar(*this, 0, Gecode::Float::Limits::max);
                            float_config[graph->getVertexId(edges->current()->getTargetVertex())][forward.second] = var;
                            auto var_source = float_config[graph->getVertexId(helper_node2)][forward.first];
                            rel(*this, var, FRT_EQ, var_source);
                            break;
                        }
                        case(constrained_based_networks::ConfigurationModel::BOOL) : {
                            auto var = Gecode::BoolVar(*this, 0, 1);
                            bool_config[graph->getVertexId(edges->current()->getTargetVertex())][forward.second] = var;
                            auto var_source = bool_config[graph->getVertexId(helper_node2)][forward.first];
                            rel(*this, var, IRT_EQ, var_source);
                            break;
                        }
                    };
                }
            }
        }
        if (task) {
            setupProperties(task, helper_node2, graph);
        }
    }

    // Handle the interlaaving, means if a component should be the same than another one in the real instanciation
    // This is maybe the most important part of this class to idntify single and double-tasks
    interleaved = Gecode::BoolVarArray(*this, verticies_in_tree * verticies_in_tree, 0, 1);
    for (auto _n1 : graph->vertices()) {
        auto i = graph->getVertexId(_n1);
        auto n1 = boost::static_pointer_cast<ComponentInstanceHelper>(_n1);
        assert(n1);
        for (auto _n2 : graph->vertices()) {
            auto n2 = boost::static_pointer_cast<ComponentInstanceHelper>(_n2);
            assert(n2);
            auto j = graph->getVertexId(_n2);

            // The relation interleaved is symetric, if we are the same than another, the another is the same than we
            rel(*this, interleaved[i + (verticies_in_tree * j)], IRT_EQ, interleaved[j + (verticies_in_tree * i)]);

            if (n1->component != n2->component) {
                // std::cout << "Cannot be interleaved " << n1->component->toString() << " <-> " << n2->component->toString() << std::endl;
                rel(*this, interleaved[i + (verticies_in_tree * j)], IRT_NQ, 1);
                /* We don't need this becase the root is always diffeent to anything else
                if(i == 0 || j==0){
                    rel(*this,interleaved[i+(max*j)], IRT_NQ, 1);
                }
                */
            } else {
                // We cannot interleave us which us self
                if (i == j) {
                    // std::cout << "Cannot be interleaved because its th same " << n1->component->toString() << " <-> " << n2->component->toString() << std::endl;
                    rel(*this, interleaved[i + (verticies_in_tree * j)], IRT_NQ, 1);
                } else {
                    // Ok the components are equal in her name, make sure that they are
                    // interleaved only if the configuration is consistent
                    auto component = dynamic_cast<Component*>(n2->component.get());
                    assert(component);

                    for (auto prop : component->getProperties()) {
                        switch (prop.t) {
                            case ConfigurationModel::DOUBLE:
                                rel(*this, interleaved[i + (verticies_in_tree * j)] >> (float_config[i][prop.name] == float_config[j][prop.name]));
                                break;
                            case ConfigurationModel::INT:
                                rel(*this, interleaved[i + (verticies_in_tree * j)] >> (int_config[i][prop.name] == int_config[j][prop.name]));
                                break;
                            case ConfigurationModel::STRING:
                                rel(*this, interleaved[i + (verticies_in_tree * j)] >> (string_config[i][prop.name] == string_config[j][prop.name]));
                                break;
                            case ConfigurationModel::BOOL:
                                rel(*this, interleaved[i + (verticies_in_tree * j)] >> (bool_config[i][prop.name] == bool_config[j][prop.name]));
                                break;
                            default:
                                throw std::runtime_error("Unknown type in config handling");
                        }
                    }
                    auto children1 = graph->getOutEdgeIterator(n2);  //->//composition->getChildren();
                    auto children2 = graph->getOutEdgeIterator(n1);  ////dynamic_cast<Composition*>(n1->component.get())->getChildren();
                    while (children1->next() && children2->next()) {
                        auto child_id1 = graph->getVertexId(children1->current()->getTargetVertex());
                        auto child_id2 = graph->getVertexId(children2->current()->getTargetVertex());
                        rel(*this, interleaved[i + (verticies_in_tree * j)] >> interleaved[child_id1 + (verticies_in_tree * child_id2)]);
                    }
                    // std::cout << "could be interleaved " << n1->component->toString() << " <-> " << n2->component->toString() << std::endl;
                    // std::cout << i << " and " << j << std::endl;
                    // std::cout << i+(verticies_in_tree*j) << " and " << j+(verticies_in_tree*i) << std::endl;
                }
            }
        }
    }

    // Setup the branching for ALL task-context here, this could
    // be done within the previous loop to save effienfy, but to have the code
    // more strutured do this explicitly and separeated here
    for (auto node : graph->getAllVertices()) {
        if (dynamic_cast<Task*>(node.get())) {
            auto id = graph->getVertexId(node);
            for (auto c : bool_config[id]) {
                branch(*this, c.second, INT_VAL_MIN());
            }
            for (auto c : float_config[id]) {
                branch(*this, c.second, FLOAT_VAL_SPLIT_MIN());
            }
            for (auto c : int_config[id]) {
                branch(*this, c.second, INT_VAL_MIN());
            }
            for (auto c : string_config[id]) {
                branch(*this, c.second, INT_VAL_MIN());
            }
        }
    }
    branch(*this, interleaved, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
}

InstanceSolution::InstanceSolution(bool share, InstanceSolution& s) : Space(share, s)
{
    graph = s.graph;
    string_helper = s.string_helper;
    verticies_in_tree = s.verticies_in_tree;

    float_config.resize(s.float_config.size());
    for (size_t i = 0; i < s.float_config.size(); i++) {
        for (auto c : s.float_config[i]) {
            float_config[i][c.first] = FloatVar();
            float_config[i][c.first].update(*this, share, s.float_config[i][c.first]);
        }
    }

    bool_config.resize(s.bool_config.size());
    for (size_t i = 0; i < s.bool_config.size(); i++) {
        for (auto c : s.bool_config[i]) {
            bool_config[i][c.first] = BoolVar();
            bool_config[i][c.first].update(*this, share, s.bool_config[i][c.first]);
        }
    }

    int_config.resize(s.int_config.size());
    for (size_t i = 0; i < s.int_config.size(); i++) {
        for (auto c : s.int_config[i]) {
            int_config[i][c.first] = IntVar();
            int_config[i][c.first].update(*this, share, s.int_config[i][c.first]);
        }
    }
    string_config.resize(s.string_config.size());
    for (size_t i = 0; i < s.string_config.size(); i++) {
        for (auto c : s.string_config[i]) {
            string_config[i][c.first] = IntVar();
            string_config[i][c.first].update(*this, share, s.string_config[i][c.first]);
        }
    }
    interleaved.update(*this, share, s.interleaved);
}

Space* InstanceSolution::copy(bool share)
{
    return new InstanceSolution(share, *this);
}

void InstanceSolution::printToDot(std::ostream& os) const
{
    for (auto node : graph->getAllVertices()) {
        auto component = dynamic_cast<Component*>(node.get());
        if (auto composition = dynamic_cast<Composition*>(component)) {
            os << "Cmp::" << composition->getName() << std::endl;
            for (auto c : float_config[graph->getVertexId(node)]) {
                std::cout << c.first.c_str() << std::endl;
                os << "-- " << c.first << ": " << c.second << std::endl;
            }
            for (auto c : bool_config[graph->getVertexId(node)]) {
                std::cout << c.first.c_str() << std::endl;
                os << "-- " << c.first << ": " << c.second << std::endl;
            }
            for (auto c : int_config[graph->getVertexId(node)]) {
                std::cout << c.first.c_str() << std::endl;
                os << "-- " << c.first << ": " << c.second << std::endl;
            }
            for (auto c : string_config[graph->getVertexId(node)]) {
                std::cout << c.first.c_str() << std::endl;
                os << "-- " << c.first << ": " << c.second << std::endl;
            }
        } else if (auto task = dynamic_cast<Task*>(component)) {
            os << task->getName() << std::endl;
            for (auto c : float_config[graph->getVertexId(node)]) {
                std::cout << c.first.c_str() << std::endl;
                os << "-- " << c.first << ": " << c.second << std::endl;
            }
            for (auto c : bool_config[graph->getVertexId(node)]) {
                std::cout << c.first.c_str() << std::endl;
                os << "-- " << c.first << ": " << c.second << std::endl;
            }
            for (auto c : int_config[graph->getVertexId(node)]) {
                std::cout << c.first.c_str() << std::endl;
                os << "-- " << c.first << ": " << c.second << std::endl;
            }
            for (auto c : string_config[graph->getVertexId(node)]) {
                std::cout << c.first.c_str() << std::endl;
                os << "-- " << c.first << ": " << c.second << std::endl;
            }
        } else {
            std::runtime_error("HAve somehting unknown in graphe here");
        }
    }
}

void InstanceSolution::printToStream(std::ostream& os, bool full) const
{
    for (auto _node : graph->vertices()) {
        auto node = boost::reinterpret_pointer_cast<ComponentInstanceHelper>(_node);
        auto component = dynamic_cast<Component*>(node->component.get());
        std::cout << "- " << component->toString() << std::endl;
        if (auto task = dynamic_cast<Task*>(component)) {
            (void)task;
            //            os << task->getName() << std::endl;
            for (auto c : int_config[graph->getVertexId(node)]) {
                os << "-- " << c.first << ": " << c.second << std::endl;
            }
            for (auto c : string_config[graph->getVertexId(node)]) {
                os << "-- " << c.first << ": " << c.second << std::endl;
            }
            for (auto c : bool_config[graph->getVertexId(node)]) {
                os << "-- " << c.first << ": " << c.second << std::endl;
            }
            for (auto c : float_config[graph->getVertexId(node)]) {
                os << "-- " << c.first << ": " << c.second << std::endl;
            }
        }

        for (auto _n2 : graph->vertices()) {
            const auto idx = graph->getVertexId(_n2) + (graph->getVertexId(_node) * verticies_in_tree);
            assert(interleaved[idx].assigned());
            if (interleaved[idx].val()) {
                // auto interleaved_component = boost::reinterpret_pointer_cast<ComponentInstanceHelper>(_n2);
                os << "--- is interleved with:" << _n2->toString() << " " << interleaved[idx].val() << std::endl;
            }
        }
    }
}

graph_analysis::Vertex::Ptr InstanceSolution::getConfiguredComponent(graph_analysis::Vertex::Ptr vertex)
{
    auto id = graph->getVertexId(vertex);

    // Search for the lowest id for a interleaving, the lowest id if the component we use
    for (size_t i = 0; i < verticies_in_tree; i++) {
        if (interleaved[id + (i * verticies_in_tree)].val()) {
            if (i < id) {
                id = i;
            }
        }
    }

    // Never created yet such Configured Component, let's create one
    if (configured_component_helper.find(id) == configured_component_helper.end()) {
        auto helper = boost::static_pointer_cast<ComponentInstanceHelper>(vertex).get()->component.get();
        assert(helper);
        auto component = dynamic_cast<Component*>(helper);
        assert(component);
        auto s = string_config[id];
        auto i = int_config[id];
        auto b = bool_config[id];
        auto f = float_config[id];
        configured_component_helper[id] = graph_analysis::Vertex::Ptr(new ConfiguredComponent(component, f, b, i, s, string_helper));
    }

    assert(configured_component_helper[id].get());
    return configured_component_helper[id];
}

void InstanceSolution::build_tree(graph_analysis::BaseGraph::Ptr erg, graph_analysis::Vertex::Ptr parent)
{
    // If we are on level 0 (e.g need the root_knot
    if (parent.get() == 0) {
        parent = getRoot(graph);
    }
    for (auto child : graph->outEdges(parent)) {
        graph_analysis::Edge::Ptr e(new graph_analysis::Edge());
        e->setSourceVertex(getConfiguredComponent(parent));
        e->setTargetVertex(getConfiguredComponent(child->getTargetVertex()));
        erg->addEdge(e);
        build_tree(erg, child->getTargetVertex());
    }
}

std::vector<graph_analysis::BaseGraph::Ptr> InstanceSolution::babSearch(graph_analysis::BaseGraph::Ptr input_graph)
{
    std::vector<graph_analysis::BaseGraph::Ptr> erg;
    // Initial situation
    InstanceSolution* so = new InstanceSolution(input_graph);
    BAB<InstanceSolution> e(so);
    // search
    InstanceSolution* best = NULL;
    while (InstanceSolution* s = e.next()) {
        if (best != NULL) {
            delete best;
            best = 0;
        }
        //Got a solution print statistics
        auto c = e.statistics();
        std::cout << "Fail: " << c.fail<< " Restart: " << c.restart << " Nogood: " << c.nogood << " depth: " << c.depth << " node: "<< c.node << std::endl;

        graph_analysis::BaseGraph::Ptr out_graph = graph_analysis::BaseGraph::getInstance(graph_analysis::BaseGraph::LEMON_DIRECTED_GRAPH);
        s->build_tree(out_graph, graph_analysis::Vertex::Ptr());
        erg.push_back(out_graph);
        best = s;
    }

    if (best == NULL) {
        delete so;
        throw std::runtime_error("InstanceSolution babSearch: No solutions");
    }
    delete so;
    delete best;
    return erg;
}


}  // end namespace constrained_based_networks
