#include <chrono>
#include <vector>
#include <thread>
#include <iostream>

#include "barrier.h"

using namespace chrono;
using namespace std;
using namespace this_thread;

Barrier Bar(16);
Barrier Bar2(16);
Barrier BarGemm;

void barSyncAll1(unsigned TID) {
  sleep_for(seconds(3));
  Bar.handleBarSync(1, TID);
  sleep_for(seconds(1));
  Bar.handleBarSync(2, TID);
  sleep_for(seconds(5));
  Bar.handleBarSync(3, TID);
}

void barSyncAll2(unsigned TID) {
  Bar.handleBarSync(1, TID);
  Bar.handleBarSync(2, TID);
  Bar.handleBarSync(3, TID);
}

void barSyncAll3(unsigned TID) {
  sleep_for(seconds(1));
  Bar.handleBarSync(1, TID);
  sleep_for(seconds(2));
  Bar.handleBarSync(2, TID);
  sleep_for(seconds(4));
  Bar.handleBarSync(3, TID);
}

void case1BarSyncAll() {
  unsigned CaseID = 1;
  cout << "========== Case " << CaseID << ": BarSyncAll ==========" << endl;

  vector<thread> threads;
  threads.emplace_back(thread(barSyncAll1, 0));
  threads.emplace_back(thread(barSyncAll2, 1));
  threads.emplace_back(thread(barSyncAll3, 2));
  threads.emplace_back(thread(barSyncAll1, 3));
  threads.emplace_back(thread(barSyncAll2, 4));
  threads.emplace_back(thread(barSyncAll3, 5));
  threads.emplace_back(thread(barSyncAll1, 6));
  threads.emplace_back(thread(barSyncAll2, 7));
  threads.emplace_back(thread(barSyncAll1, 8));
  threads.emplace_back(thread(barSyncAll2, 9));
  threads.emplace_back(thread(barSyncAll3, 10));
  threads.emplace_back(thread(barSyncAll1, 11));
  threads.emplace_back(thread(barSyncAll2, 12));
  threads.emplace_back(thread(barSyncAll3, 13));
  threads.emplace_back(thread(barSyncAll1, 14));
  threads.emplace_back(thread(barSyncAll2, 15));

  for(auto &t : threads) {
    t.join();
  }
  cout << "========== Case " << CaseID << " Finished ==========" << endl;
}

void barSyncAll4(unsigned TID) {
  sleep_for(seconds(3));
  Bar.handleBarSync(1, TID);
  sleep_for(seconds(1));
  Bar2.handleBarSync(2, TID);
  sleep_for(seconds(5));
  Bar.handleBarSync(3, TID);
}

void barSyncAll5(unsigned TID) {
  Bar.handleBarSync(1, TID);
  Bar2.handleBarSync(2, TID);
  Bar.handleBarSync(3, TID);
}

void barSyncAll6(unsigned TID) {
  sleep_for(seconds(1));
  Bar.handleBarSync(1, TID);
  sleep_for(seconds(2));
  Bar2.handleBarSync(2, TID);
  sleep_for(seconds(4));
  Bar.handleBarSync(3, TID);
}

void case2BarSyncAll() {
  unsigned CaseID = 2;
  cout << "========== Case " << CaseID << ": BarSyncAll ==========" << endl;

  vector<thread> threads;
  threads.emplace_back(thread(barSyncAll4, 0));
  threads.emplace_back(thread(barSyncAll5, 1));
  threads.emplace_back(thread(barSyncAll6, 2));
  threads.emplace_back(thread(barSyncAll4, 3));
  threads.emplace_back(thread(barSyncAll5, 4));
  threads.emplace_back(thread(barSyncAll6, 5));
  threads.emplace_back(thread(barSyncAll4, 6));
  threads.emplace_back(thread(barSyncAll5, 7));
  threads.emplace_back(thread(barSyncAll4, 8));
  threads.emplace_back(thread(barSyncAll5, 9));
  threads.emplace_back(thread(barSyncAll6, 10));
  threads.emplace_back(thread(barSyncAll4, 11));
  threads.emplace_back(thread(barSyncAll5, 12));
  threads.emplace_back(thread(barSyncAll6, 13));
  threads.emplace_back(thread(barSyncAll4, 14));
  threads.emplace_back(thread(barSyncAll5, 15));

  for(auto &t : threads) {
    t.join();
  }
  cout << "========== Case " << CaseID << " Finished ==========" << endl;
}

void barSyncCnt1(unsigned TID) {
  sleep_for(seconds(3));
  Bar.handleBarSync(8, 1, TID);
  sleep_for(seconds(1));
  Bar.handleBarSync(8, 2, TID);
  sleep_for(seconds(5));
  Bar.handleBarSync(3, TID);
}

void barSyncCnt2(unsigned TID) {
  Bar.handleBarSync(8, 1, TID);
  Bar.handleBarSync(8, 2, TID);
  Bar.handleBarSync(3, TID);
}

void barSyncCnt3(unsigned TID) {
  sleep_for(seconds(1));
  Bar.handleBarSync(8, 1, TID);
  sleep_for(seconds(2));
  Bar.handleBarSync(8, 2, TID);
  sleep_for(seconds(4));
  Bar.handleBarSync(3, TID);
}

void case3BarSyncCnt() {
  unsigned CaseID = 3;
  cout << "========== Case " << CaseID << ": BarSyncCnt ==========" << endl;

  vector<thread> threads;
  threads.emplace_back(thread(barSyncCnt1, 0));
  threads.emplace_back(thread(barSyncCnt2, 1));
  threads.emplace_back(thread(barSyncCnt3, 2));
  threads.emplace_back(thread(barSyncCnt1, 3));
  threads.emplace_back(thread(barSyncCnt2, 4));
  threads.emplace_back(thread(barSyncCnt3, 5));
  threads.emplace_back(thread(barSyncCnt1, 6));
  threads.emplace_back(thread(barSyncCnt2, 7));
  threads.emplace_back(thread(barSyncCnt1, 8));
  threads.emplace_back(thread(barSyncCnt2, 9));
  threads.emplace_back(thread(barSyncCnt3, 10));
  threads.emplace_back(thread(barSyncCnt1, 11));
  threads.emplace_back(thread(barSyncCnt2, 12));
  threads.emplace_back(thread(barSyncCnt3, 13));
  threads.emplace_back(thread(barSyncCnt1, 14));
  threads.emplace_back(thread(barSyncCnt2, 15));

  for(auto &t : threads) {
    t.join();
  }
  cout << "========== Case " << CaseID << " Finished ==========" << endl;
}

void barSyncCnt4(unsigned TID) {
  sleep_for(seconds(3));
  Bar.handleBarSync(3, 1, TID);
  sleep_for(seconds(1));
  Bar.handleBarSync(6, 2, TID);
  sleep_for(seconds(5));
  Bar.handleBarSync(7, 3, TID);
}

void barSyncCnt5(unsigned TID) {
  Bar.handleBarSync(3, 1, TID);
  Bar.handleBarSync(6, 2, TID);
  Bar.handleBarSync(7, 3, TID);
}

void barSyncCnt6(unsigned TID) {
  sleep_for(seconds(1));
  Bar.handleBarSync(3, 1, TID);
  sleep_for(seconds(2));
  Bar.handleBarSync(6, 2, TID);
  sleep_for(seconds(4));
  Bar.handleBarSync(7, 3, TID);
}

void case4BarSyncCnt() {
  unsigned CaseID = 4;
  cout << "========== Case " << CaseID << ": BarSyncCnt ==========" << endl;

  vector<thread> threads;
  threads.emplace_back(thread(barSyncCnt4, 0));
  threads.emplace_back(thread(barSyncCnt5, 1));
  threads.emplace_back(thread(barSyncCnt6, 2));
  threads.emplace_back(thread(barSyncCnt4, 3));
  threads.emplace_back(thread(barSyncCnt5, 4));
  threads.emplace_back(thread(barSyncCnt6, 5));
  threads.emplace_back(thread(barSyncCnt4, 6));
  threads.emplace_back(thread(barSyncCnt5, 7));
  threads.emplace_back(thread(barSyncCnt4, 8));
  threads.emplace_back(thread(barSyncCnt5, 9));
  threads.emplace_back(thread(barSyncCnt6, 10));
  threads.emplace_back(thread(barSyncCnt4, 11));
  threads.emplace_back(thread(barSyncCnt5, 12));
  threads.emplace_back(thread(barSyncCnt6, 13));
  threads.emplace_back(thread(barSyncCnt4, 14));
  threads.emplace_back(thread(barSyncCnt5, 15));

  for(auto &t : threads) {
    t.join();
  }
  cout << "========== Case " << CaseID << " Finished ==========" << endl;
}

void barProduce1() {
  BarGemm.handleBarProduce(15, 1);
}

void barConsume1(unsigned TID) {
  BarGemm.handleBarConsume(2, TID);
}

void case5BarCsm() {
  unsigned CaseID = 5;
  cout << "========== Case " << CaseID << ": BarCsm ==========" << endl;

  vector<thread> threads;
  threads.emplace_back(thread(barConsume1, 1));
  threads.emplace_back(thread(barConsume1, 2));
  threads.emplace_back(thread(barConsume1, 3));
  threads.emplace_back(thread(barConsume1, 4));
  threads.emplace_back(thread(barConsume1, 5));
  threads.emplace_back(thread(barConsume1, 6));
  threads.emplace_back(thread(barConsume1, 7));
  threads.emplace_back(thread(barConsume1, 8));
  threads.emplace_back(thread(barConsume1, 9));
  threads.emplace_back(thread(barProduce1));
  threads.emplace_back(thread(barConsume1, 10));
  threads.emplace_back(thread(barConsume1, 11));
  threads.emplace_back(thread(barConsume1, 12));
  threads.emplace_back(thread(barConsume1, 13));
  threads.emplace_back(thread(barConsume1, 14));
  threads.emplace_back(thread(barConsume1, 15));

  for(auto &t : threads) {
    t.join();
  }
  cout << "========== Case " << CaseID << " Finished ==========" << endl;
}

void barProduce2(unsigned TID) {
  sleep_for(seconds(1));
  Bar.handleBarSync(4, 1, TID);
  sleep_for(seconds(2));
  Bar.handleBarSync(4, 2, TID);
  sleep_for(seconds(2));
  Bar.handleBarSync(4, 3, TID);
  sleep_for(seconds(4));
  BarGemm.handleBarProduce(15, 1);
}

void barConsume2(unsigned TID) {
  Bar.handleBarSync(4, 1, TID);
  sleep_for(seconds(1));
  Bar.handleBarSync(4, 2, TID);
  sleep_for(seconds(2));
  Bar.handleBarSync(4, 3, TID);
  sleep_for(seconds(2));
  BarGemm.handleBarConsume(2, TID);
}

void case6BarSyncCsm() {
  unsigned CaseID = 6;
  cout << "========== Case " << CaseID << ": BarSyncCsm ==========" << endl;

  vector<thread> threads;
  threads.emplace_back(thread(barConsume2, 1));
  threads.emplace_back(thread(barConsume2, 2));
  threads.emplace_back(thread(barConsume2, 3));
  threads.emplace_back(thread(barConsume2, 4));
  threads.emplace_back(thread(barConsume2, 5));
  threads.emplace_back(thread(barConsume2, 6));
  threads.emplace_back(thread(barConsume2, 7));
  threads.emplace_back(thread(barConsume2, 8));
  threads.emplace_back(thread(barConsume2, 9));
  threads.emplace_back(thread(barProduce2, 0));
  threads.emplace_back(thread(barConsume2, 10));
  threads.emplace_back(thread(barConsume2, 11));
  threads.emplace_back(thread(barConsume2, 12));
  threads.emplace_back(thread(barConsume2, 13));
  threads.emplace_back(thread(barConsume2, 14));
  threads.emplace_back(thread(barConsume2, 15));

  for(auto &t : threads) {
    t.join();
  }
  cout << "========== Case " << CaseID << " Finished ==========" << endl;
}

int main() {
  case1BarSyncAll();
  case2BarSyncAll();
  case3BarSyncCnt();
  case4BarSyncCnt();
  case5BarCsm();
  case6BarSyncCsm();
}
