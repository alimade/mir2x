local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 祖玛神殿6层_D5074
{
    {
        name = '守卫神将',
        loc = {
            {x = 73, y = 21, w = 20, h = 20, count = 10, time = 300},
        }
    },
    {
        name = '楔蛾',
        loc = {
            {x = 50, y = 50, w = 50, h = 50, count = 25, time = 600},
        }
    },
    {
        name = '祖玛卫士',
        loc = {
            {x = 50, y = 50, w = 50, h = 50, count = 30, time = 600},
        }
    },
    {
        name = '祖玛卫士0',
        loc = {
            {x = 50, y = 50, w = 50, h = 50, count = 1, time = 3600},
        }
    },
    {
        name = '祖玛卫士8',
        loc = {
            {x = 50, y = 50, w = 50, h = 50, count = 1, time = 3600},
        }
    },
    {
        name = '祖玛弓箭手',
        loc = {
            {x = 50, y = 50, w = 50, h = 50, count = 25, time = 600},
        }
    },
    {
        name = '祖玛弓箭手0',
        loc = {
            {x = 50, y = 50, w = 50, h = 50, count = 2, time = 3600},
        }
    },
    {
        name = '祖玛弓箭手8',
        loc = {
            {x = 50, y = 50, w = 50, h = 50, count = 2, time = 3600},
        }
    },
    {
        name = '祖玛雕像',
        loc = {
            {x = 50, y = 50, w = 50, h = 50, count = 25, time = 600},
        }
    },
    {
        name = '祖玛雕像0',
        loc = {
            {x = 50, y = 50, w = 50, h = 50, count = 1, time = 3600},
        }
    },
    {
        name = '祖玛雕像8',
        loc = {
            {x = 50, y = 50, w = 50, h = 50, count = 1, time = 3600},
        }
    },
    {
        name = '角蝇',
        loc = {
            {x = 50, y = 50, w = 50, h = 50, count = 20, time = 600},
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
