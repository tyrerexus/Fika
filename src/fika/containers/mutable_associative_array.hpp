#pragma once
#ifndef FIKA_CONTAINERS_MUTABLE_ASSOCIATIVE_ARRAY_HPP
#define FIKA_CONTAINERS_MUTABLE_ASSOCIATIVE_ARRAY_HPP

#include "associative_array.hpp"
#include "mutable_container.hpp"
#include "fika/pair.hpp"

namespace fika {
    template<typename K, typename V> class MutableAssociativeArray : public AssociativeArray<K, V>, public MutableContainer<Pair<K, V>> {
    public:
        virtual void set(K key, V value) = 0;
    };
}

#endif