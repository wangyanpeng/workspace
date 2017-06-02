/*************************************************************************
    > File Name: threadpool.h
    > Created Time: 2017年06月02日 星期五 16时34分42秒
 ************************************************************************/

#include <vector>
#include <pthread.h>

class Runnable
{
public:
	virtual void Run() = 0;
};

class ThreadPool
{
public:
	typedef std::vector< Runnable* > TASKVEC;
	ThreadPool( int thread_count ) : _thread_count( thread_count ) { Create(); }
	void AddTask( Runnable* task );
	void Create();
	static void* ThreadFunc( void* param );
	Runnable* FetchTask();
	bool TaskComplete() { return _taskvec.size() == 0; }
public:
	static pthread_mutex_t _mutex;
	static pthread_cond_t _cond;
	TASKVEC _taskvec;
	int _thread_count;
};
