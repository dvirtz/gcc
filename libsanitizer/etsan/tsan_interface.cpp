//===-- tsan_interface.cc -------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// (c) 2017 - 2021  Hassan Salehe Matar, Koc University
//            Email: hmatar@ku.edu.tr
//===----------------------------------------------------------------------===//

#include "tsan_interface.h"
#include "fasttrack.h"
#include "race_report.h"
#include "defs.h"

typedef unsigned long uptr; // NOLINT
#define CALLERPC ((uptr)__builtin_return_address(0))

void __tsan_init() {}

void __tsan_main_func_exit() {}

// 1. Callbacks for memory accesses
void __tsan_read1(void* addr,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_read( getVarState(addr, false), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnRead( lineNo, objName, fileName );
    }
  }
  //  MemoryRead(cur_thread(), CALLERPC, (uptr)addr, kSizeLog1);
}

void __tsan_read2(
       void* addr,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_read( getVarState(addr, false), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnRead( lineNo, objName, fileName );
    }
  }
}

void __tsan_read4(
       void* addr,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_read( getVarState(addr, false), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnRead( lineNo, objName, fileName );
    }
  }
}

void __tsan_read8(
       void* addr,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_read( getVarState(addr, false), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnRead( lineNo, objName, fileName );
    }
  }
}

void __tsan_read16(
       void* addr,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_read( getVarState(addr, false), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnRead( lineNo, objName, fileName );
    }
  }
}

void __tsan_write1(
       void* addr,
       int lineNo,
       void* objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_write( getVarState(addr, true), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnWrite( lineNo, objName, fileName );
    }
  }
}

void __tsan_write2(void * addr,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_write( getVarState(addr, true), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnWrite( lineNo, objName, fileName );
    }
  }
}

void __tsan_write4(
       void* addr,
       int lineNo,
       void * objName,
       void* fileName) {
//  printf("Memory write at line: %p\n", CALLERPC);
  if (isConcurrent) {
    bool isRace = ft_write( getVarState(addr, true), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnWrite( lineNo, objName, fileName );
    }
  }
}

void __tsan_write8(
       void* addr,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_write( getVarState(addr, true), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnWrite( lineNo, objName, fileName );
    }
  }
}

void __tsan_write16(
       void* addr,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_write( getVarState(addr, true), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnWrite( lineNo, objName, fileName );
    }
  }
}


// 2. Callbacks for unaligned memory accesses
void __tsan_unaligned_read2(
       const void *addr,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_read( getVarState(addr, false), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnRead( lineNo, objName, fileName );
    }
  }
}


void __tsan_unaligned_read4(
       const void *addr,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_read( getVarState(addr, false), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnRead( lineNo, objName, fileName );
    }
  }
}

void __tsan_unaligned_read8(
       const void *addr,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_read( getVarState(addr, false), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnRead( lineNo, objName, fileName );
    }
  }
}

void __tsan_unaligned_read16(
       const void *addr,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_read( getVarState(addr, false), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnRead( lineNo, objName, fileName );
    }
  }
}

void __tsan_unaligned_write2(
       void* addr,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_write( getVarState(addr, true), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnWrite( lineNo, objName, fileName );
    }
  }
}

void __tsan_unaligned_write4(
       void* addr,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_write( getVarState(addr, true), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnWrite( lineNo, objName, fileName );
    }
  }
}

void __tsan_unaligned_write8(
       void* addr,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_write( getVarState(addr, true), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnWrite( lineNo, objName, fileName );
    }
  }
}

void __tsan_unaligned_write16(
       void* addr,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_write( getVarState(addr, true), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnWrite( lineNo, objName, fileName );
    }
  }
}

// 3. Callbacks for virtual pointer accesses
void __tsan_vptr_read(void **vptr_p,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_read( getVarState(vptr_p, false), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnWrite( lineNo, objName, fileName );
    }
  }
}

void __tsan_vptr_update(void **vptr_p, void *new_val,
       int lineNo,
       void * objName,
       void* fileName) {
  if (isConcurrent) {
    bool isRace = ft_write( getVarState(vptr_p, true), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnWrite( lineNo, objName, fileName );
    }
  }
}

void __tsan_read_range(void *addr, unsigned long size, int lineNo, void* objName, void * fileName) {
  if (isConcurrent) {
    bool isRace = ft_read( getVarState(addr, false), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnRead( lineNo, objName, fileName );
    }
  }
}

void __tsan_write_range(void *addr, unsigned long /* size */, int lineNo, void* objName, void * fileName) {
  if (isConcurrent) {
    bool isRace = ft_write( getVarState(addr, true), getThreadState() );
    if ( isRace ) {
      etsan::reportRaceOnWrite( lineNo, objName, fileName );
    }
  }
}

// 4. Callbacks for synchronization events
void __tsan_thread_create(void * childIdAddr) {
  const auto child_id = *reinterpret_cast<ThreadID*>(childIdAddr);
  const auto parent_id = pthread_self();
  ft_fork( getState(parent_id), getState(child_id) );
}

void __tsan_thread_join(void * childIdAddr) {

  const auto child_id = reinterpret_cast<ThreadID>(childIdAddr);
  const auto parent_id = pthread_self();
  ft_join( getState(parent_id), getState(child_id) );
}

void __tsan_thread_lock(void * lock) {
  ft_acquire( getThreadState(), getLockState(lock) );
}

void __tsan_thread_unlock(void * lock) {
  ft_release( getThreadState(), getLockState(lock) );
}

__tsan_atomic8 __tsan_atomic8_load(const volatile __tsan_atomic8 *a,
                                   __tsan_memory_order mo) {
  ft_atomic_load();
  return {};
}
__tsan_atomic16 __tsan_atomic16_load(const volatile __tsan_atomic16 *a,
                                     __tsan_memory_order mo) {
  ft_atomic_load();
  return {};
}

__tsan_atomic32 __tsan_atomic32_load(const volatile __tsan_atomic32 *a,
                                     __tsan_memory_order mo) {
  ft_atomic_load();
  return {};
}

a8 __tsan_atomic32_fetch_add(volatile a8 *a, a8 v,
                             __tsan_memory_order mo) {
  printf("EmbedSanitizer: atomic_fetch_add not implemented\n");
  return {};
}

void __tsan_func_entry(void *funcName) {
  etsan::pushFunction((char*)funcName);
}

void __tsan_func_exit(void *funcName) {
  etsan::popFunction((char *)funcName);
}

void __tsan_mutex_create(void */* addr */, unsigned /* flags */) {}
void __tsan_mutex_destroy(void */* addr */, unsigned /* flags */) {}
void __tsan_mutex_pre_lock(void */* addr */, unsigned /* flags */) {}
void __tsan_mutex_post_lock(void */* addr */, unsigned /* flags */, int /* recursion */) {}
int __tsan_mutex_pre_unlock(void */* addr */, unsigned /* flags */) { return 0; }
void __tsan_mutex_post_unlock(void */* addr */, unsigned /* flags */) {}
void __tsan_mutex_pre_signal(void */* addr */, unsigned /* flags */) {}
void __tsan_mutex_post_signal(void */* addr */, unsigned /* flags */) {}
void __tsan_mutex_pre_divert(void */* addr */, unsigned /* flags */) {}
void __tsan_mutex_post_divert(void */* addr */, unsigned /* flags */) {}