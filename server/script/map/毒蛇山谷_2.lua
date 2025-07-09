addGuard('禁军卫士', 311, 216, DIR_DOWNLEFT)
addGuard('禁军卫士', 310, 228, DIR_DOWNLEFT)
addGuard('禁军卫士', 364, 202, DIR_DOWNLEFT)
addGuard('禁军卫士', 366, 204, DIR_DOWNLEFT)

local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 毒蛇山谷_2
{
    {
        name = '七点白蛇',
        loc = {
            {x = 200, y = 200, w = 190, h = 190, count = 5, time = 7200},
        }
    },
    {
        name = '千年毒蛇',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 30, time = 1200},
        }
    },
    {
        name = '半兽人',
        loc = {
            {x = 150, y = 250, w = 50, h = 50, count = 15, time = 300},
            {x = 150, y = 350, w = 50, h = 50, count = 15, time = 300},
            {x = 250, y = 50, w = 50, h = 50, count = 15, time = 300},
            {x = 250, y = 150, w = 50, h = 50, count = 20, time = 300},
            {x = 250, y = 250, w = 50, h = 50, count = 20, time = 300},
            {x = 250, y = 250, w = 50, h = 50, count = 20, time = 300},
            {x = 350, y = 150, w = 50, h = 50, count = 20, time = 300},
        }
    },
    {
        name = '半兽人0',
        loc = {
            {x = 150, y = 250, w = 50, h = 50, count = 1, time = 3600},
            {x = 350, y = 150, w = 50, h = 50, count = 1, time = 3600},
        }
    },
    {
        name = '多钩猫',
        loc = {
            {x = 250, y = 150, w = 50, h = 50, count = 15, time = 300},
            {x = 250, y = 250, w = 50, h = 50, count = 15, time = 300},
            {x = 250, y = 250, w = 50, h = 50, count = 15, time = 300},
            {x = 350, y = 150, w = 50, h = 50, count = 15, time = 300},
        }
    },
    {
        name = '多钩猫0',
        loc = {
            {x = 250, y = 150, w = 50, h = 50, count = 1, time = 3600},
            {x = 250, y = 250, w = 50, h = 50, count = 1, time = 3600},
        }
    },
    {
        name = '夜行鬼09',
        loc = {
            {x = 200, y = 200, w = 200, h = 200, count = 100, time = 1200},
        }
    },
    {
        name = '栗子树',
        loc = {
            {x = 50, y = 150, w = 50, h = 50, count = 3, time = 1200},
            {x = 50, y = 250, w = 50, h = 50, count = 3, time = 1200},
            {x = 150, y = 150, w = 50, h = 50, count = 3, time = 1200},
            {x = 150, y = 250, w = 50, h = 50, count = 3, time = 1200},
            {x = 150, y = 350, w = 50, h = 50, count = 3, time = 1200},
            {x = 250, y = 50, w = 50, h = 50, count = 3, time = 1200},
            {x = 250, y = 150, w = 50, h = 50, count = 3, time = 1200},
            {x = 250, y = 250, w = 50, h = 50, count = 3, time = 1200},
            {x = 350, y = 50, w = 50, h = 50, count = 3, time = 1200},
            {x = 350, y = 150, w = 50, h = 50, count = 3, time = 1200},
            {x = 50, y = 150, w = 50, h = 50, count = 13, time = 300},
            {x = 50, y = 250, w = 50, h = 50, count = 13, time = 300},
            {x = 150, y = 150, w = 50, h = 50, count = 13, time = 300},
            {x = 150, y = 250, w = 50, h = 50, count = 13, time = 300},
            {x = 150, y = 350, w = 50, h = 50, count = 13, time = 300},
            {x = 250, y = 50, w = 50, h = 50, count = 13, time = 300},
            {x = 250, y = 150, w = 50, h = 50, count = 13, time = 300},
            {x = 250, y = 250, w = 50, h = 50, count = 13, time = 300},
            {x = 250, y = 250, w = 50, h = 50, count = 13, time = 300},
            {x = 350, y = 150, w = 50, h = 50, count = 13, time = 300},
        }
    },
    {
        name = '森林雪人',
        loc = {
            {x = 150, y = 250, w = 50, h = 50, count = 20, time = 300},
            {x = 150, y = 350, w = 50, h = 50, count = 20, time = 300},
            {x = 250, y = 50, w = 50, h = 50, count = 20, time = 300},
            {x = 250, y = 150, w = 50, h = 50, count = 20, time = 300},
            {x = 250, y = 250, w = 50, h = 50, count = 20, time = 300},
            {x = 250, y = 250, w = 50, h = 50, count = 20, time = 300},
            {x = 350, y = 150, w = 50, h = 50, count = 20, time = 300},
        }
    },
    {
        name = '森林雪人0',
        loc = {
            {x = 250, y = 250, w = 50, h = 50, count = 1, time = 3600},
        }
    },
    {
        name = '狼',
        loc = {
            {x = 150, y = 250, w = 50, h = 50, count = 15, time = 300},
            {x = 150, y = 350, w = 50, h = 50, count = 15, time = 300},
            {x = 250, y = 50, w = 50, h = 50, count = 15, time = 300},
            {x = 250, y = 150, w = 50, h = 50, count = 15, time = 300},
            {x = 250, y = 250, w = 50, h = 50, count = 15, time = 300},
            {x = 250, y = 250, w = 50, h = 50, count = 15, time = 300},
            {x = 350, y = 150, w = 50, h = 50, count = 15, time = 300},
        }
    },
    {
        name = '红蛇',
        loc = {
            {x = 50, y = 150, w = 50, h = 50, count = 45, time = 300},
            {x = 50, y = 250, w = 50, h = 50, count = 45, time = 300},
            {x = 150, y = 150, w = 50, h = 50, count = 45, time = 300},
            {x = 150, y = 250, w = 50, h = 50, count = 20, time = 300},
            {x = 150, y = 350, w = 50, h = 50, count = 20, time = 300},
            {x = 250, y = 50, w = 50, h = 50, count = 20, time = 300},
        }
    },
    {
        name = '红蛇0',
        loc = {
            {x = 50, y = 250, w = 50, h = 50, count = 1, time = 3600},
            {x = 150, y = 150, w = 50, h = 50, count = 1, time = 3600},
            {x = 150, y = 350, w = 50, h = 50, count = 1, time = 3600},
        }
    },
    {
        name = '虎蛇',
        loc = {
            {x = 50, y = 150, w = 50, h = 50, count = 40, time = 300},
            {x = 50, y = 250, w = 50, h = 50, count = 40, time = 300},
            {x = 150, y = 150, w = 50, h = 50, count = 40, time = 300},
            {x = 150, y = 250, w = 50, h = 50, count = 20, time = 300},
            {x = 150, y = 350, w = 50, h = 50, count = 20, time = 300},
            {x = 250, y = 50, w = 50, h = 50, count = 20, time = 300},
        }
    },
    {
        name = '虎蛇0',
        loc = {
            {x = 50, y = 150, w = 50, h = 50, count = 1, time = 3600},
            {x = 50, y = 250, w = 50, h = 50, count = 1, time = 3600},
            {x = 150, y = 350, w = 50, h = 50, count = 1, time = 3600},
            {x = 250, y = 50, w = 50, h = 50, count = 1, time = 3600},
        }
    },
    {
        name = '钉耙猫',
        loc = {
            {x = 250, y = 150, w = 50, h = 50, count = 15, time = 300},
            {x = 250, y = 250, w = 50, h = 50, count = 15, time = 300},
            {x = 250, y = 250, w = 50, h = 50, count = 15, time = 300},
            {x = 350, y = 150, w = 50, h = 50, count = 15, time = 300},
        }
    },
    {
        name = '钉耙猫0',
        loc = {
            {x = 250, y = 150, w = 50, h = 50, count = 1, time = 3600},
            {x = 250, y = 250, w = 50, h = 50, count = 1, time = 3600},
        }
    },
    {
        name = '食人花',
        loc = {
            {x = 50, y = 150, w = 50, h = 50, count = 20, time = 300},
            {x = 50, y = 250, w = 50, h = 50, count = 20, time = 300},
            {x = 150, y = 150, w = 50, h = 50, count = 20, time = 300},
            {x = 150, y = 250, w = 50, h = 50, count = 15, time = 300},
            {x = 150, y = 350, w = 50, h = 50, count = 15, time = 300},
            {x = 250, y = 50, w = 50, h = 50, count = 15, time = 300},
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
