#include <constrained_based_networks/Task.hpp>
#include <constrained_based_networks/Composition.hpp>
#include <constrained_based_networks/Pool.hpp>
#include <constrained_based_networks/DataService.hpp>
#include <constrained_based_networks/ClassSolution.hpp>
#include <constrained_based_networks/InstanceSolution.hpp>
#include <constrained_based_networks/SpecializedComponent.hpp>
#include <graph_analysis/GraphIO.hpp>
#include "dump.hpp"

using namespace constrained_based_networks;
Pool *pool;

struct Tests{
    std::string (*v)();
    std::string name;
};





void solve_final_network(ClassSolution s){

}


//void resolve(std::string name, bool res, bool debug = false){
ClassSolution* resolve(Component *c, bool res, bool debug = false){
    /*
        std::cout << "Resolving for component: " <<  c->getName() << " (" << c->getID() << ")" << std::endl;
        //Checking check check
        if(c != pool->operator[](c->getID())){
            std::cout << "Failig id in step 1: " << c->getID() << " for component with name: " << c->getName() << std::endl;
            if(auto spec = dynamic_cast<SpecializedComponentBase *>(c)){
                std::cout << "It is a specialized one, bsae id: " << spec->getOrginal()->getID() << std::endl;
            }
            throw std::runtime_error("1 WHAAAAAAAAARRRRRRRRRRRRRRRRRRRR            Pool is inconsistent to IDs");
        }
*/
    //Check again
    for(auto co: pool->getItems<Component*>()){
        if(co != pool->operator[](co->getID())){
            std::cout << "Check in resolve for the following component failed: " << c->getName() << std::endl;
            std::cout << "Failig id: " << co->getID() << " for component with name: " << co->getName() << std::endl;
            if(auto spec = dynamic_cast<SpecializedComponentBase*>(co)){
                std::cout << "It is a specialized one: " << spec->getID() << " and base id: " << spec->getComponent()->getID() << std::endl;
            }
            throw std::runtime_error("Pool is inconsistent to IDs");
        }
    }

    if(auto sm =  dynamic_cast<StateMachine*>(c)){
        for(auto state : sm->getStates()){
            printf("??????????????      ClassSolution for statemachien %s, for task %s ??????????????????????????\n",sm->getName().c_str(),state->getName().c_str());
            if(dynamic_cast<SpecializedComponentBase *>(state)){
                std::cout << "Habe specialized component" << std::endl;
            }
            return resolve(state,res,debug);
            printf("??????????????      !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ??????????????????????????\n");
        }
    }

    c->setActive(true);
/*
    if(!dynamic_cast<SpecializedComponentBase *>(c)){
        throw std::runtime_error("I currently want a specialized\n");
    }else{
        std::cout << "starte: \n";
        std::cout << dynamic_cast<SpecializedComponentBase *>(c)->getComponent()->getName() << ": " << dynamic_cast<SpecializedComponentBase *>(c)->getComponent()->getID() << std::endl;
        std::cout << "pointer in main: " << c  << " | " << dynamic_cast<SpecializedComponentBase *>(c)->getComponent() << std::endl;
        std::cout << "Pool in main: " << pool << std::endl;
//        std::cout << "pointer in vector in main: " << pool->operator[](360)  << std::endl;

    }
*/
/**
        if(c != pool->operator[](c->getID())){
            std::cout << "Failig id: " << c->getID() << " for component with name: " << c->getName() << std::endl;
            if(auto spec = dynamic_cast<SpecializedComponentBase *>(c)){
                std::cout << "It is a specialized one, bsae id: " << spec->getOrginal()->getID() << std::endl;
            }
            throw std::runtime_error("2 WHAAAAAAAAARRRRRRRRRRRRRRRRRRRR            Pool is inconsistent to IDs");
        }
        */

/*
    for(auto c : pool->getItems<Component*>()){
        auto d = dynamic_cast<SpecializedComponentBase*>(c);
        if(d){
            std::cout << "test 2: \n";
            std::cout << d->getComponent()->getName() << ": " << d->getComponent()->getID() << std::endl;
            std::cout << "pointer in main: " << d  << " | " << dynamic_cast<SpecializedComponentBase *>(d)->getComponent() << std::endl;
        }
    }
*/
    try{
        ClassSolution* s=0;
        if(debug){
            s = ClassSolution::gistBaBSeach();
        }else{
            s = ClassSolution::babSearch(pool);
        }

        std::cout << "+++++ Is solveable: " << c->getName() << std::endl;
        s->rprint();
        std::cout << "End ClassSolution " << c->getName() << std::endl;
        return s;

    }catch(std::runtime_error e){
        std::cout << "!!!!! UN-Solveable: " << c->getName() << " " << e.what() << " " << std::endl;
        if(res){
            c->setActive(false);
            Composition *comp = dynamic_cast<Composition*>(c);
            if(!comp){
                std::cerr << c->getName() << " is No compositon FATAL" << std::endl;
                return 0;
            }
            for(auto child : comp->getChildren()){
                if(child.second->abstract()){
                    if(c->getName() == (child.second->getName() + "_cmp")){
                        std::cerr << "Cannot finally solve " <<  c->getName() << std::endl;
                        return 0;
                    }
                    //TODO fix here specializations got lost
                    resolve(pool->getComponent(child.second->getName() + "_cmp"),res,debug);
                }else{
                    resolve(child.second,res, debug);
                }
            }
        }
        return 0;
    }
}

std::string test_cmp_recursion2(){
//    auto a2 = new Composition("AuvControl::DepthFusionCmp");
    return "A";
}

std::string test_cmp_recursion_w_unused_CS(){
    std::cout << "Testing " << __FUNCTION__ << std::endl;

    //auto a2 = new Composition("A2");
    auto a = new Composition("A");
    auto b = new Composition("B");
    //auto b2 = new Composition("B2");
    a->addChild(b,"b_child");
    auto t = new Task("T");
    b->addChild(t,"t_child");
    return "A";
}

std::string test_ds(){
    std::cout << "Testing " << __FUNCTION__ << std::endl;

    auto a = new Composition("A");
    auto b = new Task("B");
    //auto ds = new DataService("DS");
    b->addFullfillment("DS");
    a->addChild(b,"b_child_is_ds");
    return "A";

}

std::string test_ambigious_ds(){
    std::cout << "Testing " << __FUNCTION__ << std::endl;

    auto a = new Composition("A");
    auto b = new Task("B");
    auto b2 = new Task("B2");
    auto ds = new DataService("DS");

    b->addFullfillment("DS");
    b2->addFullfillment("DS");

    a->addChild(ds,"b_child_is_ds");
    return "A";

}

std::string test_cmp_recursion_w_more_used(){
    std::cout << "Testing " << __FUNCTION__ << std::endl;

    auto a2 = new Composition("A2");
    auto a = new Composition("A");
    auto b = new Composition("B");
    auto b2 = new Composition("B2");
    auto ds = new DataService("DS");
    //auto ds2 = new DataService("DS2");


    b->addFullfillment("DS");
    b2->addFullfillment("DS");
    b->addFullfillment("DS2");
    b2->addFullfillment("DS2");

    a->addChild(ds,"b_child_is_ds");
    a2->addChild(ds,"b_child");
    auto t = new Task("T");
    b->addChild(t,"t_child");
    return "A";

}

std::string test_cmp_recursion_w_used_DS(){
    std::cout << "Testing " << __FUNCTION__ << std::endl;

    //auto a2 = new Composition("A2");
    auto a = new Composition("A");
    auto b = new Composition("B");
    //auto b2 = new Composition("B2");
    auto ds = new DataService("DS");
    //auto ds2 = new DataService("DS2");


    b->addFullfillment("DS");
    //b2->addFullfillment("DS");
    //b->addFullfillment("DS2");
    //b2->addFullfillment("DS2");

    a->addChild(ds,"b_child_is_ds");
    //a2->addChild(ds,"b_child");
    auto t = new Task("T");
    b->addChild(t,"t_child");
    return "A";

}

std::string test_cmp_recursion_w_unused_DS(){
    std::cout << "Testing " << __FUNCTION__ << std::endl;
    auto a = new Composition("A");
    auto b = new Composition("B");
    a->addChild(b,"b_child");
    auto t = new Task("T");
    b->addChild(t,"t_child");
    //auto ds = new DataService("DS");
    return "A";
}

std::string test_cmp_recursion_w_unused_DS2(){
    std::cout << "Testing " << __FUNCTION__ << std::endl;
    auto a = new Composition("A");
    auto b = new Composition("B");
    //auto ds = new DataService("DS");
    a->addChild(b,"b_child");
    auto t = new Task("T");
    b->addChild(t,"t_child");
    return "A";
}

std::string test_cmp_recursion(){
    std::cout << "Testing " << __FUNCTION__ << std::endl;
    auto a = new Composition("A");
    auto b = new Composition("B");
    a->addChild(b,"b_child");
    auto t = new Task("T");
    b->addChild(t,"t_child");
    return "A";
}

std::string test_cmp_recursion_child2_time(){
    std::cout << "Testing " << __FUNCTION__ << std::endl;
    auto a = new Composition("A");
    auto b = new Composition("B");
    auto t = new Task("T");
    a->addChild(t,"t_child");
    a->addChild(b,"b_child");
    b->addChild(t,"t_child");
    return "A";
}

std::string test_cmp_recursion_child2_time_abstract(){
    std::cout << "Testing " << __FUNCTION__ << std::endl;
    auto ds2 = new DataService("DS2-task");
    auto a = new Composition("A");
    auto b = new Composition("B");
    auto t = new Task("T");
    a->addChild(ds2,"t_abstract_child");
    a->addChild(b,"b_child");
    b->addChild(ds2,"t_abstract_child");
    //auto a2 = new Composition("A2");
    //auto a3 = new Composition("A3");
    auto b3 = new Composition("B2");
    auto b2 = new Composition("B2");
    //auto ds = new DataService("DS");

    b3->addChild(t,"task_child");
    b3->addFullfillment(ds2->getName());

    t->addFullfillment(ds2->getName());
    b3->addFullfillment("DS");
    b2->addFullfillment("DS");
    b3->addFullfillment("DS2");
    b2->addFullfillment("DS2");

    return "A";
}

std::string test_possible_loop_unused(){
    std::cout << "Testing " << __FUNCTION__ << std::endl;
    auto a = new Composition("A");
    auto a2 = new Composition("A2");
    auto b = new Composition("B");
    auto c = new Composition("C");
    auto t = new Task("T-not");
    auto t2 = new Task("T-yes");

    a->addChild(a2,"a2_child");
    a2->addChild(t2,"t_child");

    b->addChild(c,"c_child");
    c->addChild(t,"task_child");
    c->addChild(b,"b_child");

    return "A";
}

std::string test_possible_loop_unused2(){
    std::cout << "Testing " << __FUNCTION__ << std::endl;
    auto a = new Composition("A");
    auto a2 = new Composition("A2");
    auto b = new Composition("B");
    auto c = new Composition("C");
    auto d = new Composition("D");
    auto t = new Task("T");

    a->addChild(a2,"a2_child");

    b->addChild(c,"c_child");
    c->addChild(t,"task_child");
    c->addChild(d,"d_child");
    d->addChild(b,"b_child");

    return "A";
}

// main test function
int main(int argc, char* argv[]) {
    bool debug = false;
    bool resolve_nonresolveable = false;
    int test_id =0;

    char c;
    while((c=getopt(argc,argv,"dr")) != -1){
        switch(c){
            case 'd':
                debug = true;
                break;
            case 'r':
                resolve_nonresolveable=true;
                break;
            default:
                printf("On default block\n");
        }
    }

    if(optind == argc){
        std::cerr << "please pass testname" << std::endl;
        exit(-1);
    }
    test_id = atoi(argv[optind]);

    printf("Running test: %i\n",test_id);

    using namespace constrained_based_networks;

    Tests tests[] = {
        {test_cmp_recursion, ""},
        {test_cmp_recursion_w_unused_CS,""},
        {test_cmp_recursion_w_unused_DS,""},
        {test_cmp_recursion_w_unused_DS2,""},
        {test_cmp_recursion_w_used_DS,""},
        {test_ds,""},
        {test_ambigious_ds,""},
        {test_cmp_recursion_w_more_used,""},
        {test_cmp_recursion_child2_time,""},
        {test_cmp_recursion_child2_time_abstract,""},
        {test_possible_loop_unused,""},
        {test_possible_loop_unused2,""},
        {create_model,"AuvControl::DepthFusionCmp"},
        {create_model,"Pipeline::Follower"},
        {create_model,"Buoy::DetectorNewCmp"},
        {create_model,"Wall::Follower"},
        {create_model,"Main::LawnMoverOverPipe"},
        {create_model,"AuvControl::SimpleMove"},
        {0,""}
    };

    std::string name;
    if(tests[test_id].name == ""){
        name = tests[test_id].v();
    }else{
        tests[test_id].v();
        name = tests[test_id].name;
    }

    printf("Running test with name: %s\n",name.c_str());



    pool = Pool::getInstance();

    pool->mergeDoubles();

    std::cout << "Have Components: " << pool->getItems<Component*>().size() << std::endl;

    /*
    for(auto c :  pool->getItems<Composition*>()){
        std::cout << c->getName() << std::endl;
    }
    return 0;
    */
    //std::string name("Base::WorldXYPositionControllerSrv");
    //std::string name("AuvCont::WorldXYPositionCmp");
//    std::string name("Pipeline::Detector_new"); //Nicht ok!!!
    //std::string name("AuvControl::DepthFusionCmp"); //ok!!!
//    std::string name("Base::OrientationWithZSrv_cmp"); //Nicht ok!!!
//    std::string name("PoseAuv::PoseEstimatorBlindCmp"); //Nicht ok!!!

    //std::string name("Base::WorldXYPositionControllerSrv_cmp"); //NICHT ok
    //std::string name("Wall::DetectorNew"); //NICHT ok //Velocity Service
    //std::string name("Localization::ParticleDetector"); //NICHT ok //Hough service
    //std::string name("Localization::HoughDetector"); //NICHT ok //Hough service

    //std::string name("A"); //NICHT ok //Hough service

//    auto a = new Composition("A");
//    a->addChild(pool->getComponent("AuvControl::DepthFusionCmp"),"main_child");


    //pool->getComponent("Pipeline::Detector_new")->setActive(true);
    //pool->getComponent("Pipeline::Follower")->setActive(true);
    //pool->getComponent("AuvControl::DepthFusionCmp")->setActive(true);

    //try{
    graph_analysis::BaseGraph::Ptr graph = graph_analysis::BaseGraph::getInstance(graph_analysis::BaseGraph::LEMON_DIRECTED_GRAPH);
    
    for(auto c: pool->getItems<Component*>()){
        if(c != pool->operator[](c->getID())){
            std::cout << "Failig id: " << c->getID() << " for component with name: " << c->getName() << std::endl;
            if(auto spec = dynamic_cast<SpecializedComponentBase*>(c)){
                std::cout << "It is a specialized one: " << spec->getID() << " and base id: " << spec->getComponent()->getID() << std::endl;
            }
            throw std::runtime_error("Pool is inconsistent to IDs");
        }
    }



    auto s = resolve(pool->getComponent(name),resolve_nonresolveable,debug);
    if(s){
        s->build_tree(graph, 0);
        std::cout << "Finished calculuation of ClassSolution continue with instance" << std::endl;
        graph_analysis::io::GraphIO::write("output.dot",graph,graph_analysis::representation::GRAPHVIZ);
//        InstanceSolution::gistBaBSeach(s);
        std::cout << "Finished calculuation of Instance InstanceSolution, Solution is:" << std::endl;
        std::cout << "################################################################################"<< std::endl;
        std::cout << "################################################################################"<< std::endl;
        std::cout << "################################################################################"<< std::endl;
        auto is = InstanceSolution::babSearch(s);
        is->rprint();
    }else{
        std::cerr << "Cannot create instance solution, class resolution does not return" << std::endl;
    }


    //}catch(...){
    //    std::cerr << " Got maybe a out of mem error" << std::endl;
    //}
//    ClassSolution* s = ClassSolution::babSearch(pool);
//    s->rprint();
    return 0;
}
