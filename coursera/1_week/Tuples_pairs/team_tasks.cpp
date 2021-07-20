#include <iostream>
#include <vector>

#include <tuple>
#include <map>

using namespace std;

#ifdef MY

// Перечислимый тип для статуса задачи
enum class TaskStatus 
{
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>, позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

#endif

class TeamTasks 
{
  map<string, TasksInfo> person_to_tasks;

public:
  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask (const string &person) { person_to_tasks[person][TaskStatus::NEW]++; }
  
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo (const string &person) const
    { return person_to_tasks.at (person); }

  tuple<TasksInfo, TasksInfo> PerformPersonTasks 
    (const string& person, int task_count);
};

TaskStatus get_next_TaskStatus (TaskStatus st) 
{ return static_cast<TaskStatus> (static_cast<int> (st) + 1); }

TaskStatus get_prev_TaskStatus (TaskStatus st) 
{ return static_cast<TaskStatus> (static_cast<int> (st) - 1); }

void fix_TasksInfo (TasksInfo& tasks_info) 
{
  vector<TaskStatus> need_erase;
  for (const auto & [st, value] : tasks_info)
    if (value == 0) 
      need_erase.push_back (st);
  
  for (const TaskStatus st : need_erase) 
    tasks_info.erase(st);
}

// Обновить статусы по данному количеству задач конкретного разработчика
tuple<TasksInfo, TasksInfo> 
TeamTasks::PerformPersonTasks (const string &person, int task_count)
{
  TasksInfo& ALL_tasks = person_to_tasks[person];
  TasksInfo changed, unchanged;

  for (TaskStatus st = TaskStatus::NEW; st != TaskStatus::DONE; st = get_next_TaskStatus (st))
  {
    TaskStatus next_st = get_next_TaskStatus (st);
    changed[next_st] = min (task_count, ALL_tasks[st]);
    task_count -= changed[next_st];
  }

  for (TaskStatus st = TaskStatus::NEW; st != TaskStatus::DONE; st = get_next_TaskStatus (st))
  {
    TaskStatus next_st = get_next_TaskStatus (st);
    unchanged[st]  = ALL_tasks[st] - changed[next_st];
    ALL_tasks[st] +=   changed[st] - changed[next_st];
  }

  ALL_tasks[TaskStatus::DONE] += changed[TaskStatus::DONE];

  fix_TasksInfo (ALL_tasks);
  fix_TasksInfo (changed);
  fix_TasksInfo (unchanged);

  return {changed, unchanged};
}
 
void 
PrintTasksInfo (TasksInfo tasks_info) 
{
  cout << tasks_info[TaskStatus::NEW]         << " new tasks, "
       << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress, "
       << tasks_info[TaskStatus::TESTING]     << " tasks are being tested, "
       << tasks_info[TaskStatus::DONE]        << " tasks are done" << endl;
}

int main() 
{
  TeamTasks tasks;
  tasks.AddNewTask ("Ilia");
  for (int i = 0; i < 3; ++i)
    tasks.AddNewTask ("Ivan");
  
  cout << "Ilia's tasks: ";
  PrintTasksInfo (tasks.GetPersonTasksInfo ("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo (tasks.GetPersonTasksInfo ("Ivan"));
  
  TasksInfo updated_tasks, untouched_tasks;
  
  tie (updated_tasks, untouched_tasks) = tasks.PerformPersonTasks ("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo (updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo (untouched_tasks);
  
  tie (updated_tasks, untouched_tasks) = tasks.PerformPersonTasks ("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo (updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo (untouched_tasks);

  return 0;
}

