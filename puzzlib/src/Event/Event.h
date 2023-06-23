#pragma once
#include "Core/Inherit.h"
#include "Core/Object.h"
#include "Core/ref_ptr.h"
#include <string>
#include <iostream>

namespace puzz
{
    class DataHolder
    {
    public:
        virtual ~DataHolder() {}
    };

    template<typename T>
    class Data : public DataHolder
    {
    public:
        Data(const T& data) : data(data) {}
        T get() const { return data; }

    private:
        T data;
    };

    class Event : public Inherit<abstract_method<Event>, Object>
    {
    public:
        Event(std::string name) : Name(name) {}
        virtual ~Event() {}

        virtual bool Handle()
        {
            std::cout << getName() << std::endl;
            return true;
        }

        void setName(std::string name) { Name = name; }
        std::string getName() const { return Name; }

        void setDataHolder(ref_ptr<DataHolder> dataHolder) { dataHolder_ = dataHolder; }

        template<typename T>
        T getData() const
        {
            ref_ptr<Data<T>> data = dynamic_pointer_cast<DataHolder,Data<T>>(dataHolder_);
            return (*data).get();
        }

    private:
        std::string Name = "Event";
        ref_ptr<DataHolder> dataHolder_;
    };
}