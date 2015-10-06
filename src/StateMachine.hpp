#pragma once

#include "Component.hpp"
#include <vector>

namespace constrained_based_networks {

    class Pool;

    struct Transition{
        Transition(Component *_target, Component *_source, Component *_event_source, std::string _event):
            target(_target),
            source(_source),
            event_source(_event_source),
            event(_event)
        {
        }

        Component *target;
        Component *source;
        Component *event_source;
        std::string event;
    };

    class StateMachine : public Component{
        public:
            StateMachine(std::string name, Pool *pool);
            ~StateMachine();
            void addTransition(std::string s, std::string t, std::string event_s, std::string event_name);
            void addTransition(Component *source,  Component *target, Component *event_source, std::string ev);
            void addTransition(SpecializedComponentBase *source,  SpecializedComponentBase *target, SpecializedComponentBase *event_source, std::string ev);
            void addTransition(Component *source,  SpecializedComponentBase *target, SpecializedComponentBase *event_source, std::string ev);
            void addTransition(SpecializedComponentBase *source,  Component *target, SpecializedComponentBase *event_source, std::string ev);
            void addTransition(SpecializedComponentBase *source,  SpecializedComponentBase *target, Component *event_source, std::string ev);
            void addTransition(Component *source,  SpecializedComponentBase *target, Component *event_source, std::string ev);
            void addTransition(SpecializedComponentBase *source,  Component *target, Component *event_source, std::string ev);
            void setStart(std::string name);
            void setStart(const Component *c);
            void setStart(SpecializedComponentBase *c);
            bool abstract() const{return false;}
            virtual std::string getClassName() const { return "constrained_based_networks::StateMachine"; }

            /*
             * This is a ugly part again, we need to update out internal components
             * and searching for the correspinding one in a pool
             * This is used when the pool get altered by e.G. mergeDoubles
             */
            void updateInternals(Pool *pool);

            SpecializedComponentBase *getSpecialized();
/*
            SpecializedComponent<StateMachine> *getSpecialized()
            {
                return new SpecializedComponent<StateMachine>(this, pool);
            }
            */

           /*
            void addConfig(std::string name, std::string value){
                if(auto c = dynamic_cast<SpecializedComponent<StateMachine> *>(this)){
                    c->addConfig(name,value);
                }else{
                    throw std::runtime_error("Called addConfig on invalid class");
                }
            }
            */

            std::vector<Component*> getStates();

        protected:
            std::vector<Transition> transitions;
            const Component *start;
            Component* searchCorresponding(Component *c, Pool *pool);

    };
}
