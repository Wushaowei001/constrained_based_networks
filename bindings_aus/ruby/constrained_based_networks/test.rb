require 'constrained_based_networks'

include CONSTRAINED_BASED_NETWORKS

compA = Composition.new(0, "a")
compB = Composition.new(1, "b")
compC = Composition.new(2, "c")
# And their ports
compA.pushBackOutPort(OutgoingPort.new("std::string","out0"))
compA.pushBackOutPort(OutgoingPort.new("int","out1"))
compA.pushBackInPort(IncomingPort.new("std::string","in0"))
compB.pushBackInPort(IncomingPort.new("std::string","in0"))
compB.pushBackInPort(IncomingPort.new("float","in1"))
compC.pushBackOutPort(OutgoingPort.new("std::string","out0"))
compC.pushBackOutPort(OutgoingPort.new("float","out1"))
compC.pushBackInPort(IncomingPort.new("int","in0"))

# Query components
queryCompA = compA.copy
queryCompB = compB.copy
queryCompC = compC.copy
queryCompAnotherC = compC.copy
queryCompAnotherC.setName("anotherC")
# Configure query components
#compAConf = ["3", "1"]
#queryCompA.setConfiguration(compAConf)
# No constraint on B's config
#compCConf = ["2"]
#queryCompC.setConfiguration(compCConf)
# Construct query and subquery
query = Query.new("query")
subquery = Query.new("subquery")
query.addComposition(queryCompA)
query.addComposition(queryCompAnotherC)
subquery.addComposition(queryCompB)
subquery.addComposition(queryCompC)


# Configure connections
subquery.addConnection(queryCompC.getName(), "out1",
                       queryCompB.getName(), "in1");
query.integrateSubQuery(subquery)

query.addConnection(queryCompA.getName(), "out0",
                    queryCompB.getName(), "in0");
query.addConnection(queryCompA.getName(), "out1",
                    queryCompAnotherC.getName(), "in0");
query.addConnection(queryCompAnotherC.getName(), "out0",
                    queryCompA.getName(), "in0");

# Pool components
poolCompA0 = compA.copy
poolCompA0.setName("a0")
poolCompA1 = compA.copy
poolCompA1.setName("a1")
poolCompB0 = compB.copy
poolCompB0.setName("b0")
poolCompB1 = compB.copy
poolCompB1.setName("b1")
poolCompC0 = compC.copy
poolCompC0.setName("c0")
poolCompC1 = compC.copy
poolCompC1.setName("c1")
# Configure pool components
compA0Conf = ["1", "2"]
poolCompA0.setConfiguration(compA0Conf)
compA1Conf = ["2", "2"]
poolCompA1.setConfiguration(compA1Conf)
compB0Conf = ["1"]
poolCompB0.setConfiguration(compB0Conf)
compB1Conf = ["2"]
poolCompB1.setConfiguration(compB1Conf)
compC0Conf = ["1"]
poolCompC0.setConfiguration(compC0Conf)
compC1Conf = ["2"]
poolCompC1.setConfiguration(compC1Conf)
# Construct pool
pool = Query.new("pool")
pool.addComposition(poolCompA0)
pool.addComposition(poolCompA1)
pool.addComposition(poolCompB0)
pool.addComposition(poolCompB1)
pool.addComposition(poolCompC0)
pool.addComposition(poolCompC1)

# Configure connections
pool.addConnection(poolCompA0.getName(), "out0", 
                   poolCompB0.getName(), "in0");
pool.addConnection(poolCompA0.getName(), "out1", 
                   poolCompC1.getName(), "in0");
pool.addConnection(poolCompC0.getName(), "out0", 
                   poolCompA0.getName(), "in0");
pool.addConnection(poolCompC1.getName(), "out1", 
                   poolCompB0.getName(), "in1");
# Optional:
pool.addConnection(poolCompA0.getName(), "out0", 
                   poolCompB1.getName(), "in0");

# Print pool and query
print "Pool: " + pool.toString()
print "Query: " + query.toString()

s = Solution.babSearch(query, pool)
s.print()
