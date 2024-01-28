#pragma once
#include <string>
#include "engine/utils/types.hpp"
#include "engine/utils/timer.hpp"

namespace bubble
{
struct Engine;

class IEditorInterface
{
public:
    virtual ~IEditorInterface(){}
    virtual string_view Name() = 0;
    virtual void OnInit() = 0;
    virtual void OnUpdate( DeltaTime dt ) = 0;
    virtual void OnDraw( Engine& engine ) = 0;
protected:
    bool mOpen = true;
};
}
