/**
 * Fibonacci Queue
 * Copyright (c) 2014, Emmanuel Benazera beniz@droidnik.fr,
 * 2017, Kyle Vedder kvedder@umass.edu, All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.
 */

/**
 * This is basically a Fibonacci heap with an added fast store for retrieving
 * nodes, and decrease their key as needed. Useful for search algorithms (e.g.
 * Dijstra, heuristic, ...).
 */

#ifndef FIBOQUEUE_H
#define FIBOQUEUE_H

#include <algorithm>
#include <unordered_map>
#include "fiboheap.h"

template <class T>
class FibQueue : public FibHeap<T> {
 public:
  FibQueue() : FibHeap<T>() {}

  ~FibQueue() {}

  void decrease_key(typename FibHeap<T>::FibNode *x, int k) {
    typename std::unordered_map<T, typename FibHeap<T>::FibNode *>::iterator
        mit = find(x->key);
    fstore.erase(mit);
    fstore.insert(std::pair<T, typename FibHeap<T>::FibNode *>(k, x));
    FibHeap<T>::decrease_key(x, k);
  }

  typename FibHeap<T>::FibNode *push(T k, int idx) {
    typename FibHeap<T>::FibNode *x = FibHeap<T>::push(k, idx);
    fstore.insert(std::pair<T, typename FibHeap<T>::FibNode *>(k, x));
    return x;
  }

  typename std::unordered_map<T, typename FibHeap<T>::FibNode *>::iterator find(
      T k) {
    typename std::unordered_map<T, typename FibHeap<T>::FibNode *>::iterator
        mit = fstore.find(k);
    return mit;
  }

  typename FibHeap<T>::FibNode *findNode(T k) {
    typename std::unordered_map<T, typename FibHeap<T>::FibNode *>::iterator
        mit = find(k);
    return (*mit).second;
  }

  int pop() {
    if (FibHeap<T>::empty()) return 0;
    typename FibHeap<T>::FibNode *x = FibHeap<T>::extract_min();
    if (x == nullptr) {
      std::cerr << "Returned nullptr!";
      exit(0);
      return 0;  // should not happen.
    }

    auto index = x->index;
    auto range = fstore.equal_range(x->key);
    auto mit = std::find_if(
        range.first, range.second,
        [x](const std::pair<T, typename FibHeap<T>::FibNode *> &ele) {
          return ele.second == x;
        });
    if (mit != range.second)
      fstore.erase(mit);
    else
      std::cerr << "[Error]: key " << x->key
                << " cannot be found in FiboQueue fast store\n";
    delete x;
    return index;
  }

  bool empty() {
    return FibHeap<T>::empty();
  }

  std::unordered_multimap<T, typename FibHeap<T>::FibNode *> fstore;
};

#endif
