addGuard('大刀卫士', 232, 180, DIR_UPLEFT)
addGuard('大刀卫士', 228, 184, DIR_UPLEFT)
addGuard('大刀卫士', 244, 168, DIR_UPLEFT)
addGuard('大刀卫士', 247, 165, DIR_UPLEFT)
addGuard('大刀卫士', 274, 167, DIR_UPRIGHT)
addGuard('大刀卫士', 277, 170, DIR_UPRIGHT)
addGuard('大刀卫士', 283, 176, DIR_UPRIGHT)
addGuard('大刀卫士', 287, 180, DIR_UPRIGHT)
addGuard('大刀卫士', 289, 205, DIR_DOWNRIGHT)
addGuard('大刀卫士', 286, 208, DIR_DOWNRIGHT)
addGuard('大刀卫士', 277, 233, DIR_DOWNRIGHT)
addGuard('大刀卫士', 274, 236, DIR_DOWNRIGHT)
addGuard('大刀卫士', 229, 239, DIR_DOWNLEFT)
addGuard('大刀卫士', 227, 237, DIR_DOWNLEFT)

local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 银杏山谷_02
{
    {
        name = '半兽人',
        loc = {
            {x = 50, y = 450, w = 50, h = 50, count = 20, time = 600},
            {x = 250, y = 550, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 550, w = 50, h = 50, count = 25, time = 600},
            {x = 450, y = 250, w = 50, h = 50, count = 25, time = 600},
            {x = 450, y = 350, w = 50, h = 50, count = 25, time = 600},
        }
    },
    {
        name = '半兽人0',
        loc = {
            {x = 250, y = 550, w = 50, h = 50, count = 1, time = 3600},
            {x = 450, y = 350, w = 50, h = 50, count = 1, time = 3600},
        }
    },
    {
        name = '多钩猫',
        loc = {
            {x = 150, y = 150, w = 50, h = 50, count = 20, time = 600},
            {x = 150, y = 250, w = 50, h = 50, count = 20, time = 600},
            {x = 150, y = 350, w = 50, h = 50, count = 20, time = 600},
            {x = 150, y = 450, w = 50, h = 50, count = 20, time = 600},
            {x = 250, y = 350, w = 50, h = 50, count = 20, time = 600},
            {x = 250, y = 450, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 50, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 150, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 250, w = 50, h = 50, count = 25, time = 600},
            {x = 350, y = 350, w = 50, h = 50, count = 25, time = 600},
            {x = 350, y = 450, w = 50, h = 50, count = 25, time = 600},
            {x = 450, y = 150, w = 50, h = 50, count = 25, time = 600},
        }
    },
    {
        name = '多钩猫0',
        loc = {
            {x = 150, y = 150, w = 50, h = 50, count = 1, time = 3600},
            {x = 150, y = 450, w = 50, h = 50, count = 1, time = 3600},
            {x = 250, y = 450, w = 50, h = 50, count = 1, time = 3600},
            {x = 350, y = 150, w = 50, h = 50, count = 1, time = 3600},
            {x = 350, y = 450, w = 50, h = 50, count = 1, time = 3600},
        }
    },
    {
        name = '夜行鬼09',
        loc = {
            {x = 300, y = 300, w = 300, h = 300, count = 150, time = 1200},
        }
    },
    {
        name = '栗子树',
        loc = {
            {x = 50, y = 150, w = 50, h = 50, count = 3, time = 1200},
            {x = 150, y = 150, w = 50, h = 50, count = 3, time = 1200},
            {x = 150, y = 250, w = 50, h = 50, count = 3, time = 1200},
            {x = 150, y = 350, w = 50, h = 50, count = 3, time = 1200},
            {x = 250, y = 50, w = 50, h = 50, count = 3, time = 1200},
            {x = 250, y = 150, w = 50, h = 50, count = 3, time = 1200},
            {x = 250, y = 250, w = 50, h = 50, count = 3, time = 1200},
            {x = 250, y = 350, w = 50, h = 50, count = 3, time = 1200},
            {x = 250, y = 450, w = 50, h = 50, count = 3, time = 1200},
            {x = 250, y = 550, w = 50, h = 50, count = 3, time = 1200},
            {x = 350, y = 50, w = 50, h = 50, count = 3, time = 1200},
            {x = 350, y = 150, w = 50, h = 50, count = 3, time = 1200},
            {x = 350, y = 450, w = 50, h = 50, count = 3, time = 1200},
            {x = 350, y = 550, w = 50, h = 50, count = 3, time = 1200},
            {x = 450, y = 50, w = 50, h = 50, count = 3, time = 1200},
            {x = 450, y = 150, w = 50, h = 50, count = 3, time = 1200},
            {x = 450, y = 250, w = 50, h = 50, count = 3, time = 1200},
            {x = 50, y = 450, w = 50, h = 50, count = 13, time = 300},
            {x = 150, y = 150, w = 50, h = 50, count = 13, time = 300},
            {x = 150, y = 250, w = 50, h = 50, count = 13, time = 300},
            {x = 150, y = 350, w = 50, h = 50, count = 13, time = 300},
            {x = 150, y = 450, w = 50, h = 50, count = 13, time = 300},
            {x = 250, y = 350, w = 50, h = 50, count = 13, time = 300},
            {x = 250, y = 450, w = 50, h = 50, count = 13, time = 300},
            {x = 250, y = 550, w = 50, h = 50, count = 13, time = 300},
            {x = 350, y = 50, w = 50, h = 50, count = 13, time = 300},
            {x = 350, y = 150, w = 50, h = 50, count = 13, time = 300},
            {x = 350, y = 250, w = 50, h = 50, count = 13, time = 300},
            {x = 350, y = 350, w = 50, h = 50, count = 13, time = 300},
            {x = 350, y = 450, w = 50, h = 50, count = 13, time = 300},
            {x = 350, y = 550, w = 50, h = 50, count = 13, time = 300},
            {x = 450, y = 150, w = 50, h = 50, count = 13, time = 300},
            {x = 450, y = 250, w = 50, h = 50, count = 13, time = 300},
            {x = 450, y = 350, w = 50, h = 50, count = 13, time = 300},
        }
    },
    {
        name = '森林雪人',
        loc = {
            {x = 50, y = 450, w = 50, h = 50, count = 20, time = 600},
            {x = 250, y = 550, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 550, w = 50, h = 50, count = 25, time = 600},
            {x = 450, y = 250, w = 50, h = 50, count = 25, time = 600},
            {x = 450, y = 350, w = 50, h = 50, count = 25, time = 600},
        }
    },
    {
        name = '森林雪人0',
        loc = {
            {x = 50, y = 450, w = 50, h = 50, count = 1, time = 3600},
            {x = 250, y = 550, w = 50, h = 50, count = 1, time = 3600},
            {x = 350, y = 550, w = 50, h = 50, count = 1, time = 3600},
            {x = 450, y = 250, w = 50, h = 50, count = 1, time = 3600},
            {x = 450, y = 350, w = 50, h = 50, count = 1, time = 3600},
        }
    },
    {
        name = '毒蜘蛛',
        loc = {
            {x = 50, y = 450, w = 50, h = 50, count = 20, time = 600},
            {x = 250, y = 550, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 550, w = 50, h = 50, count = 25, time = 600},
            {x = 450, y = 250, w = 50, h = 50, count = 25, time = 600},
            {x = 450, y = 350, w = 50, h = 50, count = 25, time = 600},
        }
    },
    {
        name = '牛',
        loc = {
            {x = 250, y = 150, w = 50, h = 50, count = 20, time = 600},
            {x = 250, y = 250, w = 50, h = 50, count = 20, time = 600},
        }
    },
    {
        name = '狼',
        loc = {
            {x = 50, y = 450, w = 50, h = 50, count = 20, time = 600},
            {x = 150, y = 450, w = 50, h = 50, count = 20, time = 600},
            {x = 250, y = 450, w = 50, h = 50, count = 20, time = 600},
            {x = 250, y = 550, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 50, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 450, w = 50, h = 50, count = 25, time = 600},
            {x = 350, y = 550, w = 50, h = 50, count = 25, time = 600},
            {x = 450, y = 150, w = 50, h = 50, count = 25, time = 600},
            {x = 450, y = 250, w = 50, h = 50, count = 25, time = 600},
            {x = 450, y = 350, w = 50, h = 50, count = 25, time = 600},
        }
    },
    {
        name = '猪',
        loc = {
            {x = 250, y = 150, w = 50, h = 50, count = 20, time = 600},
            {x = 250, y = 250, w = 50, h = 50, count = 20, time = 600},
        }
    },
    {
        name = '稻草人',
        loc = {
            {x = 150, y = 150, w = 50, h = 50, count = 20, time = 600},
            {x = 150, y = 250, w = 50, h = 50, count = 20, time = 600},
            {x = 150, y = 350, w = 50, h = 50, count = 20, time = 600},
            {x = 150, y = 450, w = 50, h = 50, count = 20, time = 600},
            {x = 250, y = 350, w = 50, h = 50, count = 20, time = 600},
            {x = 250, y = 450, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 50, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 150, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 250, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 350, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 450, w = 50, h = 50, count = 25, time = 600},
            {x = 450, y = 150, w = 50, h = 50, count = 25, time = 600},
        }
    },
    {
        name = '稻草人0',
        loc = {
            {x = 150, y = 150, w = 50, h = 50, count = 1, time = 3600},
            {x = 350, y = 150, w = 50, h = 50, count = 1, time = 3600},
            {x = 350, y = 350, w = 50, h = 50, count = 1, time = 3600},
            {x = 350, y = 450, w = 50, h = 50, count = 1, time = 3600},
            {x = 450, y = 150, w = 50, h = 50, count = 1, time = 3600},
        }
    },
    {
        name = '蛤蟆',
        loc = {
            {x = 150, y = 150, w = 50, h = 50, count = 20, time = 600},
            {x = 150, y = 250, w = 50, h = 50, count = 20, time = 600},
            {x = 150, y = 350, w = 50, h = 50, count = 20, time = 600},
            {x = 250, y = 350, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 150, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 250, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 350, w = 50, h = 50, count = 25, time = 600},
        }
    },
    {
        name = '蛤蟆0',
        loc = {
            {x = 150, y = 250, w = 50, h = 50, count = 1, time = 3600},
            {x = 150, y = 350, w = 50, h = 50, count = 1, time = 3600},
            {x = 250, y = 350, w = 50, h = 50, count = 1, time = 3600},
            {x = 250, y = 450, w = 50, h = 50, count = 1, time = 3600},
            {x = 350, y = 250, w = 50, h = 50, count = 1, time = 3600},
            {x = 350, y = 350, w = 50, h = 50, count = 1, time = 3600},
        }
    },
    {
        name = '钉耙猫',
        loc = {
            {x = 150, y = 150, w = 50, h = 50, count = 20, time = 600},
            {x = 150, y = 250, w = 50, h = 50, count = 20, time = 600},
            {x = 150, y = 350, w = 50, h = 50, count = 20, time = 600},
            {x = 150, y = 450, w = 50, h = 50, count = 20, time = 600},
            {x = 250, y = 350, w = 50, h = 50, count = 20, time = 600},
            {x = 250, y = 450, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 50, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 150, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 250, w = 50, h = 50, count = 25, time = 600},
            {x = 350, y = 350, w = 50, h = 50, count = 25, time = 600},
            {x = 350, y = 450, w = 50, h = 50, count = 25, time = 600},
            {x = 450, y = 150, w = 50, h = 50, count = 25, time = 600},
        }
    },
    {
        name = '钉耙猫0',
        loc = {
            {x = 150, y = 350, w = 50, h = 50, count = 1, time = 3600},
            {x = 350, y = 50, w = 50, h = 50, count = 1, time = 3600},
            {x = 450, y = 150, w = 50, h = 50, count = 1, time = 3600},
        }
    },
    {
        name = '鸡',
        loc = {
            {x = 250, y = 150, w = 50, h = 50, count = 20, time = 600},
            {x = 250, y = 250, w = 50, h = 50, count = 20, time = 600},
        }
    },
    {
        name = '鹿',
        loc = {
            {x = 150, y = 150, w = 50, h = 50, count = 20, time = 600},
            {x = 150, y = 250, w = 50, h = 50, count = 20, time = 600},
            {x = 150, y = 350, w = 50, h = 50, count = 20, time = 600},
            {x = 150, y = 450, w = 50, h = 50, count = 20, time = 600},
            {x = 250, y = 350, w = 50, h = 50, count = 20, time = 600},
            {x = 250, y = 450, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 50, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 150, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 250, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 350, w = 50, h = 50, count = 20, time = 600},
            {x = 350, y = 450, w = 50, h = 50, count = 20, time = 600},
            {x = 450, y = 150, w = 50, h = 50, count = 25, time = 600},
        }
    },
})

function main()
    while true do
        local rc, errMsg = coroutine.resume(addMonCo)
        if not rc then
            fatalPrintf('addMonCo failed: %s', argDefault(errMsg, 'unknown error'))
        end
        pause(1000 * 5)
    end
end
