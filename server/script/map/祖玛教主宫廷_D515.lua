local addmon = require('map.addmonster')
local addMonCo = addmon.monGener( -- 祖玛教主宫廷_D515
{
    {
        name = '守卫神将',
        loc = {
            {x = 20, y = 20, w = 20, h = 20, count = 10, time = 300},
        }
    },
    {
        name = '楔蛾',
        loc = {
            {x = 20, y = 20, w = 20, h = 20, count = 1, time = 3600},
        }
    },
    {
        name = '楔蛾93',
        loc = {
            {x = 20, y = 20, w = 20, h = 20, count = 1, time = 3600},
        }
    },
    {
        name = '祖玛卫士',
        loc = {
            {x = 20, y = 20, w = 20, h = 20, count = 1, time = 3600},
        }
    },
    {
        name = '祖玛卫士90',
        loc = {
            {x = 20, y = 20, w = 20, h = 20, count = 1, time = 3600},
        }
    },
    {
        name = '祖玛弓箭手',
        loc = {
            {x = 20, y = 20, w = 20, h = 20, count = 1, time = 3600},
        }
    },
    {
        name = '祖玛弓箭手92',
        loc = {
            {x = 20, y = 20, w = 20, h = 20, count = 1, time = 3600},
        }
    },
    {
        name = '祖玛教主',
        loc = {
            {x = 19, y = 24, w = 1, h = 1, count = 1, time = 18000},
        }
    },
    {
        name = '祖玛雕像',
        loc = {
            {x = 20, y = 20, w = 20, h = 20, count = 1, time = 3600},
        }
    },
    {
        name = '祖玛雕像91',
        loc = {
            {x = 20, y = 20, w = 20, h = 20, count = 1, time = 3600},
        }
    },
    {
        name = '角蝇',
        loc = {
            {x = 20, y = 20, w = 20, h = 20, count = 2, time = 3600},
        }
    },
    {
        name = '角蝇80',
        loc = {
            {x = 20, y = 20, w = 20, h = 20, count = 2, time = 3600},
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
