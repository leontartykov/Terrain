#ifndef _TERRAIN_FACADE_H_
#define _TERRAIN_FACADE_H_

class TerrainFacade
{
    public:
        TerrainFacade() = default;
        ~TerrainFacade() = default;
        void execute(std::shared_ptr<BaseAppCommand> cmd);
};

#endif
