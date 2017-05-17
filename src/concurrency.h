#pragma once
#include <atomic>
#include <memory>
#include <vector>

namespace sb {
namespace cc {
typedef void (*TaskFunction)(void *arg);

struct Task {
  unsigned long id;
  TaskFunction tf;
  void *data;
  std::atomic<unsigned int> depcount;         // how many people waiting on me
  std::atomic<unsigned int> parentcount;      // How many people I'm waiting on
  std::vector<std::shared_ptr<Task>> deps;    // Who's waiting on me
  std::vector<std::shared_ptr<Task>> parents; // who am I waiting on
  ~Task();
};

std::shared_ptr<Task> makeTask(TaskFunction tf);
std::shared_ptr<Task> makeTask(TaskFunction tf, std::vector<std::shared_ptr<Task>> parents);
std::shared_ptr<Task> GetTask(const unsigned int queueID);
std::shared_ptr<Task> AddTask(const unsigned int queueID, std::shared_ptr<Task> tf);
void DoTasks();
void PurgeTasks();
} // namespace cc
} // namespace sb