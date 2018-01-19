/*
 * Copyright (C) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2017 NXP.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _FSL_MEMORY_MANAGER_H
#define _FSL_MEMORY_MANAGER_H

#include <hardware/gralloc.h>
#include "Memory.h"
#include "MemoryDesc.h"

namespace fsl {

class MemoryManager
{
public:
    virtual ~MemoryManager();

    static MemoryManager* getInstance();

    // allocate memory interface.
    virtual int allocMemory(MemoryDesc& desc, Memory** out) = 0;
    // release memory interface.
    int releaseMemory(Memory* handle);

    // keep memory reference and import it.
    virtual int retainMemory(Memory* handle) = 0;
    // lock memory to get virtual address for CPU access.
    virtual int lock(Memory* handle, int usage,
            int l, int t, int w, int h,
            void** vaddr) = 0;
    // lock YUV memory to get virtual address for CPU access.
    virtual int lockYCbCr(Memory* handle, int usage,
            int l, int t, int w, int h,
            android_ycbcr* ycbcr) = 0;
    // unlock memory after CPU access.
    virtual int unlock(Memory* handle) = 0;

protected:
    MemoryManager();
    int verifyMemory(Memory* handle);

private:
    static Mutex sLock;
    static MemoryManager* sInstance;
};

}
#endif
