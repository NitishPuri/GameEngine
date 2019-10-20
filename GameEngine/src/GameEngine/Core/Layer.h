#pragma once

#include "GameEngine/Core/Core.h"
#include "GameEngine/Core/Timestep.h"
#include "GameEngine/Events/Event.h"

namespace GE {

    class GE_API Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {};
        virtual void OnDetach() {};
        virtual void OnUpdate(Timestep ts) {};
        virtual void OnImGuiRender() {};
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return m_DebugName; }

    protected:
        std::string m_DebugName;
    };

}
