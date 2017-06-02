/*************************************************************************
    > File Name: main.cpp
    > Created Time: 2017年06月02日 星期五 17时11分01秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <unistd.h>
#include "threadpool.h"

using namespace std;

class WorkTask : public Runnable
{
public:
	WorkTask( const string& str ) : _str( str ) {}
	virtual void Run()
	{
		cout << _str <<endl;
	}

public:
	string _str;
};

int main()
{
	ThreadPool pool( 10 );
	for( int i = 0; i < 100; ++i )
	{
		string tmpstr = "hello thread";
		WorkTask task( tmpstr );
		pool.AddTask( &task );
	}
	while( !pool.TaskComplete() ) {}
	return 0;
}
