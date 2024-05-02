#pragma once

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIND_ACTION_FN(fn) std::bind(&fn, this)

namespace puzz
{

}