/**
 * \file macros.cpp
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <array>
#include <cassert>
#include <iostream>

namespace pulp
{
    template <typename T, size_t N>
    class InstanceArray
    {
      public:
        InstanceArray()
        {
            for (size_t i = 0; i < N; ++i)
            {
                instances[i] = T();
            }
        }
        T &operator[](size_t index)
        {
            assert(index < N);
            /*
            if (index >= N)
            {
                throw std::out_of_range("Index out of range");
            }
            */
            return instances[index];
        }

        const T &operator[](size_t index) const
        {
            assert(index < N);
            /*
            if (index >= N)
            {
                throw std::out_of_range("Index out of range");
            }
            */
            return instances[index];
        }

        void printInstances() const
        {
            for (const auto &instance : instances)
            {
                instance.print();
            }
        }

      private:
        std::array<T, N> instances;
    };

    /*
    class MyClass
    {
      public:
        MyClass() :
            id(counter++)
        {
        }

        void print() const { std::cout << "Instance ID: " << id << std::endl; }

      private:
        int id;
        static int counter;
    };

        int MyClass::counter = 1;

        int main()
        {
            constexpr size_t instanceCount = 3;
            InstanceArray<MyClass, instanceCount> instances;
            instances.printInstances();

            return 0;
        }
    */
}