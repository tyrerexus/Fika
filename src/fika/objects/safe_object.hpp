#pragma once
#ifndef FIKA_OBJECTS_SAFE_OBJECT_HPP
#define FIKA_OBJECTS_SAFE_OBJECT_HPP

namespace fika {
    class SafeObject {
    public:
        virtual ~SafeObject() {

        }
    protected:
        SafeObject() {}
        SafeObject(const SafeObject &) {}
        SafeObject &operator = (const SafeObject &) = delete;
    };
}

#endif