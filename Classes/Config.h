//
//  Config.h
//  KinectGame
//
//  Created by ArcherPeng on 15/3/12.
//
//

#ifndef __KinectGame__Config__
#define __KinectGame__Config__

#include <stdio.h>
#include "HandData.h"
class Config
{
private:
    static Config * c;
public:
    static Config * getInstance()
    {
        if(!c)
        {
            c = new Config();
        }
        return c;
    }
    HandData handData;
    int upY = 1;
    int downY = 1;
    int LeftX = 1;
    int RightX = 1;
};

#endif /* defined(__KinectGame__Config__) */
