
#include <graph_analysis/GraphIO.hpp>
#include <graph_analysis/BaseGraph.hpp>
#include <graph_analysis/VertexTypeManager.hpp>
#include "NetworkHelper.hpp"
#include "Pool.hpp"
#include "ClassSolution.hpp"
#include "XML.hpp"

using namespace constrained_based_networks;

void NetworkHelper::initializeExporter()
{
    graph_analysis::VertexTypeManager *vManager = graph_analysis::VertexTypeManager::getInstance();
    graph_analysis::Vertex::Ptr cc = graph_analysis::Vertex::Ptr(new ConfiguredComponent());
    vManager->registerType(cc);
    vManager->registerAttribute(cc->getClassName(), "config", (graph_analysis::VertexTypeManager::serialize_func_t) & ConfiguredComponent::serializeConfig,
                                (graph_analysis::VertexTypeManager::deserialize_func_t) & ConfiguredComponent::deSerializeConfig,
                                (graph_analysis::VertexTypeManager::print_func_t) & ConfiguredComponent::printConfig);
    vManager->registerAttribute(cc->getClassName(), "underlaying_name", (graph_analysis::VertexTypeManager::serialize_func_t) & ConfiguredComponent::serializeName,
                                (graph_analysis::VertexTypeManager::deserialize_func_t) & ConfiguredComponent::deserializeName,
                                (graph_analysis::VertexTypeManager::print_func_t) & ConfiguredComponent::serializeName);
}

void NetworkHelper::createClassSolution(std::string core_model, std::list<std::string> additionalRequirements, std::vector<unsigned int> ids){
    Pool *pool = XML::load(XML::loadInstanceSolution(core_model,ids));

    for (auto s : additionalRequirements) {
        if (!pool->hasComponent(s)) {
            throw std::invalid_argument("Cannot start component: " + s + ", it does not exist in the pool");
        }
        pool->getComponent(s)->setActive(true);
    }

    for(auto c : pool->getItems<Component*>()){
        if(c->isActive()){
            std::cout << "Should start: " << c->getName() << std::endl;
            if(auto cmp = dynamic_cast<Composition*>(c)){
                for(auto child : cmp->getChildren()){
                    std::cout << "\t -child: " << child.second->getName() << std::endl;
                }
            }
        }
    }
    auto solutions = ClassSolution::babSearch(pool);
    XML::saveClassSolutions(solutions,core_model, additionalRequirements, ids);
    delete pool;
}

void NetworkHelper::createInstanceSolution(std::string core_model, std::vector<unsigned int> ids){
    Pool *pool = XML::load(core_model);
    auto instance_graph_filename = XML::loadClassSolution(core_model, ids);

    graph_analysis::BaseGraph::Ptr graph_imported = graph_analysis::BaseGraph::getInstance(graph_analysis::BaseGraph::LEMON_DIRECTED_GRAPH);
    graph_analysis::BaseGraph::Ptr graph = graph_analysis::BaseGraph::getInstance(graph_analysis::BaseGraph::LEMON_DIRECTED_GRAPH);
    graph_analysis::io::GraphIO::read(instance_graph_filename, graph_imported, graph_analysis::representation::GEXF);

    // Start to create our graph based on the imported graph
    for (auto node : graph_imported->getAllEdges()) {
        graph_analysis::Edge::Ptr e(new graph_analysis::Edge(node->getLabel()));
        const auto &v1 = pool->getComponent(node->getSourceVertex()->getLabel());
        const auto &v2 = pool->getComponent(node->getTargetVertex()->getLabel());
        assert(v1->getPtr());
        assert(v2->getPtr());
        e->setSourceVertex(v1->getPtr());
        e->setTargetVertex(v2->getPtr());
        graph->addEdge(e);
    }

    std::cout << "Start to create instance-solutions" << std::endl;
    auto is = InstanceSolution::babSearch(graph);
    std::cout << "All " << is.size() << " instance solutions are calculated" << std::endl;

    std::vector<std::pair<graph_analysis::BaseGraph::Ptr, std::list<TransitionTrigger>>> results;
    for (auto solution : is) {
        graph_analysis::DirectedGraphInterface::Ptr g = boost::reinterpret_pointer_cast<graph_analysis::DirectedGraphInterface>(solution);
        auto trigger_events = EventModelHandler(pool, g);
        auto events = trigger_events.getTrigger();
        /*
        std::cout << "Event size is: " <<events.size() << std::endl;
        for(auto e : events){
            std::cout << "\t- " << e.resulting_requirement.network.size() << std::endl;
        }
        */
        results.push_back({solution,events});
    }
    std::cout << "Calculated all follow solutions " << results.size() << std::endl;
    XML::addInstanceSolutions(core_model, results, ids);
    std::cout << "Finish" << std::endl;
    delete pool;
}

bool NetworkHelper::getNextUncalculatedIDs(std::string core_model, std::vector<unsigned int> &ids){
    return XML::findUnresolvedIDs(core_model,ids);
}