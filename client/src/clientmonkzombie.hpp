#pragma once
#include "uidf.hpp"
#include "pathf.hpp"
#include "clientmonster.hpp"

class ClientMonkZombie: public ClientMonster
{
    public:
        ClientMonkZombie(uint64_t uid, ProcessRun *proc, const ActionNode &action)
            : ClientMonster(uid, proc)
        {
            fflassert(isMonster(u8"僧侣僵尸"));
            switch(action.type){
                case ACTION_SPAWN:
                    {
                        m_currMotion.reset(new MotionNode
                        {
                            .type = MOTION_MON_SPAWN,
                            .direction = pathf::dirValid(action.direction) ? action.direction : to_d(DIR_UP),
                            .x = action.x,
                            .y = action.y,
                        });

                        m_currMotion->addTrigger(true, [proc](MotionNode *motionPtr)
                        {
                            if(motionPtr->frame < 9){
                                return false;
                            }

                            proc->addFixedLocMagic(std::unique_ptr<FixedLocMagic>(new MonkZombieSpawnEffect_RUN
                            {
                                motionPtr->x,
                                motionPtr->y,
                                motionPtr->direction - DIR_BEGIN,
                            }));
                            return true;
                        });
                        break;
                    }
                case ACTION_DIE:
                    {
                        m_currMotion.reset(new MotionNode
                        {
                            .type = MOTION_MON_DIE,
                            .direction = pathf::dirValid(action.direction) ? action.direction : to_d(DIR_UP),
                            .x = action.x,
                            .y = action.y,
                        });
                        break;
                    }
                default:
                    {
                        m_currMotion.reset(new MotionNode
                        {
                            .type = MOTION_MON_STAND,
                            .direction = pathf::dirValid(action.direction) ? action.direction : to_d(DIR_UP),
                            .x = action.x,
                            .y = action.y,
                        });
                        break;
                    }
            }
        }
};
