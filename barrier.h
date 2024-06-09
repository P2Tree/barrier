#include <condition_variable>
#include <array>

using namespace std;

class Barrier {
public:
  Barrier(int Expect);
  Barrier() = default;

  void handleBarSync(unsigned PC, unsigned TID);
  void handleBarSync(unsigned Expect, unsigned PC, unsigned TID);

  void handleBarProduce(unsigned Expect, unsigned PC);
  void handleBarConsume(unsigned PC, unsigned TID);

private:
  void wait(unsigned Expect, unsigned PC, unsigned TID);
  void produce(unsigned Expect, unsigned PC);
  void consume(unsigned PC, unsigned TID);

private:
  mutex MutexLock;
  condition_variable Cond;

  unsigned Expect;
  unsigned Count;
  unsigned Release;
  array<unsigned, 8*16> Actives;
};
