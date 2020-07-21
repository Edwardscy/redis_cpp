#include <stdio.h>
#include <iostream>  
#include <stdlib.h>
#include <string.h>
#include "hiredis.h" //����ǰ���include�ļ�·������
#define NO_QFORKIMPL 
#include "win32_fixes.h" //����ǰ���include�ļ�·������
#include <fstream>
#include <cassert>
using namespace std;

int main() {
	redisContext *c;
	redisReply *reply;
	const char *hostname = "127.0.0.1"; //���������ӣ�����ip��127.0.0.1
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

	//����redis��ͬ�����ݿ� db1��Ĭ��������db0 �л����ݿ�
	reply = (redisReply*)redisCommand(c, "select 1");
	printf("���ӵ�db1: %s\n", reply->str);
	freeReplyObject(reply);

	redisFree(c);

	system("pause");
	return 0;
}
