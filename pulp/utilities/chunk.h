/**
 * \file chunk.h
 * \author Roman Koch, koch.roman@gmail.com
 *
 * Copyright (c) 2024, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 *
 */
/**
    \brief Byte chunk

    \internal
    \author Roman Koch, koch.roman@gmail.com
*/

#pragma once

#include <stdint.h>
#include <stdlib.h>

/** \brief Chunk structure */
struct chunk_t
{
    uint8_t *space;
    size_t size;
};

struct const_chunk_t
{
    uint8_t const *space;
    size_t size;
};
