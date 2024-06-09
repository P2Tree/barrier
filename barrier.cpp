#include <iostream>

#include "barrier.h"

Barrier::Barrier(int Expect) : Expect(Expect), Count(0), Release(0) {
  for (unsigned I = 0; I < Expect; I++) {
    Actives[I] = 0;
  }
}

void Barrier::handleBarSync(unsigned PC, unsigned TID) {
  wait(Expect, PC, TID);
}

void Barrier::handleBarSync(unsigned Expect, unsigned PC, unsigned TID) {
  wait(Expect, PC, TID);
}

void Barrier::handleBarProduce(unsigned Expect, unsigned PC) {
  produce(Expect, PC);
}

void Barrier::handleBarConsume(unsigned PC, unsigned TID) {
  consume(PC, TID);
}

void Barrier::wait(unsigned Expect, unsigned PC, unsigned TID) {
  unique_lock<mutex> Lock(MutexLock);
  if (Actives[TID] != Release) {
    Actives[TID]++;
#ifdef DEBUG
    cout << "Dropped sync of " << TID << " in " << PC << ", Active = " << Actives[TID] << endl;
#endif
    return;
  }
  Count++;
  Actives[TID]++;
#ifdef DEBUG
  cout << "Enter sync of " << TID << " in " << PC << ", Active = " << Actives[TID] << ", Count = " << Count << endl;
#endif
  if (Count == Expect) {
    Count = 0;
    Release++;
    Cond.notify_all();
#ifdef DEBUG
    cout << "Notify sync of " << TID << " in " << PC << ", Release = " << Release << ", Count = " << Count << endl;
#endif
  } else {
#ifdef DEBUG
    cout << "Wait sync of " << TID << " in " << PC << endl;
#endif
    unsigned LocalRelease = Release + 1;
    Cond.wait(Lock, [&]{ return LocalRelease - Release <= 0; });
#ifdef DEBUG
    cout << "Awake sync of " << TID << " in " << PC << endl;
#endif
  }
}

void Barrier::produce(unsigned Expect, unsigned PC) {
  unique_lock<mutex> Lock(MutexLock);
  Count = Expect;
#ifdef DEBUG
  cout << "Enter produce in " << PC << ", Count = " << Count << endl;
#endif
  Cond.notify_all();
#ifdef DEBUG
  cout << "Notify produce in " << PC << ", Count = " << Count << endl;
#endif
}

void Barrier::consume(unsigned PC, unsigned TID) {
  unique_lock<mutex> Lock(MutexLock);
  Actives[TID]++;
#ifdef DEBUG
  cout << "Enter consume of " << TID << " in " << PC << ", Active = " << Actives[TID] << ", Count = " << Count << endl;
#endif
  if (Count != 0) {
    Count--;
#ifdef DEBUG
    cout << "Decrease consume of " << TID << " in " << PC << ", Count = " << Count << endl;
#endif
  } else {
#ifdef DEBUG
    cout << "Wait consume of " << TID << " in " << PC << endl;
#endif
    Cond.wait(Lock, [&]{ return Count != 0; });
    Count--;
#ifdef DEBUG
    cout << "Awake consume of " << TID << " in " << PC << ", Count = " << Count << endl;
#endif
  }
}

