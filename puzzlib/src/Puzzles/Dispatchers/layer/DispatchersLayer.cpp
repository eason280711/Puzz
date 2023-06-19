#include "DispatchersLayer.h"
namespace puzz
{
    ref_ptr<Layer> CreateDispatchersLayer()
    {
        ref_ptr<Layer> layer = new DispatchersLayer("DispatchersLayer");
        
        return layer;
    }
}