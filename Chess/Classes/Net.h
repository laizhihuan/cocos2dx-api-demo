//
//  Net.h
//  Chess
//
//  Created by zhihuanglai on 15/7/13.
//
//

#ifndef __Chess__Net__
#define __Chess__Net__

#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket close
#include <fcntl.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "cocos2d.h"
USING_NS_CC;

class Net
{
protected:
    Net()
    {
        _server = INVALID_SOCKET;
        _client = INVALID_SOCKET;
        _isServer = false;
        _isListen = false;
        _isConnect = false;
    }
    
    SOCKET _server;
    SOCKET _client;
    
    bool _isServer;
    bool _isListen;
    bool _isConnect;
    static Net* _theOne;
};

#endif /* defined(__Chess__Net__) */
