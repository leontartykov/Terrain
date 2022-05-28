#ifndef _SCENE_COMMAND_BASE_H_
#define _SCENE_COMMAND_BASE_H_

class BaseSceneCommand{
    virtual ~BaseSceneCommand() = 0;
    virtual void execute() = 0;
};

#endif
