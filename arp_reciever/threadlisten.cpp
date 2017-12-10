#include "threadlisten.h"

ThreadListen::ThreadListen()
{
  stopped = false;
  re = std::make_shared<FilterDataReceiver>();
  re->find_all_devs();
  dev_num = 1;
}

void ThreadListen::run()
{
  qDebug() << "start listen" << dev_num;
  re->listen(dev_num);
}

void ThreadListen::stop()
{
  stopped = true;
}


