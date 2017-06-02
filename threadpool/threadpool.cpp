/*************************************************************************
    > File Name: threadpool.cpp
    > Created Time: 2017年06月02日 星期五 16时57分23秒
 ************************************************************************/

#include <iostream>
#include <string>
#include "threadpool.h"
using namespace std;

pthread_mutex_t ThreadPool::_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ThreadPool::_cond = PTHREAD_COND_INITIALIZER;

void ThreadPool::AddTask( Runnable* task )
{
	_taskvec.push_back( task );
	pthread_cond_signal( &_cond );
}

void ThreadPool::Create()
{
	for( int i = 0; i < _thread_count; ++i )
	{
		pthread_t tid;
		pthread_create( &tid, NULL, ThreadFunc, this );
		pthread_detach( tid );
	}
}

void* ThreadPool::ThreadFunc( void* param )
{
	pthread_t tid = pthread_self();
	pthread_mutex_lock( &_mutex );
	ThreadPool* tmp = ( ThreadPool* )param;
	if( !tmp ) return NULL;
	Runnable* task = tmp->FetchTask();
	if( task )
	{
		cout << "thread "<< tid << " running ..." << endl;
		task->Run();
	}
	else
	{
		pthread_cond_wait( &_cond, &_mutex );
	}
	pthread_mutex_unlock( &_mutex );
	return NULL;
}

Runnable* ThreadPool::FetchTask()
{
	if( _taskvec.size() > 0 )
	{
		TASKVEC::iterator it = _taskvec.begin();
		Runnable* task = *it;
		_taskvec.erase( it );
		return task;
	}
	else
	{
		return NULL;
	}
}
