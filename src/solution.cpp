#include <gecode/int.hh>
#include <gecode/search.hh>
#include <gecode/gist.hh>
#include <gecode/minimodel.hh>

#include<vector>
#include<map>

#include "query.h"

using namespace Gecode;

namespace composition_management {

// TODO consider VarArray instead of vector
class Solution : public Space {
protected:
    Query query;
    Query componentPool;
    
    
    // array of assignments (as rows x cols)
    //BoolVarArray assignments; 
    IntVarArray assignments_int;
public:
    Solution(Query query, Query componentPool) 
        : query(query)
        , componentPool(componentPool)
        //, assignments(*this, componentPool.getComponents().size() * query.getComponents().size())
        , assignments_int(*this, query.getComponents().size(), 0, componentPool.getComponents().size())
    {
        // matrix version of assigenments
        //Matrix<BoolVarArray> assignments_matrix(assignments, componentPool.getComponents().size(), query.getComponents().size());
        
        // Each row must have exactly one one. 
        //for(int r = 0; r < assignments_matrix.height(); r++) {
        //    linear(*this, assignments_matrix.row(r), IRT_EQ, 1);
        //}
        // This one must be at a spot where the col and row type are equal
        //rel(*this, north, IRT_EQ, east);
        //element(*this, assignments_matrix, );
        
        // The first indices of a type, in the componentPool
        std::vector<int> typeIndicesPool;
        for(int i = 0; i < componentPool.getComponents().size(); i++) {
            if(i == 0 || componentPool.getComponents().at(i - 1).getType() != componentPool.getComponents().at(i).getType()) {
                typeIndicesPool.push_back(i);
            }
        }
        // The first indices of a type, in the query
        std::vector<int> typeIndicesQuery;
        for(int i = 0; i < query.getComponents().size(); i++) {
            if(i == 0 || query.getComponents().at(i - 1).getType() != query.getComponents().at(i).getType()) {
                typeIndicesQuery.push_back(i);
            }
        }
        
        for(int i = 0, type = -1; i < assignments_int.size(); i++)
        {
            // Increment type if necessary
            if(std::find(typeIndicesQuery.begin(), typeIndicesQuery.end(), i) != typeIndicesQuery.end())
            {
                type++;
            }
            int upperLimit = type + 1 < typeIndicesPool.size() ? typeIndicesPool[type + 1] - 1 : componentPool.getComponents().size() - 1;
            // Constraint domain such that the types equal
            dom(*this, assignments_int[i], typeIndicesPool[type], upperLimit);
        }
        
        // For all queried components
        for(int i = 0; i < assignments_int.size(); i++)
        {
            std::cout << "Constraints for query " << query.getComponents()[i].toString() << std::endl;
            
            // For all possible pool components they can be assigned
            for(int j = assignments_int[i].min(); j <= assignments_int[i].max(); j++)
            {
                std::cout << " Against pool " << componentPool.getComponents()[j].toString() << std::endl;
                
                // TODO extern method testing if two components are compitable regarding their configurations
                // as vector<string>
                // At the moment, the conf vector just has to be equal
                std::vector<std::string>& requiredConfiguration = query.getComponents()[i].getConfiguration();
                std::vector<std::string>& actualConfiguration = componentPool.getComponents()[j].getConfiguration();
                // If the configurations are not compatible, post != constraint on this assignment
                if(!requiredConfiguration.empty()&& !actualConfiguration.empty() && requiredConfiguration != actualConfiguration)
                {
                    // TODO best solution: already assigned conf is better, for reusing components
                    rel(*this, assignments_int[i], IRT_NQ, j);
                }
                
                
                // For all incoming ports of the query component
                std::map<IncomingPort, Component> map = query.getComponents()[i].getIncomingConnections();
                for(std::map<IncomingPort, Component>::const_iterator it = map.begin(); it != map.end(); ++it)
                {
                    std::cout << "Checking connection constraint. Component " << query.getComponents()[i].getName() << "=" << componentPool.getComponents()[j].getName() 
                                  << " on in port " << it->first.name << std::endl;
                    
                    // If the ith query component gets assigned to the jth pool component
                    // and they both are connected on the same input port,
                    // the connection origin must also be assigned equally.
                    std::map<IncomingPort, Component> poolComponentMap = componentPool.getComponents()[j].getIncomingConnections();
                    if(poolComponentMap.count(it->first) != 0)
                    {
                        // Get number of the origins
                        int originQueryNum = std::find(query.getComponents().begin(), query.getComponents().end(), it->second) - query.getComponents().begin();
                        int originPoolNum = std::find(componentPool.getComponents().begin(), componentPool.getComponents().end(), poolComponentMap.at(it->first)) 
                                            - componentPool.getComponents().begin();
                                            
                        std::cout << "Adding connection constraint. Component " << query.getComponents()[i].getName() << "=" << componentPool.getComponents()[j].getName() 
                                  << " => " << it->second.getName() << "=" << poolComponentMap.at(it->first).getName() << std::endl;
                        
                        // Both connected on same port
                        BoolVar ithAssignedToJth(*this, 0, 1);
                        rel(*this, assignments_int[i], IRT_EQ, j, ithAssignedToJth);
                        
                        BoolVar originsConnectedEqually(*this, 0, 1);
                        rel(*this, assignments_int[originQueryNum], IRT_EQ, originPoolNum, originsConnectedEqually);
                        
                        BoolVar implication(*this, 0, 1);
                        rel(*this, ithAssignedToJth, BOT_IMP, originsConnectedEqually, 1);
                    }
                }
                
                //post(home, tt(imp(~(v1 == 2),~(v2 != 1) && ~(v3 != 3)));
                // http://www.gecode.org/pipermail/users/2008-March/001420.html
            }
        }
        
        // branching
        branch(*this, assignments_int, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    }
    
    // search support
    Solution(bool share, Solution& s) 
        : Space(share, s)
        , query(s.query)
        , componentPool(s.componentPool)
    {
        assignments_int.update(*this, share, s.assignments_int);
    }
    virtual Space* copy(bool share) {
        return new Solution(share,*this);
    }
    // print support
    void print(void) const {
        std::cout << "Solution: " << assignments_int << std::endl;
    }
    void print(std::ostream& os) const {
        os << assignments_int << std::endl;
    }
};

} // end namespace composition_management

// main function
int main(int argc, char* argv[]) {
    using namespace composition_management;
    // General components
    Component compA (0, "a", std::vector<IncomingPort>(), std::vector<OutgoingPort>());
    Component compB (1, "b", std::vector<IncomingPort>(), std::vector<OutgoingPort>());
    Component compC (2, "c", std::vector<IncomingPort>(), std::vector<OutgoingPort>());
    // And their ports
    compA.getOutPorts().push_back(OutgoingPort("std::string","a_out_1"));
    compA.getOutPorts().push_back(OutgoingPort("int","a_out_2"));
    compA.getInPorts().push_back(IncomingPort("std::string","a_in_1"));
    compB.getInPorts().push_back(IncomingPort("std::string","b_in_1"));
    compB.getInPorts().push_back(IncomingPort("float","b_in_2"));
    compC.getOutPorts().push_back(OutgoingPort("std::string","c_out_1"));
    compC.getOutPorts().push_back(OutgoingPort("float","c_out_2"));
    compC.getInPorts().push_back(IncomingPort("int","c_in_1"));
    
    // Query components
    Component queryCompA = compA;
    Component queryCompB = compB;
    Component queryCompC = compC;
    // Configure query components
    queryCompA.getConfiguration().push_back("3");
    queryCompA.getConfiguration().push_back("1");
    // No constraint on B's config
    queryCompC.getConfiguration().push_back("2");
    // Push into vector
    std::vector<Component> queryComps;
    queryComps.push_back(queryCompA);
    queryComps.push_back(queryCompB);
    queryComps.push_back(queryCompC);
    // Construct query
    Query query (queryComps);
    // Configure connections
    query.addConnection(query.getComponents()[0], query.getComponents()[0].getOutPorts()[0], query.getComponents()[1], query.getComponents()[1].getInPorts()[0]);
    query.addConnection(query.getComponents()[0], queryCompA.getOutPorts()[1], query.getComponents()[2], query.getComponents()[2].getInPorts()[0]);
    query.addConnection(query.getComponents()[2], query.getComponents()[2].getOutPorts()[0], query.getComponents()[0], query.getComponents()[0].getInPorts()[0]);
    query.addConnection(query.getComponents()[2], query.getComponents()[2].getOutPorts()[1], query.getComponents()[1], query.getComponents()[1].getInPorts()[1]);
    
    // Pool components
    Component poolCompA0 = compA;
    poolCompA0.setName("a0");
    Component poolCompA1 = compA;
    poolCompA1.setName("a1");
    Component poolCompB0 = compB;
    poolCompB0.setName("b0");
    Component poolCompB1 = compB;
    poolCompB1.setName("b1");
    Component poolCompC0 = compC;
    poolCompC0.setName("c0");
    Component poolCompC1 = compC;
    poolCompC1.setName("c1");
    // Configure pool components
    poolCompA0.getConfiguration().push_back("3");
    poolCompA0.getConfiguration().push_back("3");
    poolCompB0.getConfiguration().push_back("2");
    poolCompC1.getConfiguration().push_back("2");
    // Push into vector
    std::vector<Component> poolComps;
    poolComps.push_back(poolCompA0);
    poolComps.push_back(poolCompA1);
    poolComps.push_back(poolCompB0);
    poolComps.push_back(poolCompB1);
    poolComps.push_back(poolCompC0);
    poolComps.push_back(poolCompC1);
    // Construct pool
    Query pool (poolComps);
    // Configure connections
    //pool.addConnection(pool.getComponents()[0], pool.getComponents()[0].getOutPorts()[0], pool.getComponents()[2], pool.getComponents()[2].getInPorts()[0]);
    //pool.addConnection(pool.getComponents()[0], pool.getComponents()[0].getOutPorts()[1], pool.getComponents()[5], pool.getComponents()[5].getInPorts()[0]);
    //pool.addConnection(pool.getComponents()[4], pool.getComponents()[4].getOutPorts()[0], pool.getComponents()[0], pool.getComponents()[0].getInPorts()[0]);
    //pool.addConnection(pool.getComponents()[5], pool.getComponents()[5].getOutPorts()[1], pool.getComponents()[2], pool.getComponents()[2].getInPorts()[1]);
    // Optional:
    //pool.addConnection(pool.getComponents()[0], pool.getComponents()[0].getOutPorts()[0], pool.getComponents()[3], pool.getComponents()[3].getInPorts()[0]);
    
    Solution* s = new Solution(query, pool);
    DFS<Solution> e(s);
    delete s;
    // search and print all solutions
    while (Solution* s = e.next()) {
        s->print(); delete s;
    } 
    return 0;
}
