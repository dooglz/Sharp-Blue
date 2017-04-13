//
// Created by Sam Serrels on 01/04/2017.
//
#include "concurrency.h"
#include <atomic>
#include <mutex>
#include <queue>
#include <iostream>
using namespace std;
namespace sb {
namespace cc {
queue<shared_ptr<Task>> mainTasks, tasks;
mutex tmutx, mtmutx;
atomic<unsigned long> idpool;

  shared_ptr<Task> AddTask(const unsigned int queueID, shared_ptr<Task> tf) {
  auto &mu = (queueID ? tmutx : mtmutx);
  auto &qu = (queueID ? tasks : mainTasks);
  lock_guard<mutex> lock(mu);
  qu.push(tf);
    return tf;
}

shared_ptr<Task> GetTask(const unsigned int queueID) {
  auto &mu = (queueID ? tmutx : mtmutx);
  auto &qu = (queueID ? tasks : mainTasks);
  lock_guard<mutex> lock(mu);
  auto ss = qu.size();
  if (ss < 1) {
    return NULL;
  }
  while(qu.front()->parentcount > 0){
    //haha there goes our perf.
    auto a = move(qu.front());
    qu.pop();
    qu.push(a);
    ss--;

    if(ss <=1 ){return NULL;}
  }

  auto a = move(qu.front());
  qu.pop();
  return a;
}

std::shared_ptr<Task> makeTask(TaskFunction tf) {
  auto t = std::shared_ptr<Task>(new Task());
  t->id = idpool++;
  t->tf = tf;
  t->data = nullptr;
  t->depcount.store(0);
  t->parentcount.store(0);
  return t;
}
std::shared_ptr<Task> makeTask(TaskFunction tf, vector<shared_ptr<Task>> parents) {
  auto t = std::shared_ptr<Task>(new Task());
  t->id = idpool++;
  //if(idpool %100 == 0){ std::cout << mainTasks.size() << endl;}
  t->tf = tf;
  t->data = nullptr;
  t->depcount.store(0);
  t->parentcount.store(parents.size());
  for (size_t i = 0; i < parents.size(); ++i) {
    parents[i]->depcount++;
    parents[i]->deps.push_back(t);
  }
  return t;
}

  Task::~Task() {
    //std::cout << "Goodbye from task: "<< id<<endl;
    if (depcount > 0){
      //Notify deps that we're done
      for (size_t i = 0; i < deps.size(); ++i) {
        deps[i]->parentcount--;
      }
    }
  }
}
}