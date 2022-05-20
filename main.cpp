#include "config.h"

int main(int argc, char *argv[])
{
    //需要修改的数据库信息,登录名,密码,库名
    string user = "root";
    string passwd = "201786023";
    string databasename = "yourdb";

    //命令行解析
    Config config;
    config.parse_arg(argc, argv);

    WebServer server;//构造函数中进行了root路径的获取，构建http_conn连接数组和user_time客户端的定时器数组

    //初始化
    server.init(config.PORT, user, passwd, databasename, config.LOGWrite, 
                config.OPT_LINGER, config.TRIGMode,  config.sql_num,  config.thread_num, 
                config.close_log, config.actor_model);
    

    //日志
    server.log_write();//调用get_instance()->init();创建实例，init()创建处理block_queue的pthread

    //数据库
    server.sql_pool();//创建sql连接池，获取一个sql连接，初始化数据库读取表：将  用户名，密码保存在全局的map<> user中

    //线程池
    server.thread_pool();//构建线程池

    //触发模式
    server.trig_mode();//设置监听和连接的触发模式

    //监听
    server.eventListen();//创建listen_socket和定时器事件，对信号量绑定处理函数

    //运行
    server.eventLoop();//epoll循环阻塞等待

    return 0;
}