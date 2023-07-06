#include "render.h"

#include "Core/Core.h"
#include "Core/Inherit.h"

namespace puzz
{
    class MagnumManager : public Inherit<MagnumManager, RuntimeModule>
    {
    public:
        MagnumManager() {}
        ~MagnumManager() override {}

        void startUp() override
        {
        }

        void shutDown() override
        {
        }

        void Tick() override
        {
            /* You might want to update Magnum rendering here */
        }
    private:
    };
}