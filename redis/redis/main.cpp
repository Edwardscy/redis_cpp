#include <stdio.h>
#include <iostream>  
#include <stdlib.h>
#include <string.h>
#include "hiredis.h" //这个是按照include文件路径来的
#define NO_QFORKIMPL 
#include "win32_fixes.h" //这个是按照include文件路径来的
#include <fstream>
#include <cassert>
using namespace std;

int main() {
	redisContext *c;
	redisReply *reply;
	const char *hostname = "127.0.0.1"; //这里是连接，本地ip：127.0.0.1
	int port = 6379;

	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	c = redisConnectWithTimeout(hostname, port, timeout);

	///* PING server */
	reply = (redisReply*)redisCommand(c, "ping");
	printf("ping: %s\n", reply->str);
	freeReplyObject(reply);

	reply = (redisReply*)redisCommand(c, "set %s %s", "foo", "hello world");
	printf("set: %s\n", reply->str);
	freeReplyObject(reply);

	reply = (redisReply*)redisCommand(c, "set %s %s", "id", "666");
	printf("set: %s\n", reply->str);
	freeReplyObject(reply);

	reply = (redisReply*)redisCommand(c, "GET foo");
	char *a;
	a = reply->str;
	printf("GET foo: %s\n", a);
	freeReplyObject(reply);

	//连接redis不同的数据库 db1，默认是连接db0 切换数据库
	reply = (redisReply*)redisCommand(c, "select 1");
	printf("连接到db1: %s\n", reply->str);
	freeReplyObject(reply);

	redisFree(c);

	system("pause");
	return 0;
}
